#pragma once
#include <string>
#include <vector>


class City
{
public:
	std::string city_name_;
	int distance;

	City(std::string name = "None", int d = 0) : city_name_{std::move(name)}, distance{ d } {}
};

