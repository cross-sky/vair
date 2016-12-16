#ifndef __MODE_STATE_H
#define __MODE_STATE_H

typedef enum {
	MODE_OFF = 0,
	MODE_ON,
	MODE_HAND,
	MODE_MAX
}ModeStateEnum;

typedef void (*pModeFun)(void);

void ModeState_setNewMode(ModeStateEnum newMode);
uint8_t ModeState_haveNewMode(void);
void ModeState_changeMode(void);
void ModeState_runFunction(void);
ModeStateEnum ModeState_getCurMode(void);
void ModeState_init(void);
#endif // __MODE_STATE_H



