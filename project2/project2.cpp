#include <iostream>
#include "Graph.h"

void print_menu()
{
	std::cout << "a.Enter city(or select)" << std::endl;
	std::cout << "b.Print selected(or entered) city" << std::endl;
	std::cout << "c.List k closest  cities(to selected city)" << std::endl;
	std::cout << "d.Find shortest path to" << std::endl;
	std::cout << "e.exit" << std::endl;
}


int main()
{
	char choice{};
	Graph obj;

	do
	{

		std::cout << "==========================================" << std::endl;
		print_menu();
		std::cout << "==========================================" << std::endl;
		std::cout << std::endl << "Choose a choice:" << ' ';
		std::cin >> choice;
		std::cout << "==========================================" << std::endl;




		if(choice >= 'a' && choice <= 'e')
		{

			switch (choice)
			{
			case 'a': { obj.choose_city(); break; }
			case 'b': { obj.display_selected_city(); break; }
			case 'c': { obj.find_k_closest_cities(); break; }
			case 'd': { obj.find_shortest_path(); break; }
			case 'e': { break; }
			default: break;
			}
		}
		else
		{
			std::cout << "==========================================" << std::endl;
			std::cout << "Choose a valid choice (a,b,c,d,e):" << ' ';
			std::cin >> choice;
			std::cout << "==========================================" << std::endl;


		}

		
		

	}
	while (choice != 'e');


}
