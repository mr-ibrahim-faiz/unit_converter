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

#include<cmath>

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
		Base_Unit pound { "pound", "lb", 16, 1/453.59237, 0, 0, Base_Unit::Measure::mass };
		Base_Unit stone { "stone", "st", 7, 14, 0, 0, Base_Unit::Measure::mass };
		Base_Unit long_ton { "long ton", "l.t", 8, 160, 0, 0, Base_Unit::Measure::mass };
		Base_Unit short_ton { "short ton", "sh.t", 9, 1/1.12, 0, 0, Base_Unit::Measure::mass };
		Base_Unit ounce { "ounce", "oz", 10, 1/32000.0, 0, 0, Base_Unit::Measure::mass };
		Base_Unit pound_ounce { "pound", "lb", 11, 16, 0, 0, Base_Unit::Measure::mass };
		Base_Unit slug { "slug", "slug", 12, 9.80665/0.3048, 0, 0, Base_Unit::Measure::mass };
		Base_Unit gram { "gram", "g", 13, 0.3048/(9.80665*453.59237), 0, 0, Base_Unit::Measure::mass, true };
		Base_Unit tonne { "tonne", "t", 14, 1e6, 0, 0, Base_Unit::Measure::mass };
		Base_Unit gram_tonne { "gram", "g", 15, 1./1e6, 0, 0, Base_Unit::Measure::mass, true };

		// temperature
		Base_Unit kelvin { "Kelvin", "K", 19, 5./9, -32, 273.15, Base_Unit::Measure::temperature };
		Base_Unit celsius { "Celsius", "°C", 17, 1, 0, 273.15, Base_Unit::Measure::temperature };
		Base_Unit fahrenheit { "Fahrenheit", "°F", 18, 5./9, -32.0, 0, Base_Unit::Measure::temperature };

		// time
		Base_Unit second { "second", "s", 30, 3153600000.0, 0, 0, Base_Unit::Measure::time, true };
		Base_Unit minute { "minute", "min", 20, 60, 0, 0, Base_Unit::Measure::time };
		Base_Unit hour { "hour", "h", 21, 60, 0, 0, Base_Unit::Measure::time };
		Base_Unit day { "day", "d", 22, 24, 0, 0, Base_Unit::Measure::time };
		Base_Unit week { "week", "wk", 23, 7, 0, 0, Base_Unit::Measure::time };
		Base_Unit day_week { "day", "d", 24, 1./7, 0, 0, Base_Unit::Measure::time };
		Base_Unit year { "year", "yr", 25, 365, 0, 0, Base_Unit::Measure::time };
		Base_Unit month { "month", "mo", 26, 1./12, 0, 0, Base_Unit::Measure::time };
		Base_Unit year_month { "year", "yr", 27, 12.0, 0, 0, Base_Unit::Measure::time };
		Base_Unit decade { "decade", "dec", 28, 10.0, 0, 0, Base_Unit::Measure::time };
		Base_Unit century { "century", "c", 29, 10.0, 0, 0, Base_Unit::Measure::time };

		// area
		Base_Unit acre { "acre", "ac", 39, 640.0, 0, 0, Base_Unit::Measure::area };
		Base_Unit square_mile_acre { "square mile", "sq.mi", 31, 640.0, 0, 0, Base_Unit::Measure::area };
		Base_Unit hectare { "hectare", "ha", 32, 1/258.9988110336, 0, 0, Base_Unit::Measure::area };
		Base_Unit square_kilometer { "square kilometer", "sq.km", 33, 100, 0, 0, Base_Unit::Measure::area };
		Base_Unit square_meter { "square meter", "sq.m", 34, 1e-6, 0, 0, Base_Unit::Measure::area };
		Base_Unit square_inch { "square inch", "sq.in", 35, 0.00064516, 0, 0, Base_Unit::Measure::area };
		Base_Unit square_yard { "square yard", "sq.yd", 36, 1296.0, 0, 0, Base_Unit::Measure::area };
		Base_Unit square_foot { "square foot", "sq.ft", 37, 1./9, 0, 0, Base_Unit::Measure::area };
		Base_Unit square_mile { "square mile", "sq.mi", 38, 27878400.0, 0, 0, Base_Unit::Measure::area };

		// volume
		Base_Unit us_teaspoon { "US teaspoon", "us.tsp", 64, 768, 0, 0, Base_Unit::Measure::volume };
		Base_Unit us_tablespoon { "US tablespoon", "us.tbsp", 40, 3, 0, 0, Base_Unit::Measure::volume };
		Base_Unit us_fluid_ounce { "US fluid ounce", "us.fl.oz", 41, 2, 0, 0, Base_Unit::Measure::volume };
		Base_Unit us_cup { "US cup", "us.cup", 42, 8, 0, 0, Base_Unit::Measure::volume };
		Base_Unit us_pint { "US pint", "us.pt", 43, 2, 0, 0, Base_Unit::Measure::volume };
		Base_Unit us_quart { "US quart", "us.qt", 44, 2, 0, 0, Base_Unit::Measure::volume };
		Base_Unit us_gallon { "US gallon", "us.gal", 45, 4, 0, 0, Base_Unit::Measure::volume };
		Base_Unit cubic_inch { "cubic inch", "cu.in", 46, 1./231, 0, 0, Base_Unit::Measure::volume };
		Base_Unit cubic_yard { "cubic yard", "cu.yd", 47, 46656.0, 0, 0, Base_Unit::Measure::volume };
		Base_Unit cubic_foot { "cubic foot", "cu.ft", 48, 1./27, 0, 0, Base_Unit::Measure::volume };
		Base_Unit cubic_meter { "cubic meter", "cu.m", 49, 1./pow(0.3048,3), 0, 0, Base_Unit::Measure::volume };
		Base_Unit cubic_centimeter { "cubic centimeter", "cu.cm", 50, 1e-6, 0, 0, Base_Unit::Measure::volume };
		Base_Unit liter { "liter", "l", 51, 1000, 0, 0, Base_Unit::Measure::volume, true };
		Base_Unit legal_cup { "legal cup", "l.cup", 52, 0.24, 0, 0, Base_Unit::Measure::volume };
		Base_Unit liter_legal_cup { "liter", "l", 53, 1/0.24, 0, 0, Base_Unit::Measure::volume };
		Base_Unit imperial_gallon { "imperial gallon", "gal", 54, 4.54609, 0, 0, Base_Unit::Measure::volume };
		Base_Unit imperial_quart { "imperial quart", "qt", 55, 1./4, 0, 0, Base_Unit::Measure::volume };
		Base_Unit imperial_pint { "imperial pint", "pt", 56, 1./2, 0, 0, Base_Unit::Measure::volume };
		Base_Unit imperial_cup { "imperial cup", "cup", 57, 1./2, 0, 0, Base_Unit::Measure::volume };
		Base_Unit imperial_fluid_ounce { "imperial fluid ounce", "fl.oz", 58, 1./10., 0, 0, Base_Unit::Measure::volume };
		Base_Unit imperial_tablespoon { "imperial tablespoon", "tbsp", 59, 1/1.6, 0, 0, Base_Unit::Measure::volume };
		Base_Unit imperial_teaspoon { "imperial teaspoon", "tsp", 60, 1/3.0, 0, 0, Base_Unit::Measure::volume };
		Base_Unit imperial_gallon_imperial_teaspoon { "imperial quart", "qt", 61, 768., 0, 0, Base_Unit::Measure::volume };
		Base_Unit liter_imperial_gallon { "liter", "l", 62, 1/4.54609, 0, 0, Base_Unit::Measure::volume };
		Base_Unit us_gallon_liter { "US gallon", "us.gal", 63, 3.785411784, 0, 0, Base_Unit::Measure::volume };

		// force
		Base_Unit dyne { "dyne", "dyn", 67, 0.45359237*9.80665*1e5, 0, 0, Base_Unit::Measure::force };
		Base_Unit newton { "newton", "N", 65, 1e5, 0, 0, Base_Unit::Measure::force };
		Base_Unit pound_force { "pound-force", "lbf", 66, 0.45359237*9.80665, 0, 0, Base_Unit::Measure::force };

		// energy
		Base_Unit british_thermal_unit { "british thermal unit", "Btu", 76, (9*1.3558179483314004)/9489.1523804, 0, 0, Base_Unit::Measure::energy };
		Base_Unit erg { "erg", "erg", 68, 9/(1e7*9489.1523804), 0, 0, Base_Unit::Measure::energy };
		Base_Unit joule { "joule", "J", 69, 1e7, 0, 0, Base_Unit::Measure::energy, true };
		Base_Unit calorie { "calorie", "cal", 70, 4.184, 0, 0, Base_Unit::Measure::energy, true };
		Base_Unit watt_hour { "watt hour", "Wh", 71, 3600/4.184, 0, 0, Base_Unit::Measure::energy, true };
		Base_Unit electronvolt { "electronvolt", "eV", 72, 1.602176634e-19/3600, 0, 0, Base_Unit::Measure::energy, true };
		Base_Unit british_thermal_unit_it { "british thermal unit", "IT.Btu", 73, 1055.05585262/1.602176634e-19, 0, 0, Base_Unit::Measure::energy };
		Base_Unit us_therm { "us therm", "us.thm", 74, 105480400/1055.05585262, 0, 0, Base_Unit::Measure::energy };
		Base_Unit foot_pound { "foot pound", "ft.lb", 75, 1.3558179483314004/105480400, 0, 0, Base_Unit::Measure::energy };

		// power
		Base_Unit calories_per_second { "calories per second", "cal/s", 80, 745.69987158227022/4.1868, 0, 0, Base_Unit::Measure::power }; // approximation
		Base_Unit btu_per_hour { "btu per hour", "Btu/h", 77, 1/(4.1868*3.412141633), 0, 0, Base_Unit::Measure::power }; // approximation
		Base_Unit watt { "watt", "W", 78, 3.412141633, 0, 0, Base_Unit::Measure::power, true };
		Base_Unit horsepower { "mechanical horsepower", "hp", 79, 745.69987158227022, 0, 0, Base_Unit::Measure::power };

		// angle
		Base_Unit gradian { "gradian", "grad", 85, 10./9, 0, 0, Base_Unit::Measure::angle };
		Base_Unit radian { "radian", "rad", 81, 200./acos(-1), 0, 0, Base_Unit::Measure::angle, true };
		Base_Unit arcsecond { "arcsecond", "arcsec", 82, acos(-1)/648000.0, 0, 0, Base_Unit::Measure::angle };
		Base_Unit arcminute { "arcminute", "arcmin", 83, 60., 0, 0, Base_Unit::Measure::angle };
		Base_Unit degree { "degree", "deg", 84, 60., 0, 0, Base_Unit::Measure::angle };

		units = vector<Base_Unit> { 
				foot, inch, meter_nautical_mile, nautical_mile, meter_mile, mile, yard, // length
				pound, stone, long_ton, short_ton, ounce, pound_ounce, slug, gram, tonne, gram_tonne, // mass
				kelvin, celsius, fahrenheit, // temperature
				second, minute, hour, day, week, day_week, year, month, year_month, decade, century, // time
				acre, square_mile_acre, hectare, square_kilometer, square_meter, square_inch, square_yard, square_foot, square_mile, // area
				us_teaspoon, us_tablespoon, us_fluid_ounce, us_cup, us_pint, us_quart, us_gallon, cubic_inch, cubic_yard, cubic_foot, cubic_meter, 
				cubic_centimeter, liter, legal_cup, liter_legal_cup, imperial_gallon, imperial_quart, imperial_pint, imperial_cup, imperial_fluid_ounce, imperial_tablespoon,
				imperial_teaspoon, imperial_gallon_imperial_teaspoon, liter_imperial_gallon, us_gallon_liter, // volume
				dyne, newton, pound_force, // force
				british_thermal_unit, erg, joule, calorie, watt_hour, electronvolt, british_thermal_unit_it, us_therm, foot_pound, // energy
				calories_per_second, btu_per_hour, watt, horsepower, // power
				gradian, radian, arcsecond, arcminute, degree // angle
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
