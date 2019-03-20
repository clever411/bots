#include "CellPrinter.hpp"





// core
CellPrinter::CellPrinter(Cell const &cell)
{
	set(cell);
	return;
}

CellPrinter &CellPrinter::set(Cell const &cell)
{
	static constexpr int const
		WHITE = 0xaa;
	static constexpr auto const
		fun = [](int i) { return i > WHITE ? WHITE : i; };

	double k;

	if(cell.body)
	{
		if(last_ != body)
		{
			// set body
		}
		k = cell.body->energy / (Bot::AGE_DIE_TAX * 100);
		if(k > 1.0)
			k = 1.0;
		setFillColor( sf::Color(
			0xaa, 0x00, 0xaa,
			int(0xff * k)
		) );

		last_ = body;
		return *this;
	}

	if(last_ == body)
	{
		// set no body
	}

	if(cell.plant)
	{
		k = cell.plant->energy / Plant::MAX_ENERGY;
		setFillColor( sf::Color(
			WHITE - fun( int(0xff * 2*k) ),
			0xff - int(k > 0.5 ? 0xff*(k-0.5) : 0),
			WHITE - fun( int(0xff * 2*k) ),
			0xaa
		) );

		last_ = plant;
		return *this;
	}

	if(cell.bot)
	{
		k = (cell.bot->energy - cell.bot->dieedge()) / Bot::MAX_ENERGY * 2;
		if(k > 1.0)
			k = 1.0;
		setFillColor( sf::Color(
			0xff - int(k > 0.5 ? 0xff*(k-0.5) : 0),
			WHITE - fun( int(0xff * 2*k) ),
			WHITE - fun( int(0xff * 2*k) ),
			0xaa
		) );

		last_ = bot;
		return *this;
	}

	// if empty
	k = cell.energy / Cell::DEFAULT_GROUND_ENERGY;
	if(k > 1.0)
		k = 1.0;
	setFillColor( sf::Color(
		0, 0, 0, int(255*k)
	) );


	last_ = empty;
	return *this;
}





// end
