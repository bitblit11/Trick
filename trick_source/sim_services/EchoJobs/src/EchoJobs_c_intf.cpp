#include <stdio.h>
#include "sim_services/EchoJobs/include/EchoJobs.hh"

/* Global singleton pointer to the echo jobs class */
extern Trick::EchoJobs * the_ej ;

/*************************************************************************/
/* These routines are the "C" interface to echo jobs instrumentation     */
/*************************************************************************/

/**
 * @relates Trick::EchoJobs
 * @copydoc Trick::EchoJobs::echojobs_on
 * C wrapper for Trick::EchoJobs::echojobs_on
 */
extern "C" int echo_jobs_on() {
    if (the_ej != NULL) {
        return the_ej->echojobs_on() ;
    }
    return(0) ;
}

/**
 * @relates Trick::EchoJobs
 * @copydoc Trick::EchoJobs::echojobs_off
 * C wrapper for Trick::EchoJobs::echojobs_off
 */
extern "C" int echo_jobs_off() {
    if (the_ej != NULL) {
        return the_ej->echojobs_off() ;
    }
    return(0) ;
}
