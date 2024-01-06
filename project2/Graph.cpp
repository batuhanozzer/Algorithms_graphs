#include "Graph.h"
#include "city.h"
#include <iostream>
#include <queue>

struct compare_Distances
{
	bool operator()(const City& obj1, const City& obj2) const {
		// Sort based on distance
		return obj1.distance > obj2.distance;
	}
};

int Graph::find_Idx(std::vector<std::string> my_vector, std::string key)
{
	for (int i{}; i < my_vector.size(); i++)
	{
		if (my_vector[i] == key) return i; // Return the index
	}
	return -1; // Not found the index
}

int Graph::find_Idx(std::vector<City> my_vector, std::string key)
{
	for (int i{}; i < my_vector.size(); i++)
	{
		if (my_vector[i].city_name_ == key) return i; // Return the index
	}
	return -1; // Not found the index
}

void Graph::choose_city()
{
	std::string name;
	std::cout << "Please choose a city:" << ' ';
	std::cin >> name;
	std::transform(name.begin(), name.end(), name.begin(), ::tolower);
	while (find_Idx(city_list,name) == -1)
	{
		std::cout << "Please choose a valid city name:" << ' ';
		std::cin >> name;
		std::transform(name.begin(), name.end(), name.begin(), ::tolower);
	}
	selected_city = name;
}

void Graph::display_selected_city()
{
	std::cout << "Selected city" << ' ' << selected_city << std::endl;
}

void Graph::choose_destination()
{
	std::string name;
	std::cout << "Please choose a destination:" << ' ';
	std::cin >> name;
	std::transform(name.begin(), name.end(), name.begin(), ::tolower);
	while (find_Idx(city_list, name) == -1)
	{
		std::cout << "Please choose a valid city name:" << ' ';
		std::cin >> name;
		std::transform(name.begin(), name.end(), name.begin(), ::tolower);
	}
	destination_city = name;
}

void Graph::choose_k_number()
{
	int number;
	std::string choice;
	std::cout << "Please choose k number:" << ' ';
	std::cin >> choice;

	number = std::stoi(choice);

	while (number < 0 || number > 81)
	{
		std::cout << "Please choose k number between 0 and 81:" << ' ';
		std::cin >> choice;
		number = std::stoi(choice);
	}
	k_number = number;
}

void Graph::find_k_closest_cities()
{
	choose_k_number();
	int counter = k_number + 1;
	std::vector<City> visited;
	std::priority_queue<City, std::vector<City>, compare_Distances> priority_queue;	// Store city type, and sort according to distance

	if (selected_city.empty()) choose_city();	// If user didn't choice the current city send him to choose it
	priority_queue.emplace(selected_city);		// Start with the current city

	while (counter != 0)
	{
		std::vector<City> neighbors;
		std::vector<int> distance;

		if (priority_queue.empty()){break;}	// If pq is empty then there is not enough number of neighbors to satisfy the k number
		if (find_Idx(visited, priority_queue.top().city_name_) != -1) {priority_queue.pop();}
		else{
			int pos = find_Idx(city_list, priority_queue.top().city_name_);	// Find the key element idx in 'city_list'
			visited.emplace_back(priority_queue.top());	// Add to visited list
			City parent = priority_queue.top();	// Hold the previous value to calculate the total cost of the branch
			priority_queue.pop();	// Pop the element from the queue

			neighbors = cities_[pos];	// Neighbors hold the vector<City> objects of a certain city
			for (size_t i{ 1 }; i < neighbors.size(); i++)
			{
				if (find_Idx(visited, neighbors[i].city_name_) == -1) priority_queue.push(City(neighbors[i].city_name_, neighbors[i].distance + parent.distance));
			}	// Push the neighbors which doesn't visited before to the priority queue


			counter--;
		}
	}
	//-------------------------------------------------------------------
	std::cout << "Selected City:" << ' ' << selected_city << std::endl << " Path:" << ' ';
	for(const auto& element : visited) { std::cout << " ->" << ' ' << '(' << element.city_name_ << ',' << element.distance << ')';}
	std::cout << std::endl;
}

void Graph::find_shortest_path()
{
	std::vector<std::vector<City>> heuristic_matrix;
	std::vector<City> temp;
	for (const auto& city : city_list) { temp.emplace_back(city); }
	/*
	 *	adana:0, adiyaman:0, ..., duzce:0	=> 1 dimension
	 *
	 */
	for (int i{}; i < city_list.size(); i++) { heuristic_matrix.push_back(temp); }
	/*
	*	adana:0, adiyaman:0, ..., duzce:0
	*	adana:0, adiyaman:0, ..., duzce:0
	*	.									=> 2 dimension
	*	.
	*	.
	*	adana:0, adiyaman:0, ..., duzce:0
	*/
	read_city_distance_file(heuristic_matrix);	//Set the values

	std::vector<City> visited;
	std::priority_queue<City, std::vector<City>, compare_Distances> priority_queue;	// Store city type, and sort according to distance

	
	if (selected_city.empty()) choose_city();	// If user didn't choice the current city send him to choose it
	choose_destination();	// Choose the destination
	priority_queue.emplace(selected_city);		// Start with the current city

	while (find_Idx(visited,destination_city) == -1)
	{
		std::vector<City> neighbors;
		std::vector<int> distance;

		if (priority_queue.empty()) { break; }	// If pq is empty then there is not enough number of neighbors to satisfy the k number
		if (find_Idx(visited, priority_queue.top().city_name_) != -1) { priority_queue.pop(); }
		else {
			int pos = find_Idx(city_list, priority_queue.top().city_name_);	// Find the key element idx in 'city_list'
			visited.emplace_back(priority_queue.top());	// Add to visited list
			City parent = priority_queue.top();	// Hold the previous value to calculate the total cost of the branch
			priority_queue.pop();	// Pop the element from the queue

			neighbors = cities_[pos];	// Neighbors hold the vector<City> objects of a certain city
			for (size_t i{ 1 }; i < neighbors.size(); i++)
			{
				if (find_Idx(visited, neighbors[i].city_name_) == -1)
				{
					const int idx_src = find_Idx(city_list, neighbors[i].city_name_);
					const int idx_dst = find_Idx(city_list, destination_city);
					priority_queue.emplace(City(neighbors[i].city_name_, neighbors[i].distance + heuristic_matrix[idx_src][idx_dst].distance));
				} // Push the neighbors which doesn't visited before to the priority queue
			}	

		}
	}
	std::cout << "Selected City:" << ' ' << selected_city << " Destination:" << ' ' << destination_city << std::endl << " Path:" << ' ';
	for (const auto& element : visited) { std::cout << " ->" << ' ' << '(' << element.city_name_ << ',' << element.distance << ')'; }
	std::cout << std::endl;
}

