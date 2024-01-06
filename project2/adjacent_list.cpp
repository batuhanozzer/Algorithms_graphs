#include "adjacent_list.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cctype>    // For std::tolower


void adjacent_list::read_adjacent_city_file()
{
    if (!cities_.empty())
        std::cout << "The file already read" << std::endl;
    else {
        std::ifstream file("adjacent_cities.txt");
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) { // getline(file, line, delim): file: where to read the input from, delim:  tells the function to stop reading when reach the delim char
                std::istringstream iss(line);
                std::string select_city;
                std::vector<City> obj;

                if (std::getline(iss, select_city, ',')) { // takes the first parameter which is the city name
                    std::transform(select_city.begin(), select_city.end(), select_city.begin(), ::tolower);
                    obj.emplace_back(select_city);

                    std::string neighbor;
                    while (std::getline(iss, neighbor, ',')) { // takes the rest of the parameters which are the neighbors of the city
                        std::transform(neighbor.begin(), neighbor.end(), neighbor.begin(), ::tolower);
                        obj.emplace_back(neighbor);
                    }
                    city_list.push_back(select_city);
                    cities_.emplace_back(obj);  // Create new city objects 
                }
            }
            file.close();
        }
        else { std::cout << "File couldn't open adjacent file!!!" << std::endl; }
    }
}

void adjacent_list::read_city_distance_file(std::vector<std::vector<City>>& Cities_)
{
    std::ifstream file("CityDistances.txt");


    if (file.is_open()) {
        std::string line;
        std::getline(file, line); // Read the first line which is useless
        int idx = 0;
        while (std::getline(file, line)) { // getline(file, line, delim): file: where to read the input from, delim:  tells the function to stop reading when reach the delim char

            std::istringstream iss(line);
            std::string select_city;
            std::vector<int> distances;

            if (std::getline(iss, select_city, ';')) // takes the first parameter which is the plate id
            {
                if (std::getline(iss, select_city, ';')) // takes the second parameter which is the city name
                {
                    size_t i{ 0 };
                    std::string dst;
                    while (std::getline(iss, dst, ';')) // takes the rest of the parameters which are the neighbors of the city
                    {
                        size_t j{ 0 }, flag{ 0 };
                        while (j != Cities_[idx].size())
                        {
                            if (city_list[i] == Cities_[idx][j].city_name_) { flag = 1; break; }
                            j++;
                        }

                        i++;
                        if (flag == 1) { Cities_[idx][j].distance = std::stoi(dst); }
                    }
                    idx++;
                }

            }
        }
        file.close();
    }
    else { std::cout << "File couldn't open distance file!!!" << std::endl; }

}
