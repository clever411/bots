#include "CellPrinter.hpp"

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
	if(cell.plant)
	{
		k = cell.plant->energy / Plant::MAX_ENERGY;
		setFillColor( plantgrad_(k) );
		return *this;
	}

	if(cell.bot)
	{
		k = (cell.bot->energy - cell.bot->dieedge()) / Bot::MAX_ENERGY * 2;
		setFillColor( botgrad_(k) );
		return *this;
	}

	if(cell.body)
	{
		k = cell.body->energy / (Bot::AGE_DIE_TAX * 200);
		setFillColor( bodygrad_(k) );
		return *this;
	}

	k = cell.energy / Cell::DEFAULT_GROUND_ENERGY;
	setFillColor( emptygrad_(k) );
	return *this;
}





// end
