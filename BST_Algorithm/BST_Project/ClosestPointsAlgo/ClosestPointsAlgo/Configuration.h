#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#pragma once

namespace CLOSEST_POINTS_ALGO {

		class Configuration {
		public:
			Configuration(int argc, char * argv[]);

			std::string GetInputFileName() const;
			std::string GetResultFileName() const;

			static std::string GetRequirementsString();

		private:
			std::string inputFileName;
			std::string resultFileName;
		};

} //namespace CLOSEST_POINTS_ALGO

#endif //CONFIGURATION_H