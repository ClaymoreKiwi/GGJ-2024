#include "EnemypathFinding.h"
#include <queue>
#include <iostream>
#include <fstream>

int tileW = 66 * mapWidth;
int tileH = 60 * mapHeight;

// Returns if the position specified by x,y is
// one where the player can move to, e.g. not wall
bool isValid(const TileMap& theMap, int x, int y)
{
	if (x < 0 || x >= mapWidth) {
		return false;
	}
	if (y < 0 || y >= mapHeight) {
		return false;
	}
	if (theMap[y][x] == 2) {
		return false;
	}
	return true;
}

// Indicates if the position x,y corresponds to the destination
bool isDestination(int x, int y, Node destination)
{
	if (x == destination.x && y == destination.y) {
		return true;
	}
	return false;
}

//cost function used to figure out the hueristics
//using the Euclidean distance (includes diagonal movements)
float calculateH(int x, int y, Node destination)
{
	int xDiff = destination.x - x;
	int yDiff = destination.y - y;
	//ommiting sqrt results the same calculation
	return static_cast<float>(xDiff * xDiff + yDiff * yDiff);
}

std::vector<Node> makePath(std::array<std::array<Node, mapWidth>, mapHeight>& map, Node dest)
{
	// Stores the path
	std::vector<Node> usablePath;

	// Start at the destination
	int x = dest.x;
	int y = dest.y;

	// Check bounds and valid start node
	while (!(map[y][x].parentX == x && map[y][x].parentY == y)
			&& map[y][x].x != -1 && map[y][x].y != -1)
	{
		// Put the node in the list
		usablePath.push_back(map[y][x]);

		int tempX = map[y][x].parentX;
		int tempY = map[y][x].parentY;

		// Move to parent for the next repetition
		x = tempX;
		y = tempY;
	}

	// Check bounds and push the start node into the list
	if (y >= 0 && y < mapHeight && x >= 0 && x < mapWidth) {
		usablePath.push_back(map[y][x]);
	}

	// Reverse the list so it is in start to dest order
	reverse(usablePath.begin(), usablePath.end());

	return usablePath;
}


// and stores details about the search for each tile
std::array<std::array<Node, mapWidth>, mapHeight> nodeDetails;
// Indicates if a tile has been visited (true) or not (false)
std::array<std::array<bool, mapWidth>, mapHeight> closedList;

// This is used to represent no path
std::vector<Node> emptyPath;


std::vector<Node> aStar(const TileMap& theMap, const Node& enemy, const Node& dest) 
{

	// Check if the destination is valid. e.g not water
	if (!isValid(theMap, dest.x, dest.y)) {
		return emptyPath;
	}

	// Check if the destination is the player eg, already by the player
	if (isDestination(enemy.x, enemy.y, dest)) {
		return emptyPath;
	}

	// Initialise the helper arrays
	for (int y = 0; y < mapHeight; y++) {
		for (int x = 0; x < mapWidth; x++) {
			// Position
			nodeDetails[y][x].x = x;
			nodeDetails[y][x].y = y;

			// Maximum cost
			nodeDetails[y][x].fCost = FLT_MAX;
			nodeDetails[y][x].gCost = FLT_MAX;
			nodeDetails[y][x].hCost = FLT_MAX;

			// No parent (yet anyway)
			//nodeDetails[y][x].parentX = -1;
			//nodeDetails[y][x].parentY = -1;

			// Not visited
			closedList[y][x] = false;
		}
	}

	// Open list is the list of nodes to visit after making a move
	// to a new location
	std::vector<Node> openList;

	// Initialise the starting point to the player position
	nodeDetails[enemy.y][enemy.x].x = enemy.x;
	nodeDetails[enemy.y][enemy.x].y = enemy.y;
	nodeDetails[enemy.y][enemy.x].fCost = 0.0f;
	nodeDetails[enemy.y][enemy.x].gCost = 0.0f;
	nodeDetails[enemy.y][enemy.x].hCost = 0.0f;
	nodeDetails[enemy.y][enemy.x].parentX = enemy.x;
	nodeDetails[enemy.y][enemy.x].parentY = enemy.y;

	// Put the start node into the open list to start the algorithm
	openList.push_back(nodeDetails[enemy.y][enemy.x]);

	// Indicates if the destination was found.
	// Could be the case the destination is unreachable
	bool found = false;

	// While there are nodes to process
	while (!openList.empty()) {
		// Get one from the list
		Node current = openList.front();

		// Remove it from the list so it isn't processed again
		openList.erase(openList.begin());

		// Indicate visited
		closedList[current.y][current.x] = true;

		// Is the node the destination?
		if (isDestination(current.x, current.y, dest)) {
			// Indicate found it if it is
			found = true;

			// And exit the loop
			break;
		}

		//up
		if (isValid(theMap, current.x, current.y - 1) && !closedList[current.y - 1][current.x]) {
			// Calculate the cost in terms of the distance from the node to the destination
			float gNew = nodeDetails[current.y][current.x].gCost + 1.0f;
			float hNew = calculateH(current.x, current.y - 1, dest);
			float fNew = gNew + hNew;

			if (nodeDetails[current.y - 1][current.x].fCost == FLT_MAX || nodeDetails[current.y - 1][current.x].fCost > fNew) {
				// Update the details of this neighbour node
				nodeDetails[current.y - 1][current.x].fCost = fNew;
				nodeDetails[current.y - 1][current.x].gCost = gNew;
				nodeDetails[current.y - 1][current.x].hCost = hNew;
				nodeDetails[current.y - 1][current.x].parentX = current.x;
				nodeDetails[current.y - 1][current.x].parentY = current.y;

				// Put it in the list for next time
				openList.push_back(nodeDetails[current.y - 1][current.x]);
			}
		}

		// Right
		if (isValid(theMap, current.x + 1, current.y) && !closedList[current.y][current.x + 1]) {
			float gNew = nodeDetails[current.y][current.x].gCost + 1.0f;
			float hNew = calculateH(current.x + 1, current.y, dest);
			float fNew = gNew + hNew;

			if (nodeDetails[current.y][current.x + 1].fCost == FLT_MAX || nodeDetails[current.y][current.x + 1].fCost > fNew) {
				// Update the details of this neighbour node
				nodeDetails[current.y][current.x + 1].fCost = fNew;
				nodeDetails[current.y][current.x + 1].gCost = gNew;
				nodeDetails[current.y][current.x + 1].hCost = hNew;
				nodeDetails[current.y][current.x + 1].parentX = current.x;
				nodeDetails[current.y][current.x + 1].parentY = current.y;

				openList.push_back(nodeDetails[current.y][current.x + 1]);
			}
		}

		// Down
		if (isValid(theMap, current.x, current.y + 1) && !closedList[current.y + 1][current.x]) {
			float gNew = nodeDetails[current.y][current.x].gCost + 1.0f;
			float hNew = calculateH(current.x, current.y + 1, dest);
			float fNew = gNew + hNew;

			if (nodeDetails[current.y + 1][current.x].fCost == FLT_MAX || nodeDetails[current.y + 1][current.x].fCost > fNew) {
				// Update the details of this neighbour node
				nodeDetails[current.y + 1][current.x].fCost = fNew;
				nodeDetails[current.y + 1][current.x].gCost = gNew;
				nodeDetails[current.y + 1][current.x].hCost = hNew;
				nodeDetails[current.y + 1][current.x].parentX = current.x;
				nodeDetails[current.y + 1][current.x].parentY = current.y;

				openList.push_back(nodeDetails[current.y + 1][current.x]);
			}
		}

		// Left
		if (isValid(theMap, current.x - 1, current.y) && !closedList[current.y][current.x - 1]) {
			float gNew = nodeDetails[current.y][current.x].gCost + 1.0f;
			float hNew = calculateH(current.x - 1, current.y, dest);
			float fNew = gNew + hNew;

			if (nodeDetails[current.y][current.x - 1].fCost == FLT_MAX || nodeDetails[current.y][current.x - 1].fCost > fNew) {
				// Update the details of this neighbour node
				nodeDetails[current.y][current.x - 1].fCost = fNew;
				nodeDetails[current.y][current.x - 1].gCost = gNew;
				nodeDetails[current.y][current.x - 1].hCost = hNew;
				nodeDetails[current.y][current.x - 1].parentX = current.x;
				nodeDetails[current.y][current.x - 1].parentY = current.y;

				openList.push_back(nodeDetails[current.y][current.x - 1]);
			}
		}

	}

	// Out of loop.  Was the destination found?
	if (found) {
		// Yes, then create the path for the current node state
		return makePath(nodeDetails, dest);
	}
	else {
		// No, return no path
		return emptyPath;
	}
}