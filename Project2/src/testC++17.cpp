#include <iostream>
#include <map>
[[deprecated("use funcy instead")]] void funx()
{
	static int a = 0;
}
[[nodiscard]] int connect()
{
	return 0;
}
int niubie()
{
	std::map<int, double>map;
	int id = 0;
	auto [iter, inserted] = map.try_emplace(0);
	if (inserted)
		iter->second = 0;
	return 0;
}
int test()
{
	//funx();
	int discard= connect();
	return 0;
}
