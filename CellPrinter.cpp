#include "CellPrinter.hpp"

#include "declare.hpp"

using namespace sf;





CellPrinter::CellPrinter(int value)
{
	set(value);
	return;
}

CellPrinter::~CellPrinter() {}

CellPrinter &CellPrinter::set(int value)
{
	switch(value)
	{
	case 0:
		setFillColor( Color::Transparent );
		break;
	default:
		setFillColor( Color( maincolor ) );
		break;
	}
	return *this;
}





// end
