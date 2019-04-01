#include "CellPrinter.hpp"
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
	if(cell.plant)
	{
		k = cell.plant->energy / Plant::MAX_ENERGY;
		setFillColor( plantgrad_(k) );
		return *this;
	}

	if(cell.bot)
	{
		k = (cell.bot->energy - cell.bot->deathedge()) / cell.bot->maxenergy();
		setFillColor( botgrad_(k) );
		return *this;
	}

	if(cell.body)
	{
		k = cell.body->energy / (Bot::AGE_DEATH_TAX * 200);
		setFillColor( bodygrad_(k) );
		return *this;
	}

	k = cell.energy / Cell::DEFAULT_GROUND_ENERGY;
	if(k > 1.0)
		k = 1.0;

	double kair = cell.airenergy / 20.0;
	if(kair > 1.0)
		kair = 1.0;

	setFillColor( Color(
		0xff, 0x00, 0x00, 0xff*kair
	) );

	// setFillColor( emptygrad_(k) );
	return *this;
}





// end
