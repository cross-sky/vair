#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(ModeStateTest)
{
	RUN_TEST_CASE(ModeStateTest, OffsetOnMode);
	RUN_TEST_CASE(ModeStateTest, OffsetHandMode);
	RUN_TEST_CASE(ModeStateTest, OffToOnToOffMode);
}



