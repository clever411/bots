#include "Stat.hpp"





Stat::Stat()
{
	code_.reserve(10000);
	return;
}

void Stat::add(Unit const &unit)
{
	code_.push_back(unit);
	return;
}

void Stat::write(char const *filename) const
{
	auto file = fopen(filename, "w");
	for(int i = 0; i < code_.size(); ++i)
	{
		fprintf(
			file, "%i %f %f %f %f %f %f %f\n", 
			i,
			code_[i].summ,
			code_[i].ground,
			code_[i].air,
			code_[i].plant,
			code_[i].bot,
			code_[i].body,
			code_[i].mineral
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
