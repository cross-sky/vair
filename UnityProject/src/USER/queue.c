#include "cominc.h"


uint8_t Que_create(uint8_t len, void* queDataBuf, QueueStruct* queue)
{
	queue->in = 0;
	queue->out = 0;
	queue->qlength = 0;
	queue->maxSize = len;
	queue->buff[0] = queDataBuf;
	return TRUE;
}

/*  
 * if full ,return 0; else return 1;  
 */  
uint8_t IsFull(QueueStruct* queue)  
{  
    return (queue->qlength >= queue->maxSize);  
} 

//具体数据地址需要外部获取，只能按照顺序取出，不能跳过取出
uint8_t Que_push(void* srcdata, uint8_t srcdataLen, QueueStruct* queue, void* queDataBuf)
{
	//void* queDataBuf
	if (IsFull(queue))
		return FALSE;
	//先用再+
	memcpy(queue->buff[queue->in], srcdata, srcdataLen);
	queue->dataLen[queue->in] = srcdataLen;
	queue->in = (queue->in+1)%queue->maxSize;
	queue->buff[queue->in] = queDataBuf;
	queue->qlength++;
	return TRUE;
}

/* if null return 1. else 0 */  
uint8_t IsEmpty(QueueStruct* queue)  
{  
	return (queue->qlength == 0);  
} 

uint8_t Que_queLength(QueueStruct* queue)  
{  
	return queue->qlength;  
} 

uint8_t Que_pop(QueueStruct* queue, void* dst)
{
	if (IsEmpty(queue))
		return FALSE;
	memcpy(dst, queue->buff[queue->out], queue->dataLen[queue->out]);
	queue->out = (queue->out+1)%queue->maxSize;
	queue->qlength--;
	return TRUE;
}

uint8_t Que_get(QueueStruct* queue, void* dst)
{
	if (IsEmpty(queue))
		return FALSE;
	memcpy(dst, queue->buff[queue->out], queue->dataLen[queue->out]);
	return TRUE;
}
