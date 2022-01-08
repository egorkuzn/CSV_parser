#pragma once

#include <fstream>
#include "my_tuple.hpp"

namespace csv_parser {
	template<class... Args>

	class CSVParser {
	public:
		class Iterator {
		public:
			explicit CSVParser::Iterator(std::ifstream* in) : input(in) {
				if (in != nullptr)
					(*in) >> currentRow;
				else
					position = -1;
			}
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

	private:
		std::ifstream* input;

	public:
		CSVParser(std::ifstream& in, int skipCount);
		Iterator begin();
		Iterator end();
	};
}