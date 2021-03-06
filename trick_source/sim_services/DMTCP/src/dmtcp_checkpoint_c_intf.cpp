/*
 * $Id: dmtcp_checkpoint_c_intf.cpp 2475 2012-06-25 16:19:26Z mbhatta $
 */

/**
 * @file dmtcp_checkpoint_c_intf.cpp 
 */

#include <iostream>

#ifdef _DMTCP
#include "dmtcpaware.h"
#endif

#include "sim_services/DMTCP/include/DMTCP.hh"

/** Global singleton pointer to DMTCP */
extern Trick::DMTCP * the_dmtcp ;

#ifdef _DMTCP
/**
 * @relates Trick::DMTCP
 * @copydoc Trick::DMTCP::dmtcpIsEnabled()
 */
extern "C" int dmtcp_is_enabled() {
    return dmtcpIsEnabled() ;
}

/**
 * @relates Trick::DMTCP
 * @copydoc Trick::DMTCP::dmtcp_pre_checkpoint()
 */
extern "C" void dmtcp_pre_checkpoint() {
    the_dmtcp->pre() ;
}

/**
 * @relates Trick::DMTCP
 * @copydoc Trick::DMTCP::dmtcp_post_checkpoint()
 */
extern "C" void dmtcp_post_checkpoint() {
    the_dmtcp->post() ;
}

/**
 * @relates Trick::DMTCP
 * @copydoc Trick::DMTCP::restart()
 */
extern "C" void dmtcp_restart() {
    the_dmtcp->restart() ;
}

/**
 * @relates Trick::DMTCP
 * @copydoc Trick::DMTCP::call_dmtcp()
 */
extern "C" int call_dmtcp() {
    the_dmtcp->call_dmtcp();
}

/**
 * @relates Trick::DMTCP
 * @copydoc Trick::DMTCP::dmtcpSetCheckpointNow()
 */
extern "C" void dmtcp_set_checkpoint_now() {
    the_dmtcp->dmtcpSetCheckpointNow() ;
}

/**
 * @relates Trick::DMTCP
 * @copydoc Trick::DMTCP::dmtcpJobQueue()
 */
extern "C" void dmtcp_job_queue( std::string file_name ) {
    the_dmtcp->dmtcpJobQueue( file_name );
}
#endif
