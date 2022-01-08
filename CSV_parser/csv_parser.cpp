#include "csv_parser.hpp"

namespace csv_parser {
	Iterator::Iterator(std::ifstream* in) : input(in) {
		if (in != nullptr)
			(*in) >> currentRow;
		else
			position = -1;
	}


}