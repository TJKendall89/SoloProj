///////////////////////////////////////////////////////////
//  CParseLevel.cpp
//  A class to parse and setup a level (entity templates
//  and instances) from an XML file
//  Created on:      30-Jul-2005 14:40:00
//  Original author: LN
///////////////////////////////////////////////////////////

#ifndef GEN_C_PARSE_LEVEL_H_INCLUDED
#define GEN_C_PARSE_LEVEL_H_INCLUDED

#include <string>
using namespace std;

#include "Defines.h"
#include "nodes.h"
#include "CParseXML.h"

namespace gen
{

/*---------------------------------------------------------------------------------------------
	CParseLevel class
---------------------------------------------------------------------------------------------*/
// A XML parser to read and setup a level - made up of entity templates and entity instances
// Derived from the general CParseXML class, which performs the basic syntax parsing. The base
// class calls functions (overridden) in this class when it encounters the start and end of
// elements in the XML (opening and closing tags). These functions then perform appropriate
// setup. This is an event driven system, requiring this class to store state - the entity /
// template / member variables it is currently building
class CParseLevel : public CParseXML
{

/*---------------------------------------------------------------------------------------------
	Constructors / Destructors
---------------------------------------------------------------------------------------------*/
public:
	// Constructor gets a pointer to the entity manager and initialises state variables
	CParseLevel( Node* entityManager );

	
/*-----------------------------------------------------------------------------------------
	Private interface
-----------------------------------------------------------------------------------------*/
private:

	/*---------------------------------------------------------------------------------------------
		Types
	---------------------------------------------------------------------------------------------*/

	// File section currently being parsed
	enum EFileSection
	{
		None,
		Templates,
		Entities,
	};


	/*---------------------------------------------------------------------------------------------
		Callback functions
	---------------------------------------------------------------------------------------------*/

	// Callback function called when the parser meets the start of a new element (the opening tag).
	// The element name is passed as a string. The attributes are passed as a list of (C-style)
	// string pairs: attribute name, attribute value. The last attribute is marked with a null name
	void StartElt( const string& eltName, SAttribute* attrs );

	// Callback function called when the parser meets the end of an element (the closing tag). The
	// element name is passed as a string
	void EndElt( const string& eltName );


	/*---------------------------------------------------------------------------------------------
		Section Parsing
	---------------------------------------------------------------------------------------------*/

	// Called when the parser meets the start of an element (opening tag) in the templates section
	void TemplatesStartElt( const string& eltName, SAttribute* attrs );

	// Called when the parser meets the end of an element (closing tag) in the templates section
	void TemplatesEndElt( const string& eltName );


	// Called when the parser meets the start of an element (opening tag) in the entities section
	void EntitiesStartElt( const string& eltName, SAttribute* attrs );

	// Called when the parser meets the end of an element (closing tag) in the entities section
	void EntitiesEndElt( const string& eltName );


	/*---------------------------------------------------------------------------------------------
		Entity Template and Instance Creation
	---------------------------------------------------------------------------------------------*/

	// Create an entity template using data collected from parsed XML elements
	void CreateEntityTemplate();

	// Create an entity using data collected from parsed XML elements
	void CreateEntity();


	/*---------------------------------------------------------------------------------------------
		Data
	---------------------------------------------------------------------------------------------*/

	// Constructer is passed a pointer to an entity manager used to create templates and
	// entities as they are parsed
	Node* m_Root;
	int m_Scenario;
	
	// File state
	EFileSection m_CurrentSection;


	// Current entity state (i.e. latest values read during parsing)
	string   m_NodeName;
	string   m_NodeType;
	int		 m_ParentKey;
	int		 m_Key;
};


} // namespace gen

#endif // GEN_C_PARSE_LEVEL_H_INCLUDED
