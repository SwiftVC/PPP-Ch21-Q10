/*
*	Author:	CS
*	Date:	2022_03_18	YYYY_MM_DD
*
*	Order files file1.txt and file2.txt are sorted into a vector,
*	duplicates are removed and the sum of unit_price*count for each purchase returned.
*	
*/

#include <iostream>
#include "Order_Purchase.h"
#include <iterator>	// for std::istream_iterator

int main() {
	try {
		// open input files
		std::ifstream in1{ "file1.txt" };
		std::ifstream in2{ "file2.txt" };

		// scan input file 1 into a std::vector<Order>
		std::vector<Order> orders;
		Order temp;
		in1 >> temp;
		while (temp && in1)
		{
			orders.push_back(temp);
			char ch;
			in1 >> ch;
			if (in1)
			{
				in1.putback(ch);
				in1 >> temp;
			}
		}
		// scan input file 2 into the std::vector<Order>
		in2 >> temp;
		while (temp && in2)
		{
			orders.push_back(temp);
			char ch;
			in2 >> ch;
			if (in2)
			{
				in2.putback(ch);
				in2 >> temp;
			}
		}

		// sort the vector and delete duplicates
		std::sort(orders.begin(), orders.end(), [](Order a, Order b) { return a.get_name() < b.get_name(); });
		std::unique(orders.begin(), orders.end(), [](Order a, Order b) { return a.get_name() == b.get_name(); });
		
		// delete the members with empty strings as marked by std::unique
		for (int i = 0; i < orders.size(); i++)
			if (orders[i].get_name() == ""){
				auto it = orders.begin();
				std::advance(it, i);
				orders.erase(it);
				i--;
			}

		double sum{ 0 };
		for (auto temp : orders)
			sum += temp.get_value();

		std::cout << "Total value of orders across the two files is:\n";
		std::cout << sum << std::endl;

		return 0;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}