#pragma once

#include "Command.h"
#include "MyShape.h"
#include <vector>

using namespace std;

class AddCommand : public Command {
public:
	AddCommand(vector<MyShape*> &shapes,MyShape *shape)
		: shapes(shapes), shape(shape) {}
	
	//for undo
	void perform() { shapes.push_back(shape); }

	//for redo
	void rollback() {
		vector<MyShape*>::iterator it;
		for (it = shapes.begin(); it != shapes.end(); ++it)
			if (*it == shape)
				break;
		if (it != shapes.end())
			shapes.erase(it);
	}
private:
	vector<MyShape*> &shapes;
	MyShape *shape;
};