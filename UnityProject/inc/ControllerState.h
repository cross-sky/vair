#ifndef __CONTROLLERSTATE_H
#define __CONTROLLERSTATE_H


void ControllerState_sendSig(FunSigState newSig);
FunSigState ControllerState_getSig(void);
void ControllerState_setNewFunc(FunSigState newState);

StateEnum ControllerState_getFunState(void);

void ControllerState_run(void);
void ControllerState_init(void);
#endif


