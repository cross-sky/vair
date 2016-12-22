#include "cominc.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(BSP_cd4051);

ptrState externState;

StateStruct dstState;

ptrInputProcessStruct dataInp;
TEST_SETUP(BSP_cd4051)
{
	externState = BspAdc_getPtrStateCd4051();
	dataInp = INP_getDataInput();
}

TEST_TEAR_DOWN(BSP_cd4051)
{

}

TEST(BSP_cd4051, OffStateAllDoneChangeToOnstate)
{
	dstState.state = STATE_UNDONE;
	dstState.runCount = 8;
	dstState.needRunCount = 8;
	dstState.cycleTime = 10;

	State_setDataProcessedFlag(externState,STATE_DONE);

	State_ChangeState(externState, &dstState);
	vCd4051Simpling();

	TEST_ASSERT_EQUAL(STATE_UNDONE, State_getState(externState));
	TEST_ASSERT_EQUAL(9, State_getRunCount(externState));

	vCd4051Simpling();
	TEST_ASSERT_EQUAL(STATE_DONE, State_getState(externState));
	TEST_ASSERT_EQUAL(1, State_getRunCount(externState));
}

TEST(BSP_cd4051, simpling40Times)
{
	uint8_t i;
	dstState.state = STATE_UNDONE;
	dstState.runCount = 0;
	dstState.needRunCount = CDinMax*ADC_NeedRunCount;
	dstState.cycleTime = 100;

	State_ChangeState(externState, &dstState);
	
	for(i=0;i<ADC_NeedRunCount;i++)
	{
		dataInp->dataCd4051[i]=0;
	}

	for (i=0;i<dstState.needRunCount;i++)
	{
		CD4051_startSimple(externState);
		State_addRunCount(externState);
	}

	for (i=0;i<ADC_NeedRunCount;i++)
	{
		TEST_ASSERT_EQUAL(0xff, dataInp->dataCd4051[i]);
	}
}
