//
// Created by kpiec on 18.04.2023.
//

#ifndef UNTITLED16_MANHATTANSOLVER_H
#define UNTITLED16_MANHATTANSOLVER_H

#include "Solver.h"
#include <queue>
#include <set>
#include <unordered_set>
#include <cmath>

struct comparePuzzleState {
    bool operator () (PuzzleState* state1, PuzzleState* state2) {
        int cost1 = state1->getDepth();
        int cost2 = state2->getDepth();
        for (int i = 0; i < 16; i++) {
            if (state1->getBoard()[i] != 0) {
                int xPos = i % 4;
                int yPos = i / 4;
                int xDest = (state1->getBoard()[i] - 1) % 4;
                int yDest = (state1->getBoard()[i] - 1) / 4;
                cost1 += abs(xPos - xDest) + abs(yPos - yDest);
            }
        }
        for (int i = 0; i < 16; i++) {
            if (state2->getBoard()[i] != 0) {
                int xPos = i % 4;
                int yPos = i / 4;
                int xDest = (state2->getBoard()[i] - 1) % 4;
                int yDest = (state2->getBoard()[i] - 1) / 4;
                cost2 += abs(xPos - xDest) + abs(yPos - yDest);
            }
        }
        return cost1 > cost2;
    }
};

class ManhattanSolver : public Solver {
private:
    std::vector<PuzzleState*> visited;
    std::priority_queue<PuzzleState*, std::vector<PuzzleState*>, comparePuzzleState> openSet; //unvisited nodes, nbhs to visited
public:
    ManhattanSolver();
    void solve(PuzzleState* state) override;
    int heuristicCost(PuzzleState* state);
    void printPath(PuzzleState* state);
};

#endif //UNTITLED16_MANHATTANSOLVER_H
