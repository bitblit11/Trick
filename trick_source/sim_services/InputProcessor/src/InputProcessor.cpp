/* 
   PURPOSE: ( Handle the simulation command line args )

   REFERENCE: ( Trick Simulation Environment )

   ASSUMPTIONS AND LIMITATIONS: ( None )

   CLASS: ( N/A )

   LIBRARY DEPENDENCY: ( None )

   PROGRAMMERS: ( Keith Vetter LinCom 6/2003 ) */

/* 
 * $Id: InputProcessor.cpp 2316 2012-04-16 15:12:23Z alin $
 */

#include <iostream>
#include <string.h>

#include "sim_services/InputProcessor/include/InputProcessor.hh"
#include "sim_services/CommandLineArguments/include/command_line_protos.h"

Trick::InputProcessor * the_ip ;

Trick::InputProcessor::InputProcessor() {

    the_ip = this ;

}

int Trick::InputProcessor::process_sim_args() {

    int i ;
    int argc ;
    char ** argv ;

    argc = command_line_args_get_argc() ;
    argv = command_line_args_get_argv() ;
    input_file = command_line_args_get_input_file() ;

    /* Process all other calling arguments */
    for (i = 2; i < argc; i++) {

        /* 
         * If there are more than 2 calling arguments
         */

        if (!strncmp("-d", argv[i], (size_t) 2)) {
            /* Set the 'input verification only' and echo input flags */
            verify_input = 1 ;
        }
    }

    return(0) ;

}

int Trick::InputProcessor::shutdown() {
    return(0) ;
}

