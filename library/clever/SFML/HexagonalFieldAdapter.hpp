#ifndef CLEVER_HEXAGONAL_FIELD_ADAPTER_HPP
#define CLEVER_HEXAGONAL_FIELD_ADAPTER_HPP

#include <memory>

#include <SFML/Graphics.hpp>

#include <clever/HexagonalField.hpp>





namespace clever
{
	
	
	
	
	
	
	
template<typename T, class Printer>
class HexagonalFieldAdapter: public sf::Transformable, public sf::Drawable
{
public:	
	// types
	typedef T value_type;
	typedef HexagonalField<T> field_type;
	typedef std::shared_ptr<field_type> fieldptr_type;
	typedef Printer printer_type;
	typedef std::shared_ptr<printer_type> printerptr_type;
	
	
	
	
	
	// create
	HexagonalFieldAdapter(
		fieldptr_type field = nullptr,
		sf::Vector2f const &size = {400.0f, 200.0f}
	);
	
	
	
	
	
	// core
	HexagonalFieldAdapter &update();

	PointI cursorOn(int x, int y) const;
	inline PointI cursorOn(PointI const &p) const;

	virtual void draw(
		sf::RenderTarget &target,
		sf::RenderStates states = sf::RenderStates::Default
	) const override;
	
	
	
	
	// set, get
		// field
	HexagonalFieldAdapter &setField(fieldptr_type newfield);
	fieldptr_type getField() const;
	

		// printer
	HexagonalFieldAdapter &setPrinter(printerptr_type newprinter);
	printerptr_type getPrinter() const;
	
	
		// size
	HexagonalFieldAdapter &setSize(sf::Vector2f const &newsize);
	sf::Vector2f const &getSize() const;


		// grid
	HexagonalFieldAdapter &setDrawGridEnable(bool enable);
	bool getDrawGridEnable() const;

	HexagonalFieldAdapter &setGridThickness(float newthick);
	float getGridThickness() const;

	HexagonalFieldAdapter &setGridColor(sf::Color const &newcolor);
	sf::Color const &getGridColor() const;



private:
	void adjust_();

	// data-members
		// main
	fieldptr_type field_;
	mutable printerptr_type printer_ = printerptr_type(new printer_type);

		// sizes
	sf::Vector2f size_;
	float side_;

		// background
	sf::RenderTexture rtexture_;
	sf::Sprite sprite_;
	bool drawgrid_ = true;
	float gridthick_ = 2.0f;
	sf::Color gridcolor_ = sf::Color::White;


};





#include "HexagonalFieldAdapter_implement.hpp"





}





#endif
