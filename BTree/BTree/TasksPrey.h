#pragma once
#include <ctime>

#include "nodes.h"

struct Status {
	bool started;
	int days;
	int daysHungry;
};

struct Area {
	int richness;
	bool richInFood;
	bool safe;
	bool hasHidingSpots;
};

//class LeafNode : public Node
//{
//public:
//	virtual void addChild(Node* child) override
//	{
//		std::cout << "Error: can't add child to leaf";
//	}
//};

class CheckForFood : public LeafNode
{  // Each task will be a class derived from Node
private:
	Area* zone;
	Status* world;
public:
	CheckForFood(Area* status) : zone(status) {}
	virtual bool run() override
	{
		if (zone->richness > 0)
			zone->richInFood = true;
		else
			zone->richInFood = false;

		if (zone->richInFood)
		{
			std::cout << "Area is rich enough in food to stay" << std::endl;
			return true;
		}
		else
		{
			std::cout << "No food, Searching..." << std::endl;
			world->daysHungry++;
			std::cout << "Days hungry: " << world->daysHungry << std::endl;
			return false;
		}


	}
};

class FindFood : public LeafNode
{  // Each task will be a class derived from Node
private:
	Area * zone;
public:
	FindFood(Area* status) : zone(status) {}
	virtual bool run() override
	{
		std::cout << "Travelling..." << std::endl;

		if (zone->richInFood)
		{
			std::cout << "Area is rich enough in food to stay";  // will return true
			if (zone->safe)
			{
				std::cout << " and area is safe" << std::endl;
				return true;
			}
			else
			{
				std::cout << " but area is not safe" << std::endl;
				return false;
			}
		}
		else
		{
			std::cout << "No food, Searching..." << std::endl;  // will return false
			return false;
		}
	}
};

class ConsumeFood : public LeafNode
{  
private:
	Area * zone;
	Status* world;
public:
	ConsumeFood(Area* status) : zone(status) {}
	virtual bool run() override
	{
		if (zone->safe)
		{
			std::cout << "Consuming food" << std::endl;
			zone->richness--;
			
			if(world->daysHungry > 0)
				world->daysHungry = 0;
			
			std::cout << "Food amount: " << zone->richness << std::endl;
			return true;
		}
		else
		{
			std::cout << "Danger afoot, moving..." << std::endl;
			return false;
		}
	}
};

//Leaf node that updates the world for the rest of the tree to react to
class Update : public LeafNode
{  
private:
	Area* status;
	Status* world;
public:
	Update(Area* status) : status(status) {}
	virtual bool run() override
	{
		//if (!world->started)
		//{
		//	world->days = 0;
		//	world->daysHungry = 0;
		//	world->started = true;
		//}

		world->days++;
		std::cout << "Days passed: " << world->days << std::endl;

		std::cin.get();

		if (world->days == 6)
			status->richness = 2;


		if (world->days == 10)
		{
			status->richness = 3;
			status->safe = false;
		}

		if (world->days == 12)
			status->safe = true;

		if (world->days == 15)
			status->safe = false;

		if (world->daysHungry > 7)
		{
			std::cout << "Died" << std::endl;
		}
		return true;
	}
};