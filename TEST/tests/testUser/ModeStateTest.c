#include "cominc.h" //要放在第一个位置
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(ModeStateTest);

void ChangeToMode(ModeStateEnum newMode)
{
	ModeState_setNewMode(newMode);
	ModeState_changeMode();
	ModeState_runFunction();
}


TEST_SETUP(ModeStateTest)
{ 
	ModeState_init();
	ChangeToMode(MODE_OFF);
}

TEST_TEAR_DOWN(ModeStateTest)
{
}

TEST(ModeStateTest, OffsetOnMode)
{
	ChangeToMode(MODE_ON);
	TEST_ASSERT_EQUAL(MODE_ON, ModeState_getCurMode());
}

TEST(ModeStateTest, OffsetHandMode)
{
	ChangeToMode(MODE_HAND);
	TEST_ASSERT_EQUAL(MODE_HAND, ModeState_getCurMode());
}

TEST(ModeStateTest, OffToOnToOffMode)
{
	ChangeToMode(MODE_ON);
	ChangeToMode(MODE_OFF);
	TEST_ASSERT_EQUAL(MODE_OFF, ModeState_getCurMode());
}





