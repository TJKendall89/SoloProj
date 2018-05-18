#pragma once
#include "nodes.h"

struct Guard {
	bool foundWaypoint;
	bool obstructed;
	int waypointDist;
};

class FindWaypoint : public LeafNode
{  // Each task will be a class derived from Node
private:
	Guard* guardInfo;
public:
	FindWaypoint(Guard* info) : guardInfo(info){}
	virtual bool run() override
	{
		if (guardInfo->foundWaypoint)
		{
			std::cout << "Waypoint found" << std::endl;
			return true;
		}
		else
		{
			std::cout << "No waypoint found" << std::endl;
			return false;
		}
	}
};


class RouteA : public LeafNode
{  // Each task will be a class derived from Node
private:
	Guard * guardInfo;
	bool running = true;
public:
	RouteA(Guard* info) : guardInfo(info) {}
	virtual bool run() override
	{
		if (guardInfo->obstructed)
		{
			std::cout << "Taking Route A" << std::endl;
			while (running)
			{
				guardInfo->waypointDist--;
				if (guardInfo->waypointDist <= 0)
					return true;
				
				std::cout << "Travelling... (Distance to point: " << guardInfo->waypointDist << ")" << std::endl;
			}			
		}
		else
		{
			return false;
		}
	}
};

class RouteB : public LeafNode
{  // Each task will be a class derived from Node
private:
	Guard * guardInfo;
	bool running = true;
public:
	RouteB(Guard* info) : guardInfo(info) {}
	virtual bool run() override
	{
		if (!guardInfo->obstructed)
		{
			std::cout << "Taking Route B" << std::endl;
			while (running)
			{
				guardInfo->waypointDist--;
				if (guardInfo->waypointDist <= 0)
					return true;

				std::cout << "Distance to point: " << guardInfo->waypointDist << std::endl;
			}
		}
		else
		{
			std::cout << "Cannot reach point" << std::endl;
			return false;
		}
	}
};

class Arrived : public LeafNode
{  // Each task will be a class derived from Node
private:
	Guard * guardInfo;
public:
	Arrived(Guard* info) : guardInfo(info) {}
	virtual bool run() override
	{
		std::cout << "Waypoint reached" << std::endl;
		return true;
	}
};