#ifndef GRID_H
#define GRID_H
#pragma once

#include <map>
#include <vector>

#include "Point.h"

namespace CLOSEST_POINTS_ALGO {

	class Grid {
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

		class CompositeIndex {
		public:
			CompositeIndex(size_t xIndex, size_t yIndex)
				:x(xIndex)
				, y(yIndex) {
			}

			bool operator < (const CompositeIndex & rhs) const {
				if (x < rhs.x) {
					return true;
				}
				if (x > rhs.x) {
					return false;
				}
				if (y < rhs.y) {
					return true;
				}
				return false;
			}

		private:
			const size_t x;
			const size_t y;
		};


		std::map<CompositeIndex, Box> boxes;

		const double meshSize;
	};

} //namespace CLOSEST_POINTS_ALGO

#endif //GRID_H