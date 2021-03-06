/*
 * Receiver.h
 *
 *  Created on: Feb 15, 2013
 *      Author: ajm6611
 */

#ifndef RECEIVER_H_
#define RECEIVER_H_

#include "Dispatcher.h"
#include "Event.h"
#include "ReceiverType.h"
#include <list>

using namespace std;

class Event;
class Dispatcher;

class Receiver{
public:
	Receiver();
	virtual void notify(Event* ev);

	void setDispather(Dispatcher *dispatch){
		dispatcher = dispatch;
	}

	rec::ReceiverType getRecType() {
		return REC_TYPE;
	}

protected:
	std::list<Event*> eventList;
	Dispatcher* dispatcher;
	rec::ReceiverType REC_TYPE;

};
#endif /* RECEIVER_H_ */
