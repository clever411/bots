#include "CellPrinter.hpp"

#include <iostream>

#include "Cell.hpp"
#include "Plant.hpp"
#include "Bot.hpp"
#include "Body.hpp"
#include "Mineral.hpp"


using namespace clever;
using namespace sf;





// core
CellPrinter::CellPrinter()
{
	setPointCount(6);
	setRotation(90);
	setSideSize(30.0f);
	return;
}

CellPrinter::CellPrinter(Cell const &cell):
	CellPrinter()
{
	set(cell);
	return;
}


CellPrinter &CellPrinter::setSideSize(float a)
{
	setRadius(a);
	setOrigin(a, a);
	return *this;
}

CellPrinter &CellPrinter::set(Cell const &cell)
{
	double k;
	if(cell.bot)
	{
		k = (cell.bot->energy - cell.bot->deathedge()) / cell.bot->maxenergy();
		setFillColor( botgrad(k) );
		return *this;
	}

	if(cell.body)
	{
		k = cell.body->energy / (Bot::DEATH_EDGE);
		setFillColor( bodygrad(k) );
		return *this;
	}

	if(cell.plant)
	{
		k = cell.plant->energy / Plant::MAX_ENERGY;
		setFillColor( plantgrad(k) );
		return *this;
	}

	if(cell.mineral)
	{
		k = cell.mineral->energy / (Body::TOMINERAL_EDGE);
		setFillColor( mineralgrad(k) );
		return *this;
	}

	switch(mode)
	{
	case groundmode:
		k = cell.energy / Cell::DEFAULT_GROUND_ENERGY;
		setFillColor( groundgrad(k) );
		break;

	case airmode:
		k = cell.airenergy / Cell::DEFAULT_AIR_ENERGY;
		setFillColor( airgrad(k) );
		break;
	default:
		throw std::logic_error("CellPrinter::set(): invalid mode");
	}

	return *this;
}


CellPrinter &CellPrinter::changeMode()
{
	if(mode == groundmode)
		mode = airmode;
	else
		mode = groundmode;
	return *this;
}





// end
