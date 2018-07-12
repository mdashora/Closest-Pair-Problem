#ifndef GRID_H
#define GRID_H
#pragma once

#include <vector>
#include <unordered_map>

#include "Point.h"

// ---
// Hash function suitable for chain of trivial types.
// Usage:
// std::size_t seed(0);
// hash_combine(seed, first);
// hash_combine(seed, first);
// ...
// hash_combine(seed, last);
// resulting seed is a hash of chain
// ---
template<typename T>
void hash_combine(std::size_t &seed, T const &key) {
	std::hash<T> hasher;
	seed ^= hasher(key) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace std {

	// ---
	// Hash template specification for pairs
	// ---
	template<typename T1, typename T2>
	struct hash<std::pair<T1, T2>> {
		std::size_t operator()(std::pair<T1, T2> const &p) const {
			std::size_t seed1(0);
			::hash_combine(seed1, p.first);
			::hash_combine(seed1, p.second);

			std::size_t seed2(0);
			::hash_combine(seed2, p.second);
			::hash_combine(seed2, p.first);

			return std::min(seed1, seed2);
		}
	};
}

namespace CLOSEST_POINTS_ALGO {

	class Grid {
		typedef std::pair<size_t, size_t> CompositeIndex;

	public:
		typedef std::vector<const Point *> Box;

		Grid(double meshSize)
			:meshSize(meshSize) {
		}

		Grid(double meshSize, const Grid & previousGrid)
			:meshSize(meshSize) {
			for (auto box : previousGrid.boxes) {
				for (auto point : box.second) {
					Insert(*point);
				}
			}
		}

		// ---
		// Report operation
		// Returns a Box at index (xIndex, yIndex) of grid
		// ---
		const Box & Report(size_t xIndex, size_t yIndex) {
			return boxes[CompositeIndex(GetXIndex(xIndex), GetYIndex(yIndex))];
		}

		// ---
		// Returns X index of box column
		// ---
		size_t GetXIndex(double xCoord) const {
			return static_cast<size_t>(xCoord / meshSize); //to the lower integer
		}

		// ---
		// Returns Y index of box row
		// ---
		size_t GetYIndex(double yCoord) const {
			return static_cast<size_t>(yCoord / meshSize); //to the lower integer
		}

		// ---
		// Insert operation
		// Inserts a point `p` in corresponding box
		// ---
		void Insert(const Point & p) {
			auto & boxPoints = boxes[CompositeIndex(GetXIndex(p.GetX()), GetYIndex(p.GetY()))];
			boxPoints.push_back(&p);
		}

	private:

		std::unordered_map<CompositeIndex, Box> boxes;

		const double meshSize;
	};

} //namespace CLOSEST_POINTS_ALGO


#endif //GRID_H