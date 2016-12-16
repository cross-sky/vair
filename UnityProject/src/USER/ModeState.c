#include "cominc.h"

pModeFun _modeFunTable[MODE_MAX];

ModeStateEnum _curMode=MODE_OFF, _newMode=MODE_OFF;
uint8_t _modeChangeFlag=0;

uint8_t getModeChangeFlag(void)
{
	return _modeChangeFlag;
}

void setModeChangeFlag(uint8_t newFlag)
{
	_modeChangeFlag = newFlag;
}

ModeStateEnum ModeState_getCurMode(void)
{
	return _curMode;
}

void ModeState_setCurMode(ModeStateEnum newMode)
{
	_curMode = newMode;
}

ModeStateEnum ModeState_getNewMode(void)
{
	setModeChangeFlag(0);
	return _newMode;
}

void ModeState_setNewMode(ModeStateEnum newMode)
{
	if (newMode == ModeState_getCurMode())
	{
		return;
	}
	if (newMode >= MODE_MAX)
	{
		return;
	}
	_newMode = newMode;
	setModeChangeFlag(1);
}

uint8_t ModeState_haveNewMode(void)
{
	return getModeChangeFlag();
}

void ModeState_changeMode(void)
{
	if (ModeState_haveNewMode())
	{
		ModeState_setCurMode(ModeState_getNewMode());
	}
}

void ModeState_runFunction(void)
{
	_modeFunTable[ModeState_getCurMode()]();
}

void ModeState_ModeFunOff(void)
{
	printf("off state\r\n");
}
void ModeState_ModeFunOn(void)
{
	printf("on state\r\n");
}
void ModeState_ModeFunHand(void)
{
	printf("hand state\r\n");
}

void ModeState_init(void)
{
	_modeFunTable[MODE_OFF] = ModeState_ModeFunOff;
	_modeFunTable[MODE_ON] = ModeState_ModeFunOn;
	_modeFunTable[MODE_HAND] = ModeState_ModeFunHand;
}