#include "csv_parser.hpp"

namespace csv_parser {
	template<class... Args>
	CSVParser<Args...>::CSVParser(std::ifstream& in, int skipCount) {
		std::tuple<Args...> row;
		std::string str;
		for (int idx = 0; idx < skipCount; ++idx)
			getline(in, str);
		input = &in;
	}

	template<class... Args>
	bool CSVParser<Args...>::Iterator::operator== (const typename CSVParser<Args...>::Iterator & other) const {
		if (input != other.input)
			return false;
		return position == other.position;
	}

	template<class... Args>
	bool CSVParser<Args...>::Iterator::operator!=(const typename CSVParser<Args...>::Iterator& other) const {
		if (input != other.input)
			return true;
		return position != other.position;
	}

	template<class... Args>
	typename CSVParser<Args...>::Iterator& CSVParser<Args...>::Iterator::operator++() {
		if (input == nullptr)
			return *this;
		(*input) >> currentRow;

		if (input->eof()) {
			input = nullptr;
			position = -1;
			return *this;
		}

		++position;
		return *this;
	}

	template<class... Args>
	std::tuple<Args...>& CSVParser<Args...>::Iterator::operator*() {
		return currentRow;
	}
}