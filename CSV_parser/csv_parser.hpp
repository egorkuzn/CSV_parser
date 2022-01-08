#pragma once

#include <fstream>
#include "my_tuple.hpp"

namespace csv_parser {
	class Iterator {
	public:
		Iterator(std::ifstream* in);
		~Iterator = default;
		bool operator==(const Iterator& other) const;
		bool operator!=(const Iterator& other) const;
		Iterator& operator++();
		std::tuple<Args...>& operator*();
		std::tuple<Args...>* operator->();
	private:
		std::ifstream* input;
		size_t position = 0;
		std::tuple<Args...> currentRow;
	};

	class CSVParser {
	private:
		std::ifstream* input;
	public:
		CSVParser(std::ifstream& in, int skipCount);

		Iterator begin();

		Iterator end();
	};
}