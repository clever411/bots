#include "LibConfig.hpp"

#include <iostream>





namespace clever
{





char hextodec(char ch) noexcept
{
	if(std::isdigit(ch))
		return ch-'0';
	if(ch >= 'a' && ch <= 'f')
		return ch-'a'+10;
	if(ch >= 'A' && ch <= 'F')
		return ch-'A'+10;
	return 0;
}

int hextodec( std::string const &s ) noexcept
{
	int mult = 1;
	int result = 0;
	for( auto b = s.rbegin(), e = s.rend(); b != e; ++b )
	{
		result += hextodec(*b)*mult;
		mult *= 16;
	}
	return result;
}

void tolower( std::string &s ) noexcept
{
	for(auto b = s.begin(), e = s.end(); b != e; ++b)
		*b = std::tolower(*b);
	return;
}

uint32_t tocolor( std::string s ) noexcept
{
	tolower(s);

	// write, black
	if(s.empty() || s == "black")
		return 0x000000ffu;
	if(s == "white")
		return 0xffffffffu;
	// rgb
	if(s == "red")
		return 0xff0000ffu;
	if(s == "green")
		return 0x00ff00ffu;
	if(s == "blue")
		return 0x0000ffffu;

	// double-mix
	if(s == "yellow")
		return 0xffff00ffu;
	if(s == "magenta")
		return 0xff00ffffu;
	if(s == "cyan")
		return 0x00ffffffu;

	// transparent
	if(s == "transparent")
		return 0;


	// color represented by hex number
	if(s.size() == 6)
	{
		return 
			( ( hextodec(s[0])*16 + hextodec(s[1]) ) << 24 ) +
			( ( hextodec(s[2])*16 + hextodec(s[3]) ) << 16 ) +
			( ( hextodec(s[4])*16 + hextodec(s[5]) ) << 8 ) +
			0x000000ff;
	}
	else if(s.size() == 8)
	{
		return 
			( ( hextodec(s[0])*16 + hextodec(s[1]) ) << 24 ) +
			( ( hextodec(s[2])*16 + hextodec(s[3]) ) << 16 ) +
			( ( hextodec(s[4])*16 + hextodec(s[5]) ) << 8 ) +
			( hextodec(s[6])*16 + hextodec(s[7]) );
	}


	// by default return black
	return 0x000000ff;
}





}





// end
