#pragma once
#include <ctime>

#include "nodes.h"

struct DoorStatus {
	bool doorIsOpen;
	bool doorIsLocked;
	bool atDoor;
};

class LeafNode : public Node
{
public:
	virtual void addChild(Node* child) override
	{
		std::cout << "Error: can't add child to leaf";
	}
};

class CheckIfDoorIsOpenTask : public LeafNode 
{  // Each task will be a class derived from Node
private:
	DoorStatus* status;
public:
	CheckIfDoorIsOpenTask(DoorStatus* status) : status(status) {}
	virtual bool run() override 
	{
		if (status->doorIsOpen)
		{
			std::cout << "The person sees that the door is open." << std::endl;  // will return true
		}
		else
		{
			std::cout << "The person sees that the door is closed." << std::endl;  // will return false
		}
		return status->doorIsOpen;
	}
};

class ApproachDoorTask : public LeafNode
{
private:
	DoorStatus* status;
	bool obstructed;
	int distanceToDoor = 1;

public:
	ApproachDoorTask(DoorStatus* status, bool obstructed) : status(status), obstructed(obstructed) {}
	virtual bool run() override 
	{
		if (obstructed)
		{
			return false;
		}
		if (distanceToDoor > 0)
		{
			std::cout << "The person approaches the door." << std::endl;
			distanceToDoor--;  // thus run() is not a const function
			if (distanceToDoor > 1) 
			{
				std::cout << "The person is now " << distanceToDoor << " meters from the door." << std::endl;
			}
			else if (distanceToDoor == 1) 
			{
				std::cout << "The person is now only one meter away from the door." << std::endl;
			}
			else 
			{
				std::cout << "The person is at the door." << std::endl;
				status->atDoor = true;
				return true;
			}
		}
		return false;
	}
};

class OpenDoorTask : public LeafNode
{
private:
	DoorStatus* status;
public:
	OpenDoorTask(DoorStatus* status) : status(status) {}
	virtual bool run() override 
	{
		if (!status->atDoor) 
		{
			std::cout << "The person is still too far away from the door.  He cannot open the door." << std::endl;
			return false;
		}

		if (status->doorIsLocked && status->atDoor) 
		{
			std::cout << "Door is locked" << std::endl;
			return false;
		}
		else
		{
			status->doorIsOpen = true;  // run() not const because of this too
			std::cout << "The person opens the door." << std::endl;
			return true;
		}
	}
};

class UnlockDoorTask : public LeafNode {
private:
	DoorStatus* status;
public:
	UnlockDoorTask(DoorStatus* status) : status(status) {}
	virtual bool run() override 
	{
		if (status->atDoor)
		{
			if (status->doorIsLocked)
			{
				std::cout << "Attempting to unlock..." << std::endl;
				
				srand(time(NULL));
				int chance = rand() % 100;
			
				if (chance > 50) 
				{
					std::cout << "Success!" << std::endl;
					status->doorIsLocked = false;
					return true;
				}
				else
				{
					std::cout << "Failed!" << std::endl;
					status->doorIsLocked = true;
					return false;
				}
			}
		}		
	}
};

class SmashDoorTask : public LeafNode {
private:
	DoorStatus* status;
public:
	SmashDoorTask(DoorStatus* status) : status(status) {}
	virtual bool run() override
	{	
			if (status->doorIsLocked)
			{
				std::cout << "Attempting to smash..." << std::endl;
				std::cout << "Success!" << std::endl;
				status->doorIsLocked = false;
				status->doorIsOpen = true;
				return true;
			}
		else return false;
	}
};

class EnterDoorTask : public LeafNode {
private:
	DoorStatus* status;
public:
	EnterDoorTask(DoorStatus* status) : status(status) {}
	virtual bool run() override
	{
		if (status->doorIsOpen)
		{
			std::cout << "Walk through door" << std::endl;
			return true;
		}
		else return false;
	}
};