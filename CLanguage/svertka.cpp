#include <algorithm>
#include <vector>
#include <set>

template<typename ... Ts>
auto product(Ts ... ts)
{
	return (ts * ... * 1);		// 1 - нейтральный элемент
	// return (ts + ... + 0);
}

// соотнесение диапазонов и отдельных элементов
template<typename R, typename ...Ts>
auto matches(const R& range, Ts ... ts)
{
	return(std::count(std::begin(range), std::end(range), ts) + ...);
}

// проверка успешности вставки нескольких элементов в множество
template<typename T, typename ... Ts>
bool insert_set(T &set, Ts ... ts)
{
	return(set.insert(ts).second && ...);
}

// проверка попадания всех параметров в заданный диапазон
template< typename T, typename ...Ts>
bool within(T min, T max, Ts ... ts)
{
	return ((min <= ts && ts <= max) && ...);
}

// отправка нескольких элементов в вектор
template< typename T, typename ... Ts>
void insert_all(std::vector<T> &vec, Ts ... ts)
{
	(vec.push_back(ts), ...);
}

void useSvertka()
{
	std::vector<int> v{1, 2, 3, 4, 5};
	//int countMatches = matches(v, 2, 5);					// 2
	//int countMatches_zero = matches(v, 100, 200);			// 0
	//int countMatches_str = matches("abcdesg", "a", "c");	// 2


	std::set<int> st{1, 2, 3};
	bool res_insert = insert_set(st, 4, 5, 6);		// true
	bool res_insert_2 = insert_set(st, 7, 8, 2);	// false, так как 2 - присутствует в контейнере
	bool res_insert_3 = insert_set(st, 7, 9);		// вернет false, досрочно прекратит работать и оставшиеся элементы будут не вставлены

	// сигнатура контейнера std::set
	//std::set<iterator, bool> insert(const value_type& value);

	bool res_within = within(10, 20, 1, 15, 30); // bool
	bool res_within2 = within(10, 20, 11, 12, 13); // true
	bool res_within3 = within(5.0, 5.5, 5.1, 5.2, 5.3); // true
	bool res_within_str = within("aaa", "zzz", "bbb", "eee"); // true

	std::vector<int> vec{10, 20, 30, 40, 50};
	insert_all(vec, 60, 70, 80, 90);
}