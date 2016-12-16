#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(QueueTest)
{
	RUN_TEST_CASE(QueueTest, pushAndPop);
}
