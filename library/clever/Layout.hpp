#ifndef CLEVER_LAYOUT_HPP
#define CLEVER_LAYOUT_HPP


#include <vector>

#include <clever/Point.hpp>





namespace clever
{
	
	
	
	
	
// пользоваться следующим образом:
//   1) создать экземпляр
//   2) установить размер 
//   3) в зависимости от желаемой структуры компоновки
//      установить type, mode, добавить детей, настоить их
//   4) вызвать функцию adjust()
//   5) пользоваться, вызывая необходимые функции
struct Layout
{
	struct Child
	{
		Layout *layout = nullptr;
		float weight = 1.0f;

	};

	struct Place
	{
		Layout *layout;
		int i;

		inline PointF operator()() const
		{
			return (*layout)(i);
		}

		inline PointF center() const
		{
			return layout->center(i);
		}

		inline PointF point() const
		{
			return layout->point(i);
		}

		inline PointF bounds() const
		{
			return layout->bounds(i);
		}

		inline PointF local() const
		{
			return layout->local(i);
		}
	};

	struct PlaceConst
	{
		Layout const *layout;
		int i;

		inline PointF operator()() const
		{
			return (*layout)(i);
		}

		inline PointF center() const
		{
			return layout->center(i);
		}

		inline PointF point() const
		{
			return layout->point(i);
		}

		inline PointF bounds() const
		{
			return layout->bounds(i);
		}

		inline PointF local() const
		{
			return layout->local(i);
		}
	};



	enum Type
	{
		horizontal, vertical
	};

	enum LocalType
	{
		first, second
	};

	enum Mode
	{
		centermode, pointmode, boundsmode, localmode
	};





	// определяет точку отсчёта, относительно которой будет
	// делаться позиционирование и настройка детей
	PointF refp = { 0.0f, 0.0f };

	// определяет размеры, в которых будет производиться
	// позиционирование и настройка детей
	PointF size = { 1.0f, 1.0f };

	// определяет, как будет вычисляться возвращаемое значение
	// метода operator()()
	Mode mode = centermode;

	// определяет позиционирование детей относительно друг друга
	Type type = horizontal;

	// определяет количество по горизонтали и вертикали логальных
	// объектов
	PointI locn = { 1, 1 };

	// определяет способ вычисления центра локальных объектов
	Point<LocalType> loctype = { first, first };

	// определяет количество мест, которыми располагает этот объект
	int count = 1;

	// содержит детей, а также их веса, который влияют на то, сколько
	// относительно друг друга дети будут занимать место
	std::vector<Child> childs = {};
	


	
	


	// возвращает точку в зависимости от mode:
	// если установлен centermode — center(),
	// pointmode — point(),
	// boundsmode — bounds(),
	// localmode — local()
	PointF operator()() const;
		
	// находит потока, соответствующего месту i и
	// возвращает точку, зависящую от ЕГО режима (mode)
	PointF operator()(int i) const;



	// возвращает точку центра ЭТОГО объекта
	inline PointF center() const
	{
		return refp + size/2.0f;
	}
	// возвращает точку центра объекта, расположенного
	// по месту i (может быть и локального, но в этом случае
	// центр вычисляется, как если бы loctype = {first, first})
	PointF center(int i) const;



	// возвращает точку отсчёта ЭТОГО объекта
	inline PointF point() const
	{
		return refp;
	}
	// возвращает точку отсчёта объекта, расположенного
	// по месту i (может быть и локального, но в этом случае
	// центр вычисляется, как если бы loctype = {first, first}))
	PointF point(int i) const;



	// возвращает размеры ЭТОГО объекта 
	inline PointF bounds() const
	{
		return size;
	}
	// возвращает размеры объекта, расположенного по месту
	// i (может быть и локального, но в этом случае
	// центр вычисляется, как если бы loctype = {first, first}))
	PointF bounds(int i) const;



	// возвращает точку — центр локального объекта,
	// который просчитывается в зависимости от локального
	// режима first или second
	inline PointF local(int i) const
	{
		return local( makep(i/locn.y, i%locn.y) );
	}
	PointF local(PointI const &p) const;

		



	// даёт доступ к ребёнку 
	inline Layout &operator[](int i)
	{
		return *childs[i].layout;
	}
	inline Layout const &operator[](int i) const
	{
		return *childs[i].layout;
	}





	// добавляет n или weights.size() детей в конец
	// устанавливая веса в 1.0 (в первом случае) либо
	// weights[i] (во втором случае)
	void push(int n);
	void push(std::vector<float> const &weights);



	// устанавливает режим (mode) в localmode, устанавливает
	// locn.x, locn.y, loctype.x, loctype.y. Осторожно! — если
	// вы оставите аргументы по умолчанию, то установятся
	// аргументы по умолчанию, а не останется, как было
	void setloc(
		int xn = 1, int yn = 1,
		LocalType xtype = first,
		LocalType ytype = first
	);
	void setloc(
		PointI const &n = {1, 1},
		Point<LocalType> const &type = { first, first }
	);



	// выполняет глубокий обход по дереву-графу потомства,
	// с каждым потомком в качестве аргумента вызывает 
	// унарную функцию fun()
	template<typename UnaryFunction>
	void foreach(UnaryFunction fun)
	{
		if(childs.empty())
			return;
		for(auto &i : childs)
		{
			i.layout->foreach(fun);
			fun(*i.layout);
		}
		return;
	}

	// выполняет обход по каждому листу, т.е. потомку,
	// у которого нет своих потомков (или же он находится
	// в режиме localmode, ведь в этом случае он выполняет
	// роль листа — он никак не использует своих детей)
	template<typename UnaryFunction>
	void foreachleaf(UnaryFunction fun)
	{
		if(childs.empty() || mode == localmode)
		{
			fun(*this);
			return;
		}

		for(auto &l : childs)
			l.layout->foreachleaf(fun);

		return;
	}



	// при установке новых значений (refp, size, type)
	// необходимо вызывать эту функцию, чтобы она правильно
	// настроила потомков
	void adjust();

	// уничтожает всех потомков
	void free();



	// находит потомка, который соответствует месту i или
	// потомка, потомок которого соответствует месту i, для
	// второго случая структура Place также содержит открытый
	// член i — место относительно найденного потомка
	Place place(int i);
	PlaceConst place(int i) const;



};





}





#endif
