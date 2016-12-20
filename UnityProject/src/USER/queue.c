#include "cominc.h"

uint8_t Que_create(uint8_t len, void* data, QueueStruct* queue)
{
	queue->in = 0;
	queue->out = 0;
	queue->qlength = 0;
	queue->maxSize = len;
	queue->buff = data;
	return TRUE;
}

/*  
 * if full ,return 0; else return 1;  
 */  
int IsFull(QueueStruct* queue)  
{  
    return (queue->qlength >= queue->maxSize);  
} 

uint8_t Que_push(void* data, uint16_t dataLen, QueueStruct* queue)
{
	if (IsFull(queue))
		return FALSE;
	//ÏÈÓÃÔÙ+
	memcpy(queue->buff, data, dataLen);
	queue->dataLen = dataLen;
	queue->in = (queue->in+1)%queue->maxSize;
	queue->qlength++;
	return TRUE;
}

/* if null return 1. else 0 */  
int IsEmpty(QueueStruct* queue)  
{  
	return (queue->qlength == 0);  
} 

uint8_t Que_pop(QueueStruct* queue, void* dst)
{
	if (IsEmpty(queue))
		return FALSE;
	memcpy(dst, queue->buff, queue->dataLen);
	queue->out = (queue->out+1)%queue->maxSize;
	queue->qlength--;
	return TRUE;
}

uint8_t Que_get(QueueStruct* queue, void* dst)
{
	if (IsEmpty(queue))
		return FALSE;
	memcpy(dst, queue->buff, queue->dataLen);
	return TRUE;
}
