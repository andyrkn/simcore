#include "Cromozome.h"
#include<iostream>
Cromozome::Cromozome()
{
}

Cromozome::Cromozome(long x, long y, long z, long e)
{
	setCromozome(x, y, z, e);
}

Cromozome::Cromozome(std::bitset<6> x, std::bitset<6> y, std::bitset<6> z, std::bitset<3> e)
{
	setCromozome(x, y, z, e);
}

Cromozome::~Cromozome()
{}

std::bitset<6> Cromozome::getX()
{
	return xGenes;
}

std::bitset<6> Cromozome::getY()
{
	return yGenes;
}

std::bitset<6> Cromozome::getZ()
{
	return zGenes;
}

std::bitset<3> Cromozome::getE()
{
	return eGenes;
}

void Cromozome::setCromozome(long x, long y, long z, long e)
{
	xGenes = std::bitset<6>(x);
	yGenes = std::bitset<6>(y);
	zGenes = std::bitset<6>(z);
	eGenes = std::bitset<3>(e);
}

void Cromozome::setCromozome(std::bitset<6> x, std::bitset<6> y, std::bitset<6> z, std::bitset<3> e)
{
	xGenes = x;
	yGenes = y;
	zGenes = z;
	eGenes = e;
}

glm::vec4 Cromozome::toVec4()
{
	glm::vec4 res;
	res.x = xGenes.to_ulong();
	res.y = yGenes.to_ulong();
	res.z = zGenes.to_ulong();
	res.w = eGenes.to_ulong();
	return res;
}

Cromozome Cromozome::crossOver(Cromozome& y, short index)
{
	Cromozome res;
	if (index < 6)
	{
		res.setCromozome(combine(xGenes, y.getX(), index), y.getY(), y.getZ(), y.getE());
		return res;
	}
	if (index < 12)
	{
		res.setCromozome(xGenes, combine(yGenes, y.getY(), index), y.getZ(), y.getE());
		return res;
	}
	if (index < 18)
	{
		res.setCromozome(xGenes, yGenes, combine(zGenes, y.getZ(), index), y.getE());
		return res;
	}
	if (index < 21)
	{
		std::bitset<3> newE;
		std::bitset<3> source = y.getE();
		for (int i = 0; i < index%3; i++) { newE[i] = eGenes[i]; }
		for (int i = index%3; i < 3; i++) { newE[i] = source[i]; }
		res.setCromozome(xGenes, yGenes, zGenes, newE);
		return res;
	}
}

void Cromozome::mutate(short index)
{
	if (index < 6)  xGenes.flip(index % 6);
	if (index < 12) yGenes.flip(index % 6);
	if (index < 18)	zGenes.flip(index % 6);
	if (index < 21) eGenes.flip(index % 3);
}

Cromozome Cromozome::getMutatedChild(short index)
{
	Cromozome res(xGenes, yGenes, zGenes, eGenes);
	res.mutate(index);
	return res;
}

std::bitset<6> Cromozome::combine(std::bitset<6>& source, std::bitset<6> secondPart, short index)
{
	std::bitset<6> res;
	for (int i = 0; i < index%6; i++) { res[i] = source[i]; }
	for (int i = index%6; i < 6; i++) { res[i] = secondPart[i]; }
	return res;
}

