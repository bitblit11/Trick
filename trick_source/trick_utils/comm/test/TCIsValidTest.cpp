/*
 * $Id: TCIsValidTest.cpp 3368 2013-12-19 22:34:06Z jpenn1 $
 */

#include <gtest/gtest.h>

#include "trick_utils/comm/include/tc.h"
#include "trick_utils/comm/include/tc_proto.h"
#include "trick_utils/comm/include/attributes.h"
#include "trick_utils/comm/include/hs_msg.h"
#include "trick_utils/comm/include/trick_byteswap.h"
#include "trick_utils/comm/include/trick_error_hndlr.h"

class TCIsValidTest : public testing::Test {

   protected:
      TCIsValidTest(){}
      ~TCIsValidTest(){}

      TCDevice* device;

      void SetUp(){

         device = (TCDevice *) malloc(sizeof(TCDevice));
         memset( (void *)device,'\0',sizeof(TCDevice) );

         device->socket = 1;
      }

      void TearDown(){
   
         free(device);
      }
};

TEST_F( TCIsValidTest, testNullDevice ) {

   int tcisvalid_status = tc_isValid( NULL );

   EXPECT_EQ( tcisvalid_status, 0 );
} 

TEST_F( TCIsValidTest, testInvalidSocket ) {

   device->socket = TRICKCOMM_INVALID_SOCKET;

   int tcisvalid_status = tc_isValid( device );

   EXPECT_EQ( tcisvalid_status, 0 );
} 

TEST_F( TCIsValidTest, testValidSocket ) {

   int tcisvalid_status = tc_isValid( device );

   EXPECT_EQ( tcisvalid_status, 0 );
} 

