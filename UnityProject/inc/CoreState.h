#ifndef __CORESTATE_H
#define __CORESTATE_H

void CoreState_setFunChangeFlag(StateEnum newState);
void CoreState_setFunSwitchState(StateEnum newState);
StateEnum CoreState_getFunSwitchState(void);

void CoreState_coreFun(void);
void CoreState_init(void);
void CoreState_setNewStateFlag(uint8_t newFlag);
void CoreState_setNewState(SigFunState newState);
#endif

