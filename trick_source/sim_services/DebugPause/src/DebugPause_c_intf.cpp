#include <stdio.h>
#include "sim_services/DebugPause/include/DebugPause.hh"

/* Global singleton pointer to the echo jobs class */
extern Trick::DebugPause * the_debug_pause ;

/*************************************************************************/
/* These routines are the "C" interface to echo jobs instrumentation     */
/*************************************************************************/

/**
 * @relates Trick::DebugPause
 * @copydoc Trick::DebugPause::debug_pause_on
 * C wrapper for Trick::DebugPause::debug_pause_on
 */
extern "C" int debug_pause_on() {
    if (the_debug_pause != NULL) {
        return the_debug_pause->debug_pause_on() ;
    }
    return(0) ;
}

/**
 * @relates Trick::DebugPause
 * @copydoc Trick::DebugPause::debug_pause_off
 * C wrapper for Trick::DebugPause::debug_pause_off
 */
extern "C" int debug_pause_off() {
    if (the_debug_pause != NULL) {
        return the_debug_pause->debug_pause_off() ;
    }
    return(0) ;
}

extern "C" int debug_signal() {
    if (the_debug_pause != NULL) {
        return the_debug_pause->debug_signal() ;
    }
    return(0) ;
}
