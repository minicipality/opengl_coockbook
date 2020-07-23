#include <string>
#include <vector>

template <typename T>
class addable
{
	T val;
public:
	addable(T v) : val{ v } {}
	template <typename U>
	T add(U x) const 
	{
		//return val + x;

		//auto copy(val); // получаем копию элемента
		//for (auto &n : copy) {
		//	n += x;
		//}
		//return copy;

		if constexpr (std::is_same_v <T, std::vector<U>>)
		{
			auto copy(val); // получаем копию элемента
			for (auto &n : copy)
				n += x;
			return copy;
		}
		//else
		//	return (val + x); // ERROR ???
		return val;
	};
};

void useConstexpr()
{
	addable<int>{1}.add(2);
	addable<float>{1.0}.add(2);
	addable<std::string>{"aa"}.add("bb");

	std::vector<int> v{ 1, 2, 3 };
	addable<std::vector<int>>{v}.add(10); // is std::vector<int>{11,12,13}
	
	std::vector<std::string> sv{"a", "b", "c"};
	addable<std::vector<std::string>>{sv}.add("d"); //is std::vector<std::string>{ad,bd,cd}


}