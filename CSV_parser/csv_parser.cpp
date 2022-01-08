#include "csv_parser.hpp"

namespace csv_parser {
	template<class... Args>
	bool CSVParser<Args...>::Iterator::operator== (const typename CSVParser<Args...>::Iterator & other) const {
		if (input != other.input)
			return false;
		return position == other.position;
	}

	
}