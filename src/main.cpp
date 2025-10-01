#include <iostream>
#include <vector>
#include "LiteVector.h"

static int s_AllocatedCount = 0;
static int s_CopiesCount = 0;
static int s_MovesCount = 0;

void* operator new(size_t size)
{
	std::cout << "Allocated "<< size << " bytes" << std::endl;
	s_AllocatedCount++;
	return malloc(size);
}


class Block
{
public:
	std::string name;
	int age;

	Block(std::string _name, int _age)
	{
		name = _name;
		age = _age;

		//std::cout << "Block " << _name << " created!" << std::endl;
	}
	
	Block(const Block& other)
		: name(other.name), age(other.age) 
	{
		//std::cout << "Copied " << other.name << std::endl;
		s_CopiesCount++;
	}

	Block(Block&& other) noexcept
		: name(std::move(other.name)), age(other.age)
	{
		other.age = 0;
		s_MovesCount++;
	}

	~Block()
	{
		//std::cout << "Block " << name << " destroyed!" << std::endl;
	}
};

static void PrintVector(const std::vector<Block>& vector)
{
	std::cout << "Size: " << vector.size() << std::endl;
	std::cout << "Elements: [ ";
	for(int i = 0; i < vector.size(); i++)
	{
		std::cout << "{Name: " << vector[i].name << " Age: "<< vector[i].age << "}";
		if(i < vector.size() - 1)
			std::cout << ", ";
	}
	std::cout << " ]" << std::endl;
}

static void PrintLiteVector(const LV::LiteVector<Block>& liteVector)
{
	std::cout << "LV:Size: " << liteVector.size() << std::endl;
	std::cout << "Elements: [ ";
	for(int i = 0; i < liteVector.size(); i++)
	{
		std::cout << "{Name: " << liteVector[i].name << " Age: " << liteVector[i].age << "}";
		if(i < liteVector.size() - 1)
			std::cout << ", ";
	}

	std::cout << " ]" << std::endl;
}

int main()
{
	//Block p1("Andrzej", 32);
	//Block p2("Kiemont", 64);
	
	//Block p3("Kunegunda", 21);
	Block p4("Rozwalia", 69);


	std::vector<Block> vector;
	vector.reserve(2);
	//vector.emplace_back(p1);
	//vector.emplace_back(p2);
	vector.emplace_back("Andrzej", 32);
	vector.emplace_back("Kiemont", 64);

	LV::LiteVector<Block> liteVector(2);
	liteVector.push_back(Block("Kunegunda", 21));
	liteVector.push_back(std::move(p4));

	PrintVector(vector);
	PrintLiteVector(liteVector);

	std::cout << "\n\nTotal allocations: "<< s_AllocatedCount << std::endl;
	std::cout << "Total copies: " << s_CopiesCount << std::endl;
	std::cout << "Total moves: " << s_MovesCount << std::endl;
	return 0;
}
