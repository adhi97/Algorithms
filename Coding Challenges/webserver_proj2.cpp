#include <iostream>
#include "function_defn.h"

using namespace std;

// adds a priority function to the pervious webserver design
struct Storage{
	float value;
	Storage *next;
};


int timeSeconds(timestamp t){
	return t.hh*3600 + t.mm*60 + t.ss;
}

float priorScan(uri &readData,uri*data,char*name) {
	while(data){
		if (data->name == name){
			readData = *data;
		}
		data = data->next;
	}
}

float sizeScan(uri &readData,uri*data,char*name) {
	while(data){
		if (data->name == name){
			readData = *data;
		}
		data = data->next;
	}
}

timestamp maxClientDelay(uri*uriServer,request*pending) {	
	float elapsedTime = 0;
	Storage *list = 0;
	request *listQueue = 0;
	
	do{
		
		while(pending){
			
			if (timeSeconds(pending->t) > elapsedTime) break;
			
			request *insertion = new request;
			insertion->name = pending->name;
			insertion->t = pending->t;
			insertion->next = listQueue;
			listQueue = insertion;
			
			pending = pending->next;
		}
		
		if (!listQueue){
			elapsedTime = timeSeconds(pending->t);
			continue;
		}
		
		request *front = listQueue;
		request *back = listQueue;
		
		request *ordered = listQueue;
		
		uri readData;
		priorScan(readData, uriServer, listQueue->name);
		float maxPriority = readData.priority;
		request *count = listQueue;
		
		while (count){
			priorScan(readData, uriServer, count->name);
			if (readData.priority > maxPriority){
				maxPriority = readData.priority;
				ordered = count;
				front = back;
			}
			back = count;
			count = count ->next;
		}
		
		float delayTime = elapsedTime - timeSeconds(ordered->t);
		Storage *temp = new Storage;
		temp->value = delayTime;
		temp->next = list;
		list = temp;
		
		sizeScan(readData, uriServer, ordered->name);
		elapsedTime += (float)readData.size * 0.8;
		
		if (ordered == listQueue){
			listQueue = ordered->next;
		}else{
			front->next = ordered->next;
		}
	}while(listQueue||pending);
	
	int maxDelay = 0;
	
	while(list) {
		if (list -> value > maxDelay){
			maxDelay = list -> value;
		}
		list = list->next;
	}
	
	timestamp maxDelayTime;
	maxDelayTime.hh = maxDelay/3600;
	maxDelay = maxDelay%3600;
	maxDelayTime.mm = maxDelay/60;
	maxDelayTime.ss = maxDelay%60;
	
	return maxDelayTime;
}
