#pragma once
#include "nodes.h"

struct Status {

	int days;
	int daysHungry;
};

class FindWaypoint : public LeafNode
{  // Each task will be a class derived from Node
private:
	Status* world;
	bool running = true;
public:
	FindWaypoint(Status* world) : zone(status){}
	virtual bool run() override
	{

	}
};