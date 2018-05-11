///////////////////////////////////////////////////////////
//  CParseLevel.cpp
//  A class to parse and setup a level (entity templates
//  and instances) from an XML file
//  Created on:      30-Jul-2005 14:40:00
//  Original author: LN
///////////////////////////////////////////////////////////

#include <map>

#include "BaseMath.h"
#include "CParseLevel.h"
#include "TasksDoor.h"
#include "TasksPrey.h"


DoorStatus* doorStatus = new DoorStatus{ false, true, false };
Status* world = new Status{ false, 0 , 0 };
Area* area = new Area{ 2, false, true, true };
std::map <int, Node*> behaveMap;



namespace gen
{
/*---------------------------------------------------------------------------------------------
	Constructors / Destructors
---------------------------------------------------------------------------------------------*/

// Constructor initialises state variables
CParseLevel::CParseLevel( Node* root)
{
	// Take copy of entity manager for creation
	m_Root = root;
	m_Scenario = 0;
	behaveMap.clear();
	behaveMap[0] = m_Root;

	// File state
	m_CurrentSection = None;

	// Entity state
	m_NodeType = "";
	m_NodeName = "";
	m_ParentKey = 0;
}


/*---------------------------------------------------------------------------------------------
	Callback Functions
---------------------------------------------------------------------------------------------*/

// Callback function called when the parser meets the start of a new element (the opening tag).
// The element name is passed as a string. The attributes are passed as a list of (C-style)
// string pairs: attribute name, attribute value. The last attribute is marked with a null name
void CParseLevel::StartElt( const string& eltName, SAttribute* attrs )
{
	// Open major file sections
	if (eltName == "Templates")
	{
		m_CurrentSection = Templates;
	}
	else if (eltName == "Entities")
	{
		m_CurrentSection = Entities;
	}

	// Different parsing depending on section currently being read
	switch (m_CurrentSection)
	{
		case Templates:
			TemplatesStartElt( eltName, attrs ); // Parse template start elements
			break;
		case Entities:
			EntitiesStartElt( eltName, attrs ); // Parse entity start elements
			break;
	}
}

// Callback function called when the parser meets the end of an element (the closing tag). The
// element name is passed as a string
void CParseLevel::EndElt( const string& eltName )
{
	// Close major file sections
	if (eltName == "Templates" || eltName == "Entities")
	{
		m_CurrentSection = None;
	}

	// Different parsing depending on section currently being read
	switch (m_CurrentSection)
	{
		case Templates:
			TemplatesEndElt( eltName ); // Parse template end elements
			break;
		case Entities:
			EntitiesEndElt( eltName ); // Parse entity end elements
			break;
	}
}


/*---------------------------------------------------------------------------------------------
	Section Parsing
---------------------------------------------------------------------------------------------*/

// Called when the parser meets the start of an element (opening tag) in the templates section
void CParseLevel::TemplatesStartElt( const string& eltName, SAttribute* attrs )
{
	// Started reading a new entity template - get type, name and mesh
	if (eltName == "EntityTemplate")
	{
		
	}
}

// Called when the parser meets the end of an element (closing tag) in the templates section
void CParseLevel::TemplatesEndElt( const string& eltName )
{
	// Finished reading an entity template - create it using parsed data
	if (eltName == "EntityTemplate")
	{
		CreateEntityTemplate();
	}
}



//Inititalise tasks



// Called when the parser meets the start of an element (opening tag) in the entities section
void CParseLevel::EntitiesStartElt( const string& eltName, SAttribute* attrs )
{
	// Started reading a team of entities - get team data
	if (eltName == "Entity")
	{
		m_NodeType = GetAttribute(attrs, "Type");
		m_NodeName = GetAttribute(attrs, "Name");
		m_Key = GetAttributeInt(attrs, "Key");
		m_ParentKey = GetAttributeInt(attrs, "Parent");

		if (m_NodeType == "Sequence")
		{
			behaveMap[m_Key] = new Sequence;		

		}
		else if (m_NodeType == "Selector")
		{
			behaveMap[m_Key] = new Selector;
			
		}
		else if (m_NodeType == "Leaf")
		{
			if (m_NodeName == "Approach")
			{
				behaveMap[m_Key] = new ApproachDoorTask(doorStatus, false);						
			}
			else if (m_NodeName == "Open")
			{
				behaveMap[m_Key] = new OpenDoorTask(doorStatus);
			}
			else if (m_NodeName == "Unlock")
			{
				behaveMap[m_Key] = new UnlockDoorTask(doorStatus);
			}
			else if (m_NodeName == "Smash")
			{
				behaveMap[m_Key] = new SmashDoorTask(doorStatus);
			}
			else if (m_NodeName == "Enter")
			{
				behaveMap[m_Key] = new EnterDoorTask(doorStatus);
			}
			else if (m_NodeName == "Update")
			{
				behaveMap[m_Key] = new Update(area);
			}
			else if (m_NodeName == "Check")
			{
				behaveMap[m_Key] = new CheckForFood(area);
			}
			else if (m_NodeName == "Search")
			{
				behaveMap[m_Key] = new FindFood(area);
			}
			else if (m_NodeName == "Eat")
			{
				behaveMap[m_Key] = new ConsumeFood(area);
			}

		}	
		behaveMap[m_ParentKey]->addChild(behaveMap[m_Key]);
	}
}

// Called when the parser meets the end of an element (closing tag) in the entities section
void CParseLevel::EntitiesEndElt( const string& eltName )
{
	behaveMap;
}


/*---------------------------------------------------------------------------------------------
	Entity Template and Instance Creation
---------------------------------------------------------------------------------------------*/

// Create an entity template using data collected from parsed XML elements
void CParseLevel::CreateEntityTemplate()
{

}

// Create an entity using data collected from parsed XML elements
void CParseLevel::CreateEntity()
{

}


} // namespace gen
