#include "CellPrinter.hpp"

#include <iostream>

#include "Cell.hpp"
#include "Plant.hpp"
#include "Bot.hpp"
#include "BotField.hpp"
#include "Body.hpp"
#include "Mineral.hpp"


using namespace clever;
using namespace sf;





// CellPrinter
CellPrinter::CellPrinter()
{
	setPointCount(6);
	setRotation(90);
	setSideSize(30.0f);
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
		// k = cell.mineral->energy / (Body::TOMINERAL_EDGE);
		k = cell.mineral->energy / 100.0;
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





// MapUnitPrinter
MapUnitPrinter::MapUnitPrinter()
{
	setPointCount(6);
	setRotation(90);
	setSideSize(30.0f);
	return;
}


MapUnitPrinter &MapUnitPrinter::setSideSize(float a)
{
	setRadius(a);
	setOrigin(a, a);
	return *this;
}

MapUnitPrinter &MapUnitPrinter::set(MapUnit const &unit)
{
	static constexpr double const ALPHA = 0.001;

	double k;
	double denmult = ( unit.density == 0 ? 0.0 : 1.0 / unit.density );

	switch(mode)
	{
	case groundmode:
		k = ( unit.grounden / Cell::DEFAULT_GROUND_ENERGY ) * denmult;
		if(k < ALPHA)
			setFillColor( Color::Transparent );
		else
			setFillColor( groundgrad(k) );
		return *this;
	case airmode:
		k = ( unit.airen / Cell::DEFAULT_AIR_ENERGY ) * denmult;
		if(k < ALPHA)
			setFillColor( Color::Transparent );
		else
			setFillColor( airgrad(k) );
		return *this;
	case plantmode:
		k = 2.0 * ( unit.planten / Plant::MAX_ENERGY ) * denmult;
		if(k < ALPHA)
			setFillColor( Color::Transparent );
		else
			setFillColor( plantgrad(k) );
		return *this;
	case botmode:
		k = 2.0 * ( unit.boten / Bot::MAX_ENERGY ) * denmult;
		if(k < ALPHA)
			setFillColor( Color::Transparent );
		else
			setFillColor( botgrad(k) );
		return *this;
	case bodymode:
		k = 2.0 * ( unit.bodyen / Bot::DEATH_EDGE ) * denmult;
		if(k < ALPHA)
			setFillColor( Color::Transparent );
		else
			setFillColor( bodygrad(k) );
		return *this;
	case mineralmode:
		k = 2.0 * ( unit.mineralen / 100.0 ) * denmult;
		if(k < ALPHA)
			setFillColor( Color::Transparent );
		else
			setFillColor( mineralgrad(k) );
		return *this;
	default:
		throw std::logic_error("MapUnitPrinter::set() -> unknown mode");
	}
}


MapUnitPrinter &MapUnitPrinter::setMode(Mode newmode)
{
	mode = newmode;
	return *this;
}





// end
