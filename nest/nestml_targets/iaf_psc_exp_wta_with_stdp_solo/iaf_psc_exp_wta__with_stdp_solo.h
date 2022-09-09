/* generated by common/NeuronHeader.jinja2 */ /**
 *  iaf_psc_exp_wta__with_stdp_solo.h
 *
 *  This file is part of NEST.
 *
 *  Copyright (C) 2004 The NEST Initiative
 *
 *  NEST is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  NEST is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with NEST.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Generated from NESTML at time: 2022-09-06 14:45:58.363804
**/
#ifndef IAF_PSC_EXP_WTA__WITH_STDP_SOLO
#define IAF_PSC_EXP_WTA__WITH_STDP_SOLO

#include "config.h"

// Includes from nestkernel:
#include "archiving_node.h"
#include "connection.h"
#include "event.h"
#include "nest_types.h"
#include "ring_buffer.h"
#include "universal_data_logger.h"

// Includes from sli:
#include "dictdatum.h"

namespace nest
{
namespace iaf_psc_exp_wta__with_stdp_solo_names
{
    const Name _r( "r" );
    const Name _V_m( "V_m" );
    const Name _a_pre__for_stdp_solo( "a_pre__for_stdp_solo" );
    const Name _a_post__for_stdp_solo( "a_post__for_stdp_solo" );
    const Name _I_kernel_exc__X__exc_spikes( "I_kernel_exc__X__exc_spikes" );
    const Name _I_kernel_inh__X__inh_spikes( "I_kernel_inh__X__inh_spikes" );
    const Name _C_m( "C_m" );
    const Name _tau_m( "tau_m" );
    const Name _tau_syn_inh( "tau_syn_inh" );
    const Name _tau_syn_exc( "tau_syn_exc" );
    const Name _E_L( "E_L" );
    const Name _V_reset( "V_reset" );
    const Name _R_max( "R_max" );
    const Name _tau_tr_pre__for_stdp_solo( "tau_tr_pre__for_stdp_solo" );
    const Name _tau_tr_post__for_stdp_solo( "tau_tr_post__for_stdp_solo" );
    const Name _normalization_sum( "normalization_sum" );
}
}




#include "nest_time.h"

// entry in the spiking history
class histentry__iaf_psc_exp_wta__with_stdp_solo
{
public:
  histentry__iaf_psc_exp_wta__with_stdp_solo( double t,
double a_post__for_stdp_solo,
double a_pre__for_stdp_solo,
size_t access_counter )
  : t_( t )
  , a_post__for_stdp_solo_( a_post__for_stdp_solo )
  , a_pre__for_stdp_solo_( a_pre__for_stdp_solo )
  , access_counter_( access_counter )
  {
  }

  double t_;              //!< point in time when spike occurred (in ms)
   double a_post__for_stdp_solo_;
   double a_pre__for_stdp_solo_;
  size_t access_counter_; //!< access counter to enable removal of the entry, once all neurons read it
};




/* BeginDocumentation
  Name: iaf_psc_exp_wta__with_stdp_solo.
  Description:
    """
  iaf_psc_exp - Leaky integrate-and-fire neuron model with exponential PSCs########################################################################
  Description
  +++++++++++
  iaf_psc_exp is an implementation of a leaky integrate-and-fire model
  with exponential-kernel postsynaptic currents (PSCs) according to [1]_.
  Thus, postsynaptic currents have an infinitely short rise time.
  The threshold crossing is followed by an absolute refractory period (t_ref)
  during which the membrane potential is clamped to the resting potential
  and spiking is prohibited.
  .. note::
     If tau_m is very close to tau_syn_exc or tau_syn_inh, numerical problems
     may arise due to singularities in the propagator matrics. If this is
     the case, replace equal-valued parameters by a single parameter.
     For details, please see ``IAF_neurons_singularity.ipynb`` in
     the NEST source code (``docs/model_details``).
  References
  ++++++++++
  .. [1] Tsodyks M, Uziel A, Markram H (2000). Synchrony generation in recurrent
         networks with frequency-dependent synapses. The Journal of Neuroscience,
         20,RC50:1-5. URL: https://infoscience.epfl.ch/record/183402
  See also
  ++++++++
  iaf_cond_exp
  """
  Parameters:
  The following parameters can be set in the status dictionary.
C_m [pF]  Capacitance of the membrane
 TODO: double check with paper
 Membrane time constant
tau_m [ms]  Membrane time constant
 Time constant of inhibitory synaptic current
tau_syn_inh [ms]  Time constant of inhibitory synaptic current
 INFO: only used if inhibitory connections exist
 Time constant of excitatory synaptic current
tau_syn_exc [ms]  Time constant of excitatory synaptic current
 Resting potential
E_L [mV]  Resting potential
 Reset value of the membrane potential
V_reset [mV]  Reset value of the membrane potential
 Maximum rate within current WTA circuit
R_max [Hz]  Maximum rate within current WTA circuit
tau_tr_pre__for_stdp_solo [ms]  presynaptic time constant
tau_tr_post__for_stdp_solo [ms]  postsynaptic time constant
  Dynamic state variables:
r [integer]  counts number of tick during the refractory period
V_m [mV]  Membrane potential
  Sends: nest::SpikeEvent
  Receives: Spike, Current, DataLoggingRequest
*/
class iaf_psc_exp_wta__with_stdp_solo : public nest::ArchivingNode
{
public:
  /**
   * The constructor is only used to create the model prototype in the model manager.
  **/
  iaf_psc_exp_wta__with_stdp_solo();

  /**
   * The copy constructor is used to create model copies and instances of the model.
   * @node The copy constructor needs to initialize the parameters and the state.
   *       Initialization of buffers and interal variables is deferred to
   *       @c init_buffers_() and @c pre_run_hook() (or calibrate() in NEST 3.3 and older).
  **/
  iaf_psc_exp_wta__with_stdp_solo(const iaf_psc_exp_wta__with_stdp_solo &);

  /**
   * Destructor.
  **/
  ~iaf_psc_exp_wta__with_stdp_solo();

  // -------------------------------------------------------------------------
  //   Import sets of overloaded virtual functions.
  //   See: Technical Issues / Virtual Functions: Overriding, Overloading,
  //        and Hiding
  // -------------------------------------------------------------------------

  using nest::Node::handles_test_event;
  using nest::Node::handle;
    using nest::Node::sends_secondary_event;
  /**
   * Used to validate that we can send nest::SpikeEvent to desired target:port.
  **/
  nest::port send_test_event(nest::Node& target, nest::rport receptor_type, nest::synindex, bool);

  // -------------------------------------------------------------------------
  //   Functions handling incoming events.
  //   We tell nest that we can handle incoming events of various types by
  //   defining handle() for the given event.
  // -------------------------------------------------------------------------


  void handle(nest::SpikeEvent &);        //! accept spikes
  void handle(nest::CurrentEvent &);      //! accept input current
  void handle(nest::DataLoggingRequest &);//! allow recording with multimeter
    void handle(nest::InstantaneousRateConnectionEvent &);//! accept continuous rate events
  nest::port handles_test_event(nest::SpikeEvent&, nest::port);
  nest::port handles_test_event(nest::CurrentEvent&, nest::port);
  nest::port handles_test_event(nest::DataLoggingRequest&, nest::port);
    nest::port handles_test_event(nest::InstantaneousRateConnectionEvent&, nest::port);
    void sends_secondary_event(nest::InstantaneousRateConnectionEvent&)
    {

    }

  // -------------------------------------------------------------------------
  //   Functions for getting/setting parameters and state values.
  // -------------------------------------------------------------------------

  void get_status(DictionaryDatum &) const;
  void set_status(const DictionaryDatum &);
  // support for spike archiving

  /**
   * \fn void get_history(long t1, long t2,
   * std::deque<Archiver::histentry__>::iterator* start,
   * std::deque<Archiver::histentry__>::iterator* finish)
   * return the spike times (in steps) of spikes which occurred in the range
   * (t1,t2].
   * XXX: two underscores to differentiate it from nest::Node::get_history()
   */
  void get_history__( double t1,
    double t2,
    std::deque< histentry__iaf_psc_exp_wta__with_stdp_solo >::iterator* start,
    std::deque< histentry__iaf_psc_exp_wta__with_stdp_solo >::iterator* finish );

  /**
   * Register a new incoming STDP connection.
   *
   * t_first_read: The newly registered synapse will read the history entries
   * with t > t_first_read.
   */
  void register_stdp_connection( double t_first_read, double delay );

  // -------------------------------------------------------------------------
  //   Getters/setters for state block
  // -------------------------------------------------------------------------

  inline long get_r() const
  {
    return S_.r;
  }

  inline void set_r(const long __v)
  {
    S_.r = __v;
  }

  inline double get_V_m() const
  {
    return S_.V_m;
  }

  inline void set_V_m(const double __v)
  {
    S_.V_m = __v;
  }

  inline double get_a_pre__for_stdp_solo() const
  {
    return S_.a_pre__for_stdp_solo;
  }

  inline void set_a_pre__for_stdp_solo(const double __v)
  {
    S_.a_pre__for_stdp_solo = __v;
  }

  inline double get_a_post__for_stdp_solo() const
  {
    return S_.a_post__for_stdp_solo;
  }

  inline void set_a_post__for_stdp_solo(const double __v)
  {
    S_.a_post__for_stdp_solo = __v;
  }

  inline double get_I_kernel_exc__X__exc_spikes() const
  {
    return S_.I_kernel_exc__X__exc_spikes;
  }

  inline void set_I_kernel_exc__X__exc_spikes(const double __v)
  {
    S_.I_kernel_exc__X__exc_spikes = __v;
  }

  inline double get_I_kernel_inh__X__inh_spikes() const
  {
    return S_.I_kernel_inh__X__inh_spikes;
  }

  inline void set_I_kernel_inh__X__inh_spikes(const double __v)
  {
    S_.I_kernel_inh__X__inh_spikes = __v;
  }


  // -------------------------------------------------------------------------
  //   Getters/setters for parameters
  // -------------------------------------------------------------------------

  inline double get_C_m() const
  {
    return P_.C_m;
  }

  inline void set_C_m(const double __v)
  {
    P_.C_m = __v;
  }

  inline double get_tau_m() const
  {
    return P_.tau_m;
  }

  inline void set_tau_m(const double __v)
  {
    P_.tau_m = __v;
  }

  inline double get_tau_syn_inh() const
  {
    return P_.tau_syn_inh;
  }

  inline void set_tau_syn_inh(const double __v)
  {
    P_.tau_syn_inh = __v;
  }

  inline double get_tau_syn_exc() const
  {
    return P_.tau_syn_exc;
  }

  inline void set_tau_syn_exc(const double __v)
  {
    P_.tau_syn_exc = __v;
  }

  inline double get_E_L() const
  {
    return P_.E_L;
  }

  inline void set_E_L(const double __v)
  {
    P_.E_L = __v;
  }

  inline double get_V_reset() const
  {
    return P_.V_reset;
  }

  inline void set_V_reset(const double __v)
  {
    P_.V_reset = __v;
  }

  inline double get_R_max() const
  {
    return P_.R_max;
  }

  inline void set_R_max(const double __v)
  {
    P_.R_max = __v;
  }

  inline double get_tau_tr_pre__for_stdp_solo() const
  {
    return P_.tau_tr_pre__for_stdp_solo;
  }

  inline void set_tau_tr_pre__for_stdp_solo(const double __v)
  {
    P_.tau_tr_pre__for_stdp_solo = __v;
  }

  inline double get_tau_tr_post__for_stdp_solo() const
  {
    return P_.tau_tr_post__for_stdp_solo;
  }

  inline void set_tau_tr_post__for_stdp_solo(const double __v)
  {
    P_.tau_tr_post__for_stdp_solo = __v;
  }


  // -------------------------------------------------------------------------
  //   Getters/setters for internals
  // -------------------------------------------------------------------------

  inline double get___h() const
  {
    return V_.__h;
  }

  inline void set___h(const double __v)
  {
    V_.__h = __v;
  }

  inline double get___P__V_m__V_m() const
  {
    return V_.__P__V_m__V_m;
  }

  inline void set___P__V_m__V_m(const double __v)
  {
    V_.__P__V_m__V_m = __v;
  }

  inline double get___P__V_m__I_kernel_exc__X__exc_spikes() const
  {
    return V_.__P__V_m__I_kernel_exc__X__exc_spikes;
  }

  inline void set___P__V_m__I_kernel_exc__X__exc_spikes(const double __v)
  {
    V_.__P__V_m__I_kernel_exc__X__exc_spikes = __v;
  }

  inline double get___P__V_m__I_kernel_inh__X__inh_spikes() const
  {
    return V_.__P__V_m__I_kernel_inh__X__inh_spikes;
  }

  inline void set___P__V_m__I_kernel_inh__X__inh_spikes(const double __v)
  {
    V_.__P__V_m__I_kernel_inh__X__inh_spikes = __v;
  }

  inline double get___P__a_pre__for_stdp_solo__a_pre__for_stdp_solo() const
  {
    return V_.__P__a_pre__for_stdp_solo__a_pre__for_stdp_solo;
  }

  inline void set___P__a_pre__for_stdp_solo__a_pre__for_stdp_solo(const double __v)
  {
    V_.__P__a_pre__for_stdp_solo__a_pre__for_stdp_solo = __v;
  }

  inline double get___P__a_post__for_stdp_solo__a_post__for_stdp_solo() const
  {
    return V_.__P__a_post__for_stdp_solo__a_post__for_stdp_solo;
  }

  inline void set___P__a_post__for_stdp_solo__a_post__for_stdp_solo(const double __v)
  {
    V_.__P__a_post__for_stdp_solo__a_post__for_stdp_solo = __v;
  }

  inline double get___P__I_kernel_exc__X__exc_spikes__I_kernel_exc__X__exc_spikes() const
  {
    return V_.__P__I_kernel_exc__X__exc_spikes__I_kernel_exc__X__exc_spikes;
  }

  inline void set___P__I_kernel_exc__X__exc_spikes__I_kernel_exc__X__exc_spikes(const double __v)
  {
    V_.__P__I_kernel_exc__X__exc_spikes__I_kernel_exc__X__exc_spikes = __v;
  }

  inline double get___P__I_kernel_inh__X__inh_spikes__I_kernel_inh__X__inh_spikes() const
  {
    return V_.__P__I_kernel_inh__X__inh_spikes__I_kernel_inh__X__inh_spikes;
  }

  inline void set___P__I_kernel_inh__X__inh_spikes__I_kernel_inh__X__inh_spikes(const double __v)
  {
    V_.__P__I_kernel_inh__X__inh_spikes__I_kernel_inh__X__inh_spikes = __v;
  }

  inline double get_normalization_sum() const
  {
      return V_.normalization_sum;
  }

  inline double set_normalization_sum(const double __v)
  {
      V_.normalization_sum = __v;
  }

  /* getters/setters for variables transferred from synapse */
  double get_a_pre__for_stdp_solo( double t, const bool before_increment = true );
  double get_a_post__for_stdp_solo( double t, const bool before_increment = true );

protected:
  // support for spike archiving

  /**
   * record spike history
   */
  void set_spiketime( nest::Time const& t_sp, double offset = 0.0 );

  /**
   * return most recent spike time in ms
   */
  inline double get_spiketime_ms() const;

  /**
   * clear spike history
   */
  void clear_history();

private:
  void recompute_internal_variables(bool exclude_timestep=false);
  // support for spike archiving

  // number of incoming connections from stdp connectors.
  // needed to determine, if every incoming connection has
  // read the spikehistory for a given point in time
  size_t n_incoming_;

  double max_delay_;

  double last_spike_;

  // spiking history needed by stdp synapses
  std::deque< histentry__iaf_psc_exp_wta__with_stdp_solo > history_;

  // cache for initial values
  double a_pre__for_stdp_solo__iv;
  double a_post__for_stdp_solo__iv;

private:


  /**
   * Reset internal buffers of neuron.
  **/
  void init_buffers_();

  /**
   * Initialize auxiliary quantities, leave parameters and state untouched.
  **/
  void pre_run_hook();

  /**
   * Take neuron through given time interval
  **/
  void update(nest::Time const &, const long, const long);

  // The next two classes need to be friends to access the State_ class/member
  friend class nest::RecordablesMap<iaf_psc_exp_wta__with_stdp_solo>;
  friend class nest::UniversalDataLogger<iaf_psc_exp_wta__with_stdp_solo>;

  /**
   * Free parameters of the neuron.
   *
   *
   *
   * These are the parameters that can be set by the user through @c `node.set()`.
   * They are initialized from the model prototype when the node is created.
   * Parameters do not change during calls to @c update() and are not reset by
   * @c ResetNetwork.
   *
   * @note Parameters_ need neither copy constructor nor @c operator=(), since
   *       all its members are copied properly by the default copy constructor
   *       and assignment operator. Important:
   *       - If Parameters_ contained @c Time members, you need to define the
   *         assignment operator to recalibrate all members of type @c Time . You
   *         may also want to define the assignment operator.
   *       - If Parameters_ contained members that cannot copy themselves, such
   *         as C-style arrays, you need to define the copy constructor and
   *         assignment operator to copy those members.
  **/
  struct Parameters_
  {    /* generated by directives/MemberDeclaration.jinja2 */
    //!  Capacitance of the membrane
    //!  TODO: double check with paper
    //!  Membrane time constant
    double C_m;/* generated by directives/MemberDeclaration.jinja2 */
    //!  Membrane time constant
    //!  Time constant of inhibitory synaptic current
    double tau_m;/* generated by directives/MemberDeclaration.jinja2 */
    //!  Time constant of inhibitory synaptic current
    //!  INFO: only used if inhibitory connections exist
    //!  Time constant of excitatory synaptic current
    double tau_syn_inh;/* generated by directives/MemberDeclaration.jinja2 */
    //!  Time constant of excitatory synaptic current
    //!  Resting potential
    double tau_syn_exc;/* generated by directives/MemberDeclaration.jinja2 */
    //!  Resting potential
    //!  Reset value of the membrane potential
    double E_L;/* generated by directives/MemberDeclaration.jinja2 */
    //!  Reset value of the membrane potential
    //!  Maximum rate within current WTA circuit
    double V_reset;/* generated by directives/MemberDeclaration.jinja2 */
    //!  Maximum rate within current WTA circuit
    double R_max;/* generated by directives/MemberDeclaration.jinja2 */
    //!  presynaptic time constant
    double tau_tr_pre__for_stdp_solo;/* generated by directives/MemberDeclaration.jinja2 */
    //!  postsynaptic time constant
    double tau_tr_post__for_stdp_solo;

    /**
     * Initialize parameters to their default values.
    **/
    Parameters_();
  };

  /**
   * Dynamic state of the neuron.
   *
   *
   *
   * These are the state variables that are advanced in time by calls to
   * @c update(). In many models, some or all of them can be set by the user
   * through @c `node.set()`. The state variables are initialized from the model
   * prototype when the node is created. State variables are reset by @c ResetNetwork.
   *
   * @note State_ need neither copy constructor nor @c operator=(), since
   *       all its members are copied properly by the default copy constructor
   *       and assignment operator. Important:
   *       - If State_ contained @c Time members, you need to define the
   *         assignment operator to recalibrate all members of type @c Time . You
   *         may also want to define the assignment operator.
   *       - If State_ contained members that cannot copy themselves, such
   *         as C-style arrays, you need to define the copy constructor and
   *         assignment operator to copy those members.
  **/
  struct State_
  {    /* generated by directives/MemberDeclaration.jinja2 */
    //!  counts number of tick during the refractory period
    long r;/* generated by directives/MemberDeclaration.jinja2 */
    //!  Membrane potential
    double V_m;/* generated by directives/MemberDeclaration.jinja2 */
    double a_pre__for_stdp_solo;/* generated by directives/MemberDeclaration.jinja2 */
    double a_post__for_stdp_solo;/* generated by directives/MemberDeclaration.jinja2 */
    double I_kernel_exc__X__exc_spikes;/* generated by directives/MemberDeclaration.jinja2 */
    double I_kernel_inh__X__inh_spikes;
    //double normalization_sum;

    State_();
  };

  struct DelayedVariables_
  {
  };

  /**
   * Internal variables of the neuron.
   *
   *
   *
   * These variables must be initialized by @c pre_run_hook (or calibrate in NEST 3.3 and older), which is called before
   * the first call to @c update() upon each call to @c Simulate.
   * @node Variables_ needs neither constructor, copy constructor or assignment operator,
   *       since it is initialized by @c pre_run_hook() (or calibrate() in NEST 3.3 and older). If Variables_ has members that
   *       cannot destroy themselves, Variables_ will need a destructor.
  **/
  struct Variables_
  {/* generated by directives/MemberDeclaration.jinja2 */
    double __h;/* generated by directives/MemberDeclaration.jinja2 */
    double __P__V_m__V_m;/* generated by directives/MemberDeclaration.jinja2 */
    double __P__V_m__I_kernel_exc__X__exc_spikes;/* generated by directives/MemberDeclaration.jinja2 */
    double __P__V_m__I_kernel_inh__X__inh_spikes;/* generated by directives/MemberDeclaration.jinja2 */
    double __P__a_pre__for_stdp_solo__a_pre__for_stdp_solo;/* generated by directives/MemberDeclaration.jinja2 */
    double __P__a_post__for_stdp_solo__a_post__for_stdp_solo;/* generated by directives/MemberDeclaration.jinja2 */
    double __P__I_kernel_exc__X__exc_spikes__I_kernel_exc__X__exc_spikes;/* generated by directives/MemberDeclaration.jinja2 */
    double __P__I_kernel_inh__X__inh_spikes__I_kernel_inh__X__inh_spikes;
    double normalization_sum;
  };

  /**
   * Buffers of the neuron.
   * Usually buffers for incoming spikes and data logged for analog recorders.
   * Buffers must be initialized by @c init_buffers_(), which is called before
   * @c pre_run_hook() (or calibrate() in NEST 3.3 and older) on the first call to @c Simulate after the start of NEST,
   * ResetKernel or ResetNetwork.
   * @node Buffers_ needs neither constructor, copy constructor or assignment operator,
   *       since it is initialized by @c init_nodes_(). If Buffers_ has members that
   *       cannot destroy themselves, Buffers_ will need a destructor.
  **/
  struct Buffers_
  {
    Buffers_(iaf_psc_exp_wta__with_stdp_solo &);
    Buffers_(const Buffers_ &, iaf_psc_exp_wta__with_stdp_solo &);

    /**
     * Logger for all analog data
    **/
    nest::UniversalDataLogger<iaf_psc_exp_wta__with_stdp_solo> logger_;
    inline nest::RingBuffer& get_exc_spikes() {return exc_spikes;}
    //!< Buffer for input (type: pA)
    nest::RingBuffer exc_spikes;
    double exc_spikes_grid_sum_;
    inline nest::RingBuffer& get_inh_spikes() {return inh_spikes;}
    //!< Buffer for input (type: pA)
    nest::RingBuffer inh_spikes;
    double inh_spikes_grid_sum_;
    //!< Buffer for input (type: pA)
    nest::RingBuffer I_stim;
    inline nest::RingBuffer& get_I_stim() {return I_stim;}
    double I_stim_grid_sum_;

  };

  // -------------------------------------------------------------------------
  //   Getters/setters for inline expressions
  // -------------------------------------------------------------------------

  inline double get_I_syn() const
  {
    return get_I_kernel_exc__X__exc_spikes() - get_I_kernel_inh__X__inh_spikes();
  }


  // -------------------------------------------------------------------------
  //   Getters/setters for input buffers
  // -------------------------------------------------------------------------

  inline nest::RingBuffer& get_exc_spikes() {return B_.get_exc_spikes();};
  inline nest::RingBuffer& get_inh_spikes() {return B_.get_inh_spikes();};
  inline nest::RingBuffer& get_I_stim() {return B_.get_I_stim();};

  // -------------------------------------------------------------------------
  //   Member variables of neuron model.
  //   Each model neuron should have precisely the following four data members,
  //   which are one instance each of the parameters, state, buffers and variables
  //   structures. Experience indicates that the state and variables member should
  //   be next to each other to achieve good efficiency (caching).
  //   Note: Devices require one additional data member, an instance of the
  //   ``Device`` child class they belong to.
  // -------------------------------------------------------------------------


  Parameters_       P_;        //!< Free parameters.
  State_            S_;        //!< Dynamic state.
  DelayedVariables_ DV_;       //!< Delayed state variables.
  Variables_        V_;        //!< Internal Variables
  Buffers_          B_;        //!< Buffers.

  //! Mapping of recordables names to access functions
  static nest::RecordablesMap<iaf_psc_exp_wta__with_stdp_solo> recordablesMap_;

}; /* neuron iaf_psc_exp_wta__with_stdp_solo */

inline nest::port iaf_psc_exp_wta__with_stdp_solo::send_test_event(nest::Node& target, nest::rport receptor_type, nest::synindex, bool)
{
  // You should usually not change the code in this function.
  // It confirms that the target of connection @c c accepts @c nest::SpikeEvent on
  // the given @c receptor_type.
  nest::SpikeEvent e;
  e.set_sender(*this);
  return target.handles_test_event(e, receptor_type);
}

inline nest::port iaf_psc_exp_wta__with_stdp_solo::handles_test_event(nest::SpikeEvent&, nest::port receptor_type)
{
    // You should usually not change the code in this function.
    // It confirms to the connection management system that we are able
    // to handle @c SpikeEvent on port 0. You need to extend the function
    // if you want to differentiate between input ports.
    if (receptor_type != 0)
    {
      throw nest::UnknownReceptorType(receptor_type, get_name());
    }
    return 0;
}

inline nest::port iaf_psc_exp_wta__with_stdp_solo::handles_test_event(nest::CurrentEvent&, nest::port receptor_type)
{
  // You should usually not change the code in this function.
  // It confirms to the connection management system that we are able
  // to handle @c CurrentEvent on port 0. You need to extend the function
  // if you want to differentiate between input ports.
  if (receptor_type != 0)
  {
    throw nest::UnknownReceptorType(receptor_type, get_name());
  }
  return 0;
}

inline nest::port iaf_psc_exp_wta__with_stdp_solo::handles_test_event(nest::DataLoggingRequest& dlr, nest::port receptor_type)
{
  // You should usually not change the code in this function.
  // It confirms to the connection management system that we are able
  // to handle @c DataLoggingRequest on port 0.
  // The function also tells the built-in UniversalDataLogger that this node
  // is recorded from and that it thus needs to collect data during simulation.
  if (receptor_type != 0)
  {
    throw nest::UnknownReceptorType(receptor_type, get_name());
  }

  return B_.logger_.connect_logging_device(dlr, recordablesMap_);
}

inline nest::port iaf_psc_exp_wta__with_stdp_solo::handles_test_event(nest::InstantaneousRateConnectionEvent& dlr, nest::port receptor_type)
{
    // You should usually not change the code in this function.
    // It confirms to the connection management system that we are able
    // to handle @c DataLoggingRequest on port 0.
    // The function also tells the built-in UniversalDataLogger that this node
    // is recorded from and that it thus needs to collect data during simulation.
    if (receptor_type != 0)
    {
        throw nest::UnknownReceptorType(receptor_type, get_name());
    }

    return 0;
}

inline void iaf_psc_exp_wta__with_stdp_solo::get_status(DictionaryDatum &__d) const
{
  // parameters/* generated by directives/WriteInDictionary.jinja2 */
  def<double>(__d, nest::iaf_psc_exp_wta__with_stdp_solo_names::_C_m, get_C_m());/* generated by directives/WriteInDictionary.jinja2 */
  def<double>(__d, nest::iaf_psc_exp_wta__with_stdp_solo_names::_tau_m, get_tau_m());/* generated by directives/WriteInDictionary.jinja2 */
  def<double>(__d, nest::iaf_psc_exp_wta__with_stdp_solo_names::_tau_syn_inh, get_tau_syn_inh());/* generated by directives/WriteInDictionary.jinja2 */
  def<double>(__d, nest::iaf_psc_exp_wta__with_stdp_solo_names::_tau_syn_exc, get_tau_syn_exc());/* generated by directives/WriteInDictionary.jinja2 */
  def<double>(__d, nest::iaf_psc_exp_wta__with_stdp_solo_names::_E_L, get_E_L());/* generated by directives/WriteInDictionary.jinja2 */
  def<double>(__d, nest::iaf_psc_exp_wta__with_stdp_solo_names::_V_reset, get_V_reset());/* generated by directives/WriteInDictionary.jinja2 */
  def<double>(__d, nest::iaf_psc_exp_wta__with_stdp_solo_names::_R_max, get_R_max());/* generated by directives/WriteInDictionary.jinja2 */
  def<double>(__d, nest::iaf_psc_exp_wta__with_stdp_solo_names::_tau_tr_pre__for_stdp_solo, get_tau_tr_pre__for_stdp_solo());/* generated by directives/WriteInDictionary.jinja2 */
  def<double>(__d, nest::iaf_psc_exp_wta__with_stdp_solo_names::_tau_tr_post__for_stdp_solo, get_tau_tr_post__for_stdp_solo());

  // initial values for state variables in ODE or kernel/* generated by directives/WriteInDictionary.jinja2 */
  def<long>(__d, nest::iaf_psc_exp_wta__with_stdp_solo_names::_r, get_r());/* generated by directives/WriteInDictionary.jinja2 */
  def<double>(__d, nest::iaf_psc_exp_wta__with_stdp_solo_names::_V_m, get_V_m());/* generated by directives/WriteInDictionary.jinja2 */
  def<double>(__d, nest::iaf_psc_exp_wta__with_stdp_solo_names::_a_pre__for_stdp_solo, get_a_pre__for_stdp_solo());/* generated by directives/WriteInDictionary.jinja2 */
  def<double>(__d, nest::iaf_psc_exp_wta__with_stdp_solo_names::_a_post__for_stdp_solo, get_a_post__for_stdp_solo());/* generated by directives/WriteInDictionary.jinja2 */
  def<double>(__d, nest::iaf_psc_exp_wta__with_stdp_solo_names::_I_kernel_exc__X__exc_spikes, get_I_kernel_exc__X__exc_spikes());/* generated by directives/WriteInDictionary.jinja2 */
  def<double>(__d, nest::iaf_psc_exp_wta__with_stdp_solo_names::_I_kernel_inh__X__inh_spikes, get_I_kernel_inh__X__inh_spikes());
  def<double>(__d, nest::iaf_psc_exp_wta__with_stdp_solo_names::_normalization_sum, get_normalization_sum());

  ArchivingNode::get_status( __d );

  (*__d)[nest::names::recordables] = recordablesMap_.get_list();
}

inline void iaf_psc_exp_wta__with_stdp_solo::set_status(const DictionaryDatum &__d)
{
  // parameters/* generated by directives/ReadFromDictionaryToTmp.jinja2 */
  double tmp_C_m = get_C_m();
  updateValue<double>(__d, nest::iaf_psc_exp_wta__with_stdp_solo_names::_C_m, tmp_C_m);/* generated by directives/ReadFromDictionaryToTmp.jinja2 */
  double tmp_tau_m = get_tau_m();
  updateValue<double>(__d, nest::iaf_psc_exp_wta__with_stdp_solo_names::_tau_m, tmp_tau_m);/* generated by directives/ReadFromDictionaryToTmp.jinja2 */
  double tmp_tau_syn_inh = get_tau_syn_inh();
  updateValue<double>(__d, nest::iaf_psc_exp_wta__with_stdp_solo_names::_tau_syn_inh, tmp_tau_syn_inh);/* generated by directives/ReadFromDictionaryToTmp.jinja2 */
  double tmp_tau_syn_exc = get_tau_syn_exc();
  updateValue<double>(__d, nest::iaf_psc_exp_wta__with_stdp_solo_names::_tau_syn_exc, tmp_tau_syn_exc);/* generated by directives/ReadFromDictionaryToTmp.jinja2 */
  double tmp_E_L = get_E_L();
  updateValue<double>(__d, nest::iaf_psc_exp_wta__with_stdp_solo_names::_E_L, tmp_E_L);/* generated by directives/ReadFromDictionaryToTmp.jinja2 */
  double tmp_V_reset = get_V_reset();
  updateValue<double>(__d, nest::iaf_psc_exp_wta__with_stdp_solo_names::_V_reset, tmp_V_reset);/* generated by directives/ReadFromDictionaryToTmp.jinja2 */
  double tmp_R_max = get_R_max();
  updateValue<double>(__d, nest::iaf_psc_exp_wta__with_stdp_solo_names::_R_max, tmp_R_max);/* generated by directives/ReadFromDictionaryToTmp.jinja2 */
  double tmp_tau_tr_pre__for_stdp_solo = get_tau_tr_pre__for_stdp_solo();
  updateValue<double>(__d, nest::iaf_psc_exp_wta__with_stdp_solo_names::_tau_tr_pre__for_stdp_solo, tmp_tau_tr_pre__for_stdp_solo);/* generated by directives/ReadFromDictionaryToTmp.jinja2 */
  double tmp_tau_tr_post__for_stdp_solo = get_tau_tr_post__for_stdp_solo();
  updateValue<double>(__d, nest::iaf_psc_exp_wta__with_stdp_solo_names::_tau_tr_post__for_stdp_solo, tmp_tau_tr_post__for_stdp_solo);

  // initial values for state variables in ODE or kernel/* generated by directives/ReadFromDictionaryToTmp.jinja2 */
  long tmp_r = get_r();
  updateValue<long>(__d, nest::iaf_psc_exp_wta__with_stdp_solo_names::_r, tmp_r);/* generated by directives/ReadFromDictionaryToTmp.jinja2 */
  double tmp_V_m = get_V_m();
  updateValue<double>(__d, nest::iaf_psc_exp_wta__with_stdp_solo_names::_V_m, tmp_V_m);/* generated by directives/ReadFromDictionaryToTmp.jinja2 */
  double tmp_a_pre__for_stdp_solo = get_a_pre__for_stdp_solo();
  updateValue<double>(__d, nest::iaf_psc_exp_wta__with_stdp_solo_names::_a_pre__for_stdp_solo, tmp_a_pre__for_stdp_solo);/* generated by directives/ReadFromDictionaryToTmp.jinja2 */
  double tmp_a_post__for_stdp_solo = get_a_post__for_stdp_solo();
  updateValue<double>(__d, nest::iaf_psc_exp_wta__with_stdp_solo_names::_a_post__for_stdp_solo, tmp_a_post__for_stdp_solo);/* generated by directives/ReadFromDictionaryToTmp.jinja2 */
  double tmp_I_kernel_exc__X__exc_spikes = get_I_kernel_exc__X__exc_spikes();
  updateValue<double>(__d, nest::iaf_psc_exp_wta__with_stdp_solo_names::_I_kernel_exc__X__exc_spikes, tmp_I_kernel_exc__X__exc_spikes);/* generated by directives/ReadFromDictionaryToTmp.jinja2 */
  double tmp_I_kernel_inh__X__inh_spikes = get_I_kernel_inh__X__inh_spikes();
  updateValue<double>(__d, nest::iaf_psc_exp_wta__with_stdp_solo_names::_I_kernel_inh__X__inh_spikes, tmp_I_kernel_inh__X__inh_spikes);
  //double tmp_normalization_sum = get_normalization_sum();
  //updateValue<double>(__d, nest::iaf_psc_exp_wta__with_stdp_solo_names::_normalization_sum, tmp_normalization_sum);

  // We now know that (ptmp, stmp) are consistent. We do not
  // write them back to (P_, S_) before we are also sure that
  // the properties to be set in the parent class are internally
  // consistent.
  ArchivingNode::set_status(__d);

  // if we get here, temporaries contain consistent set of properties/* generated by directives/AssignTmpDictionaryValue.jinja2 */
  set_C_m(tmp_C_m);/* generated by directives/AssignTmpDictionaryValue.jinja2 */
  set_tau_m(tmp_tau_m);/* generated by directives/AssignTmpDictionaryValue.jinja2 */
  set_tau_syn_inh(tmp_tau_syn_inh);/* generated by directives/AssignTmpDictionaryValue.jinja2 */
  set_tau_syn_exc(tmp_tau_syn_exc);/* generated by directives/AssignTmpDictionaryValue.jinja2 */
  set_E_L(tmp_E_L);/* generated by directives/AssignTmpDictionaryValue.jinja2 */
  set_V_reset(tmp_V_reset);/* generated by directives/AssignTmpDictionaryValue.jinja2 */
  set_R_max(tmp_R_max);/* generated by directives/AssignTmpDictionaryValue.jinja2 */
  set_tau_tr_pre__for_stdp_solo(tmp_tau_tr_pre__for_stdp_solo);/* generated by directives/AssignTmpDictionaryValue.jinja2 */
  set_tau_tr_post__for_stdp_solo(tmp_tau_tr_post__for_stdp_solo);/* generated by directives/AssignTmpDictionaryValue.jinja2 */
  set_r(tmp_r);/* generated by directives/AssignTmpDictionaryValue.jinja2 */
  set_V_m(tmp_V_m);/* generated by directives/AssignTmpDictionaryValue.jinja2 */
  set_a_pre__for_stdp_solo(tmp_a_pre__for_stdp_solo);/* generated by directives/AssignTmpDictionaryValue.jinja2 */
  set_a_post__for_stdp_solo(tmp_a_post__for_stdp_solo);/* generated by directives/AssignTmpDictionaryValue.jinja2 */
  set_I_kernel_exc__X__exc_spikes(tmp_I_kernel_exc__X__exc_spikes);/* generated by directives/AssignTmpDictionaryValue.jinja2 */
  set_I_kernel_inh__X__inh_spikes(tmp_I_kernel_inh__X__inh_spikes);
  //set_normalization_sum(tmp_normalization_sum);



  // recompute internal variables in case they are dependent on parameters or state that might have been updated in this call to set_status()
  recompute_internal_variables();
};

#endif /* #ifndef IAF_PSC_EXP_WTA__WITH_STDP_SOLO */