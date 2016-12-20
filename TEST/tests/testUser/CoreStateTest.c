#include "cominc.h" //要放在第一个位置
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(CoreStateTest);

TEST_SETUP(CoreStateTest)
{
	RunFunction_init();
	CoreState_init();
}

TEST_TEAR_DOWN(CoreStateTest)
{
}

TEST(CoreStateTest, offToOn)
{
	CoreState_setNewStateFlag(1);
	CoreState_setNewState(SIG_FUN_ON);

	CoreState_coreFun();
	TEST_ASSERT_EQUAL(FUN_STATE_INIT, CoreState_getFunSwitchState());
	CoreState_coreFun();
	TEST_ASSERT_EQUAL(FUN_STATE_RUN, CoreState_getFunSwitchState());
}
