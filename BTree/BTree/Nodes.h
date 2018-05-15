#pragma once
#include <ctime>
#include <iostream>
#include <list>

class Node
{  // This class represents each node in the behaviour tree.
public:
	virtual bool run() = 0;
	virtual void addChild(Node* child) = 0;
};

class LeafNode : public Node
	{
	public:
		virtual void addChild(Node* child) override
		{
			std::cout << "Error: can't add child to leaf" << std::endl;
		}
	};



class CompositeNode : public Node
{  //  This type of Node follows the Composite Pattern, containing a list of other Nodes.
private:
	std::list<Node*> children;
public:
	const std::list<Node*>& getChildren() const { return children; }
	virtual void addChild(Node* child) override
	{ children.emplace_back(child); }
};

class Selector : public CompositeNode
{
public:
	virtual bool run() override
	{
		for (Node* child : getChildren())
		{  // The generic Selector implementation
			if (child->run())  // If one child succeeds, the entire operation run() succeeds.  Failure only results if all children fail.
				return true;
		}
		return false;  // All children failed so the entire run() operation fails.
	}
};

class Sequence : public CompositeNode
{
public:
	virtual bool run() override
	{
		for (Node* child : getChildren())
		{  // The generic Sequence implementation.
			if (!child->run())  // If one child fails, then enter operation run() fails.  Success only results if all children succeed.
				return false;
		}
		return true;  // All children suceeded, so the entire run() operation succeeds.
	}
};
