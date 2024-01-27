#pragma once
#include <algorithm> //max and min functions
#include <vector>
#include <array>
#include <stack>
#include "TileMap.h"

struct Node {
	int x, y; //this is the position of the node
	int parentX, parentY; //the X and Y of the last node in the list
	float gCost; //g cost is the cost of moving to this node based on the current position
	float hCost; //h cost is distance between this node and the goal
	float fCost; //f cost is simply the addition of g and h scores and represents the total cost of the path via the current node
};

//in our map data, 0 represents a valid tile, and 1 is an obstacle
bool isValid(TileMap& map, int x, int y);

//checks a node to see if it is the destination node
bool isDestination(int x, int y, Node destination);

//Simple H calcuation only taking into account 4 directional movement
float calculateH(int x, int y, Node destination);


// This function creates a path from the player to where
// the enemy is, then reverses it so enemy moves towards the player
std::vector<Node> makePath(std::array<std::array<Node, 32>, 24>& map, Node dest);

// Main A* algorithm
std::vector<Node> aStar(const TileMap& theMap, const Node& player, const Node& dest);
