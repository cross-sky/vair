#include "cominc.h" //要放在第一个位置
#include "unity.h"
#include "unity_fixture.h"

//#define QueueLength 10
TEST_GROUP(QueueTest);

uint16_t buf[QueueLength];
QueueStruct xQueue ;

void* getQueBufAddr(void)
{
	return &buf[(xQueue.in+1)%xQueue.maxSize];
}

TEST_SETUP(QueueTest)
{ 
	Que_create(QueueLength, (uint8_t *)&buf, &xQueue);
}

TEST_TEAR_DOWN(QueueTest)
{
}

TEST(QueueTest, pushAndPop)
{
	uint16_t srcData = 10, dscData=0;
	Que_push(&srcData, sizeof(uint16_t), &xQueue,getQueBufAddr());
	Que_pop(&xQueue, &dscData);
	TEST_ASSERT_EQUAL(10, dscData);
	srcData = 20;
	Que_push(&srcData, sizeof(uint16_t), &xQueue,getQueBufAddr());
	Que_pop(&xQueue, &dscData);
	TEST_ASSERT_EQUAL(20, dscData);
}




