#include "stdafx.h"

#include "Configuration.h"
#include "Point.h"
#include "Grid.h"

inline std::string GetNowString();


int main(int argc, char * argv[]) {

	try {

		using namespace CLOSEST_POINTS_ALGO;

		Configuration configuration(argc, argv);

		std::cout
			<< "\nInput file name: " << configuration.GetInputFileName()
			<< "\nResult file name: " << configuration.GetResultFileName()
			<< "\n" << std::endl;

		std::ifstream inputFile(configuration.GetInputFileName());
		if (!inputFile)
			throw std::runtime_error("Failed opening: " + configuration.GetInputFileName());

		std::ofstream resultFile(configuration.GetResultFileName(), std::fstream::app);
		if (!resultFile)
			throw std::runtime_error("Failed openning file: " + configuration.GetInputFileName());


		size_t pointsCounter = 0;
		double minX = 0;
		double minY = 0;
		double maxX = 0;
		double maxY = 0;

		//note: we read out coordinates of points int memory before processing
		//in order to be more accurate when measuring time

		double x;
		double y;

		std::vector<Point> points;

		while (inputFile >> x && inputFile >> y) {
						
			points.emplace_back(x, y);

			++pointsCounter;
			if (x < minX) minX = x;
			if (y < minY) minY = y;
			if (x > maxX) maxX = x;
			if (y > maxY) maxY = y;

		}

		std::string nowTimeStr = GetNowString();

		resultFile 
			<< nowTimeStr
			<< "  " << configuration.GetInputFileName()
			<< std::endl;

		if (pointsCounter < 2)
			throw std::runtime_error("At least two points are expected");

		auto startTimeStamp = std::chrono::steady_clock::now();
		
		long double minDistance = std::numeric_limits<long double>::max();

		std::shared_ptr<Grid> grid(new Grid(minDistance));

		//over all points
		for (auto newPointIt = points.begin(); newPointIt < points.cend(); ++newPointIt) {
			
			// Indexes for box where new point will lay in
			size_t xIndex = grid->GetXIndex(newPointIt->GetX());
			size_t yIndex = grid->GetYIndex(newPointIt->GetY());

			// Find all neighbour Boxes
			std::array<const Grid::Box *, 9> neighbourBoxes;

			neighbourBoxes[0] = & grid->Report(xIndex, yIndex); //the same
			assert(neighbourBoxes[0]->size() <= 4); //no more than 4 points in a box
			neighbourBoxes[1] = &grid->Report(xIndex - 1, yIndex - 1); //left-up
			assert(neighbourBoxes[1]->size() <= 4); 
			neighbourBoxes[2] = &grid->Report(xIndex - 1, yIndex); //left 
			assert(neighbourBoxes[2]->size() <= 4); 
			neighbourBoxes[3] = &grid->Report(xIndex - 1, yIndex + 1); //left-botom
			assert(neighbourBoxes[3]->size() <= 4); 
			neighbourBoxes[4] = &grid->Report(xIndex + 1, yIndex - 1); //right-up
			assert(neighbourBoxes[4]->size() <= 4); 
			neighbourBoxes[5] = &grid->Report(xIndex + 1, yIndex); //right
			assert(neighbourBoxes[5]->size() <= 4); 
			neighbourBoxes[6] = &grid->Report(xIndex + 1, yIndex + 1); //right-bottom
			assert(neighbourBoxes[6]->size() <= 4); 
			neighbourBoxes[7] = &grid->Report(xIndex, yIndex - 1); //up
			assert(neighbourBoxes[7]->size() <= 4); 
			neighbourBoxes[8] = &grid->Report(xIndex, yIndex + 1); //bottom
			assert(neighbourBoxes[8]->size() <= 4); 
			
			// Find minimal distance to new point from all points in neighbour boxes
			double minDistanceToNeighbour = minDistance;

			for (const Grid::Box * boxPtr : neighbourBoxes) {
				for (const Point * pointPtr : *boxPtr) {
					long double distance = newPointIt->Distance(*pointPtr);
					if (distance < minDistanceToNeighbour) {
						minDistanceToNeighbour = distance;
					}
				}
			}

			// Rebuild grid if `minDistance` should update
			if (minDistanceToNeighbour < minDistance) {
				minDistance = minDistanceToNeighbour;
				std::cout << "New grid with mesh size: " << minDistance << std::endl;
				resultFile << "New grid with mesh size: " << minDistance << std::endl;
				grid = std::make_shared<Grid>(minDistance, *grid.get());
			}

			// Insert point on grid
			grid->Insert(*newPointIt);
		}
		

		auto elapsedTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startTimeStamp);

		resultFile 
			<< " Time elapsed: " << (elapsedTimeMs.count() / 1000.0) << "s"
			<< " | Points:" << pointsCounter
			<< " | MinDist:" << minDistance
			<< " | MinX:" << minX
			<< " | MinY:" << minY
			<< " | MaxX:" << maxX
			<< " | MaxY:" << maxY
			<< "\n-----------------------------------------------------\n" << std::endl;

		std::cout << "Done" << std::endl
			<< "\nTime: " << (elapsedTimeMs.count() / 1000.0) << "s\n"
			<< "\nNumber of points: " << pointsCounter
			<< "\nDistance:" << minDistance
			<< "\nMin X: " << minX
			<< "\nMin Y: " << minY
			<< "\nMax X: " << maxX
			<< "\nMax Y: " << maxY
			<< std::endl;

	} catch (std::exception &ex) {
		std::cerr << "ERROR: " << ex.what() << std::endl;
	} catch (...) {
		std::cerr << "UNKNOWN ERROR" << std::endl;
	}

	return 0;
}

inline std::string GetNowString() {
	std::time_t now = time(nullptr);
	std::tm * nowTimeInfo = localtime(&now);

	std::stringstream timeMessage;
	timeMessage
		<< (nowTimeInfo->tm_year + 1900)
		<< '-'
		<< (nowTimeInfo->tm_mon + 1)
		<< '-'
		<< nowTimeInfo->tm_mday
		<< " "
		<< nowTimeInfo->tm_hour
		<< "-"
		<< nowTimeInfo->tm_min
		<< "-"
		<< nowTimeInfo->tm_sec;
	return timeMessage.str();
}