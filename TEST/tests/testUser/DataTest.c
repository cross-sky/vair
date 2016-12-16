#include "cominc.h" //要放在第一个位置
#include "unity.h"
#include "unity_fixture.h"


TEST_GROUP(DataTest);

TEST_SETUP(DataTest)
{
}

TEST_TEAR_DOWN(DataTest)
{
}

TEST(DataTest, SetAndGetTemperature)
{
	uint16_t boxT=120, WarmT=150;
	Data_setTargetBoxT(boxT);
	TEST_ASSERT_EQUAL(boxT, Data_getTargetBoxT());
}

void checkRelayState(RelayBits relayBit, StateEnum state)
{
	Data_setRelayState(relayBit, state);
	TEST_ASSERT_EQUAL(state, Data_getRelayState(relayBit));
}

TEST(DataTest, SetAndGetRelayState)
{
	//checking relay set and clear 
	checkRelayState(Relay01Box, STATE_ON);
	checkRelayState(Relay02Warm, STATE_ON);
	checkRelayState(Relay03, STATE_ON);
	checkRelayState(Relay04, STATE_ON);

	checkRelayState(Relay01Box, STATE_OFF);
	checkRelayState(Relay02Warm, STATE_OFF);
	checkRelayState(Relay03, STATE_OFF);
	checkRelayState(Relay04, STATE_OFF);
}