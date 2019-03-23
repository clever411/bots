#ifndef CLEVER_CLASSMACROS_HPP
#define CLEVER_CLASSMACROS_HPP





#define FIELD(type, name) \
	public: \
	type name() const { \
		return _##name; \
	} \
	auto& name(type const &new##name) { \
		_##name = new##name; \
		return *this; \
	} \
	private: \
	type _##name;

#define FIELD_COPY(type, name) \
	public: \
	type name() const { \
		return _##name; \
	} \
	auto& name(type new##name) { \
		_##name = new##name; \
		return *this; \
	} \
	private: \
	type _##name;

#define FIELD_RVALUE(type, name) \
	public: \
	type name() const { \
		return _##name; \
	} \
	auto& name(type &&new##name) { \
		_##name = new##name; \
		return *this; \
	} \
	auto& name(type const &new##name) { \
		_##name = new##name; \
		return *this; \
	}\
	private: \
	type _##name;

#define FIELD_POINTER_HOLD(type, name) \
	public: \
	type* name() const { \
		return _##name; \
	} \
	auto& name(type *new##name) { \
		if(_##name) \
			delete _##name; \
		_##name = new##name; \
		return *this; \
	} \
	private: \
	type *_##name;




#endif
