#include <iostream>
#include <vector>
#include "LiteVector.h"

class Block
{
public:
	std::string name;
	int age;

	Block(std::string _name, int _age)
	{
		name = _name;
		age = _age;

		std::cout << "Block " << _name << " created!" << std::endl;
	}

	~Block()
	{
		std::cout << "Block " << name << " destroyed!" << std::endl;
	}
};

int main()
{
	Block p1("Andrzej", 32);
	Block p2("Kiemont", 64);
	
	Block p3("Kunegunda", 21);
	Block p4("Rozwalia", 69);


	std::vector<Block> vector;
	vector.emplace_back(p1);
	vector.emplace_back(p2);

	LV::LiteVector<Block> liteVector;
	liteVector.push_back(p3);
	liteVector.push_back(p4);

	return 0;
}
