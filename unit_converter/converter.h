#ifndef CONVERTER_H
#define CONVERTER_H

#include "unit.h"

#include<vector>
using std::vector;

// user-defined type Value
struct Value {
	// default constructor
	Value() noexcept = delete;

	// constructor taking value and a predicate as argumentss
	explicit Value(double, bool) noexcept;

	double value;
	bool is_exit;
};

// user-defined type Mode
enum class Mode {
	name, symbol
};

// gets base units
const vector<Base_Unit>& get_base_units();

// gets prefixes
const vector<Prefix_Unit>& get_prefixes();

// gets units
const vector<Unit>& get_units();

// gets whitespace
void get_whitespace();

// checks newline
void check_newline();

// gets input value
Value get_input_value();

// gets input unit
string get_input_unit();

// gets base unit
Base_Unit get_base_unit(const string&, const Mode& = Mode::symbol);

// gets base unit
Base_Unit get_base_unit(const size_t&);

// gets unit
Unit get_unit(const string&, const Mode& = Mode::symbol);

// gets prefix
Prefix_Unit get_prefix(const string&, const Mode& = Mode::symbol);

// clears input stream
void clear_input_stream();

// converts a value
double convert(const double&, const Unit&, const Unit&);

// checks if character is a unary sign operator
bool issign(int);

#endif
