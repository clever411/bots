#ifndef CLEVER_CHANGING_OBJECT_HPP
#define CLEVER_CHANGING_OBJECT_HPP





namespace clever
{





template<typename ValueType> class ChangingObject
{
public:
	// types
	typedef ValueType value_type;


	// constructor
	ChangingObject() {}
	ChangingObject(value_type const &value): _value(value) {}
	ChangingObject(value_type &&value): _value(std::move(value)) {}



	// change
	void change(value_type const &newvalue)
	{
		_value = newvalue;
		_ischanged = true;
		return;
	}

	void change(value_type &&newvalue)
	{
		_value = std::move(newvalue);
		_ischanged = true;
		return;
	}
		
	value_type& change()
	{
		_ischanged = true;
		return _value;
	}	


	// get
	value_type const &get() const
	{
		return _value;
	}

	operator value_type const &() const
	{
		return _value;
	}



	// is changed info
	bool isChanged() const
	{
		return _ischanged;
	}
	void reset() const
	{
		_ischanged = false;
		return;
	}

private:
	value_type _value;
	mutable bool _ischanged = false;
};





}





#endif
