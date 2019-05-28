#include "converter.h"

#include<stdexcept>
using std::exception;

#include<iostream>
using std::cout;
using std::cerr;

int main() {
	cout << "Please enter a number followed by 2 units:";
	while(true){
		cout << "\n> ";

		try {
			// gets value
			const Value input_value = get_input_value();
			const double& value = input_value.value;
			const bool& is_exit = input_value.is_exit;

			if(is_exit) break;
			get_whitespace();

			// gets units
			string left_unit_name = get_input_unit();
			const Unit left_unit = get_unit(left_unit_name);
			get_whitespace();

			string right_unit_name = get_input_unit();
			const Unit right_unit = get_unit(right_unit_name);
			check_newline();

			// converts and display results
			const double result = convert(value, left_unit, right_unit);
			cout << result << '\n';
		}
		catch(const exception& e){
			cerr << "Error: " << e.what() << '\n';
		}

		clear_input_stream();
	}

	cout << "\nGoodbye !\n";

	return 0;
}
