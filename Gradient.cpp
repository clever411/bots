#include "Gradient.hpp"

using namespace clever;
using namespace sf;





// fun
Color Gradient::operator()(float k) const
{
	int const n = colors.size()-1;
	if(n == 0)
		return colors.front();

	int const i = int(n*k);
	if(i >= n)
		return colors.back();

	k = ( k - float(i)/n ) * n;
	return Color(
		colors[i].r + (colors[i+1].r - colors[i].r)*k,
		colors[i].g + (colors[i+1].g - colors[i].g)*k,
		colors[i].b + (colors[i+1].b - colors[i].b)*k,
		colors[i].a + (colors[i+1].a - colors[i].a)*k
	);
}



// objects
Gradient const Gradient::DARKLING_RED = Gradient{
	{ Color(0xf0, 0x70, 0x70), Color(0x90, 0x00, 0x00) }
};

Gradient const Gradient::DARKLING_GREEN = Gradient{
	{ Color(0x70, 0xf0, 0x70), Color(0x00, 0x90, 0x00) }
};

Gradient const Gradient::DARKLING_BLUE = Gradient{
	{ Color(0x70, 0x70, 0xf0), Color(0x00, 0x00, 0x90) }
};

Gradient const Gradient::DARKLING_YELLOW = Gradient{
	{ Color(0xf0, 0xf0, 0x70), Color(0x90, 0x90, 0x00) }
};

Gradient const Gradient::DARKLING_MAGENTA = Gradient{
	{ Color(0xf0, 0x70, 0xf0), Color(0x90, 0x00, 0x90) }
};

Gradient const Gradient::DARKLING_CYAN = Gradient{
	{ Color(0x70, 0xf0, 0xf0), Color(0x00, 0x90, 0x90) }
};

Gradient const Gradient::DARKLING_RRG = Gradient{
	{ Color(0xff, 0x90, 0x40), Color(0x90, 0x40, 0x00) }
};




Gradient Gradient::gen(int f, int s)
{
	auto const dispatch = [](int f)->int
	{
		switch(f)
		{
		case 'r':
			return 0;
		case 'g':
			return 1;
		default:
			return 2;
		}
	};

	f = dispatch(f);
	s = dispatch(s);
	int t = 3-(f+s);
	uint8_t el[2][3];

	el[0][f] = 0xff;
	el[0][s] = 0xaa;
	el[0][t] = 0x66;

	el[1][f] = 0xc0;
	el[1][s] = 0x60;
	el[1][t] = 0x30;

	return { {
		Color(el[0][0], el[0][1], el[0][2]),
		Color(el[1][0], el[1][1], el[1][2])
	} };
}





// end
