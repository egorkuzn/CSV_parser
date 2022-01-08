#pragma once

//#include <tuple>
//#include <fstream>
//#include <sstream>

namespace csv_parser {
	class CSVParser {
	public:
		class Iterator {
		public:

		private:
		};
	private:
		std::ifstream* input;
	public:
		CSVParser(std::ifstream& in, int skipCount);

		Iterator begin();

		Iterator end();
	};
}