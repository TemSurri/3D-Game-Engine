#pragma once
#include "../transform/transform.h"
#include <string>


// thing repreents the most basic entity it simply has a transform that represents its geometry in 3d space
class Thing {

	public:
		std::string name;
		int id{};
		Transform transform;

		Thing(std::string name, int id) 
			:name(name), id(id)
		{
			transform = Transform();
		}

};