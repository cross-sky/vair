#include "unity_fixture.h"

static void RunAllTests(void)
{
  RUN_TEST_GROUP(DataTest);
  RUN_TEST_GROUP(CoreStateTest);
  RUN_TEST_GROUP(QueueTest);
  //RUN_TEST_GROUP(ModeStateTest);
}

int main(int argc, const char * argv[])
{
  return UnityMain(argc, argv, RunAllTests);
}
