#include "cominc.h"
#include "unity.h"
#include "unity_fixture.h"
#include "Stm32_ub_adc_spy.h"

TEST_GROUP(ADC_simpling);

ptrState externState;

StateStruct dstState;

TEST_SETUP(ADC_simpling)
{
	externState = BspAdc_getPtrStateAdc();
}

TEST_TEAR_DOWN(ADC_simpling)
{

}


TEST(ADC_simpling, OffStateAllDoneChangeToOnstate)
{
	dstState.state = STATE_UNDONE;
	dstState.runCount = 3;
	dstState.needRunCount = 3;
	dstState.cycleTime = 5;

	State_setDataProcessedFlag(externState,STATE_DONE);
	vADCDmaChannel1_ISR();

	State_ChangeState(externState, &dstState);
	vADCSimpling();	//没有执行这个.......
	TEST_ASSERT_EQUAL(STATE_UNDONE, State_getState(externState));
	TEST_ASSERT_EQUAL(4, State_getRunCount(externState));

	vADCSimpling();
	vADCDmaChannel1_ISR();
	vADCSimpling();
	vADCDmaChannel1_ISR();
	vADCSimpling();
	TEST_ASSERT_EQUAL(STATE_UNDONE, State_getState(externState));
	TEST_ASSERT_EQUAL(3, State_getRunCount(externState));
}

TEST(ADC_simpling, OffStateWhileDataUnprocessedRunCountWillNOtAdd)
{
	dstState.state = STATE_UNDONE;
	dstState.runCount = 4;
	dstState.needRunCount = 3;
	dstState.cycleTime = 5;

	State_setDataProcessedFlag(externState,STATE_UNDONE);
	vADCsetSingleInputFlag(STATE_DONE);

	State_ChangeState(externState, &dstState);
	vADCSimpling();
	TEST_ASSERT_EQUAL(dstState.runCount, State_getRunCount(externState));
}

TEST(ADC_simpling, OffStateWhileInputUndoneThenRunCountWillNOtAdd)
{
	dstState.state = STATE_UNDONE;
	dstState.runCount = 4;
	dstState.needRunCount = 3;
	dstState.cycleTime = 5;

	State_setDataProcessedFlag(externState,STATE_DONE);
	vADCsetSingleInputFlag(STATE_UNDONE);

	State_ChangeState(externState, &dstState);
	vADCSimpling();
	TEST_ASSERT_EQUAL(dstState.runCount, State_getRunCount(externState));
}

TEST(ADC_simpling, onStateChangeToOffState)
{
	dstState.state = STATE_DONE;
	dstState.runCount = 2;
	dstState.needRunCount = 3;
	dstState.cycleTime = 5;

	State_setDataProcessedFlag(externState,STATE_DONE);
	vADCsetSingleInputFlag(STATE_DONE);

	State_ChangeState(externState, &dstState);
	vADCSimpling();
	TEST_ASSERT_EQUAL(STATE_UNDONE, State_getState(externState));
}