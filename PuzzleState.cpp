//
// Created by kpiec on 18.04.2023.
//

#include "PuzzleState.h"
#include <iostream>

PuzzleState::PuzzleState() { //random state max 20 steps from goal
    this->board = new short[16];
    for (int i = 0; i < 15; i++)
        board[i] = i+1;
    board[15] = 0;
    depth = 0;
    predecessor = nullptr;
    randomizeBoard();
}

PuzzleState::PuzzleState(short *arr) {
    this->board = new short[16];
    predecessor = nullptr;
    depth = 0;
    for (int i = 0; i < 16; i++) {
        short tmp = arr[i];
        this->board[i] = tmp;
    }
}

PuzzleState::PuzzleState(const short *arr, move m) {
    this->board = new short[16];
    predecessor = nullptr;
    depth = 0;
    for (int i = 0; i < 16; i++) {
        short tmp = arr[i];
        this->board[i] = tmp;
    }
    int gapPos = getGapPos();
    switch (m) {
        case move::UP:
            myswap(this->board, gapPos, gapPos - 4);
            break;
        case move::DOWN:
            myswap(this->board, gapPos, gapPos + 4);
            break;
        case move::RIGHT:
            myswap(this->board, gapPos, gapPos + 1);
            break;
        case move::LEFT:
            myswap(this->board, gapPos, gapPos - 1);
            break;
    }
}

short *PuzzleState::getBoard() {
    return this->board;
}

int PuzzleState::getDepth() {
    return depth;
}

void PuzzleState::setDepth(int d) {
    depth = d;
}

void PuzzleState::printBoard() {
    for (int i = 0; i < 16; i++) {
        if (board[i] < 10) std::cout << ' ';
        std::cout << board[i] << ' ';
        if (i%4 == 3) std::cout << '\n';
    }
    std::cout << '\n';
}

std::vector<PuzzleState*> PuzzleState::getNeighbours() {
    std::vector<PuzzleState*> tmp;
    int gapPos = getGapPos();
    if (gapPos > 3) {
        PuzzleState* s1 = new PuzzleState(this->board, UP);
        s1->setPredecessor(this);
        tmp.push_back(s1);
    }
    if (gapPos < 12) {
        PuzzleState* s2 = new PuzzleState(this->board, DOWN);
        s2->setPredecessor(this);
        tmp.push_back(s2);
    }
    if (gapPos%4 != 0) {
        PuzzleState * s3 = new PuzzleState(this->board, LEFT);
        s3->setPredecessor(this);
        tmp.push_back(s3);
    }
    if (gapPos%4 != 3) {
        PuzzleState* s4 = new PuzzleState(this->board, RIGHT);
        s4->setPredecessor(this);
        tmp.push_back(s4);
    }
    return tmp;
}

int PuzzleState::getGapPos() {
    for (int i = 0; i < 16; i++) {
        if (board[i] == 0)
            return i;
    }
    return 0;
}

void PuzzleState::moveGap(move m) {
    int gapPos = getGapPos();
    switch (m) {
        case move::UP:
            myswap(this->board, gapPos, gapPos - 4);
            break;
        case move::DOWN:
            myswap(this->board, gapPos, gapPos + 4);
            break;
        case move::RIGHT:
            myswap(this->board, gapPos, gapPos + 1);
            break;
        case move::LEFT:
            myswap(this->board, gapPos, gapPos - 1);
            break;
    }
}

void myswap(short* arr, int index1, int index2) {
    short tmp = arr[index2];
    arr[index2] = arr[index1];
    arr[index1] = tmp;
}

void PuzzleState::setPredecessor(PuzzleState *p) {
    this->predecessor = p;
}

bool PuzzleState::operator==(const PuzzleState& state) const {
    for (int i = 0; i < 16; i++) {
        if (board[i] != state.board[i]) {
            return  false;
        }
    }
    return true;
}

bool PuzzleState::operator!=(const PuzzleState& state) const {
    return !(*this == state);
}

bool PuzzleState::isGoal() const {
    short goal[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};
    for (int i = 0; i < 16; i++) {
        if (goal[i] != board[i])
            return false;
    }
    return true;
}

void PuzzleState::randomizeBoard() {
    srand((unsigned) time(nullptr));
    int zeroPos = getGapPos();
    int count = 0;

    while (count < 25) {
        int r = rand() % 4;
        if (r == 0 && zeroPos > 3) {
            moveGap(UP);
            count++;
        }
        else if (r == 1 && zeroPos < 12) {
            moveGap(DOWN);
            count++;
        }
        else if (r == 2 && zeroPos%4 != 0) {
            moveGap(LEFT);
            count++;
        }
        else if (r == 3 && zeroPos%4 != 3) {
            moveGap(RIGHT);
            count++;
        }
        zeroPos = getGapPos();
    }
}

short PuzzleState::movedNum() {
    if (predecessor == nullptr)
        return -1;
    int p = getGapPos();
    return predecessor->getBoard()[p];
}

PuzzleState *PuzzleState::getPredecessor() {
    return predecessor;
}

PuzzleState::~PuzzleState() {
}