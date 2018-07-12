#include "stdafx.h"

#include "Configuration.h"

namespace CLOSEST_POINTS_ALGO {

		Configuration::Configuration(int argc, char * argv[]) {

			if (argc > 1) {
				inputFileName = argv[1];
			} else
				throw std::runtime_error("Not enough agruments: output file name\n" + GetRequirementsString());

			if (argc > 2) {
				resultFileName = argv[2];
			} else
				throw std::runtime_error("Not enough agruments: result file name\n" + GetRequirementsString());
		}
		
		std::string Configuration::GetInputFileName() const {
			return inputFileName;
		}

		std::string Configuration::GetResultFileName() const {
			return resultFileName;
		}

		std::string Configuration::GetRequirementsString() {
			return "Expected arguments list: <output file name>";
		}

} //namespace CLOSEST_POINTS_ALGO
