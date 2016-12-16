#include "cominc.h" //要放在第一个位置
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(ControllerStateTest);

TEST_SETUP(ControllerStateTest)
{
	ControllerState_init();
}

TEST_TEAR_DOWN(ControllerStateTest)
{
}

TEST(ControllerStateTest, ChangeFun)
{
	//ControllerState_setCurrentState(FUN_ON);
	//TEST_ASSERT_EQUAL(FUN_ON, ControllerState_getCurrentState());

	//ControllerState_setNewFunc(FUN_ON);
	//TEST_ASSERT_EQUAL(fun_on, ControllerState_getCurFunc());
	//
}

TEST(ControllerStateTest, ChangeFunAndCheckChangeState)
{
	ControllerState_run();
	TEST_ASSERT_EQUAL(FUN_STATE_RUN, ControllerState_getFunState());

	ControllerState_sendSig(SIG_FUN_ON);
	ControllerState_run();
	TEST_ASSERT_EQUAL(FUN_STATE_INIT, ControllerState_getFunState());

	ControllerState_run();
	TEST_ASSERT_EQUAL(FUN_STATE_RUN, ControllerState_getFunState());

	ControllerState_sendSig(SIG_FUN_NULL);
	ControllerState_run();
	TEST_ASSERT_EQUAL(FUN_STATE_RUN, ControllerState_getFunState());
}



