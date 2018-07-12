#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <sstream>

using namespace std;

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
		<< ":"
		<< nowTimeInfo->tm_min
		<< ":"
		<< nowTimeInfo->tm_sec;
	return timeMessage.str();
}


typedef pair<long double, long double> PDD;

long double distancePair(const PDD& lhs, const PDD& rhs)
{
	auto dx = (lhs.first - rhs.first);
	auto dy = (lhs.second - rhs.second);

	return sqrt(dx*dx + dy*dy);
}

int main(int argc, char * argv[])
{
	if( argc != 3 ) {
		cerr << "Expected arguments: <input filename> <output filename>" << endl;
		return 0;
	}
	auto inputFilename = argv[1];
	auto outputFilename = argv[2];

	if(fclose(fopen(inputFilename, "r")) != 0 ) {
		cerr << "Cannot open file" << inputFilename << endl;
		return 0;
	}
	else {
		freopen(inputFilename, "r", stdin);
	}

	if(fclose(fopen(outputFilename, "w")) != 0 ) {
		cerr << "Cannot open for write file " << outputFilename << endl;
		return 0;
	}
	else {
		freopen(outputFilename, "w", stdout);
	}

	std::string nowTimeStr = GetNowString();

	cout << nowTimeStr << std::endl;
	auto startTimeStamp = std::chrono::steady_clock::now();


	vector<PDD> points;
	while(true) {
		double x, y;
		if( 2 != scanf("%lf%lf", &x, &y) ){
			break;
		}

		points.push_back(PDD(x, y));
	}

	if( points.size() < 2 ) {
		cerr << "Error: at least 2 points are required." << endl;
		return 0;
	}

	PDD firstPoint = points[0];
	PDD secondPoint  = points[1];
	long double minDistance = distancePair(firstPoint, secondPoint);

	auto itEnd = points.end();
	for( auto itI = points.begin(); itI != itEnd; ++itI ) {
		for( auto itJ = itI+1; itJ!=itEnd; ++itJ ) {
			auto distance = distancePair(*itI, *itJ);
			if( distance < minDistance ) {
				minDistance = distance;
				firstPoint = *itI;
				secondPoint = *itJ;
			}
		}
	}

	auto elapsedTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startTimeStamp);

	cout
		<< "-----------------------------------------------------\n"
		<< " Time elapsed: " << elapsedTimeMs.count() << "ms"
		<< " | Points:" << points.size()
		<< " | MinDist:" << minDistance
		<< " | FirstX:" << firstPoint.first
		<< " | FirstY:" << firstPoint.second
		<< " | SecondX:" << secondPoint.first
		<< " | SecondY:" << secondPoint.second
		<< "\n-----------------------------------------------------\n" << std::endl;

	return 0;
}

