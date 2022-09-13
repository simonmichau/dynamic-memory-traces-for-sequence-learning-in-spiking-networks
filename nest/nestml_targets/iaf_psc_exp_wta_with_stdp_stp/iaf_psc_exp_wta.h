/* generated by common/NeuronHeader.jinja2 */ /**
 *  iaf_psc_exp_wta.h
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
 *  Generated from NESTML at time: 2022-09-13 17:18:04.479083
**/
#ifndef IAF_PSC_EXP_WTA
#define IAF_PSC_EXP_WTA

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
namespace iaf_psc_exp_wta_names
{
    const Name _r( "r" );
    const Name _V_m( "V_m" );
    const Name _rise_time_kernel__X__exc_spikes( "rise_time_kernel__X__exc_spikes" );
    const Name _decay_time_kernel__X__exc_spikes( "decay_time_kernel__X__exc_spikes" );
    const Name _C_m( "C_m" );
    const Name _tau_m( "tau_m" );
    const Name _tau_syn_inh( "tau_syn_inh" );
    const Name _tau_syn_exc( "tau_syn_exc" );
    const Name _E_L( "E_L" );
    const Name _V_reset( "V_reset" );
    const Name _R_max( "R_max" );
}
}




#include "nest_time.h"




/* BeginDocumentation
  Name: iaf_psc_exp_wta.

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


  Dynamic state variables:
r [integer]  counts number of tick during the refractory period
V_m [mV]  Membrane potential


  Sends: nest::SpikeEvent

  Receives: Spike, Current, DataLoggingRequest
*/
class iaf_psc_exp_wta : public nest::ArchivingNode
{
public:
  /**
   * The constructor is only used to create the model prototype in the model manager.
  **/
  iaf_psc_exp_wta();

  /**
   * The copy constructor is used to create model copies and instances of the model.
   * @node The copy constructor needs to initialize the parameters and the state.
   *       Initialization of buffers and interal variables is deferred to
   *       @c init_buffers_() and @c pre_run_hook() (or calibrate() in NEST 3.3 and older).
  **/
  iaf_psc_exp_wta(const iaf_psc_exp_wta &);

  /**
   * Destructor.
  **/
  ~iaf_psc_exp_wta();

  // -------------------------------------------------------------------------
  //   Import sets of overloaded virtual functions.
  //   See: Technical Issues / Virtual Functions: Overriding, Overloading,
  //        and Hiding
  // -------------------------------------------------------------------------

  using nest::Node::handles_test_event;
  using nest::Node::handle;

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
  nest::port handles_test_event(nest::SpikeEvent&, nest::port);
  nest::port handles_test_event(nest::CurrentEvent&, nest::port);
  nest::port handles_test_event(nest::DataLoggingRequest&, nest::port);

  // -------------------------------------------------------------------------
  //   Functions for getting/setting parameters and state values.
  // -------------------------------------------------------------------------

  void get_status(DictionaryDatum &) const;
  void set_status(const DictionaryDatum &);

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

  inline double get_rise_time_kernel__X__exc_spikes() const
  {
    return S_.rise_time_kernel__X__exc_spikes;
  }

  inline void set_rise_time_kernel__X__exc_spikes(const double __v)
  {
    S_.rise_time_kernel__X__exc_spikes = __v;
  }

  inline double get_decay_time_kernel__X__exc_spikes() const
  {
    return S_.decay_time_kernel__X__exc_spikes;
  }

  inline void set_decay_time_kernel__X__exc_spikes(const double __v)
  {
    S_.decay_time_kernel__X__exc_spikes = __v;
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

  inline double get___P__rise_time_kernel__X__exc_spikes__rise_time_kernel__X__exc_spikes() const
  {
    return V_.__P__rise_time_kernel__X__exc_spikes__rise_time_kernel__X__exc_spikes;
  }

  inline void set___P__rise_time_kernel__X__exc_spikes__rise_time_kernel__X__exc_spikes(const double __v)
  {
    V_.__P__rise_time_kernel__X__exc_spikes__rise_time_kernel__X__exc_spikes = __v;
  }

  inline double get___P__decay_time_kernel__X__exc_spikes__decay_time_kernel__X__exc_spikes() const
  {
    return V_.__P__decay_time_kernel__X__exc_spikes__decay_time_kernel__X__exc_spikes;
  }

  inline void set___P__decay_time_kernel__X__exc_spikes__decay_time_kernel__X__exc_spikes(const double __v)
  {
    V_.__P__decay_time_kernel__X__exc_spikes__decay_time_kernel__X__exc_spikes = __v;
  }



protected:

private:
  void recompute_internal_variables(bool exclude_timestep=false);

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
  friend class nest::RecordablesMap<iaf_psc_exp_wta>;
  friend class nest::UniversalDataLogger<iaf_psc_exp_wta>;

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
    double R_max;

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
    double rise_time_kernel__X__exc_spikes;/* generated by directives/MemberDeclaration.jinja2 */ 
    double decay_time_kernel__X__exc_spikes;

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
    double __P__rise_time_kernel__X__exc_spikes__rise_time_kernel__X__exc_spikes;/* generated by directives/MemberDeclaration.jinja2 */ 
    double __P__decay_time_kernel__X__exc_spikes__decay_time_kernel__X__exc_spikes;
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
    Buffers_(iaf_psc_exp_wta &);
    Buffers_(const Buffers_ &, iaf_psc_exp_wta &);

    /**
     * Logger for all analog data
    **/
    nest::UniversalDataLogger<iaf_psc_exp_wta> logger_;
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
  
  inline double get_y() const
  {
    return (get_decay_time_kernel__X__exc_spikes() - get_rise_time_kernel__X__exc_spikes()) / 1.0;
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
  static nest::RecordablesMap<iaf_psc_exp_wta> recordablesMap_;

}; /* neuron iaf_psc_exp_wta */

inline nest::port iaf_psc_exp_wta::send_test_event(nest::Node& target, nest::rport receptor_type, nest::synindex, bool)
{
  // You should usually not change the code in this function.
  // It confirms that the target of connection @c c accepts @c nest::SpikeEvent on
  // the given @c receptor_type.
  nest::SpikeEvent e;
  e.set_sender(*this);
  return target.handles_test_event(e, receptor_type);
}

inline nest::port iaf_psc_exp_wta::handles_test_event(nest::SpikeEvent&, nest::port receptor_type)
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

inline nest::port iaf_psc_exp_wta::handles_test_event(nest::CurrentEvent&, nest::port receptor_type)
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

inline nest::port iaf_psc_exp_wta::handles_test_event(nest::DataLoggingRequest& dlr, nest::port receptor_type)
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

inline void iaf_psc_exp_wta::get_status(DictionaryDatum &__d) const
{
  // parameters/* generated by directives/WriteInDictionary.jinja2 */ 
  def<double>(__d, nest::iaf_psc_exp_wta_names::_C_m, get_C_m());/* generated by directives/WriteInDictionary.jinja2 */ 
  def<double>(__d, nest::iaf_psc_exp_wta_names::_tau_m, get_tau_m());/* generated by directives/WriteInDictionary.jinja2 */ 
  def<double>(__d, nest::iaf_psc_exp_wta_names::_tau_syn_inh, get_tau_syn_inh());/* generated by directives/WriteInDictionary.jinja2 */ 
  def<double>(__d, nest::iaf_psc_exp_wta_names::_tau_syn_exc, get_tau_syn_exc());/* generated by directives/WriteInDictionary.jinja2 */ 
  def<double>(__d, nest::iaf_psc_exp_wta_names::_E_L, get_E_L());/* generated by directives/WriteInDictionary.jinja2 */ 
  def<double>(__d, nest::iaf_psc_exp_wta_names::_V_reset, get_V_reset());/* generated by directives/WriteInDictionary.jinja2 */ 
  def<double>(__d, nest::iaf_psc_exp_wta_names::_R_max, get_R_max());

  // initial values for state variables in ODE or kernel/* generated by directives/WriteInDictionary.jinja2 */ 
  def<long>(__d, nest::iaf_psc_exp_wta_names::_r, get_r());/* generated by directives/WriteInDictionary.jinja2 */ 
  def<double>(__d, nest::iaf_psc_exp_wta_names::_V_m, get_V_m());/* generated by directives/WriteInDictionary.jinja2 */ 
  def<double>(__d, nest::iaf_psc_exp_wta_names::_rise_time_kernel__X__exc_spikes, get_rise_time_kernel__X__exc_spikes());/* generated by directives/WriteInDictionary.jinja2 */ 
  def<double>(__d, nest::iaf_psc_exp_wta_names::_decay_time_kernel__X__exc_spikes, get_decay_time_kernel__X__exc_spikes());

  ArchivingNode::get_status( __d );

  (*__d)[nest::names::recordables] = recordablesMap_.get_list();
}

inline void iaf_psc_exp_wta::set_status(const DictionaryDatum &__d)
{
  // parameters/* generated by directives/ReadFromDictionaryToTmp.jinja2 */ 
  double tmp_C_m = get_C_m();
  updateValue<double>(__d, nest::iaf_psc_exp_wta_names::_C_m, tmp_C_m);/* generated by directives/ReadFromDictionaryToTmp.jinja2 */ 
  double tmp_tau_m = get_tau_m();
  updateValue<double>(__d, nest::iaf_psc_exp_wta_names::_tau_m, tmp_tau_m);/* generated by directives/ReadFromDictionaryToTmp.jinja2 */ 
  double tmp_tau_syn_inh = get_tau_syn_inh();
  updateValue<double>(__d, nest::iaf_psc_exp_wta_names::_tau_syn_inh, tmp_tau_syn_inh);/* generated by directives/ReadFromDictionaryToTmp.jinja2 */ 
  double tmp_tau_syn_exc = get_tau_syn_exc();
  updateValue<double>(__d, nest::iaf_psc_exp_wta_names::_tau_syn_exc, tmp_tau_syn_exc);/* generated by directives/ReadFromDictionaryToTmp.jinja2 */ 
  double tmp_E_L = get_E_L();
  updateValue<double>(__d, nest::iaf_psc_exp_wta_names::_E_L, tmp_E_L);/* generated by directives/ReadFromDictionaryToTmp.jinja2 */ 
  double tmp_V_reset = get_V_reset();
  updateValue<double>(__d, nest::iaf_psc_exp_wta_names::_V_reset, tmp_V_reset);/* generated by directives/ReadFromDictionaryToTmp.jinja2 */ 
  double tmp_R_max = get_R_max();
  updateValue<double>(__d, nest::iaf_psc_exp_wta_names::_R_max, tmp_R_max);

  // initial values for state variables in ODE or kernel/* generated by directives/ReadFromDictionaryToTmp.jinja2 */ 
  long tmp_r = get_r();
  updateValue<long>(__d, nest::iaf_psc_exp_wta_names::_r, tmp_r);/* generated by directives/ReadFromDictionaryToTmp.jinja2 */ 
  double tmp_V_m = get_V_m();
  updateValue<double>(__d, nest::iaf_psc_exp_wta_names::_V_m, tmp_V_m);/* generated by directives/ReadFromDictionaryToTmp.jinja2 */ 
  double tmp_rise_time_kernel__X__exc_spikes = get_rise_time_kernel__X__exc_spikes();
  updateValue<double>(__d, nest::iaf_psc_exp_wta_names::_rise_time_kernel__X__exc_spikes, tmp_rise_time_kernel__X__exc_spikes);/* generated by directives/ReadFromDictionaryToTmp.jinja2 */ 
  double tmp_decay_time_kernel__X__exc_spikes = get_decay_time_kernel__X__exc_spikes();
  updateValue<double>(__d, nest::iaf_psc_exp_wta_names::_decay_time_kernel__X__exc_spikes, tmp_decay_time_kernel__X__exc_spikes);

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
  set_r(tmp_r);/* generated by directives/AssignTmpDictionaryValue.jinja2 */ 
  set_V_m(tmp_V_m);/* generated by directives/AssignTmpDictionaryValue.jinja2 */ 
  set_rise_time_kernel__X__exc_spikes(tmp_rise_time_kernel__X__exc_spikes);/* generated by directives/AssignTmpDictionaryValue.jinja2 */ 
  set_decay_time_kernel__X__exc_spikes(tmp_decay_time_kernel__X__exc_spikes);



  // recompute internal variables in case they are dependent on parameters or state that might have been updated in this call to set_status()
  recompute_internal_variables();
};

#endif /* #ifndef IAF_PSC_EXP_WTA */
