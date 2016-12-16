#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(DataTest)
{
	RUN_TEST_CASE(DataTest, SetAndGetTemperature);
	RUN_TEST_CASE(DataTest, SetAndGetRelayState);
}