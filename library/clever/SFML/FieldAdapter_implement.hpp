// implement of class FieldAdapter





// constructor desturctor
template<typename ValueType, class PrinterType>
FieldAdapter<ValueType, PrinterType>::FieldAdapter(
	fieldptr_type field,
	sf::Vector2f const &size
): field_(field)
{
	setSize(size);
	return;
}





// using methods
template<typename ValueType, class PrinterType>
FieldAdapter<ValueType, PrinterType> &
FieldAdapter<ValueType, PrinterType>::update()
{
	if(ischanged_)
		adjust_();
	return *this;
}


template<typename ValueType, class PrinterType>
void FieldAdapter<ValueType, PrinterType>::draw(
	sf::RenderTarget &target, sf::RenderStates states
) const
{
	printer_.setSize({_cellsize, _cellsize});
	printer_.setPosition(
		{boundsoffset_.x+bordersize,
		boundsoffset_.y+bordersize}
	);
	states.transform *= sf::Transformable::getTransform();

	target.draw(_background, states);
	for(unsigned int y = 0; y < field_->h; ++y) {
		for(unsigned int x = 0; x < field_->w; ++x) {
			printer_.set(field_->at(x, y));
			target.draw(printer_, states);
			printer_.move(_cellsize+2*bordersize, 0.0);
		}
		printer_.move(
			-int(field_->w)*(_cellsize+2*bordersize),
			_cellsize+2*bordersize
		);
	}

	return;
}


template<typename ValueType, class PrinterType>
std::pair<int, int>
FieldAdapter<ValueType, PrinterType>::cursorOn(
	sf::Vector2f const &point) const
{
	int x = point.x/(_cellsize+2*bordersize);
	int y = point.y/(_cellsize+2*bordersize);

	if(x < 0 || x >= field_->w || y < 0 || y >= field_->h)
		return std::pair<unsigned int, unsigned int>(-1, -1);
	else 
		return std::pair<unsigned int, unsigned int>(
			(unsigned int)(x), (unsigned int)(y)
		);
}







// size
template<typename ValueType, class PrinterType>
bool FieldAdapter<ValueType, PrinterType>::isResized() const
{
	return _isresized;
}


template<typename ValueType, class PrinterType>
FieldAdapter<ValueType, PrinterType> &
FieldAdapter<ValueType, PrinterType>::resetResized()
{
	_isresized = false;
	return *this;
}



template<typename ValueType, class PrinterType>
sf::Vector2f FieldAdapter<ValueType, PrinterType>::getSize() const
{
	return size_;
}


template<typename ValueType, class PrinterType>
FieldAdapter<ValueType, PrinterType> &
FieldAdapter<ValueType, PrinterType>::setSize(
	sf::Vector2f const &newsize
)
{
	if(size_.x != newsize.x || size_.y != newsize.y) {
		size_ = newsize;
		ischanged_ = true;
		_isresized = true;
	}
	return *this;
}





// field
template<typename ValueType, class PrinterType>
typename FieldAdapter<ValueType, PrinterType>::fieldptr_type
FieldAdapter<ValueType, PrinterType>::getField() const
{
	return field_;
}


template<typename ValueType, class PrinterType>
FieldAdapter<ValueType, PrinterType> &
FieldAdapter<ValueType, PrinterType>::setField(
	fieldptr_type newfield
)
{
	field_ = newfield;
	ischanged_ = true;
	return *this;
}





// printer
template<typename ValueType, class PrinterType>
typename FieldAdapter<ValueType, PrinterType>::printer_type const &
FieldAdapter<ValueType, PrinterType>::getPrinter() const
{
	return printer_;
}


template<typename ValueType, class PrinterType>
FieldAdapter<ValueType, PrinterType> &
FieldAdapter<ValueType, PrinterType>::setPrinter(
	printer_type const &newprinter
)
{
	printer_ = newprinter;
}





// border
template<typename ValueType, class PrinterType>
float FieldAdapter<ValueType, PrinterType>::getBordertocell() const
{
	return _bordertocell;
}


template<typename ValueType, class PrinterType>
FieldAdapter<ValueType, PrinterType> &
FieldAdapter<ValueType, PrinterType>::setBordertocell(
	float newbordertocell
)
{
	_bordertocell = newbordertocell;
	ischanged_ = true;
	return *this;
}





// bounds
	// enable
template<typename ValueType, class PrinterType>
bool FieldAdapter<ValueType, PrinterType>::isDrawBoundsEnable() const
{
	return _drawbounds;
}


template<typename ValueType, class PrinterType>
FieldAdapter<ValueType, PrinterType> &
FieldAdapter<ValueType, PrinterType>::setDrawBoundsEnable(bool enable)
{
	_drawbounds = enable;
	ischanged_ = true;
	return *this;
}


	// width
template<typename ValueType, class PrinterType>
float FieldAdapter<ValueType, PrinterType>::getBoundsWidth() const
{
	return _boundswidth;
}


template<typename ValueType, class PrinterType>
FieldAdapter<ValueType, PrinterType> &
FieldAdapter<ValueType, PrinterType>::setBoundsWidth(
	float newboundswidth
)
{
	_boundswidth = newboundswidth;
	ischanged_ = true;
	return *this;
}


	// color
template<typename ValueType, class PrinterType>
sf::Color const &
FieldAdapter<ValueType, PrinterType>::getBoundsColor() const
{
	return _boundscolor;
}
template<typename ValueType, class PrinterType>
FieldAdapter<ValueType, PrinterType> &
FieldAdapter<ValueType, PrinterType>::setBoundsColor(
	sf::Color const &newboundscolor
)
{
	_boundscolor = newboundscolor;
	ischanged_ = true;
	return *this;
}





// grid
	// enable
template<typename ValueType, class PrinterType>
bool FieldAdapter<ValueType, PrinterType>::isDrawGridEnable() const
{
	return _drawgrid;
}


template<typename ValueType, class PrinterType>
FieldAdapter<ValueType, PrinterType> &
FieldAdapter<ValueType, PrinterType>::setDrawGridEnable(bool enable)
{
	_drawgrid = enable;
	ischanged_ = true;
	return *this;
}


	// width
template<typename ValueType, class PrinterType>
float FieldAdapter<ValueType, PrinterType>::getGridWidth() const
{
	return _gridwidth;
}


template<typename ValueType, class PrinterType>
FieldAdapter<ValueType, PrinterType> &
FieldAdapter<ValueType, PrinterType>::setGridWidth(float newgridwidth)
{
	_gridwidth = newgridwidth;
	ischanged_ = true;
	return *this;
}


	// color
template<typename ValueType, class PrinterType>
sf::Color const &FieldAdapter<ValueType, PrinterType>::getGridColor() const
{
	return _gridcolor;
}


template<typename ValueType, class PrinterType>
FieldAdapter<ValueType, PrinterType> &
FieldAdapter<ValueType, PrinterType>::setGridColor(
	sf::Color const &newgridcolor
)
{
	_gridcolor = newgridcolor;
	ischanged_ = true;
	return *this;
}
	






// implement
template<typename ValueType, class PrinterType>
void FieldAdapter<ValueType, PrinterType>::adjust_()
{
	auto rsize = size_;
	if(_drawbounds) {
		rsize.x -= 2*_boundswidth;
		rsize.y -= 2*_boundswidth;
	}

	// cell
	float fullcellsize;
	float cwidth = float(rsize.x)/field_->w;
	float cheight = float(rsize.y)/field_->h;

	if(cwidth < cheight)
	{
		fullcellsize = cwidth;
		size_.y = fullcellsize*field_->h +
			( _drawbounds ? 2*_boundswidth : 0 );
		rsize.y = _drawbounds ? size_.y-2*_boundswidth : size_.y;
	}
	else
	{
		fullcellsize = cheight;
		size_.x = fullcellsize*field_->w +
			(_drawbounds ? 2*_boundswidth : 0);
		rsize.x = _drawbounds ? size_.x-2*_boundswidth : size_.x;
	}
	_isresized = true;

	_cellsize = fullcellsize / (2*_bordertocell + 1);
	bordersize = (fullcellsize-_cellsize)/2;

	// bounds offset
	if(_drawbounds)
		boundsoffset_ = {_boundswidth, _boundswidth};
	else
		boundsoffset_ = {0, 0};

	



	// draw
	_rtexture.create(size_.x, size_.y);


	// draw grid
	if(_drawgrid)
	{
		sf::RectangleShape rect;
		rect.setFillColor(_gridcolor);


		// Horizontal
		rect.setSize(
			{field_->w*(_cellsize+2*bordersize), _gridwidth}
		);
		rect.setPosition(
			{boundsoffset_.x, boundsoffset_.y-_gridwidth/2}
		);
		_rtexture.draw(rect);
		for(unsigned short int y = 0; y < field_->h; ++y)
		{
			rect.move(0.0, _cellsize+2*bordersize);
			_rtexture.draw(rect);
		}


		// Vertical
		rect.setSize(
			{_gridwidth, field_->h*(_cellsize+2*bordersize)}
		);
		rect.setPosition(
			{boundsoffset_.x-_gridwidth/2, boundsoffset_.y}
		);
		_rtexture.draw(rect);
		for(unsigned short int x = 0; x < field_->w; ++x)
		{
			rect.move(_cellsize+2*bordersize, 0.0);
			_rtexture.draw(rect);
		}
	}



	// draw bounds
	if(_drawbounds)
	{
		sf::RectangleShape rect;
		rect.setFillColor(_boundscolor);
		

		// Horizontal
		rect.setSize({size_.x, _boundswidth});
		_rtexture.draw(rect);

		rect.setPosition({0.0f, size_.y-_boundswidth});
		_rtexture.draw(rect);


		// Verical
		rect.setPosition({0.0f, 0.0f});
		rect.setSize({_boundswidth, size_.y});
		_rtexture.draw(rect);

		rect.setPosition({size_.x-_boundswidth, 0.0f});
		_rtexture.draw(rect);

	}



	// display
	_rtexture.display();
	_background.setTexture(_rtexture.getTexture(), true);

	ischanged_ = false;

	return;
}





// end
