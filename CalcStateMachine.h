/*
 * CalcStateMachine.h
 *
 *  Created on: Feb 19, 2013
 *      Author: wkb6223
 */

#ifndef CALCSTATEMACHINE_H_
#define CALCSTATEMACHINE_H_

#include "StateMachine.h"

class CalcStateMachine:public StateMachine{
public:
	CalcStateMachine(Dispatcher* dispatcher);
	void notify(Event* ev);

};

#endif /* CALCSTATEMACHINE_H_ */
