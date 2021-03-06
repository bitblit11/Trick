/*********************************** TRICK HEADER **************************
PURPOSE:                     (Test Baseball)
***************************************************************************/

/*
 * $Id: cannon_aero.h 876 2010-07-29 19:50:57Z wwoodard $
 */

#ifndef _cannon_aero_proto_h_
#define _cannon_aero_proto_h__

#include "cannon_aero.h"

#ifdef __cplusplus
extern "C" {
#endif

int cannon_force_jet(CANNON_AERO*);
int cannon_init_aero(CANNON_AERO*) ;
int cannon_force_gravity(CANNON_AERO*) ;
int cannon_force_drag(CANNON_AERO*) ;
int cannon_force_lift(CANNON_AERO*) ;
int cannon_force_cross(CANNON_AERO*) ;
int cannon_collect_forces(CANNON_AERO*) ;
int cannon_integ_aero(CANNON_AERO*) ;
double cannon_impact_monte(CANNON_AERO*) ;
int cannon_monte_default_data(CANNON_AERO*) ;
int cannon_jet_control(CANNON_AERO*) ;

#ifdef __cplusplus
}
#endif
#endif
