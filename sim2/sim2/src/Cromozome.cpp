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

std::string Cromozome::cromozomeToString()
{
	return xGenes.to_string() + yGenes.to_string() + zGenes.to_string() + eGenes.to_string();
}

glm::vec4 Cromozome::toVec4()
{
	glm::vec4 res;
	res.x = xGenes.to_ulong();
	res.y = yGenes.to_ulong();
	res.z = zGenes.to_ulong() - 63 / 2;
	res.w = eGenes.to_ulong();
	return res;
}

Cromozome Cromozome::singlePointCrossOver(Cromozome& y, short index)
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

Cromozome Cromozome::twoPointCrossOver(Cromozome& y, short start, short end)
{
	std::bitset<6> xRes = xGenes;
	std::bitset<6> yRes = yGenes;
	std::bitset<6> zRes = zGenes;
	std::bitset<3> eRes = eGenes;
	
	if (start < 6)
	{
		if (end < 6) xRes = twoPointCombination(xGenes, y.xGenes, start, end);
		else if (end < 12) yRes = combine(yGenes, y.yGenes, end);
		else if (end < 18) zRes = combine(zGenes, y.zGenes, end);
		else if (end < 21) eRes = combine(eGenes, y.eGenes, end);
	}
	else if (start < 12)
	{
		if(end<12) yRes = twoPointCombination(yGenes, y.yGenes, start, end);
		else if (end < 18) zRes = combine(zGenes, y.zGenes, end);
		else if (end < 21) eRes = combine(eGenes, y.eGenes, end);
	}
	else if (start < 18)
	{
		if(end < 18) zRes = twoPointCombination(zGenes, y.zGenes, start, end);
		else if (end < 21) eRes = combine(eGenes, y.eGenes, end);
	}
	else if (start < 21)
	{
		eRes = combine(eGenes, y.eGenes, end);
		for (int i = end % 3; i < 3; i++) eRes[i] = eGenes[i];
	}

	return Cromozome(xRes, yRes, zRes, eRes);
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

std::bitset<3> Cromozome::combine(std::bitset<3>& source, std::bitset<3> secondPart, short index)
{
	std::bitset<3> res;
	for (int i = 0; i < index % 3; i++) { res[i] = source[i]; }
	for (int i = index % 3; i < 3; i++) { res[i] = secondPart[i]; }
	return res;
}

std::bitset<6> Cromozome::twoPointCombination(std::bitset<6>& source, std::bitset<6> secondPart, short start, short end)
{
	std::bitset<6> res;
	for (int i = 0; i < start % 6; i++) { res[i] = source[i]; }
	for (int i = start % 6; i < end % 6; i++) { res[i] = secondPart[i]; }
	for (int i = end % 6; i < 6; i++) { res[i] = source[i]; }
	return res;
}

std::bitset<6>& Cromozome::getBitsAtIndex(short index)
{
	if (index < 6) return xGenes;
	if (index < 12) return yGenes;
	if (index < 18) return zGenes;
}

