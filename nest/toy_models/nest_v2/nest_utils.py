import itertools
import os
import random
import time
import numpy as np
import matplotlib.pyplot as plt
import nest
try:
    from pynestml.frontend.pynestml_frontend import generate_nest_target
except:
    pass

import nest_network as main
from nest_network import InputGenerator

SYNAPSE_MODEL_NAME = None

def generate_poisson_spiketrain(t_duration, rate) -> list:
    """Generates a list of poisson generated spike times for a given

    :rtype: list

    - duration **t_duration** (in ms) and
    - firing rate **rate** (in Hz)
    """
    n = t_duration * rate * 1e-3  # expected number of spikes in [0, t_duration)
    scale = 1 / (rate * 1e-3)  # expected time between spikes
    isi = np.random.exponential(scale, int(np.ceil(n)))  # list of [ceil(n)] input spike intervals
    spikes = np.add.accumulate(isi)
    # Hypothetical position of t_duration in spikes list
    i = np.searchsorted(spikes, t_duration)

    # Add or remove spikes
    extra_spikes = []
    if i == len(spikes):
        t_last = spikes[-1]
        while True:
            t_last += np.random.exponential(scale, 1)[0]
            if t_last >= t_duration:
                break
            else:
                extra_spikes.append(t_last)
        spikes = np.concatenate((spikes, extra_spikes))
    else:
        # Cutoff spike times outside of spike duration
        spikes = np.resize(spikes, (i,))  # spikes[:i]
    a = spikes
    b = list(spikes)
    return spikes.tolist()


def randomize_outgoing_connections(nc):
    """Randomizes the weights of outgoing connections of a NodeCollection **nc**"""
    conns = nest.GetConnections(nc)
    random_weight_list = []
    for i in range(len(conns)):
        random_weight_list.append(-np.log(np.random.rand()))
    conns.set(weight=random_weight_list)


def disable_stdp(nc):
    """Disables STDP for a given NodeCollection"""
    nc.set({'use_stdp': int(False)})


def enable_stdp(nc):
    """Disables STDP for a given NodeCollection"""
    nc.set({'use_stdp': int(True)})


def disable_stp(nc):
    synapses = nest.GetConnections(nc, synapse_model="stdp_stp__with_iaf_psc_exp_wta_rec")
    synapses.set({'use_stp': int(False)})


def enable_stp(nc):
    synapses = nest.GetConnections(nc, synapse_model="stdp_stp__with_iaf_psc_exp_wta_rec")
    synapses.set({'use_stp': int(True)})


def update_presyn_ids(network):
    """
    For each neuron, update the ids the presynaptic sources. This is needed for accurate weight updates as in Klampfl.
    """
    node_ids = network.get_node_collections()

    for gid in node_ids:
        sources = nest.GetConnections(target=gid, synapse_model=SYNAPSE_MODEL_NAME).source
        gid.set({'presyn_ids': np.array(sources).astype(float)})


class Recorder:
    """
    Recorder class
    """
    def __init__(self, network, id_list: list = None, **kwargs):
        # Network to record from
        self.network = network
        # global IDs of neurons to record
        self.id_list = id_list

        self.create_plot = kwargs.get('create_plot', True)  # Note that the following plot/figure related parameters are redundant if False
        self.save_figures = kwargs.get('save_figures', False)
        self.show_figures = kwargs.get('show_figures', True)
        self.plot_history = kwargs.get('plot_history', False)

        # Recording time interval
        self.dt_rec = kwargs.get('dt_rec', None)

    def set(self, **kwargs):
        for key, value in kwargs.items():
            pass
            self.key = value

    def get(self, arg):
        pass
        return self.arg


    def run_network(self, id_list: list = None, node_collection=None, readout_size: int = None,
                    inpgen=None, t_sim: float = 5000.0, title=None, train=True, dt_rec=None):
        """
        Simulates given **NodeCollection** for **t_sim** and plots the recorded spikes, membrane potential and presented
        patterns. Requires an **InputGenerator** object for pattern input generation.

        Readout modes (listed after priority):
            1. "Watch List": a list of Node IDs is specified and measured. Useful when observing readout over several measurements
            2. "Node Collection": A specified NodeCollection is measured
            3. "Random k": k nodes are randomly sampled from the network and measured
            4. "All": Measure all nodes in network
        """
        # Determine NodeCollection to record from (and also id_list for return value)
        if id_list is not None:  # Readout Mode 1
            node_collection = nest.NodeCollection(id_list)
        elif node_collection is not None:  # Readout Mode 2
            id_list = list(node_collection.get('global_id'))
        elif readout_size is not None:  # Readout Mode 3
            global_ids = self.network.get_node_collections().get('global_id')
            id_list = []
            while len(id_list) < readout_size:
                id_list.append(random.randrange(min(global_ids), max(global_ids)))
                id_list = list(set(id_list))  # remove duplicates
            id_list.sort()
            node_collection = nest.NodeCollection(id_list)
        else:  # Readout Mode 4
            node_collection = self.network.get_node_collections()
            id_list = list(self.network.get_node_collections().get('global_id'))

        # Create new multimeter and spikerecorder if none exist yet and connect them to the node_collection
        if self.network.multimeter is None:
            self.network.multimeter = nest.Create('multimeter')
            self.network.multimeter.set(record_from=['V_m'])
            nest.Connect(self.network.multimeter, node_collection)
        if self.network.spikerecorder is None:
            self.network.spikerecorder = nest.Create('spike_recorder')
            nest.Connect(node_collection, self.network.spikerecorder)
        if inpgen.noiserecorder is None and inpgen is not None:
            if inpgen.use_noise:
                inpgen.noiserecorder = nest.Create('spike_recorder')
                nest.Connect(inpgen.parrots, inpgen.noiserecorder)

        # Run simulation (with or without input)
        if inpgen is None:
            nest.Simulate(t_sim)
        else:
            if train:
                self.simulate(inpgen, t_sim, dt_rec)
            else:
                self.test(inpgen, t_sim, dt_rec)

        if self.create_plot:
            print("Plotting...")
            start_time = time.time()
            # Initialize plot
            fig, axes = plt.subplots(5, 1, sharex=not self.plot_history)  # only sync x axis if not the whole history is observed
            fig.set_figwidth(10)
            fig.set_figheight(12)

            # MULTIMETER
            dmm = self.network.multimeter.get()
            Vms = dmm["events"]["V_m"]
            ts = dmm["events"]["times"]

            # SPIKERECORDER
            dSD = self.network.spikerecorder.get("events")
            evs = dSD["senders"]
            ts_ = dSD["times"]

            # NOISERECORDER
            nr = inpgen.noiserecorder.get("events")
            evs__ = nr["senders"]
            ts__ = nr["times"]

            # get the indices after t_sim_start
            t_sim_start = nest.biological_time - t_sim
            multimeter_time_window = np.where(ts > t_sim_start)[0]
            spikerecorder_time_window = np.where(ts_ > t_sim_start)[0]
            noiserecorder_time_window = np.where(ts__ > t_sim_start)[0]

            n_senders = len(np.unique(dmm["events"]["senders"]))
            for idx, neuron in enumerate(np.unique(dmm["events"]["senders"])):  # iterate over all sender neurons
                print("%s/%s" % (idx, n_senders))  # , end="\r"
                src_gids = np.unique(dmm["events"]["senders"]).tolist()
                colors = ['b', 'g', 'r', 'c', 'm', 'y', 'k']

                start_time_1 = time.time()
                # MEMBRANE POTENTIAL
                indices = np.where(dmm["events"]["senders"] == neuron)[0]  # get the indices of events where 'neuron' was the sender
                if not self.plot_history:  # remove all indices from outside of multimeter_time_window
                    indices = [i for i in indices if i in multimeter_time_window]
                axes[0].plot(ts[indices], Vms[indices], label=f'neuron: {neuron}')  # plot the membrane potential of 'neuron'

                # SPIKES
                indices = np.where(dSD["senders"] == neuron)[0]
                if not self.plot_history:  # remove all indices from outside of spikerecorder_time_window
                    indices = [i for i in indices if i in spikerecorder_time_window]
                axes[1].plot(ts_[indices], evs[indices], ".")
                run_time = time.time() - start_time_1
                print("Membrane potential and Spikes complete in %s" % run_time)

                start_time_2 = time.time()
                # EPSPs
                for src_idx, src in enumerate(src_gids):
                    c = colors[src_idx%len(colors)]
                    filtered_epsps_dict = {'t': [], 'epsp': []}
                    for t, src_, tgt_, epsp in self.network.epsp_recorder:
                        if src_ == src and tgt_ == neuron: # and t >= t_sim_start
                            filtered_epsps_dict['t'].append(t)
                            filtered_epsps_dict['epsp'].append(epsp)
                    #if len(filtered_epsps):
                    axes[2].plot(filtered_epsps_dict['t'], filtered_epsps_dict['epsp'], color=c)  # label=f'{src} -> {neuron}'

                # WEIGHTS
                for src_idx, src in enumerate(src_gids):
                    c = colors[src_idx%len(colors)]
                    filtered_weights_dict = {'t': [], 'w': []}
                    for t, src_, tgt_, w in self.network.weight_recorder:
                        if src_ == src and tgt_ == neuron: # and t >= t_sim_start
                            filtered_weights_dict['t'].append(t)
                            filtered_weights_dict['w'].append(w)
                    #if len(filtered_weights):
                    axes[3].plot(filtered_weights_dict['t'], filtered_weights_dict['w'], color=c)  # label=f'{src} -> {neuron}'

                run_time = time.time() - start_time_2
                print("EPSPs and weights complete in %s" % run_time)

            # PRESENTED PATTERNS
            time_shift = nest.biological_time - t_sim
            if inpgen is not None:
                st = inpgen.spiketrain
                for i in range(len(st)):
                    # ax3.scatter(np.add(time_shift, st[i]), [i] * len(st[i]), color=(i / (len(st)), 0.0, i / (len(st))))
                    axes[4].plot(st[i], [i] * len(st[i]), ".", color='orange')
                if not self.plot_history:
                    axes[4].set_xlim(time_shift, nest.biological_time)

            axes[0].set_title("t_sim= %d, t_start= %d" % (t_sim, (nest.biological_time - t_sim)))
            axes[0].set_ylabel("Membrane potential (mV)")
            axes[1].set_title("Network spike events")
            axes[1].set_ylabel("Spike ID")
            axes[2].set_title("EPSP traces")
            # axes[2].legend()
            axes[3].set_title("Weights")
            axes[3].set_ylabel("w")
            # axes[3].legend()
            axes[4].set_ylabel("Input channels")
            axes[4].set_xlabel("time (ms)")
            if title is not None:
                fig.suptitle(title, fontsize=20)

            fig.tight_layout()

            run_time = time.time() - start_time
            print("Plotting complete in %s" % run_time)
            if self.save_figures:
                plt.savefig("simulation_%ds.png" % int(time.time()))
            if self.show_figures:
                plt.show()
        self.id_list = id_list
        return id_list

    def record_variables_step(self):
        """
        Extract and store input weights from the variables stored in the postsynaptic neurons
        """
        print("Recording step")
        if self.id_list is not None:  # limit recorded nodes to the ones from id_list
            target = nest.NodeCollection(self.id_list)
            inp_conns = nest.GetConnections(synapse_model="stdp_stp__with_iaf_psc_exp_wta_rec", target=target)
        else:
            inp_conns = nest.GetConnections(synapse_model="stdp_stp__with_iaf_psc_exp_wta_rec")
        postsyn_weights = nest.GetStatus(self.network.get_node_collections(), 'weights')
        postsyn_epsps = nest.GetStatus(self.network.get_node_collections(), 'epsp_trace')

        t_cur = nest.biological_time

        inp_conns_src = inp_conns.source
        inp_conns_tgt = inp_conns.target
        inp_conns_tgt_min = min(inp_conns_tgt)

        for idx, tgt in enumerate(inp_conns_tgt):
            src = inp_conns_src[idx]  # global ID of source node
            rel0_idx = tgt - inp_conns_tgt_min  # array index relative to 0
            self.network.weight_recorder.append((t_cur, src, tgt, postsyn_weights[rel0_idx][src]))
            self.network.epsp_recorder.append((t_cur, src, tgt, postsyn_epsps[rel0_idx][src]))

    def test(self, inpgen, t, dt_rec=None):
        # Disable STP and STDP
        disable_stp(self.network.neuron_collection)
        disable_stdp(self.network.neuron_collection)
        # Pre-generate input
        inpgen.generate_input(t, t_origin=nest.biological_time)
        update_presyn_ids(self.network)  # IMPORTANT - always set this after input generation

        if dt_rec is None:
            self.record_variables_step()
            nest.Simulate(t)
            self.record_variables_step()
        else:
            for t_ in range(int(t / dt_rec)):
                self.record_variables_step()
                nest.Simulate(dt_rec)
                print("step %s/%s complete." % (t_, t / dt_rec))
            self.record_variables_step()

    def simulate(self, inpgen, t, dt_rec=None):
        """Pre-generates input patterns for duration of simulation and then runs the simulation"""
        # Enable STP and STDP
        enable_stp(self.network.neuron_collection)
        enable_stdp(self.network.neuron_collection)
        # Pre-generate input
        inpgen.generate_input(t, t_origin=nest.biological_time)
        print("update_presyn_ids...")
        update_presyn_ids(self.network)  # IMPORTANT - always set this after input generation

        if dt_rec is None:
            self.record_variables_step()
            nest.Simulate(t)
            self.record_variables_step()
        else:
            for t_ in range(int(t / dt_rec)):
                self.record_variables_step()
                nest.Simulate(dt_rec)
                print("Step %s/%s complete. Time passed since simulation start: %s" % (
                t_, int(t / dt_rec), nest.biological_time))
            self.record_variables_step()


def generate_nest_code(neuron_model: str, synapse_model: str, target="nestml_target"):
    """Generates the code for 'iaf_psc_exp_wta' neuron model and 'stdp_stp' synapse model."""
    # module_name = "nestml_modidifed_module"
    # target += '___mod'
    module_name = "nestml_modified_master_module"
    target += '__modmaster'
    # if regen:
    #     codegen_opts = {"neuron_synapse_pairs": [{'neuron': neuron_model,
    #                                               'synapse': synapse_model,
    #                                               'post_ports': ['post_spikes'],
    #                                               }]}
    #     generate_nest_target(input_path=[os.environ["PWD"] + "/nestml_models/" + neuron_model + ".nestml",
    #                                      os.environ["PWD"] + "/nestml_models/" + synapse_model + ".nestml"],
    #                          target_path=os.environ["PWD"] + "/nestml_targets/" + target,
    #                          codegen_opts=codegen_opts,
    #                          module_name=module_name,
    #                          dev=True)
    nest.Install(module_name)
    mangled_neuron_name = neuron_model + "__with_" + synapse_model
    mangled_synapse_name = synapse_model + "__with_" + neuron_model
    print("Created ", mangled_neuron_name, " and ", mangled_synapse_name)
