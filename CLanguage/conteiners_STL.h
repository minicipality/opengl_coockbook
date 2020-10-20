#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>		// здесь находится и miltymap
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

void erase_remove()
{
	std::vector<int> vec{ 1, 2, 3, 4, 5, 3, 2, 4, 4, 5, 2 };

	const auto new_end(std::remove(std::begin(vec), std::end(vec), 2));
	
	const auto odd{ [](int i) {return i % 2 != 0; } };
	//const auto new_end(std::remove_if(std::begin(vec), std::end(vec), odd));
	
	vec.erase(new_end, std::end(vec));

	std::cout << "Capacity: " << vec.capacity() << std::endl;
	//std::cout << "Size: " << vec.size() << std::endl;
	vec.shrink_to_fit();
	std::cout << "Capacity 2: " << vec.capacity() << std::endl;;
	//std::cout << "Size 2 : " << vec.size() << std::endl;	

	for (auto i : vec)
		std::cout << i << std::endl;
}

template<typename T>
void quick_remove_at(
	std::vector<T> &v, 
	std::size_t indx)
{
	if (indx < v.size())
	{
		v[indx] = std::move(v.back());
		v.pop_back();
	}
}

template<typename T>
void quick_remove_at(
	std::vector<T> &v,
	typename std::vector<T>::iterator it)
{
	if (it != std::end(v))
	{
		*it = std::move(v.back());
		v.pop_back();
	}
}

void use_quick_remove()
{
	std::vector<int> vec{123, 456, 789, 100, 200};

	// удалить число с индексом 2
	quick_remove_at(vec, 2);
	std::cout << "Delete second element" << std::endl;
	for (auto i : vec)
		std::cout << i << std::endl;

	// удалим еще один элемент - 123, не зная его индекс
	auto res_find = std::find(std::begin(vec), std::end(vec), 123);
	quick_remove_at(vec, res_find);
	std::cout << "Delete 123" << std::endl;
	for (auto i : vec)
		std::cout << i << std::endl;
}

// вставка элемента в отсортированный контейнер 
template<typename C, typename T>
void insert_sorted(C &v, const T &item)
{
	const auto insert_pos(std::lower_bound(std::begin(v), std::end(v), item));
	v.insert(insert_pos, item);
}

void sort_vector()
{
	std::vector<std::string> vec_str{"some", "random", "words", "wothout", "order", "aaa", "yyy"};

	assert(false == std::is_sorted(std::begin(vec_str), std::end(vec_str)));
	std::sort(std::begin(vec_str), std::end(vec_str));
	assert(true == std::is_sorted(std::begin(vec_str), std::end(vec_str)));

	insert_sorted(vec_str, "foobar");
	insert_sorted(vec_str, "zzz");

	for (auto i : vec_str)
		std::cout << i << std::endl;
}

struct billionaire{
	std::string name;
	double dollars;
	std::string country;
};

void insert_to_map()
{
	std::list<billionaire> billionaires{
		{"Bill Gates", 86.0, "USA"},
		{"Warren Buffet", 75.6, "Moscow"},
		{"Mark Zuckerberg", 54.5, "France"}
	};

	// key - country, std::size_t - счетчик, 
	// который будет увеличиваться на каждого последующего миллиардера в стране

	// можно использовать unordered_map - единственное различие, что вывод unordered_map будет не упорядочен
	std::map<std::string, std::pair<const billionaire, std::size_t>> m;

	for (const auto &b : billionaires)
	{
		auto[iterator, success] = m.try_emplace(b.country, b, 1);

		if (!success)
			iterator->second.second += 1;
	}

	for (const auto &[key, value] : m)
	{
		const auto &[b, count] = value;
		std::cout << b.country << " : " << count
			<< " billionaires. Richest is "
			<< b.name << " with " << b.dollars << " B$" << std::endl;
	}
}

void new_hint_map()
{
	std::map<std::string, std::size_t>  m{{"b", 1}, {"c", 2}, {"d", 3}};

	// изначально подсказки нет - используем конечный итератор
	auto insert_it(std::end(m));

	for (const auto &s : { "z", "y", "x", "w" })
		insert_it = m.insert(insert_it, { s, 1 });
	
	// демонстрация того, как не надо решать задачу
	m.insert(std::end(m), {"a", 1});

	for (const auto &[key, value] : m)
		std::cout << "\"" << key << "\": " << value << ", ";
	
	std::cout << std::endl;
}

template<typename M>
void print_map(const M &m)
{
	std::cout << "Race placement: \n";
	for (const auto &[placement, driver] : m)
		std::cout << placement << ": " << driver << std::endl;
}

void change_key_map()
{
	std::map<int, std::string> race_placement{
		{1, "Mario"}, {2, "Jhon"}, {3, "Ted"}, {4, "Ralf"}, 
		{5, "Bowser"}, {6, "Koopa"}, {7, "Peach"}, {8, "Yoshi"} };

	print_map(race_placement);

	{
		auto a(race_placement.extract(3));
		auto b(race_placement.extract(8));

		std::swap(a.key(), b.key());

		race_placement.insert(std::move(a));
		race_placement.insert(std::move(b));
	}

	print_map(race_placement);
}

struct coord {
	int x;
	int y;
};

bool operator==(const coord &l, const coord &r)
{
	return l.x == r.x && l.y == r.y;
 }


//template<>
struct coord_hash //std::hash<coord>
{
	using argument_type = coord;
	using result_type = size_t;

	result_type operator()(const argument_type &c) const
	{
		return static_cast<result_type>(c.x) +
			   static_cast<result_type>(c.y);
	}
};


void use_unordered_map()
{
	std::unordered_map<coord, int, coord_hash> unmap{ {{0, 0}, 1},
		{{0, 1}, 2}, {{2, 1}, 3} };

	for (const auto &[key, value] : unmap)
	{
		std::cout << "{(" << key.x << ", " << key.y
			<< "): " << value << "} ";
	}
	std::cout << std::endl;
}

void filter_set()
{
	std::set<std::string> str_st{"f", "fff", "bed", "aa", "bedaa", "aa"};

	//std::istream_iterator<std::string> it{std::cin};
	//std::istream_iterator<std::string> end;

	std::copy(str_st.begin(), str_st.end(), std::inserter(str_st, str_st.end()));

	for (const auto word : str_st)
		std::cout << word << ": ";
	std::cout << std::endl;
 }

#include <typeinfo>

template<typename IT>
double evaluate_rpn(IT it, IT end)
{
	std::stack<double> val_stack;

	auto pop_stack([&]() {
		auto r(val_stack.top());		// извлекаем значение с вершины
		val_stack.pop();				// затем возвращаем значение
		return r;
	});

	// определение всех поддерживающих операций - каждый токен операции связан с самой операцией
	std::map<std::string, double(*)(double, double)> ops{
		{"+", [](double a, double b) {return(a + b); }},
		{"-", [](double a, double b) {return(a - b); }},
		{"*", [](double a, double b) {return(a * b); }},
		{"/", [](double a, double b) {return(a / b); }},
		{"^", [](double a, double b) {return std::pow(a, b); }},
		{"%", [](double a, double b) {return std::fmod(a, b); }},
	};

	for (; it != end; ++it) {
		// преобразовываем элемент стэка в std::stringstream
		std::stringstream ss{ *it };	
		// помещаем элементы в стэк
		// проверяем может ли элемент стека быть преобразован в число double
		if(double val; ss >> val)
			val_stack.push(val);
		// если элемен тне является числом, предполагаем, что это операнд
		else
		{
			// получаем значения из стека за один шаг с помощью лямбда-выражения
			const auto r{pop_stack()};
			const auto l{pop_stack()};
			// определяем какая операци, путем обращения к std::map
			try {
				const auto &op(ops.at(*it));
				const double result{ op(l,r) };
				val_stack.push(result);
			}
			catch (const std::out_of_range &) {
				throw std::invalid_argument(*it);
			}
		}
	}

	return val_stack.top();
}

void rpn_calculate()
{
	//std::set<std::string> str_st{ "3", "1", "2", "+", "*", "/"};
	std::stringstream s{"3 2 1 + * 2 /"};
	try {
		std::cout << evaluate_rpn(std::istream_iterator < std::string>{ s }, {}) << std::endl; 
	}
	catch (const std::invalid_argument &e) {
		std::cout << "Invalid operator:" << e.what() << std::endl;
	}
}

std::string filter_punctuation(const std::string &s)
{
	const char *forbidden{".,:; "};

	const auto idx_start{ s.find_first_not_of(forbidden) };
	const auto idx_end{ s.find_last_not_of(forbidden) };

	return s.substr(idx_start, idx_end - idx_start + 1);
}

// подсчитываем частоту встречаемости слов с применением контейнера std::map
void use_filter_punctuation()
{
	std::map<std::string, std::size_t> words;

	int max_word_len{ 0 };

	std::string s;

	while (std::cin >> s)
	{
		auto filtered(filter_punctuation(s));
		max_word_len = std::max<int>(max_word_len, filtered.length());
		++words[filtered];
	}

	// ассоциативный кмассив использует слова в качестве ключей, они отсортированны в алфавитном порядке
	// нужно вывести все слова, отсортировав по их частоте встречаемости, чтобы наиболее частые слова были первыми
	std::vector<std::pair<std::string, std::size_t>> word_counts;
	word_counts.reserve(words.size());
	std::move(std::begin(words), std::end(words), std::back_inserter(word_counts));
	
	// сортируем слова в порядке убыввания по длине слова
	std::sort(word_counts.begin(), word_counts.end(), []
	(const auto &a, const auto &b ) {
		return a.second > b.second;
	});

	std::cout << "# " << std::setw(max_word_len) << "<WORD>" << " #<COUNT>\n";
	for (const auto &[word, count] : word_counts)
		std::cout << std::setw(max_word_len + 2) << word << " #"
		<< count << std::endl;
}

// вспомогательный стилистический редактор для поиска длинных предложения в текстах с помощью std::multymap
// отбрасываем символы пробела, новой строки, перехода на новую строчку и т.д.
std::string filter_ws(const std::string &s)
{
	const char * ws{" \r\n\t"};
	const auto a(s.find_first_not_of(ws));
	const auto b(s.find_last_not_of(ws));
	if (a == std::string::npos)
		return {};

	return s.substr(a, b - a + 1);
}

// функция определения длины предложения
std::multimap<std::size_t, std::string> get_sentence_stats(const std::string &content)
{
	std::multimap<std::size_t, std::string> ret;

	const auto end_it(std::end(content));
	auto it1(std::begin(content));         // start at beginning of string
	auto it2(std::find(it1, end_it, '.')); // Start at first '.' dot character

	while (it1 != end_it && std::distance(it1, it2) > 0) 
	{

		std::string s{ filter_ws({it1, it2}) };

		if (s.length() > 0) 
		{
			const auto words(count(std::begin(s), std::end(s), ' ') + 1);
			ret.emplace(std::make_pair(words, std::move(s)));
		}

		if (it2 == end_it) 
			// Need to get out here, because the next line would set it1
			// _past_ end_it.
			break;
		

		it1 = std::next(it2, 1);
		it2 = std::find(it1, end_it, '.');
	}

	return ret;
}


void use_filter_sentence()
{
	std::cin.unsetf(std::ios::skipws);
	std::string content{ std::istream_iterator<char>{std::cin}, {} };

	for (const auto &[word_count, sentence]	: get_sentence_stats(content))
		std::cout << word_count << " words: " << sentence << ".\n";
}

void use_priority_queue()
{
	// тип, где число - приоритет, а запись - соответствующее дело
	using item_type = std::pair<int, std::string>;

	std::priority_queue<item_type> q;
	std::initializer_list<item_type> il{
		{1, "dishes"},
		{0, "watch tv"},
		{2, "do homework"},
		{0, "read comics"},
	};

	for (const auto &p : il)
		q.push(p);

	while (!q.empty())
	{
		std::cout << q.top().first << ": " << q.top().second << std::endl;
		q.pop();
	}
	std::cout << std::endl;
}