#pragma once
#include "city.h"

class adjacent_list
{
protected:
	std::vector<std::string> city_list;
	std::vector<std::vector<City>> cities_;

	void read_adjacent_city_file();
	void read_city_distance_file(std::vector<std::vector<City>>& Cities_);
public:
	adjacent_list() { read_adjacent_city_file(); read_city_distance_file(cities_);}
};

