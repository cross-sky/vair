#include "cominc.h" //要放在第一个位置
#include "unity.h"
#include "unity_fixture.h"

#define Qlen 10
TEST_GROUP(QueueTest);

uint16_t buf[Qlen];
QueueStruct xQueue ;

TEST_SETUP(QueueTest)
{ 
	Que_create(Qlen, &buf, &xQueue);
}

TEST_TEAR_DOWN(QueueTest)
{
}

TEST(QueueTest, pushAndPop)
{
	uint16_t srcData = 10, dscData=0;
	Que_push(&srcData, sizeof(uint16_t), &xQueue);
	Que_pop(&xQueue, &dscData);
	TEST_ASSERT_EQUAL(10, dscData);
}



