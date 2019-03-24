#ifndef CLEVER_SFML_FIELD_ADAPTER_HPP
#define CLEVER_SFML_FIELD_ADAPTER_HPP

#include <memory>

#include <SFML/Graphics.hpp>

#include <clever/Field.hpp>
#include <clever/SFML/HelpFunction.hpp>





namespace clever
{





template<typename ValueType, class PrinterType>
class FieldAdapter: public sf::Transformable, public sf::Drawable
{
public:
	// types
	typedef ValueType value_type;
	typedef Field<value_type> field_type;
	typedef std::shared_ptr< field_type > fieldptr_type;
	typedef PrinterType printer_type;





	// constructor
	FieldAdapter(
		fieldptr_type field = nullptr,
		sf::Vector2f const &size = {400.0f, 200.0f}
	);





	// using methods
	FieldAdapter &update();

	virtual void draw(
		sf::RenderTarget &target,
		sf::RenderStates states = sf::RenderStates::Default
	) const override;


	std::pair<int, int> cursorOn(
		sf::Vector2f const &point
	) const;



	// size
	FieldAdapter &resetResized();
	bool isResized() const;
	
	FieldAdapter &setSize(sf::Vector2f const &newsize);
	sf::Vector2f getSize() const;



	// field
	FieldAdapter &setField(fieldptr_type newfield);
	fieldptr_type getField() const;



	// printer
	FieldAdapter &setPrinter(printer_type const &newprinter);
	printer_type const &getPrinter() const;



	// border to cell ratio
	FieldAdapter &setBordertocell(float newbordertocell);
	float getBordertocell() const;



	// bounds
	FieldAdapter &setDrawBoundsEnable(bool enable);
	bool isDrawBoundsEnable() const;

	FieldAdapter &setBoundsWidth(float newboundswidth);
	float getBoundsWidth() const;

	FieldAdapter &setBoundsColor(sf::Color const &newboundscolor);
	sf::Color const &getBoundsColor() const;



	// grid
	FieldAdapter &setDrawGridEnable(bool enable);
	bool isDrawGridEnable() const;

	FieldAdapter &setGridWidth(float newgridwidth);
	float getGridWidth() const;
	
	FieldAdapter &setGridColor(sf::Color const &newgridcolor);
	sf::Color const &getGridColor() const;





private:
	void adjust_();

	// base
	sf::Vector2f size_;
	fieldptr_type field_;
	mutable printer_type printer_;
	sf::Vector2f boundsoffset_;

	// border, cell
	float bordersize = 0, _cellsize = 0;
	float _bordertocell = 0.1;

	sf::RenderTexture _rtexture;
	sf::Sprite _background;

	// bounds
	bool _drawbounds = true;
	float _boundswidth = 5;
	sf::Color _boundscolor = sf::Color::Black;

	// grid
	bool _drawgrid = true;
	float _gridwidth = 4;
	sf::Color _gridcolor = sf::Color::Black;

	// technical
	bool ischanged_ = false;
	bool _isresized = false;





};





// include implement
#include "FieldAdapter_implement.hpp"





}





#endif
