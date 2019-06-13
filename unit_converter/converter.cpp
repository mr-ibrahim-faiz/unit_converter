#include "converter.h"

#include<iostream>
using std::cin;
using std::streamsize;

#include<stdexcept>
using std::runtime_error;
using std::invalid_argument;

#include<algorithm>
using std::find;

#include<limits>
using std::numeric_limits;

// symbolic names
constexpr char newline { '\n' };
constexpr char unary_negative { '-' };
constexpr char unary_positive { '+' };
const string exit_sequence { "exit" };

// constant expressions
const Prefix_Unit PREFIX_IDENTITY { "", "", 1 }; // identity prefix

// constructor taking value and a predicate as argumentss
Value::Value(double value, bool is_exit) noexcept
	: value { value }, is_exit { is_exit }{}

// gets base units
const vector<Base_Unit>& get_base_units()
// initializes and returns base units
{
	static bool is_initialized { false };
	static vector<Base_Unit> units;

	if(!is_initialized){
		// length
		Base_Unit yard { "yard", "yd", 6, 1.0/3.0, 0, 0, Base_Unit::Measure::length };
		Base_Unit mile { "mile", "mi", 0, 1760.0, 0, 0, Base_Unit::Measure::length };
		Base_Unit meter_mile { "meter", "m", 1, 1/1609.344, 0, 0, Base_Unit::Measure::length, true };
		Base_Unit nautical_mile { "nautical mile", "nmi", 2, 1852.0, 0, 0, Base_Unit::Measure::length };
		Base_Unit meter_nautical_mile { "meter", "m", 3, 1/1852.0, 0, 0, Base_Unit::Measure::length, true };
		Base_Unit inch { "inch", "in", 4, 0.0254, 0, 0, Base_Unit::Measure::length };
		Base_Unit foot { "foot", "ft", 5, 12.0, 0, 0, Base_Unit::Measure::length }; 

		// mass
		Base_Unit pound { "pound", "lb", 15, 1/453.59237, 0, 0, Base_Unit::Measure::mass };
		Base_Unit stone { "stone", "st", 7, 14, 0, 0, Base_Unit::Measure::mass };
		Base_Unit long_ton { "long ton", "l.t", 8, 160, 0, 0, Base_Unit::Measure::mass };
		Base_Unit short_ton { "short ton", "sh.t", 9, 1/1.12, 0, 0, Base_Unit::Measure::mass };
		Base_Unit ounce { "ounce", "oz", 10, 1/32000.0, 0, 0, Base_Unit::Measure::mass };
		Base_Unit pound_ounce { "pound", "lb", 11, 16, 0, 0, Base_Unit::Measure::mass };
		Base_Unit gram { "gram", "g", 12, 1/453.59237, 0, 0, Base_Unit::Measure::mass, true };
		Base_Unit tonne { "tonne", "t", 13, 1e6, 0, 0, Base_Unit::Measure::mass };
		Base_Unit gram_tonne { "gram", "g", 14, 1./1e6, 0, 0, Base_Unit::Measure::mass, true };

		// temperature
		Base_Unit kelvin { "Kelvin", "K", 18, 5./9, -32, 273.15, Base_Unit::Measure::temperature };
		Base_Unit celsius { "Celsius", "°C", 16, 1, 0, 273.15, Base_Unit::Measure::temperature };
		Base_Unit fahrenheit { "Fahrenheit", "°F", 17, 5./9, -32.0, 0, Base_Unit::Measure::temperature };

		// time
		Base_Unit second { "second", "s", 29, 3153600000.0, 0, 0, Base_Unit::Measure::time, true };
		Base_Unit minute { "minute", "min", 19, 60, 0, 0, Base_Unit::Measure::time };
		Base_Unit hour { "hour", "h", 20, 60, 0, 0, Base_Unit::Measure::time };
		Base_Unit day { "day", "d", 21, 24, 0, 0, Base_Unit::Measure::time };
		Base_Unit week { "week", "wk", 22, 7, 0, 0, Base_Unit::Measure::time };
		Base_Unit day_week { "day", "d", 23, 1./7, 0, 0, Base_Unit::Measure::time };
		Base_Unit year { "year", "yr", 24, 365, 0, 0, Base_Unit::Measure::time };
		Base_Unit month { "month", "mo", 25, 1./12, 0, 0, Base_Unit::Measure::time };
		Base_Unit year_month { "year", "yr", 26, 12.0, 0, 0, Base_Unit::Measure::time };
		Base_Unit decade { "decade", "dec", 27, 10.0, 0, 0, Base_Unit::Measure::time };
		Base_Unit century { "century", "c", 28, 10.0, 0, 0, Base_Unit::Measure::time };

		// area
		Base_Unit acre { "acre", "ac", 38, 640.0, 0, 0, Base_Unit::Measure::area };
		Base_Unit square_mile_acre { "square mile", "sq.mi", 30, 640.0, 0, 0, Base_Unit::Measure::area };
		Base_Unit hectare { "hectare", "ha", 31, 1/258.9988110336, 0, 0, Base_Unit::Measure::area };
		Base_Unit square_kilometer { "square kilometer", "sq.km", 32, 100, 0, 0, Base_Unit::Measure::area };
		Base_Unit square_meter { "square meter", "sq.m", 33, 1e-6, 0, 0, Base_Unit::Measure::area };
		Base_Unit square_inch { "square inch", "sq.in", 34, 0.00064516, 0, 0, Base_Unit::Measure::area };
		Base_Unit square_yard { "square yard", "sq.yd", 35, 1296.0, 0, 0, Base_Unit::Measure::area };
		Base_Unit square_foot { "square foot", "sq.ft", 36, 1./9, 0, 0, Base_Unit::Measure::area };
		Base_Unit square_mile { "square mile", "sq.mi", 37, 27878400.0, 0, 0, Base_Unit::Measure::area };

		units = vector<Base_Unit> { 
				foot, inch, meter_nautical_mile, nautical_mile, meter_mile, mile, yard, // length
				pound, stone, long_ton, short_ton, ounce, pound_ounce, gram, tonne, gram_tonne, // mass
				kelvin, celsius, fahrenheit, // temperature
				second, minute, hour, day, week, day_week, year, month, year_month, decade, century, // time
				acre, square_mile_acre, hectare, square_kilometer, square_meter, square_inch, square_yard, square_foot, square_mile // area
		};

		is_initialized = true;
	}

	return units;
}

// gets prefixes
const vector<Prefix_Unit>& get_prefixes()
// initializes and returns unit prefixes
{
	static bool is_initialized { false };
	static vector<Prefix_Unit> prefixes;

	if(!is_initialized){
		Prefix_Unit kilo { "kilo", "k", 1e3 };
		Prefix_Unit centi { "centi", "c", 1e-2 };
		Prefix_Unit milli { "milli", "m", 1e-3 };
		Prefix_Unit micro { "micro", "µ", 1e-6 };
		Prefix_Unit nano { "nano", "n", 1e-9 };

		prefixes = vector<Prefix_Unit> { kilo, centi, milli, micro, nano };

		is_initialized = true;
	}

	return prefixes;
}

// gets units
const vector<Unit>& get_units()
// initializes and returns units
{
	static bool is_initialized { false };
	static vector<Unit> units;

	if(!is_initialized){
		const vector<Base_Unit>& base_units = get_base_units();
		const vector<Prefix_Unit>& prefixes = get_prefixes();

		for(const Base_Unit& base_unit : base_units){
			Unit unit_identity { PREFIX_IDENTITY, base_unit };
			
			// initializes a unit if it doesn't exist
			using const_iterator = typename vector<Unit>::const_iterator;
			const_iterator first = units.begin();
			const_iterator last = units.end();
			const_iterator found = find(first, last, unit_identity);

			if(found == last){
				units.push_back(unit_identity);
				if(base_unit.Can_be_preceded()){
					for(const Prefix_Unit& prefix : prefixes){
						Unit unit { prefix, base_unit };
						units.push_back(unit);
					}
				}
			}
		}

		is_initialized = true;
	}

	return units;
}

// gets whitespace
void get_whitespace()
// gets whitespace if present, throws an exception otherwise
{
	if(isblank(cin.peek())) getchar();
	else throw invalid_argument("(arguments) whitespace expected.");
}

// checks newline
void check_newline()
// checks for a newline and throws an exception if not present
{
	if(cin.peek() == newline); // does nothing
	else throw invalid_argument("(arguments) newline expected.");
}

// gets input value
Value get_input_value()
// gets a double value and a boolean value representing the user's intent to quit the program
{
	double value { 0.0 };
	const int next = cin.peek();

	if(isdigit(next) || issign(next)) cin >> value;
	else {
		if(isalpha(cin.peek())) {
			string stream;
			getline(cin, stream);
			if(stream == exit_sequence) return Value { value, true };
			cin.putback(newline);
		}
		throw invalid_argument("(arguments) invalid value.");
	}
	return Value{ value, false };
}

// gets input unit
string get_input_unit()
// gets a string value, representing a unit
{
	string unit;
	const int next = cin.peek();
	if(!isspace(next) && !isdigit(next)) cin >> unit;
	else throw invalid_argument("(arguments) invalid unit.");
	return unit;
}

// gets base unit
Base_Unit get_base_unit(const string& name, const Mode& mode)
// gets base unit from name
// the name must be valid; i.e. equals the name or symbol of a known unit
{
	const vector<Base_Unit>& units = get_base_units();
	for(const Base_Unit& unit : units){
		const string unit_name = (mode == Mode::name)? unit.Name() : unit.Symbol();
		if(name == unit_name) return unit;
	}
	throw runtime_error("(unit) unknown base unit (" + name + ").");
}

// gets base unit
Base_Unit get_base_unit(const size_t& id)
// gets unit from id
// the id must be valid; i.e. equals the id of a known unit
{
	const vector<Base_Unit>& units = get_base_units();
	for(const Base_Unit& unit : units){
		if(id == unit.ID()) return unit;
	}
	throw runtime_error("(unit) unknown unit id.");
}

// gets unit
Unit get_unit(const string& name, const Mode& mode)
// gets unit from name 
// the name must be valid; i.e. equals the name or symbol of a known unit
{
	const vector<Unit>& units = get_units();
	for(const Unit& unit : units){
		const string unit_name = (mode == Mode::name)? unit.Name() : unit.Symbol();
		if(name == unit_name) return unit;
	}
	throw runtime_error("(unit) unknown unit (" + name + ").");
}

// gets prefix
Prefix_Unit get_prefix(const string& name, const Mode& mode)
// gets prefix from name
// the name must be valid; i.e. equals the name or symbol of a known prefix
{
	const vector<Prefix_Unit>& prefixes = get_prefixes();
	for(const Prefix_Unit& prefix : prefixes){
		const string prefix_name = (mode == Mode::name)? prefix.Name() : prefix.Symbol();
		if(name == prefix_name) return prefix;
	}
	return PREFIX_IDENTITY;
}

// clears input stream
void clear_input_stream(){
	if(!cin) cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// converts a value
double convert(const double& value, const Unit& left_unit, const Unit& right_unit)
// converts a value of a unit left_unit to another unit right_unit
// the units must be valid and of the same quantity
{
	if(left_unit.Base().Quantity() != right_unit.Base().Quantity()) throw runtime_error("(conversion) measure mismatch.");

	const size_t id_left = left_unit.Base().ID();
	const size_t id_right = right_unit.Base().ID();

	size_t id_result = id_left;
	double result { value };
	result *= left_unit.Prefix().Factor(); // applies unit prefix
	
	while(id_result != id_right){
		Base_Unit unit = get_base_unit(id_result);

		const double factor = unit.Factor();
		const double summand = unit.Summand();
		const double addend = unit.Addend();

		if(id_result > unit.ID_conversion()) result = (result + summand)*factor + addend;
		else result = (result - addend)/factor - summand;

		id_result = unit.ID_conversion();
	}

	result /= right_unit.Prefix().Factor(); // applies unit prefix

	return result;
}

// checks if character is a unary sign operator
bool issign(int c){
	if(c == int(unary_negative) || c == int(unary_positive)) return true;
	return false;
}
