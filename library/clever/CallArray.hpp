#ifndef CLEVER_CALL_ARRAY_HPP
#define CLEVER_CALL_ARRAY_HPP





/*
 * Структура CallArray предназначена для динамической 
 * диспетчеризации переопределенных методов. Диспетчеризации
 * происходит за счет приведения указателя на экземпляр класса
 * к указателю на экземпляр более старшего в цепочке наследования
 * класса.
 * 
 * Использование происходит следующим образом. Сначала создается
 * класс для вызова нужной функции. Это делается с помощью макроса
 * CLEVER_GEN_FUNCTION_DISPATCHER( functionane ). В макрос передается
 * имя вызываемой функции. Затем наобходимо использовать typedef или 
 * using, конкретизируя структуру CallArray. В первом шаблонном 
 * аргументом является структура сгенерированная с помощью макроса.
 * Ее имя начинается на то слово, что вы передали в макрос, затем
 * идет окончание FunctionDispatcher. Так если вы указали в макросе
 * 'print' то имя структуры будет printFunctionDispatcher.
 * Вторым шаблонным аргументом будет основной класс, для которого
 * будет происходить диспетчеризация.
 * Третьим и более аргументами будут классы, к которым будет 
 * приводится главный(второй аргумент) во время диспетчеризации.
 * Далее следует конкретизировать подструктуру F, которая находится
 * в структуре CallArray. Первым шаблонным аргументом будет 
 * возвращаемое значение функции, далее идут аргументы функции.
 * Собственно для диспетчеризации необходимо вызывать функцию
 * из массива функций в подструктуре F. Массив функций имеет имя c.
 * Количество элементов в массиве - количество тех классов к которым
 * будет приводится основной(это те что указываются в структуре 
 * CallArray на местре >= 3). Вызов c[0]() произведет диспетчеризацию
 * к первому указаному классу. И так далее.
 * 
 * Пример. Допустим наше имя функции - print. Она возвращает void и 
 * непринимает никаких аргументов.
 * 1 - Генерация FunctionDispatcher:
 *         CLEVER_GEN_FUNCTION_DISPATCHER( print )
 * 2 - Затем наобходим typedef:
 *         typedef CallArray<printFunctionDispatcher, C, A, B, C>::F<void> f;
 * 3 - Теперь мы можем использовать наш диспетчеризатор:
 *         f::c[0](pointerToC); // Вызовет A::print();
 *         f::c[1](pointerToC); // Вызовет B::print();
 *         f::c[2](pointerToC); // Вызовет C::print();
 */

namespace clever
{

	// call array
	template<
		template<class, class, typename, typename...>
		class FunctionDispatcher, class Main, class...Args
	>
	struct CallArray;





	// for one
	template<
		template<class, class, typename, typename...>
		class FunctionDispatcher,
		class Main, class C1
	>
	struct CallArray<FunctionDispatcher, Main, C1>
	{
		template<typename ReturnValue, typename...FunArgs> struct F
		{
			static ReturnValue(*const c[])(Main *, FunArgs...); 
		};
	};


	template<
		template<class, class, typename, typename...>
		class FunctionDispatcher,
		class Main, class C1
	>
	template<typename ReturnValue, typename...FunArgs>
	ReturnValue(
		*const CallArray<
			FunctionDispatcher, Main, C1
		>::F<ReturnValue, FunArgs...>::c[]
	)(Main *, FunArgs...) =
	{
		&FunctionDispatcher<Main, C1, ReturnValue, FunArgs...>::work
	};





	// for two
	template<
		template<class, class, typename, typename...>
		class FunctionDispatcher,
		class Main, class C1, class C2
	>
	struct CallArray<FunctionDispatcher, Main, C1, C2>
	{
		template<typename ReturnValue, typename...FunArgs>
		struct F
		{
			static ReturnValue(*const c[])(Main *, FunArgs...); 
		};
	};


	template<
		template<class, class, typename, typename...>
		class FunctionDispatcher,
		class Main, class C1, class C2
	>
	template<typename ReturnValue, typename...FunArgs>
	ReturnValue(
		*const CallArray<
			FunctionDispatcher, Main, C1, C2
		>::F<ReturnValue, FunArgs...>::c[]
	)(Main *, FunArgs...) =
	{
		&FunctionDispatcher<Main, C1, ReturnValue, FunArgs...>::work,
		&FunctionDispatcher<Main, C2, ReturnValue, FunArgs...>::work
	};





	// for three
	template<
		template<class, class, typename, typename...>
		class FunctionDispatcher,
		class Main, class C1, class C2, class C3
	> struct CallArray<FunctionDispatcher, Main, C1, C2, C3>
	{
		template<typename ReturnValue, typename...FunArgs> struct F
		{
			static ReturnValue(*const c[])(Main *, FunArgs...); 
		};
	};


	template<
		template<class, class, typename, typename...>
		class FunctionDispatcher,
		class Main, class C1, class C2, class C3
	>
	template<typename ReturnValue, typename...FunArgs>
	ReturnValue(
		*const CallArray<
			FunctionDispatcher, Main, C1, C2, C3
		>::F<ReturnValue, FunArgs...>::c[]
	)(Main *, FunArgs...) =
	{
		&FunctionDispatcher<Main, C1, ReturnValue, FunArgs...>::work,
		&FunctionDispatcher<Main, C2, ReturnValue, FunArgs...>::work,
		&FunctionDispatcher<Main, C3, ReturnValue, FunArgs...>::work
	};

	



	// for four
	template<
		template<class, class, typename, typename...>
		class FunctionDispatcher,
		class Main, class C1, class C2, class C3, class C4
	>
	struct CallArray<FunctionDispatcher, Main, C1, C2, C3, C4>
	{
		template<typename ReturnValue, typename...FunArgs> struct F
		{
			static ReturnValue(*const c[])(Main *, FunArgs...); 
		};
	};

	template<
		template<class, class, typename, typename...>
		class FunctionDispatcher,
		class Main, class C1, class C2, class C3, class C4
	>
	template<typename ReturnValue, typename...FunArgs>
	ReturnValue(
		*const CallArray<
			FunctionDispatcher, Main, C1, C2, C3, C4
		>::F<ReturnValue, FunArgs...>::c[]
	)(Main *, FunArgs...) =
	{
		&FunctionDispatcher<Main, C1, ReturnValue, FunArgs...>::work,
		&FunctionDispatcher<Main, C2, ReturnValue, FunArgs...>::work,
		&FunctionDispatcher<Main, C3, ReturnValue, FunArgs...>::work,
		&FunctionDispatcher<Main, C4, ReturnValue, FunArgs...>::work
	};

	



	// for five
	template<
		template<class, class, typename, typename...>
		class FunctionDispatcher,
		class Main, class C1, class C2, class C3, class C4, class C5
	>
	struct CallArray<FunctionDispatcher, Main, C1, C2, C3, C4, C5>
	{
		template<typename ReturnValue, typename...FunArgs> struct F
		{
			static ReturnValue(*const c[])(Main *, FunArgs...); 
		};
	};

	template<
		template<class, class, typename, typename...>
		class FunctionDispatcher,
		class Main, class C1, class C2, class C3, class C4, class C5
	>
	template<typename ReturnValue, typename...FunArgs>
	ReturnValue(
		*const CallArray<
			FunctionDispatcher, Main, C1, C2, C3, C4, C5
		>::F<ReturnValue, FunArgs...>::c[]
	)(Main *, FunArgs...) =
	{
		&FunctionDispatcher<Main, C1, ReturnValue, FunArgs...>::work,
		&FunctionDispatcher<Main, C2, ReturnValue, FunArgs...>::work,
		&FunctionDispatcher<Main, C3, ReturnValue, FunArgs...>::work,
		&FunctionDispatcher<Main, C4, ReturnValue, FunArgs...>::work,
		&FunctionDispatcher<Main, C5, ReturnValue, FunArgs...>::work
	};

};





// macroses
#define CLEVER_GEN_FUNCTION_DISPATCHER(functionname)\
	template<class Main, class C, typename ReturnValue, typename...FunArgs> \
	struct functionname##FunctionDispatcher\
	{\
		static ReturnValue work(Main *obj, FunArgs...args)\
		{\
			return static_cast<C*>(obj)->functionname(args...);\
		}\
	};\
\
	template<class Main, class C, typename...FunArgs> \
	struct functionname##FunctionDispatcher<Main, C, void, FunArgs...>\
	{\
		static void work(Main *obj, FunArgs...args)\
		{\
			static_cast<C*>(obj)->functionname(args...);\
			return;\
		}\
	};





#endif
