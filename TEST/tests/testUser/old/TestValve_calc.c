#include "cominc.h"
#include "unity.h"
#include "unity_fixture.h"

ValveStatus_t testValveData[ValveKindsMax];
ValveProcess_t *valveSigs;
ValveSig_t sig;

TEST_GROUP(ValveCalc);


TEST_SETUP(ValveCalc)
{
	ValveCalv_changeValveData(testValveData);
	 valveSigs = ValveCalc_getSigNodes();
}

TEST_TEAR_DOWN(ValveCalc)
{

}

TEST(ValveCalc, PopAndPushSig)
{
	ValveSig_t tsig;
	sig.code = -10;
	sig.sig = valveInit;
	sig.kindValue = ValveMainA;
	ValveCalc_pushSig(&sig);
	ValveCalc_popSig(&tsig);
	TEST_ASSERT_EQUAL(valveInit,tsig.sig);
}
