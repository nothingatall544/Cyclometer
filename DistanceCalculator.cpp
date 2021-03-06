/*
 * DistanceCalculator.cpp
 *
 *  Created on: Feb 19, 2013
 *      Author: wkb6223
 */

#include "DistanceCalculator.h"

#include "PulseEvent.h"
#include "SetKilometerEvent.h"
#include "UpdateDisplayDistanceEvent.h"
#include "TireSizeEvent.h"
#include "UpdateDistanceEvent.h"

#include <pthread.h>
#include <unistd.h>

DistanceCalculator::DistanceCalculator(Dispatcher* dispatch){
	REC_TYPE = rec::dc;
	setUp = false;
	calc = true;
	totalDist = 0.0;
	DistanceCalculator::setDispatcher(dispatch);
	sub(ev::PULSES2, this);
	sub(ev::TIRE_SIZE2, this);
	sub(ev::KILO2, this);
	sub(ev::CALC_OFF2, this);
	sub(ev::CALC_ON2, this);
}

void DistanceCalculator::addPulse(int pulses){
	if (calc){
		totalDist = totalDist + calcDist(pulses);
	}
	printf("%f\n",totalDist);
}

void DistanceCalculator::setKilo(bool kilo){
	km = kilo;
}

void DistanceCalculator::setTireSize(int tire){
	tireSize = tire;
	setUp = true;
}

double DistanceCalculator::calcDist(int pulses){
	if(setUp){
		double dist = ((double)(pulses * tireSize))/100000;
		if (!km){
			dist = dist / 1.60934;
		}
		return dist;
	} else {
		return 0.0;
	}
}

void DistanceCalculator::notify(Event* event){
	if (event->getEventType() == ev::PULSES2){
		((PulseEvent*)event)->run(this);
	} else if (event->getEventType() == ev::KILO2){
		((SetKilometerEvent*)event)->run(this);
	} else if (event->getEventType() == ev::TIRE_SIZE2){
		((TireSizeEvent*)event)->run(this);
	} else if (event->getEventType() == ev::CALC_OFF2){
		printf("off\n");
		calc = false;
	} else if (event->getEventType() == ev::CALC_ON2){
		printf("on\n");
		calc = true;
	}
}

Event* DistanceCalculator::makeEvent(){
	if(setUp){
		UpdateDistanceEvent* update = new UpdateDistanceEvent();
		update->setDistance(totalDist);
		return update;
	}
	return NULL;
}

void* checkDist(void* dc){
	DistanceCalculator* dist = ((DistanceCalculator*)dc);
	while (true){
		Event* event = dist->makeEvent();
		dist->trigger(event);
		usleep(1000000);
	}
	return NULL;
}

void DistanceCalculator::genDist(){
	pthread_t dist_t;
	pthread_create(&dist_t, NULL, checkDist, this);
}
