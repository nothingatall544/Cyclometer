/*
 * UpdateDisplayEvent.cpp
 *
 *  Created on: Feb 12, 2013
 *      Author: wkb6223
 */

#include "UpdateDisplayEvent.h"
#include "SevenSegmetController.h"
#include "EventType.h"

UpdateDisplayEvent::UpdateDisplayEvent(){
    EVENT_TYPE = ev::DISPLAY;
}

void UpdateDisplayEvent::setCurrent(double newCurrent){
	current = newCurrent;
}

void UpdateDisplayEvent::setAverage(double newAverage){
	average = newAverage;
}

void UpdateDisplayEvent::run(Receiver* ssc){
	if (ssc->getRecType() == rec::ssc){
		((SevenSegmetController*)ssc)->setDisplay(current, average);
	}
}
