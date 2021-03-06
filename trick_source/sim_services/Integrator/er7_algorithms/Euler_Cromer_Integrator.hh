/*******************************************************************************

Purpose:
  (Define class Euler_Cromer_Integrator.)

Programmers:
  (((David Hammen) (Odyssey) (July 2012) (JEOD_2.2 #462)
    (Joint /JEOD integration framework)))

*******************************************************************************/

#ifndef TRICK_ER7_EULER_CROMER_INTEGRATOR_HH
#define TRICK_ER7_EULER_CROMER_INTEGRATOR_HH

#include <cstring>

#include "er7_utils/integration/symplectic_euler/include/symplectic_euler_integrator_constructor.hh"
#include "er7_utils/trick/integration/include/second_order_ode_integrator.hh"


namespace Trick {

/**
 * Helper class for Euler_Cromer_Integrator
 */
class Euler_Cromer_IntegratorHelper {
#ifndef SWIG
   friend class InputProcessor;
   friend void init_attrTrick__Euler_Cromer_IntegratorHelper();
#endif

protected:

   er7_utils::SymplecticEulerIntegratorConstructor
   helper_integ_constructor; /* --
      The integrator constructor associated with Euler Cromer integration. */
};


/**
 * Integrator using the Euler Cromer method.
 */
class Euler_Cromer_Integrator :
   protected Euler_Cromer_IntegratorHelper,
   public er7_utils::TrickSecondOrderOdeIntegrator {
#ifndef SWIG
   friend class InputProcessor;
   friend void init_attrTrick__Euler_Cromer_Integrator();
#endif

public:

   /** Default constructor, needed by the MemoryManager. */
   Euler_Cromer_Integrator () {}

   /** Copy constructor, needed for backwards compatibility. */
   Euler_Cromer_Integrator (const Euler_Cromer_Integrator & src)
   :
      Euler_Cromer_IntegratorHelper (src),
      TrickSecondOrderOdeIntegrator (src, helper_integ_constructor)
   {}

   /** Non default constructor, needed by getIntegrator. */
   Euler_Cromer_Integrator (int state_size, double delta_t)
   :
      Euler_Cromer_IntegratorHelper (),
      TrickSecondOrderOdeIntegrator (
         helper_integ_constructor, state_size, delta_t, true)
   {}

   /** Assignment operator. */
   Euler_Cromer_Integrator & operator= (Euler_Cromer_Integrator src)
   {
      helper_integ_constructor = src.helper_integ_constructor;
      TrickSecondOrderOdeIntegrator::swap (src);
      return *this;
   }


   /**
    * Take the next integration step.
    * @return non-zero step number or zero upon completion.
    */
   virtual int integrate ()
   {
      std::memcpy (state + half_state_size,
                   er7_deriv, half_state_size*sizeof(double));
      return TrickSecondOrderOdeIntegrator::integrate();
   }

   /** Destructor. */
   virtual ~Euler_Cromer_Integrator() {}

   virtual Integrator_type get_Integrator_type() { return Euler_Cromer; }

};

}

#endif
