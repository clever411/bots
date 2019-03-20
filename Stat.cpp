#include "Stat.hpp"





void Stat::add(
	float summen,
	float grounden,
	float planten,
	float boten,
	float bodyen
)
{
	code_.push_back( {
		summen, grounden, planten, boten, bodyen
	} );
	return;
}
void Stat::write(char const *filename) const
{
	auto file = fopen(filename, "w");
	for(int i = 0; i < code_.size(); ++i)
	{
		fprintf(
			file, "%i %f %f %f %f %f\n", 
			i,
			code_[i].summ,
			code_[i].ground,
			code_[i].plant,
			code_[i].bot,
			code_[i].body
		);
	}
	fclose(file);
	return;
}
void Stat::reset()
{
	code_.clear();
	return;
}





// end
