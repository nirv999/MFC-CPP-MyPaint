#pragma once

#include "MyFactory.h"
#include "MyLine.h"

class MyLineFactory : public MyFactory {
public:
	MyShape* create() { return new MyLine(); }
};