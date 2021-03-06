/*******************************************************************************

Purpose:
  (Define class RK4_Integrator.)

Programmers:
  (((David Hammen) (Odyssey) (July 2012) (JEOD_2.2 #462)
    (Joint /JEOD integration framework)))

*******************************************************************************/

#ifndef TRICK_ER7_RK4_INTEGRATOR_HH
#define TRICK_ER7_RK4_INTEGRATOR_HH

#include "er7_utils/integration/rk4/include/rk4_integrator_constructor.hh"
#include "er7_utils/trick/integration/include/first_order_ode_integrator.hh"


namespace Trick {

/**
 * Helper class for RK4_Integrator
 */
class RK4_IntegratorHelper {
#ifndef SWIG
   friend class InputProcessor;
   friend void init_attrTrick__RK4_IntegratorHelper();
#endif

protected:

   er7_utils::RK4IntegratorConstructor
   helper_integ_constructor; /* --
      The integrator constructor associated with RK4 integration. */
};


/**
 * Integrator using Runge Kutta 4 method.
 */
class RK4_Integrator :
   protected RK4_IntegratorHelper,
   public er7_utils::TrickFirstOrderOdeIntegrator {
#ifndef SWIG
   friend class InputProcessor;
   friend void init_attrTrick__RK4_Integrator();
#endif

public:

   /** Default constructor, needed by the MemoryManager. */
   RK4_Integrator () {}

   /** Copy constructor, needed for backwards compatibility. */
   RK4_Integrator (const RK4_Integrator & src)
   :
      RK4_IntegratorHelper (src),
      TrickFirstOrderOdeIntegrator (src, helper_integ_constructor)
   {}

   /** Non-default constructor, needed by getIntegrator. */
   RK4_Integrator (int state_size, double delta_t)
   :
      RK4_IntegratorHelper (),
      TrickFirstOrderOdeIntegrator (
         helper_integ_constructor, state_size, delta_t)
   {}

   /** Assignment operator. */
   RK4_Integrator & operator= (RK4_Integrator src)
   {
      helper_integ_constructor = src.helper_integ_constructor;
      TrickFirstOrderOdeIntegrator::swap (src);
      return *this;
   }

   /** Destructor. */
   virtual ~RK4_Integrator() {}

   virtual Integrator_type get_Integrator_type() { return Runge_Kutta_4; }
};

}

#endif
