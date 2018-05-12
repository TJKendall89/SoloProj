#include <iostream>
#include <ostream>
#include <sstream>
#include <list>

#include "TasksDoor.h"
#include "TasksPrey.h"
#include "CParseLevel.h"

int selection = 0;
bool isRunning = true;

gen::CParseXML parseFile;

Node* root = new Sequence();

gen::CParseLevel levelParser(root);

// Behaviour tree that models the behaviour of a person whose goal is to open a door.


void main() 
{
	//while (isRunning)
	//{
	//	std::cout << std::endl;
	//	std::cout << "-----------------------------" << std::endl;
	//	std::cout << "Select a simulation:" << std::endl;
	//	std::cout << "1 = Open Door" << std::endl;
	//	//std::cout << "2 = Prey searching for food" << std::endl;
	//	std::cout << "3 = Quit" << std::endl;
	//	std::cin >> selection;
	//	std::cout << std::endl << std::endl;

	//	switch (selection)
	//	{
	//		
	//	default:
	//		break;
	//	case 0:
	//		break;
	//	case 1:
	//		std::system("CLS");
	//		DoorExample();		
	//		break;
	//	case 2:
	//		std::system("CLS");
	//		/*PreyExample();*/
	//		break;
	//	case 3:
	//		isRunning = false;
	//		break;
	//	}
	//	std::cout << "-----------------------------" << std::endl;
	//}

	//levelParser.ParseFile("Entities.xml");
	levelParser.ParseFile("Entities2.xml");

	while (!root->run())
	{
		std::cout << "--------------------" << std::endl;
	}
	std::cout << std::endl << "Operation complete.  Behaviour tree exited." << std::endl;


	std::system("PAUSE");

}





/*
void DoorExample()
{

	//Create nodes
	Sequence *root = new Sequence, *sequence1 = new Sequence, *sequence2 = new Sequence;;  // Note that root can be either a Sequence or a Selector, since it has only one child.
	Selector *selector1 = new Selector, *selector2 = new Selector;  // In general there will be several nodes that are Sequence or Selector, so they should be suffixed by an integer to distinguish between them.

																	//Set door status
	DoorStatus* doorStatus = new DoorStatus{ false, true, false };


	//Inititalise tasks
	CheckIfDoorIsOpenTask* checkOpen = new CheckIfDoorIsOpenTask(doorStatus);
	ApproachDoorTask* approach = new ApproachDoorTask(doorStatus, false);
	OpenDoorTask* open = new OpenDoorTask(doorStatus);
	UnlockDoorTask* unlock = new UnlockDoorTask(doorStatus);
	SmashDoorTask* smash = new SmashDoorTask(doorStatus);
	EnterDoorTask* enter = new EnterDoorTask(doorStatus);

	//Root
	root->addChild(sequence1);

	//Depth 1
	sequence1->addChild(approach);
	sequence1->addChild(selector1);
	sequence1->addChild(enter);

	//Depth 2
	selector1->addChild(open);
	selector1->addChild(sequence2);
	selector1->addChild(smash);

	//Depth 3
	sequence2->addChild(unlock);
	sequence2->addChild(open);

	// If the operation starting from the root fails, keep trying until it succeeds.
	while (!root->run())
	{
		std::cout << "--------------------" << std::endl;
	}
	std::cout << std::endl << "Operation complete.  Behaviour tree exited." << std::endl;
}

void PreyExample()
{
	
	//Build area

	//Create nodes
	Sequence *root = new Sequence, *sequence1 = new Sequence, *sequence2 = new Sequence;;  // Note that root can be either a Sequence or a Selector, since it has only one child.
	Selector *selector1 = new Selector, *selector2 = new Selector;  // In general there will be several nodes that are Sequence or Selector, so they should be suffixed by an integer to distinguish between them.

	//Set door status
	const int AREA_SIZE_X = 10;
	const int AREA_SIZE_Y = 10;
	Area* area = new Area{ 2, false, true, true };

	//Set climate
	Status* climate = new Status{ 0, 0 };
	Area* zone = new Area{ 2, false, true, true };

	//Inititalise tasks
	CheckForFood* check = new CheckForFood(area, zone);
	FindFood* search = new FindFood(area);
	ConsumeFood* eat = new ConsumeFood(area, zone);

	//Root
	root->addChild(sequence1);

	//Depth 1
	sequence1->addChild(check);
	sequence1->addChild(sequence2);
	sequence1->addChild(selector1);

	//Depth 2
	sequence2->addChild(search);
	sequence2->addChild(eat);




	// If the operation starting from the root fails, keep trying until it succeeds.
	while (!root->run())
	{
	climate->days++;
	std::cout << "Days passed: " << climate->days << std::endl;


	std::cin.get();

	if (climate->days == 6)
	area->richness = 2;


	if (climate->days == 10)
	{
	area->richness = 3;
	area->safe = false;
	}

	if (climate->days == 12)
	area->safe = true;

	if (climate->days == 15)
	area->safe = false;

	if (climate->daysHungry > 7)
	{
	std::cout << "Died" << std::endl;
	break;
	}

	std::cout << "--------------------" << std::endl;
	}

	std::cout << std::endl << "Operation complete.  Behaviour tree exited." << std::endl;

	
}
*/