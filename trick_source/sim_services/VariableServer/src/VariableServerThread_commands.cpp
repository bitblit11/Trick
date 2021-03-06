/*
 * $Id: VariableServerThread.cpp 432 2009-12-07 22:10:08Z hchen $
 */

#include <string.h>
#include <iostream>
#include "sim_services/VariableServer/include/VariableServer.hh"
#include "sim_services/VariableServer/include/variable_server_message_types.h"
#include "sim_services/MemoryManager/include/memorymanager_c_intf.h"
#include "trick_utils/comm/include/tc_proto.h"
#include "sim_services/Executive/include/exec_proto.h"
#include "sim_services/CommandLineArguments/include/command_line_protos.h"
#include "trick_utils/units/include/Unit.hh"
#include "sim_services/Message/include/message_proto.h"
#include "sim_services/include/TrickConstant.hh"
#include "sim_services/Sie/include/sie_c_intf.h"
#include <stdlib.h> /* calloc, free */

int Trick::VariableServerThread::bad_ref_int = 0 ;

REF2* Trick::VariableServerThread::make_error_ref(std::string in_name) {
    REF2* new_ref;
    new_ref = (REF2*)calloc(1, sizeof(REF2));
    new_ref->reference = strdup(in_name.c_str()) ;
    new_ref->units = NULL ;
    new_ref->address = (char *)&bad_ref_int ;
    new_ref->attr = (ATTRIBUTES*)calloc(1, sizeof(ATTRIBUTES)) ;
    new_ref->attr->type = TRICK_NUMBER_OF_TYPES ;
    new_ref->attr->units = (char *)"--" ;
    new_ref->attr->size = sizeof(int) ;
    return new_ref;
}

int Trick::VariableServerThread::var_add(std::string in_name) {

    VariableReference * new_var ;
    REF2 * new_ref ;

    new_ref = ref_attributes(const_cast<char*>(in_name.c_str())) ;

    if ( new_ref == NULL ) {
        message_publish(MSG_ERROR, "Variable Server could not find variable %s.\n", in_name.c_str());
        new_ref = make_error_ref(in_name);
    } else if ( new_ref->attr ) {
        if ( new_ref->attr->type == TRICK_STRUCTURED ) {
            message_publish(MSG_ERROR, "Variable Server: var_add cant add \"%s\" because its a composite variable.\n", in_name.c_str());
            // Replace the REF2 object we got from ref_attributes with an error-ref.
            if (new_ref->attr) {
                free(new_ref->attr);
            }
            free(new_ref);
            new_ref = make_error_ref(in_name);
        }
    } else {
        message_publish(MSG_ERROR, "Variable Server: BAD MOJO - Missing ATTRIBUTES.");
        new_ref = make_error_ref(in_name);
    }

    new_var = new VariableReference(new_ref) ;
    vars.push_back(new_var) ;

    return(0) ;
}

int Trick::VariableServerThread::var_add(std::string var_name, std::string units_name) {
    var_add(var_name) ;
    var_units(var_name, units_name) ;
    return(0) ;
}

int Trick::VariableServerThread::var_remove(std::string in_name) {

    unsigned int ii ;
    for ( ii = 0 ; ii < vars.size() ; ii++ ) {
        std::string var_name = vars[ii]->ref->reference;
        if ( ! var_name.compare(in_name) ) {
            vars.erase(vars.begin() + ii) ;
            break ;
        }
    }

    return(0) ;

}

int Trick::VariableServerThread::var_units(std::string var_name, std::string units_name) {

    unsigned int ii ;

    for ( ii = 0 ; ii < vars.size() ; ii++ ) {
        if ( ! std::string(vars[ii]->ref->reference).compare(var_name) ) {
            if (!units_name.compare("xx")) {
                vars[ii]->ref->units = strdup(vars[ii]->ref->attr->units);
            }
            else {
                Unit orig_units(vars[ii]->ref->attr->units) ;
                try {
                    vars[ii]->conversion_factor = orig_units.Conversion_to(units_name.c_str()) ;
                    vars[ii]->ref->units = strdup(units_name.c_str());
                }
                catch (Unit::CONVERSION_ERROR & ce_err ) {
                    message_publish(MSG_ERROR, "Variable Server Error: var_units Units conversion error for \"%s\".\n",var_name.c_str());
                    return(-1) ;
                }
            }
        }
    }
    return(0) ;
}

int Trick::VariableServerThread::var_exists(std::string in_name) {

    char buf1[5] ;
    bool error = false ;

    unsigned int msg_type ;
    REF2* var_ref = ref_attributes(const_cast<char*>(in_name.c_str()));

    if ( var_ref == (REF2*)NULL ) {
        error = true;
    }

    if (binary_data) {
        /* send binary 1 or 0 */
        msg_type = VS_VAR_EXISTS ;
        memcpy(buf1, &msg_type , sizeof(msg_type)) ;

        buf1[4] = (error==false);

        if (debug >= 2) {
            message_publish(MSG_DEBUG, "%p tag=<%s> var_server sending 1 binary byte\n", &connection, connection.client_tag);
        }
        tc_write(&connection, (char *) buf1, 5);
    } else {
        /* send ascii "1" or "0" */
        sprintf(buf1, "%d\t%d\n", VS_VAR_EXISTS, (error==false));
        if (debug >= 2) {
            message_publish(MSG_DEBUG, "%p tag=<%s> var_server sending:", &connection, connection.client_tag) ;
            message_publish(MSG_NORMAL, "%s\n", buf1);
        }
        tc_write(&connection, (char *) buf1, strlen(buf1));
    }

    return(0) ;
}

int Trick::VariableServerThread::var_clear() {
    vars.clear() ;
    return(0) ;
}

int Trick::VariableServerThread::var_send() {
    copy_sim_data();
    write_data();
    return(0) ;
}

int Trick::VariableServerThread::var_cycle(double in_rate) {
    update_rate = in_rate ;
    cycle_tics = (long long)(update_rate * exec_get_time_tic_value()) ;
    return(0) ;
}

bool Trick::VariableServerThread::get_pause() {
    return pause_cmd ;
}

void Trick::VariableServerThread::set_pause( bool on_off) {
    pause_cmd = on_off ;
}

int Trick::VariableServerThread::var_exit() {
    exit_cmd = true ;
    return(0) ;
}

int Trick::VariableServerThread::var_debug(int level) {
    debug = level ;
    return(0) ;
}

int Trick::VariableServerThread::var_ascii() {
    binary_data = 0 ;
    return(0) ;
}

int Trick::VariableServerThread::var_binary() {
    binary_data = 1 ;
    return(0) ;
}

int Trick::VariableServerThread::var_binary_nonames() {
    binary_data = 1 ;
    binary_data_nonames = 1 ;
    return(0) ;
}

int Trick::VariableServerThread::var_retry_bad_ref() {
    retry_bad_ref = 1 ;
    return(0) ;
}

int Trick::VariableServerThread::var_set_copy_mode(int mode) {
    if ( mode >= VS_COPY_ASYNC and mode <= VS_COPY_TOP_OF_FRAME ) {
        copy_mode = (VS_COPY_MODE)mode ;
        if ( copy_mode == VS_COPY_SCHEDULED ) {
            long long sim_time_tics ;
            sim_time_tics = exec_get_time_tics() ;
            // round the next call time to a multiple of the cycle
            sim_time_tics -= sim_time_tics % cycle_tics ;
            next_tics = sim_time_tics + cycle_tics ;

            sim_time_tics = exec_get_freeze_time_tics() ;
            // round the next call time to a multiple of the cycle
            sim_time_tics -= sim_time_tics % cycle_tics ;
            freeze_next_tics = sim_time_tics + cycle_tics ;

        } else {
            next_tics = TRICK_MAX_LONG_LONG ;
        }
        return 0 ;
    }
    return -1 ;
}

int Trick::VariableServerThread::var_set_write_mode(int mode) {
    if ( mode >= VS_WRITE_ASYNC and mode <= VS_WRITE_WHEN_COPIED ) {
        write_mode = (VS_WRITE_MODE)mode ;
        return 0 ;
    }
    return -1 ;
}

int Trick::VariableServerThread::var_sync(int mode) {

    switch (mode) {
        case 1:
            var_set_copy_mode(VS_COPY_SCHEDULED) ;
            var_set_write_mode(VS_WRITE_ASYNC) ;
            break ;
        case 2:
            var_set_copy_mode(VS_COPY_SCHEDULED) ;
            var_set_write_mode(VS_WRITE_WHEN_COPIED) ;
            break ;
        case 0:
        default:
            var_set_copy_mode(VS_COPY_ASYNC) ;
            var_set_write_mode(VS_WRITE_ASYNC) ;
            break ;
    }

    return 0 ;
}

int Trick::VariableServerThread::var_set_frame_multiple(unsigned int mult) {
    frame_multiple = mult ;
    return 0 ;
}

int Trick::VariableServerThread::var_set_frame_offset(unsigned int offset) {
    frame_offset = offset ;
    return 0 ;
}

int Trick::VariableServerThread::var_set_freeze_frame_multiple(unsigned int mult) {
    freeze_frame_multiple = mult ;
    return 0 ;
}

int Trick::VariableServerThread::var_set_freeze_frame_offset(unsigned int offset) {
    freeze_frame_offset = offset ;
    return 0 ;
}

int Trick::VariableServerThread::var_byteswap(bool on_off) {
    byteswap = on_off ;
    return(0) ;
}

bool Trick::VariableServerThread::get_send_stdio() {
    return send_stdio ;
}

int Trick::VariableServerThread::set_send_stdio(bool on_off) {
    send_stdio = on_off ;
    return(0) ;
}

int Trick::VariableServerThread::var_signal() {

    message_publish(MSG_ERROR,"Variable Server Error: var_signal is currently not implemented.\n") ;

    return(0) ;
}

int Trick::VariableServerThread::var_multicast(bool on_off) {

    multicast = on_off ;

    message_publish(MSG_ERROR, "Variable Server Error: var_multicast is currently not implemented.\n") ;

    return(0) ;
}

int Trick::VariableServerThread::send_list_size() {
    char buf1[12] ;
    unsigned int msg_type ;
    int var_count;

    // send number of variables
    var_count = vars.size();
    if (binary_data) {
        // send in the binary message header format:
        // <message_indicator><message_size><number_of_variables>
        msg_type = VS_LIST_SIZE;
        memcpy(buf1, &msg_type , sizeof(msg_type)) ;

        memset(&(buf1[4]), 0, sizeof(int)); // message size = 0
        memcpy(&(buf1[8]), &var_count, sizeof(var_count));

        if (debug >= 2) {
            message_publish(MSG_DEBUG, "%p tag=<%s> var_server sending %d event variables\n", &connection, connection.client_tag, var_count);
        }
        tc_write(&connection, (char *) buf1, 12);
    } else {
        // ascii
        sprintf(buf1, "%d\t%d\n", VS_LIST_SIZE, var_count);
        if (debug >= 2) {
            message_publish(MSG_DEBUG, "%p tag=<%s> var_server sending number of event variables:", &connection, connection.client_tag) ;
            message_publish(MSG_NORMAL, "%s\n", buf1);
        }
        tc_write(&connection, (char *) buf1, strlen(buf1));
    }

    return 0 ;
}

int Trick::VariableServerThread::transmit_file(std::string sie_file) {
    const unsigned int packet_size = 4095 ;
    FILE * fp ;
    unsigned int file_size ;
    unsigned int current_size = 0 ;
    unsigned int bytes_read ;
    char buffer[packet_size] ;
    int ret ;

    if (debug >= 2) {
        message_publish(MSG_DEBUG,"%p tag=<%s> var_server opening %s.\n", &connection, connection.client_tag, sie_file.c_str()) ;
    }

    if ((fp = fopen(sie_file.c_str() , "r")) == NULL ) {
        message_publish(MSG_ERROR,"Variable Server Error: Cannot open %s.\n", sie_file.c_str()) ;
        sprintf(buffer, "%d\t-1\n", VS_SIE_RESOURCE) ;
        tc_write(&connection , buffer , strlen(buffer)) ;
        return(-1) ;
    }

    fseek(fp , 0L, SEEK_END) ;
    file_size = ftell(fp) ;

    sprintf(buffer, "%d\t%d\n" , VS_SIE_RESOURCE, file_size) ;
    tc_write(&connection , buffer , strlen(buffer)) ;
    rewind(fp) ;

    // Switch to blocking writes since this could be a large transfer.
    if (tc_blockio(&connection, TC_COMM_BLOCKIO)) {
        message_publish(MSG_DEBUG,"Variable Server Error: Failed to set TCDevice to TC_COMM_BLOCKIO.\n");
    }

    while ( current_size < file_size ) {
        bytes_read = fread(buffer , 1 , packet_size , fp) ;
        ret = tc_write(&connection , buffer , bytes_read ) ;
        if (ret != (int)bytes_read) {
            message_publish(MSG_ERROR,"Variable Server Error: Failed to send SIE file.\n", sie_file.c_str()) ;
            return(-1);
        }
        current_size += bytes_read ;
    }

    // Switch back to non-blocking writes.
    if (tc_blockio(&connection, TC_COMM_NOBLOCKIO)) {
        message_publish(MSG_ERROR,"Variable Server Error: Failed to set TCDevice to TC_COMM_NOBLOCKIO.\n");
        return(-1);
    }

    return(0) ;
}

int Trick::VariableServerThread::send_file(std::string file_name) {
    return transmit_file(file_name) ;
}

int Trick::VariableServerThread::send_sie_resource() {
    sie_print_xml() ;
    return transmit_file(std::string(command_line_args_get_default_dir()) + "/S_sie.resource") ;
}

int Trick::VariableServerThread::send_sie_class() {
    sie_class_attr_map_print_xml() ;
    return transmit_file(std::string(command_line_args_get_default_dir()) + "/" + "S_sie_class.xml") ;
}

int Trick::VariableServerThread::send_sie_enum() {
    sie_enum_attr_map_print_xml() ;
    return transmit_file(std::string(command_line_args_get_default_dir()) + "/" + "S_sie_enum.xml") ;
}

int Trick::VariableServerThread::send_sie_top_level_objects() {
    sie_top_level_objects_print_xml() ;
    return transmit_file(std::string(command_line_args_get_default_dir()) + "/" + "S_sie_top_level_objects.xml") ;
}
