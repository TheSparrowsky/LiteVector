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

template<typename T, typename Allocator>
static void PrintLiteVector(const LV::LiteVector<T, Allocator>& liteVector)
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

	LV::LiteVector<Block, std::allocator<Block>> test({ {"Pola", 16}, {"Aurelia", 76}});
	PrintLiteVector(test);

	LV::LiteVector<Block> liteVector(3);
	liteVector.push_back(Block("Kunegunda", 21));
	liteVector.push_back(std::move(p4));
	liteVector.emplace_back("Chloe", 38);

	PrintVector(vector);
	PrintLiteVector(liteVector);

	LV::LiteVector<int> numbers(16);
	numbers.push_back(12);
	numbers.push_back(1);
	numbers.push_back(16);
	numbers.push_back(54);
	numbers.push_back(24);
	numbers.push_back(36);
	numbers.push_back(72);

	std::cout << "\nBefore:\n" << std::endl;
	for(auto it = numbers.begin(); it != numbers.end(); ++it)
		std::cout << *it << std::endl;

	std::sort(numbers.begin(), numbers.end());
	
	std::cout << "\nAfter:\n" << std::endl;
	for(auto it = numbers.begin(); it != numbers.end(); ++it)
		std::cout << *it << std::endl;


	std::cout << "\n\nTotal allocations: "<< s_AllocatedCount << std::endl;
	std::cout << "Total copies: " << s_CopiesCount << std::endl;
	std::cout << "Total moves: " << s_MovesCount << std::endl;
	return 0;
}
