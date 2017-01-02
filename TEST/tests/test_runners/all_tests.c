#include "unity_fixture.h"

static void RunAllTests(void)
{
  RUN_TEST_GROUP(DataTest);
  RUN_TEST_GROUP(CoreStateTest);
  RUN_TEST_GROUP(QueueTest);
  RUN_TEST_GROUP(ADC_simpling);
  RUN_TEST_GROUP(BSP_cd4051);
  RUN_TEST_GROUP(INP_err);
  RUN_TEST_GROUP(User_IODetectErr);
  RUN_TEST_GROUP(INP_err);
  RUN_TEST_GROUP(ValveCalc);
}

int main(int argc, const char * argv[])
{
  return UnityMain(argc, argv, RunAllTests);
}
