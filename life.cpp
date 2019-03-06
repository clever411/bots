#include "life.hpp"

#include "declare.hpp"





bool update_cell_tape(int x, int y)
{
	int count = 0;

	if( field.tapeAt( x-1, y-1 ) )
		++count;
	if( field.tapeAt( x, y-1 ) )
		++count;
	if( field.tapeAt( x+1, y-1 ) )
		++count;

	if( field.tapeAt( x-1, y ) )
		++count;
	if( field.tapeAt( x+1, y ) )
		++count;

	if( field.tapeAt( x-1, y+1 ) )
		++count;
	if( field.tapeAt( x, y+1 ) )
		++count;
	if( field.tapeAt( x+1, y+1 ) )
		++count;

	return field.at(x, y) ?
		( count == 2 || count == 3 ) :
		( count == 3 );
}

bool update_cell_cut(int x, int y)
{
	int count = 0;

	if( field.isValid(x-1, y-1) && field.at( x-1, y-1 ) )
		++count;
	if( field.isValid(x, y-1) && field.at( x, y-1 ) )
		++count;
	if( field.isValid(x+1, y-1) && field.at( x+1, y-1 ) )
		++count;

	if( field.isValid(x-1, y) && field.at( x-1, y ) )
		++count;
	if( field.isValid(x+1, y) && field.at( x+1, y ) )
		++count;

	if( field.isValid(x-1, y+1) && field.at( x-1, y+1 ) )
		++count;
	if( field.isValid(x, y+1) && field.at( x, y+1 ) )
		++count;
	if( field.isValid(x+1, y+1) && field.at( x+1, y+1 ) )
		++count;

	return field.at(x, y) ?
		( count == 2 || count == 3 ) :
		( count == 3 );
}

void update_field()
{
	static field_type spf = {0, 0, nullptr};
	if(spf.w != field.w || spf.h != field.h)
	{
		if(spf.d)
			spf.free();
		spf.init( field.w, field.h );
	}

	for(int y = 0; y < field.h; ++y)
	for(int x = 0; x < field.w; ++x)
	{
		spf.at(x, y) = update_cell_cut(x, y) ? 1 : 0;
	}

	std::swap( field.d, spf.d );
	return;
}





// end
