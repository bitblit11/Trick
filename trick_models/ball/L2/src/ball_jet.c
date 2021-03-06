/********************************* TRICK HEADER *******************************
PURPOSE:
    (Ball model reaction control jet job.)
REFERENCE:
    (((Bailey, R.W, and Paddock, E.J.)
      (Trick Simulation Environment) (NASA:JSC #37943)
      (JSC/Engineering Directorate/Automation, Robotics and Simulation Division)
      (March 1997)))
ASSUMPTIONS AND LIMITATIONS:
    ((2 jets)
     (jet 0 fires down)
     (jet 1 fires up))
CLASS:
    (effector)
LIBRARY DEPENDENCY:
    ((ball_jet.o))
PROGRAMMERS:
    (((Your Name) (Company Name) (Date) (Trick tutorial)))
*******************************************************************************/

/*
 * $Log: ball_jet.c,v $
 * Revision 5.2  2005-01-31 15:45:48-06  lin
 * remove "register" keyword
 *
 * Revision 5.1  2004-08-05 13:06:29-05  lin
 * Bump
 *
 * Revision 4.1  2003/10/21 21:49:34  lin
 * Bump version number for 04
 *
 * Revision 3.2  2002/10/07 15:16:06  lin
 * Add rcs version info to all trick_models files
 *
 */

#include "../include/ball_jet.h"

int ball_jet(
               /* RETURN: -- Always return zero */
  BJET * J ,   /* INOUT:  -- Ball reaction control jet parameters */
  Flag * com ) /* IN:     -- Ball jet commands from the flight software */
{

BJET_IN * JI = &(J->input) ;
BJET_OUT * JO = &(J->output) ;

#define FIRE_UP 0
#define FIRE_DOWN 1

    /* ZERO RESULTING FORCE ON BALL */
    JO->force[FIRE_UP] = 0.0 ;
    JO->force[FIRE_DOWN] = 0.0 ;

    if( com[FIRE_UP] == On && JI->jet_fail[FIRE_UP] == No )
        JO->force[1] = JI->force[FIRE_UP] ;
    if( com[FIRE_DOWN] == On && JI->jet_fail[FIRE_DOWN] == No )
        JO->force[1] = JI->force[FIRE_DOWN] ;

    return( 0 ) ;
}

