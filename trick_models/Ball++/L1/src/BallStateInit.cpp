/********************************* TRICK HEADER *******************************
PURPOSE:
    (Ball::state_init performs the following:
        - passes the input position vector to the output vector
        - xforms the input ball speed and trajectory elevation into a
          velocity vector.)
REFERENCE:
    (((Bailey, R.W, and Paddock, E.J.)
      (Trick Simulation Environment) (NASA:JSC #37943)
      (JSC/Engineering Directorate/Automation, Robotics and Simulation Division)
      (March 1997)))
ASSUMPTIONS AND LIMITATIONS:
    ((2 dimensional space)
     (Positive X is horizontal to the right)
     (Positive Y is vertical and up))
CLASS:
    (initialization)
LIBRARY DEPENDENCY:
    ((BallStateInit.o))
PROGRAMMERS:
    (((Robert W. Bailey) (Sweet Systems Inc) (March 1997) (Tutorial Lesson 1))
     ((Edwin Z. Crues)(Titan Systems Corp.)(Jan 2002)(Crude C++ translation)))
*******************************************************************************/

/*
 * $Id: BallStateInit.cpp 627 2010-03-30 16:21:13Z wwoodard $
 *
 * Revision 5.1  2004-08-05 13:06:22-05  lin
 * Bump
 *
 * Revision 4.1  2003/10/21 21:49:41  lin
 * Bump version number for 04
 *
 * Revision 1.2  2002/10/07 15:15:56  lin
 * Add rcs version info to all trick_models files
 *
 */

/* System include files. */
#include <math.h>

/* Model include files. */
#include "../include/Ball.hh"

     /* ENTRY POINT */
int Ball::state_init() /* RETURN: -- Always return zero. */
{

   /* GET SHORHAND NOTATION FOR DATA STRUCTURES */
   BallStateInput  * state_in  = &(this->state.input);
   BallStateOutput * state_out = &(this->state.output);

   /* TRANSFER INPUT POSITION STATES TO OUTPUT POSITION STATES */
   state_out->position[0] = state_in->position[0];  /* X state */
   state_out->position[1] = state_in->position[1];  /* Y state */

   /* TRANSFER INPUT SPEED AND ELEVATION INTO THE VELOCITY VECTOR */
   state_out->velocity[0] =   state_in->speed * cos( state_in->elevation ); /* X velocity */
   state_out->velocity[1] =   state_in->speed * sin( state_in->elevation ); /* Y velocity */

   /* RETURN */
   return( 0 );

}

