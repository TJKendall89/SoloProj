#pragma once
#include <ctime>

#include "nodes.h"

struct Status {
	int days;
	int daysHungry;
};

struct Area {
	int richness;
	bool richInFood;
	bool safe;
	bool hasHidingSpots;
};

class CheckForFood : public LeafNode
{  // Each task will be a class derived from Node
private:
	Area* zone;
	Status* world;
public:
	CheckForFood(Area* status, Status* world) : zone(status), world(world) {}
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
			std::cout << " New zone is rich enough in food to stay";  // will return true
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
	Area* zone;
	Status* world;
public:
	ConsumeFood(Area* status, Status* world) : zone(status), world(world) {}
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
	Area* zone;
	Status* world;
public:
	Update(Area* status, Status* world) : zone(status), world(world){}
	virtual bool run() override
	{
		world->days++;
		std::cout << "Days passed: " << world->days << std::endl;

		std::cin.get();

		if (world->days == 6)
			zone->richness = 2;


		if (world->days == 10)
		{
			zone->richness = 3;
			zone->safe = false;
		}

		if (world->days == 12)
			zone->safe = true;

		if (world->days == 15)
			zone->safe = false;

		if (world->daysHungry > 7)
		{
			std::cout << "Died" << std::endl;
			
		}
		return true;
	}
};