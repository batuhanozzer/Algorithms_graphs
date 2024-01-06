#pragma once
#include "adjacent_list.h"

class Graph : public adjacent_list
{
private:
	int k_number{-1};
	std::string selected_city; 
	std::string destination_city;
public:

	void choose_city();
	void display_selected_city();
	void choose_destination();

	void choose_k_number();

	void find_k_closest_cities();
	void find_shortest_path();

	int find_Idx(std::vector<std::string> my_vector, std::string key); 
	int find_Idx(std::vector<City> my_vector, std::string key);
};




