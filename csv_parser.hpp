#pragma once

#include <fstream>
#include "my_tuple.hpp"

namespace csv_parser {
	template<class... Args>

	class CSVParser {
	public:
		class Iterator {
		public:
			explicit Iterator(std::ifstream *in) : input(in) {
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

	template<class... Args>
	std::tuple<Args...>* CSVParser<Args...>::Iterator::operator->() {
		return &currentRow;
	}

	template<class... Args>
	typename CSVParser<Args...>::Iterator CSVParser<Args...>::begin() {
		return Iterator(input);
	}

	template<class... Args>
	typename CSVParser<Args...>::Iterator CSVParser<Args...>::end() {
		return Iterator(nullptr);
	}
}