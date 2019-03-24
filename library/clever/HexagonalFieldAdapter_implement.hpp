#include <algorithm>
#include <cmath>

// create
template<typename T, class Printer>
HexagonalFieldAdapter<T, Printer>::HexagonalFieldAdapter(
	fieldptr_type field,
	sf::Vector2f const &size
): field_(field), size_(size)
{
	adjust_();
	return;
}





// core
template<typename T, class Printer>
HexagonalFieldAdapter<T, Printer> &
HexagonalFieldAdapter<T, Printer>::update()
{
	return *this;
}

template<typename T, class Printer>
PointI HexagonalFieldAdapter<T, Printer>::cursorOn(
	int x, int y
) const
{
	PointF p(x-side_, y-0.866025*side_);
	PointI fp, sp;
	int const
		i = int( p.x / (1.5f*side_) ),
		j = int( p.y / (0.866025*side_) );
	if(i%2 == j%2)
	{
		fp = { i, j };
		sp = { i+1, j+1 };
	}
	else
	{
		fp = { i+1, j };
		sp = { i, j+1 };
	}
	return
		field_->origin(fp, side_).dis(p) <
		field_->origin(sp, side_).dis(p) ? fp : sp;
}

template<typename T, class Printer>
void HexagonalFieldAdapter<T, Printer>::draw(
	sf::RenderTarget &target,
	sf::RenderStates states
) const
{
	states.transform *= getTransform();
	PointF pos;
	for(auto b = field_->begin(), e = field_->end(); b != e; ++b)
	{
		pos = field_->origin(b, side_);
		pos.x += side_;
		pos.y += 0.866025*side_;
		printer_->setPosition(pos);
		printer_->set(*b);
		target.draw(*printer_, states);
	}

	return;
}





// field
template<typename T, class Printer>
HexagonalFieldAdapter<T, Printer> &
HexagonalFieldAdapter<T, Printer>::setField(
	fieldptr_type newfield
)
{
	field_ = newfield;
	return *this;
}

template<typename T, class Printer>
typename HexagonalFieldAdapter<T, Printer>::fieldptr_type 
HexagonalFieldAdapter<T, Printer>::getField() const
{
	return field_;
}





// printer
template<typename T, class Printer>
HexagonalFieldAdapter<T, Printer> &
HexagonalFieldAdapter<T, Printer>::setPrinter(
	printerptr_type newprinter
)
{
	printer_ = newprinter;
	adjust_();
	return *this;
}

template<typename T, class Printer>
typename HexagonalFieldAdapter<T, Printer>::printerptr_type
HexagonalFieldAdapter<T, Printer>::getPrinter() const
{
	return printer_;
}





// size
template<typename T, class Printer>
HexagonalFieldAdapter<T, Printer> &
HexagonalFieldAdapter<T, Printer>::setSize(
	sf::Vector2f const &newsize
)
{
	size_ = newsize;
	adjust_();
	return *this;
}

template<typename T, class Printer>
sf::Vector2f const &
HexagonalFieldAdapter<T, Printer>::getSize() const
{
	return size_;
}






// private
template<typename T, class Printer>
void HexagonalFieldAdapter<T, Printer>::adjust_()
{
	side_ = std::min(
		size_.x / ( 3.0f * field_->w + 0.5f ),
		1.154701f*size_.y / ( 1.0f + field_->h )
	);
	printer_->setSideSize(side_);
	return;
}







// end
