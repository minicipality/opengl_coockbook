#include <vector>
#include <iostream>
#include <algorithm>

void erase_remove()
{
	std::vector<int> vec{1, 2, 3, 4, 5, 3, 2, 4, 4, 5, 2};

	const auto new_end(std::remove(std::begin(vec), std::end(vec), 2));

	vec.erase(new_end, std::end(vec));
	
	for (auto i : vec)
		std::cout << i << std::endl;

}
