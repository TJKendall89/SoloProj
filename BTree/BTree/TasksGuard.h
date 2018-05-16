#pragma once
#include "nodes.h"

struct Status {
	bool foundWaypoint;

};

class FindWaypoint : public LeafNode
{  // Each task will be a class derived from Node
private:
	Status* guard;
	bool running = true;
public:
	FindWaypoint(Status* world) : zone(status){}
	virtual bool run() override
	{

	}
};