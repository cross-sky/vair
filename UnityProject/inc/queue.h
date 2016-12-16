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
	uint8_t dataLen;
	void* buff;
}QueueStruct;

uint8_t  Que_create(uint16_t len, void* data, QueueStruct* queue);
uint8_t Que_push(void* data, uint16_t dataLen, QueueStruct* queue);
uint8_t Que_pop(QueueStruct* queue, void* dst);


#endif



