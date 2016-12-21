#ifndef __QUEUE_H
#define __QUEUE_H

#include <stdint.h>
#include <string.h>

typedef struct 
{
	uint8_t in;
	uint8_t out;
	uint8_t qlength;
	uint8_t maxSize;
	uint8_t dataLen[10];
	//void* buff;
	void *buff[10];
}QueueStruct;

uint8_t Que_create(uint8_t len, void* queDataBuf, QueueStruct* queue);
uint8_t Que_push(void* data, uint8_t dataLen, QueueStruct* queue, void* queDataBuf);
uint8_t Que_pop(QueueStruct* queue, void* dst);
uint8_t Que_get(QueueStruct* queue, void* dst);
uint8_t Que_queLength(QueueStruct* queue);

#endif



