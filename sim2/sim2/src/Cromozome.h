#pragma once
#include <glm/vec4.hpp>
#include <string>
#include <bitset>

class Cromozome
{
private:
	std::bitset<6> xGenes;
	std::bitset<6> yGenes;
	std::bitset<6> zGenes;
	std::bitset<3> eGenes;
public:
	Cromozome();
	Cromozome(long x,long y,long z,long e);
	Cromozome(std::bitset<6> x, std::bitset<6> y, std::bitset<6> z, std::bitset<3> e);
	~Cromozome();

	std::bitset<6> getX();
	std::bitset<6> getY();
	std::bitset<6> getZ();
	std::bitset<3> getE();

	void setCromozome(long x, long y, long z, long e);
	void setCromozome(std::bitset<6> x, std::bitset<6> y, std::bitset<6> z, std::bitset<3> e);
	std::string cromozomeToString();

	glm::vec4 toVec4();

	Cromozome crossOver(Cromozome& y, short index);
	void mutate(short index);
	Cromozome getMutatedChild(short index);

private:
	std::bitset<6> combine(std::bitset<6>& source,std::bitset<6> secondPart, short index);
};

