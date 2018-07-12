#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#pragma once

#include <istream>

namespace CLOSEST_POINTS_ALGO {
	namespace GENERATE_INPUT_FILE {

		class Configuration {
		public:
			Configuration(int argc, char * argv[]);

			std::string GetOutpuFileName() const;
			size_t GetNumberOfPointToGenerate() const;
			double GetMinXValue() const;
			double GetMinYValue() const;
			double GetMaxXValue() const;
			double GetMaxYValue() const;

			static std::string GetRequirementsString();

		private:
			std::string outputFileName;
			size_t numberOfPointsToGenerate;
			double minXValue;
			double minYValue;
			double maxXValue;
			double maxYValue;
		};

	} //namespace GENERATEINPUTFILE
} //namespace CLOSEST_POINTS_ALGO

#endif //CONFIGURATION_H