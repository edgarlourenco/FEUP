#include <iostream>
#include<vector>
#include<set>
#include<stack>
#include<queue>
#include <chrono>
#include <climits> 
#include <algorithm>
#include <list>

#ifdef _WIN32
#include <windows.h>

#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#define DISABLE_NEWLINE_AUTO_RETURN  0x0008

void activateVirtualTerminal() //for red color in path, makes seeing it easier
{
    HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD consoleMode;
    GetConsoleMode(handleOut, &consoleMode);
    consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    consoleMode |= DISABLE_NEWLINE_AUTO_RETURN;
    SetConsoleMode(handleOut, consoleMode);
}
#endif

using namespace std;

enum COLORS {
    NC = -1,
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,
};

/**
* Colorize terminal colors ANSI escape sequences.
*
* @param font font color (-1 to 7), see COLORS enum
* @param back background color (-1 to 7), see COLORS enum
* @param style font style (1==bold, 4==underline)
**/
const char* colorize(int font, int back = -1, int style = -1) { //from derzu here https://stackoverflow.com/questions/4053837/colorizing-text-in-the-console-with-c
    static char code[20];

    if (font >= 0)
        font += 30;
    else
        font = 0;
    if (back >= 0)
        back += 40;
    else
        back = 0;

    if (back > 0 && style > 0) {
        sprintf(code, "\033[%d;%d;%dm", font, back, style);
    }
    else if (back > 0) {
        sprintf(code, "\033[%d;%dm", font, back);
    }
    else {

        sprintf(code, "\033[%dm", font);
    }

    return code;
}


using namespace std;
using namespace std::chrono;

typedef vector< vector<char> > grid;

enum class Moves
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

grid grid0
{
    {'A','A','A','B','B','.'},
    {'.','C','A','B','D','.'},
    {'.','C','.','B','D','F'},
    {'.','C','C','D','D','F'},
    {'.','E','E','E','F','F'},
    {'X','.','.','E','.','.'}
};

grid grid1
{
    {'.', '.', '.', 'A', 'A', '.'},
    {'B', 'B', 'F', 'F', 'A', '.'},
    {'.', 'B', 'F', '.', 'A', '.'},
    {'.', 'B', 'F', '.', 'E', 'D'},
    {'.', 'C', 'E', 'E', 'E', 'D'},
    {'X', 'C', 'C', 'C', 'D', 'D'}
};

grid grid2 {
    {'A','.','E','E','E','.'},
    {'A','.','E','.','.','F'},
    {'A','A','D','F','F','F'},
    {'B','.','D','D','D','.'},
    {'B','B','B','.','C','.'},
    {'X','.','C','C','C','.'}
};

grid grid3 {
    {'.','A','A','.','.','.'},
    {'.','A','.','.','E','.'},
    {'.','A','E','E','E','D'},
    {'.','B','B','.','.','D'},
    {'.','B','C','.','D','D'},
    {'X','B','C','C','C','.'}
};

grid grid4 {
    {'A','A','D','E','.','.'},
    {'B','A','D','E','E','E'},
    {'B','A','D','D','.','F'},
    {'B','B','C','.','.','F'},
    {'.','.','C','G','F','F'},
    {'X','C','C','G','G','G'}
};

grid grid5 {
    {'A','A','B','B','B','.'},
    {'.','A','B','.','C','D'},
    {'.','A','C','C','C','D'},
    {'F','.','.','.','D','D'},
    {'F','F','F','E','E','E'},
    {'X','.','.','.','.','E'}
};

grid grid6 {
    {'.','B','B','B','.','.'},
    {'.','B','C','C','C','.'},
    {'A','A','C','D','D','D'},
    {'A','.','.','E','E','D'},
    {'A','F','F','F','E','.'},
    {'X','F','.','.','E','.'}
};

grid grid7 {
    {'C','.','.','.','E','E','.'},
    {'C','D','D','D','E','F','.'},
    {'C','C','.','D','E','F','.'},
    {'.','G','G','G','F','F','.'},
    {'A','A','.','G','B','H','.'},
    {'.','A','B','B','B','H','.'},
    {'X','A','.','.','H','H','.'}
};

grid grid8{
    {'.','.','C','.','.','D','.'},
    {'B','B','C','C','C','D','.'},
    {'B','.','.','E','D','D','.'},
    {'B','A','.','E','H','H','H'},
    {'.','A','E','E','.','.','H'},
    {'A','A','F','.','G','G','G'},
    {'X','.','F','F','F','.','G'}
};

grid grid9{
    {'.','.','.','.','.','.','.'},
    {'C','C','D','D','H','H','H'},
    {'C','.','D','E','H','G','G'},
    {'C','B','D','E','.','G','.'},
    {'.','B','.','E','E','G','.'},
    {'.','B','B','A','.','.','I'},
    {'X','A','A','A','I','I','I'}
};

grid grid10{
    {'A','B','B','C','C','C','.'},
    {'A','.','B','D','.','C','.'},
    {'A','A','B','D','D','D','.'},
    {'E','E','.','G','G','I','.'},
    {'E','.','F','G','H','I','.'},
    {'E','.','F','G','H','I','I'},
    {'X','.','F','F','H','H','.'}
};

grid grid11{
    {'.','I','I','I','.','.','.'},
    {'.','I','H','H','.','.','G'},
    {'A','A','.','H','G','G','G'},
    {'A','B','B','H','D','D','.'},
    {'A','.','B','.','D','E','E'},
    {'.','C','B','.','D','.','E'},
    {'X','C','C','C','.','.','E'}
};

grid grid12{
    {'.','E','E','F','F','J','.','.'},
    {'.','E','G','G','F','J','J','J'},
    {'.','E','.','G','F','I','I','.'},
    {'.','D','.','G','C','.','I','.'},
    {'A','D','D','D','C','H','I','.'},
    {'A','.','.','C','C','H','.','L'},
    {'A','A','B','B','B','H','H','L'},
    {'X','.','.','.','B','.','L','L'}
};

grid grid13{
    {'.','.','D','.','.','.','.','.'},
    {'.','.','D','D','D','J','J','J'},
    {'C','C','.','E','E','J','I','I'},
    {'C','B','B','.','E','.','I','.'},
    {'C','B','.','.','E','.','I','.'},
    {'.','B','F','F','F','G','H','H'},
    {'.','A','F','.','.','G','.','H'},
    {'X','A','A','A','.','G','G','H'}
};

grid grid14{
    {'.','.','.','F','F','F','.','.'},
    {'E','E','E','F','.','.','G','.'},
    {'.','.','E','.','G','G','G','.'},
    {'D','D','D','.','H','H','H','.'},
    {'D','.','C','C','H','I','I','I'},
    {'.','A','A','C','.','I','J','.'},
    {'.','A','.','C','B','.','J','.'},
    {'X','A','B','B','B','J','J','.'}
};

grid grid15{
    {'H','H','.','G','.','F','F','.'},
    {'.','H','.','G','G','G','F','.'},
    {'I','H','B','.','.','L','F','.'},
    {'I','.','B','L','L','L','E','.'},
    {'I','I','B','B','.','C','E','.'},
    {'.','.','A','C','C','C','E','E'},
    {'A','A','A','D','D','D','.','.'},
    {'X','.','.','.','.','D','.','.'}
};

grid grid16{
    {'D','D','.','G','G','G','H','.','.'},
    {'D','E','E','G','H','H','H','.','L'},
    {'D','.','E','F','.','I','J','J','L'},
    {'.','.','E','F','.','I','J','L','L'},
    {'C','.','F','F','I','I','J','.','.'},
    {'C','C','C','B','B','O','O','O','.'},
    {'.','A','A','B','.','O','.','.','M'},
    {'.','A','.','B','N','N','N','.','M'},
    {'X','A','.','.','N','.','.','M','M'}
};

grid grid17{
    {'O','O','.','.','.','I','I','I','.'},
    {'O','.','J','J','J','I','H','.','.'},
    {'O','.','J','L','L','L','H','.','G'},
    {'N','N','N','L','.','M','H','H','G'},
    {'A','A','N','M','M','M','.','G','G'},
    {'A','.','C','C','.','.','F','F','F'},
    {'A','.','C','.','D','D','E','.','F'},
    {'.','B','C','.','.','D','E','E','E'},
    {'X','B','B','B','.','D','.','.','.'}
};

grid grid18{
    {'E','.','F','F','.','N','N','.','.'},
    {'E','E','E','F','.','.','N','.','M'},
    {'D','D','D','F','G','G','N','.','M'},
    {'D','C','.','H','.','G','.','M','M'},
    {'.','C','.','H','.','G','.','L','.'},
    {'.','C','C','H','H','.','I','L','.'},
    {'B','B','B','.','I','I','I','L','L'},
    {'.','.','B','A','J','J','J','.','.'},
    {'X','A','A','A','.','.','J','.','.'}
};

grid grid19
{
    {'.','A','B','B','C','C','C','.','.'},
    {'D','A','.','B','C','.','E','E','E'},
    {'D','A','A','B','.','F','F','F','E'},
    {'D','D','.','G','G','G','.','F','.'},
    {'H','H','.','G','.','I','.','J','J'},
    {'.','H','.','I','I','I','.','J','K'},
    {'L','H','.','M','M','M','.','J','K'},
    {'L','L','L','N','.','M','O','K','K'},
    {'X','.','.','N','N','N','O','O','O'}
};
grid blocks = {}; //currently used grid stored here so we can recover its state after undo's
set<char> blocksToCross; //list of blocks(chars) we need to cross we compare when exploring solution

struct State {
    int row;
    int col;
    grid fills;
    set<char> blocksCrossed;
    stack<Moves> plMoves;
};

void initGrid(grid choice) { //initialize grid
    blocks = choice; //save it to global
    blocksToCross.clear();
    for (int i = 0; i < blocks.size(); i++) { //save all the blocks well need to check to cross
        for (int j = 0; j < blocks[i].size(); j++) {
            if (blocks[i][j] != '.' && blocks[i][j] != 'X')
                blocksToCross.insert(blocks[i][j]);
        }
    }
}

void arrprint(grid arr) { //prints a grid
    for (int i = 0; i < arr.size(); ++i)
    {
        for (int j = 0; j < arr[i].size(); ++j)
        {
            if (arr[i][j] == 'X') {
                cout << colorize(RED) << "X "; //path in red
            }
            else {
                std::cout << colorize(WHITE) << arr[i][j] << ' ';
            }
        }
        std::cout << std::endl;
    }
    cout << endl;
}

void printCrosses(const set<char> &blocksCrossed) {
    cout << "Crossed blocks: ";
    for (auto it = blocksCrossed.begin(); it != blocksCrossed.end(); it++) {
        cout << *it;
    }
    cout << endl;
}

void printNeeded() {
    cout << "Blocks needed: ";
    for (auto it = blocksToCross.begin(); it != blocksToCross.end(); it++) {
        cout << *it;
    }
    cout << endl;
}

bool Move(Moves move, State &s) { //handles move making
    int nr = s.row;
    int nc = s.col;
    switch (move) { //update pos based on move
    case Moves::UP:
        nr -= 1;
        break;
    case Moves::DOWN:
        nr += 1;
        break;
    case Moves::LEFT:
        nc -= 1;
        break;
    case Moves::RIGHT:
        nc += 1;
        break;
    default:
        return false;
    }

    int limitCols = s.fills.size();
    int limitRows = s.fills[0].size();
    if (nr < 0 || nc < 0 || nr >= limitRows || nc >= limitCols) { //check for limits for validity of moves
        return false;
    }
    char pos = s.fills[nr][nc]; //passed limits, check in grid

    if (pos == '.' || (pos != 'X' && s.blocksCrossed.find(pos) == s.blocksCrossed.end())) { //must be new letter or . to insert
        if(pos != '.') //if its  a new letter, new block is crossed, add it
            s.blocksCrossed.insert(pos);
        s.row = nr;
        s.col = nc; //position and board update
        s.fills[nr][nc] = 'X';
        s.plMoves.push(move); //save the move for undo
        return true;
    }
    return false;
}

void undo(State &s) { //undoes a move
    s.fills[s.row][s.col] = blocks[s.row][s.col]; //returns pos to original state (. or block letter)
    s.blocksCrossed.erase(blocks[s.row][s.col]); //if it was block, it gets erased from cross list
    Moves move = s.plMoves.top();
    s.plMoves.pop();
    switch (move) { //get move from stack and update pos
    case Moves::UP:
        s.row += 1;
        break;
    case Moves::DOWN:
        s.row -= 1;
        break;
    case Moves::LEFT:
        s.col += 1;
        break;
    case Moves::RIGHT:
        s.col -= 1;
        break;
    default:
        break;
    }
}

void printTip(vector<Moves> player, vector<Moves> ai) {
    if (player.size() > ai.size()) { //if were bigger than ai list of moves, already failed
        cout << "\nYou should UNDO!\n";
        return;
    }
    for (int i = 0; i < player.size(); i++) {
        if (player[i] != ai[i]) { //diverged from path, failed
            cout << "\nYou should UNDO!\n";
            return;
        }
    }
    Moves next = ai[player.size()]; //didnt diverge, tip is next move
    cout << "\nYou should move ";
    switch (next) {
    case Moves::UP:
        cout << "UP!\n";
        break;
    case Moves::DOWN:
        cout << "DOWN!\n";
        break;
    case Moves::LEFT:
        cout << "LEFT!\n";
        break;
    case Moves::RIGHT:
        cout << "RIGHT!\n";
        break;
    default:
        break;
    }
}

vector<Moves> makeVec(stack<Moves> st) {
    vector<Moves> vec;
    while (!st.empty()) {
        vec.push_back(st.top());
        st.pop();
    }
    reverse(vec.begin(), vec.end());
    return vec;
}

void proccessInput(State &s, vector<Moves> moveList) {
    bool validInput = false;
    string in;
    Moves move;
    do {
        cout << "Choose action UP/DOWN/LEFT/RIGHT/UNDO/TIP\n";
        cin >> in;
        if (in == "UP") {
            move = Moves::UP;
            validInput = true;
        }
        else if (in == "DOWN") {
            move = Moves::DOWN;
            validInput = true;
        }
        else if (in == "LEFT") {
            move = Moves::LEFT;
            validInput = true;
        }
        else if (in == "RIGHT") {
            move = Moves::RIGHT;
            validInput = true;
        }
        else if (in == "UNDO") {
            undo(s); //dont need to call Move, exit function
            return;
        } else if(in == "TIP") {
            printTip(makeVec(s.plMoves), moveList); //no board effect, while after this
        } else {
            cout << "\nInvalid input\n";
        }
    } while (!validInput);
    if (!Move(move, s)) {
        cout << "\nCan't move there!!!\n";
    }
}

bool isAtWinningSpot(const grid fills) {
    int col = fills[0].size() - 1;
    char elem = fills[0][col];
    if (elem == 'X') {
        return true;
    }
    return false;
}

bool win(const grid fills, const set<char>& blocksCrossed) {
    if (isAtWinningSpot(fills) && blocksCrossed == blocksToCross) { //win condition
        return true;
    }
    return false;
}

State initState() { //initializes State based on current board
    int row = blocks.size() - 1;
    int col = 0;
    grid fills = blocks;
    set<char> blocksCrossed;
    stack<Moves> plMoves;
    State s;
    s.row = row;
    s.col = col;
    s.fills = fills;
    s.blocksCrossed = blocksCrossed;
    s.plMoves = plMoves;
    return s;
}

int dist(const State& s) { //calculates distance (number of moves to get to target position)
    int size = s.fills[0].size();
    int distcol = size - s.col;
    int distrow = s.row;
    return distcol + distrow - 1;
}

bool aiDepth(State &s, int depthLeft, const bool pruning, const bool talk) {
    if ((pruning && dist(s) > depthLeft) || depthLeft < 0) { //if checking by pruning, we can cut off if our distant to the target > than the remaining depth to move, otherwise depth ends at 0
        if(talk)
            cout << "No depth left\n\n";
        return false;
    }
    vector<Moves> search = { Moves::UP, Moves::RIGHT, Moves::DOWN, Moves::LEFT }; //all 4 possible moves are checked (put in vector to iterate with for loop
    if (talk) {
        arrprint(s.fills);
    }
    for (int i = 0; i < 4; i++) { //checking the 4 moves
        if (Move(search[i], s)) { //move legality check, nothing done if illegal
            if (win(s.fills, s.blocksCrossed)) { //confirmed victory
                return true;
            }
            else if (!isAtWinningSpot(s.fills) && aiDepth(s, depthLeft-1, pruning, talk)) { //can still move (not at winning spot) -> recursion (return true if recursion wins)
                return true;
            }
            if (talk)
                cout << "Dead end, undoing\n\n";
            undo(s); //not a victory and recursion doesnt lead to victory, undo dead end
            if (talk)
                arrprint(s.fills);
        }
    }
    return false;
}

bool iterativeDepth(State& s, const bool pruning, const bool talk) { //basic iterative depth algorithm, just increases depth after failure
    grid gr = s.fills;
    int ver = gr.size();
    int hor = gr[0].size();
    int idealPath = ver + hor - 2; //base depth to check should be length of the ideal path to target (no backtracking)
    bool found = false;
    int maxTries = 1000; //failsafe in case of infinite looping, if board is solvable shouldnt happen
    while(maxTries > 0) {
        found = aiDepth(s, idealPath, pruning, talk);
        if (found)
            return true;
        maxTries--;
        s = initState(); //board reset
        idealPath++; //depth increase on failure
    }
}

bool aiDepthITNOR(State& s, int depthLeft, const bool talk, queue<State> &depOptions, queue<int> &depAdd) { //depth algo for improved iteratyive depth
    if (dist(s) > depthLeft) { //pruning built in
        depOptions.push(s); //dont throw away movements that exceed depth, store them to start over from there
        depAdd.push(depthLeft + 1); //increase deppth by 1
        if (talk)
            cout << "No depth left\n\n";
        return false;
    }
    //otherwise identical to regular depth recursion
    vector<Moves> search = { Moves::UP, Moves::RIGHT, Moves::DOWN, Moves::LEFT };
    if (talk) {
        arrprint(s.fills);
    }
    for (int i = 0; i < 4; i++) {
        if (Move(search[i], s)) {
            if (win(s.fills, s.blocksCrossed)) {
                return true;
            }
            else if (!isAtWinningSpot(s.fills) && aiDepthITNOR(s, depthLeft - 1, talk, depOptions, depAdd)) {
                return true;
            }
            if (talk)
                cout << "Dead end, undoing\n\n";
            undo(s);
            if (talk)
                arrprint(s.fills);
        }
    }
    return false;
}

bool iterativeDepthNoRepeat(State& s, const bool talk) { //does iterative without wasting time repeating already done path
    grid gr = s.fills;
    int ver = gr.size();
    int hor = gr[0].size();
    int idealPath = ver + hor - 2;
    bool found = false;
    queue<State> depOptions; //queue of states to try
    queue<int> depAdd; //queue of depth to corresponding states
    depOptions.push(s);
    depAdd.push(idealPath); //first checks paths of ideal size
    while (!depOptions.empty()) {
        State trye = depOptions.front();
        depOptions.pop();
        int de = depAdd.front();
        depAdd.pop();
        found = aiDepthITNOR(trye, de, talk, depOptions, depAdd); //after checking path of a certain size, paths of size+1 are added to depOptions (and +1 to depAdd)
        //effectively checks all paths of idealPath size first, then idealPath+1, then idealPath+2, without recalculating the same subpaths every time
        if (found) {
            s = trye;
            return true;
        }
    }
}

bool aiBreadth(State& init, const bool talk) { //breadth algorith, simple
    queue<State> explore; //states to explore and kept in queue
    explore.push(init);
    while (!explore.empty()) {
        State s = explore.front();
        if (talk) {
            cout << "Exploring:\n\n";
            arrprint(s.fills);
        }
        explore.pop();
        //cout << "Exploring " << s.row << " " << s.col << "\n";
        vector<Moves> search = { Moves::UP, Moves::RIGHT, Moves::DOWN, Moves::LEFT };
        for (int i = 0; i < 4; i++) {
            State newS = s;
            if (Move(search[i], newS)) { //if move is legal
                if (win(newS.fills, newS.blocksCrossed)) {
                    init = newS; //found our winner, save it
                    return true;
                }
                else if (!isAtWinningSpot(newS.fills)) { //not at the end, worth exploring
                    explore.push(newS); //add to queue if worth exploring
                }
            }
        }
    }
    return false;
}

//heuristics
int minDist(const State& s) {
    return -dist(s);
}
int crossed(const State& s) {
    return s.blocksCrossed.size();
}
int minusCrossed(const State& s) {
    return -s.blocksCrossed.size();
}
int BDist(const State& s) {
    return crossed(s) + dist(s);
}
int mBDist(const State& s) {
    return minusCrossed(s) + dist(s);
}
int mBmDist(const State& s) {
    return minusCrossed(s) - dist(s);
}
int BmDist(const State& s) {
    return crossed(s) - dist(s);
}
int aStar(const State& s) {
    return s.plMoves.size() + dist(s);
}
//heuristics

bool informedSearch(State& init, const bool talk, int (*func)(const State&)) { //func returns value for state, according to heuristic
    list<State> explore; //keep list of open nodes
    explore.push_back(init);
    while (!explore.empty()) {
        State s = explore.front(); //get the one at front (ideal node according to heuristic)
        if (talk) {
            cout << "Exploring:\n\n";
            arrprint(s.fills);
        }
        explore.pop_front(); //explored, remove
        vector<Moves> search = { Moves::UP, Moves::RIGHT, Moves::DOWN, Moves::LEFT };
        for (int i = 0; i < 4; i++) {
            State newS = s;
            if (Move(search[i], newS)) { //if move is legal
                if (win(newS.fills, newS.blocksCrossed)) {
                    init = newS; //found our winner, save it
                    return true;
                }
                else if (!isAtWinningSpot(newS.fills)) { //not at the end, worth exploring
                    explore.push_back(newS); //add to list if worth exploring
                }
            }
        }
        explore.sort([&func](const State& a, const State& b) { return func(a) < func(b); }); //new nodes added, resort according to heuristic
    }
    return false;
}

void aiAnalysis(vector<grid> grids) { //checks all 5 algorithms, for all boards
    for (int i = 0; i < grids.size(); i++) {
        grid gr1d = grids[i];
        initGrid(gr1d);
        State dep = initState();
        State bed = initState();
        State itd = initState();
        State itdp = initState();
        State itdnr = initState();
        auto start = high_resolution_clock::now();
        bool depdone = aiDepth(dep, INT_MAX, false, false); //normal depth
        auto mid1 = high_resolution_clock::now();
        bool beddone = aiBreadth(bed, false); //breadth
        auto mid2 = high_resolution_clock::now();
        bool itddone = iterativeDepth(itd, false, false); //iterative, no pruning
        auto mid3 = high_resolution_clock::now();
        bool itdpdone = iterativeDepth(itdp, true, false); //iterative, pruning
        auto mid4 = high_resolution_clock::now();
        bool itdnrdone = iterativeDepthNoRepeat(itdnr, false); //iterative, recalculation avoidance
        auto done = high_resolution_clock::now();
        if (!depdone || !beddone || !itddone || !itdpdone || !itdnrdone) { //all must pass
            cout << "Solving failure at " << i;
        }
        else if (dep.fills != bed.fills || dep.fills != itd.fills || dep.fills != itdp.fills || dep.fills != itdnr.fills) { //and all should be equal
            cout << "Incongruent answers at " << i;
        }
        else {
            cout << "Grid " << i << " solution: \n";
            arrprint(dep.fills);
            auto deptime = duration_cast<microseconds>(mid1 - start);
            auto bedtime = duration_cast<microseconds>(mid2 - mid1);
            auto itdtime = duration_cast<microseconds>(mid3 - mid2);
            auto itdptime = duration_cast<microseconds>(mid4 - mid3);
            auto itdnrtime = duration_cast<microseconds>(done - mid4);
            cout << "Depth time: " << ((float)deptime.count()) / 1000 << "ms" << "\n";
            cout << "Breadth time: " << ((float)bedtime.count())/1000 << "ms" << "\n";
            cout << "Iterative depth time: " << ((float)itdtime.count())/1000 << "ms" << "\n";
            cout << "Iterative depth with pruning time: " << ((float)itdptime.count())/1000 << "ms" << "\n";
            cout << "Iterative depth without recalc: " << ((float)itdnrtime.count())/1000 << "ms" << "\n\n\n";
        }
    }
}

void heuristicAiAnalysis(vector<grid> grids) { //checks all heuristics, for all boards
    for (int i = 0; i < grids.size(); i++) {
        grid gr1d = grids[i];
        initGrid(gr1d);
        State st = initState(); //using just one state and resetting, effect on time should be minimal
        auto start = high_resolution_clock::now(); //used diff states to check if they all agreed on resolution but its pretty clear algorithms work by now so we can assume they do
        bool ddone = informedSearch(st, false, dist);
        st = initState();
        auto mid1 = high_resolution_clock::now();
        bool mddone = informedSearch(st, false, minDist);
        st = initState();
        auto mid2 = high_resolution_clock::now();
        bool bdone = informedSearch(st, false, crossed);
        st = initState();
        auto mid3 = high_resolution_clock::now();
        bool mbdone = informedSearch(st, false, minusCrossed);
        st = initState();
        auto mid4 = high_resolution_clock::now();
        bool bddone = informedSearch(st, false, BDist);
        st = initState();
        auto mid5 = high_resolution_clock::now();
        bool bmddone = informedSearch(st, false, BmDist);
        st = initState();
        auto mid6 = high_resolution_clock::now();
        bool mbmddone = informedSearch(st, false, mBmDist);
        st = initState();
        auto mid7 = high_resolution_clock::now();
        bool mbddone = informedSearch(st, false, mBDist);
        st = initState();
        auto mid8 = high_resolution_clock::now();
        bool adone = informedSearch(st, false, aStar);
        auto done = high_resolution_clock::now();
        if (!ddone || !mddone || !bdone || !mbdone || !bddone || !bmddone || !mbmddone || !mbddone || !adone) { //all must pass
            cout << "Solving failure at " << i;
        }
        else {
            cout << "Grid " << i << " solution: \n";
            arrprint(st.fills);
            auto dtime = duration_cast<microseconds>(mid1 - start);
            auto mdtime = duration_cast<microseconds>(mid2 - mid1);
            auto btime = duration_cast<microseconds>(mid3 - mid2);
            auto mbtime = duration_cast<microseconds>(mid4 - mid3);
            auto bdtime = duration_cast<microseconds>(mid5 - mid4);
            auto bmdtime = duration_cast<microseconds>(mid6 - mid5);
            auto mbmdtime = duration_cast<microseconds>(mid7 - mid6);
            auto mbdtime = duration_cast<microseconds>(mid8 - mid7);
            auto atime = duration_cast<microseconds>(done - mid8);
            cout << "Dist(s): " << ((float)dtime.count()) / 1000 << "ms" << "\n";
            cout << "-Dist(s): " << ((float)mdtime.count()) / 1000 << "ms" << "\n";
            cout << "Crossed(s): " << ((float)btime.count()) / 1000 << "ms" << "\n";
            cout << "-Crossed(s): " << ((float)mbtime.count()) / 1000 << "ms" << "\n";
            cout << "Dist(s)+Crossed(s): " << ((float)bdtime.count()) / 1000 << "ms" << "\n";
            cout << "-Dist(s)+Crossed(s): " << ((float)bmdtime.count()) / 1000 << "ms" << "\n";
            cout << "-Dist(s)-Crossed(s): " << ((float)mbmdtime.count()) / 1000 << "ms" << "\n";
            cout << "Dist(s)-Crossed(s): " << ((float)mbdtime.count()) / 1000 << "ms" << "\n";
            cout << "A*(s): " << ((float)atime.count()) / 1000 << "ms" << "\n\n\n";
        }
    }
}

void printgrids(vector<grid> grids) { //prints all grids (to display for choice)
    for (int i = 0; i < grids.size(); i++) {
        cout << "Grid " << i << "\n";
        arrprint(grids[i]);
    }
}

void heuristicChoice(grid gchoice) {
    cout << "Distance (D), -Distance (C), Blocks Crossed (B), -Blocks Crossed (P), Dist + Blocks (Z), Dist - Blocks(X), -Dist + Blocks(W), -Dist - Blocks(S), A* (A)\n";
    char choice;
    bool repeat = true;
    initGrid(gchoice);
    State st = initState();
    bool solve;
    while (repeat) {
        repeat = false;
        cin >> choice;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice) {
        case 'D':
            solve = informedSearch(st, true, dist);
            break;
        case 'C':
            solve = informedSearch(st, true, minDist);
            break;
        case 'B':
            solve = informedSearch(st, true, crossed);
            break;
        case 'P':
            solve = informedSearch(st, true, minusCrossed);
            break;
        case 'Z':
            solve = informedSearch(st, true, BDist);
            break;
        case 'X':
            solve = informedSearch(st, true, mBDist);
            break;
        case 'W':
            solve = informedSearch(st, true, BmDist);
            break;
        case 'S':
            solve = informedSearch(st, true, mBmDist);
            break;
        case 'A':
            solve = informedSearch(st, true, aStar);
            break;
        default:
            repeat = true;
            break;
        }
    }
    if (solve) {
        arrprint(st.fills);
        cout << "Solved\n";
    }
    else {
        cout << "Failed to solve, shouldn't happen";
    }
}

void choosingAI(grid gchoice) { //choosing ai for auto-solving option
    cout << "Depth (D), Breadth (B), Iterative Depth (I), Iterative Depth with Pruning (P), Iterative Depth with no Recalc(R), Informed (F)\n";
    char choice;
    while (true) {
        cin >> choice;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (choice == 'F') { //if were going by informed open another choice to choose which heuristic to try
            heuristicChoice(gchoice);
            return;
        }
        if (choice != 'D' && choice != 'B' && choice != 'I' && choice != 'P' && choice != 'R') {
            cout << "Invalid input\n";
        }
        else {
            break;
        }
    }
    initGrid(gchoice);
    State st = initState(); //ai chosen so we can initiate the board
    bool solve = false;
    switch (choice) {
        case 'D':
            solve = aiDepth(st, INT_MAX, false, true);
            break;
        case 'B':
            solve = aiBreadth(st, true);
            break;
        case 'I':
            solve = iterativeDepth(st, false, true);
            break;
        case 'P':
            solve = iterativeDepth(st, true, true);
            break; 
        case 'R':
            solve = iterativeDepthNoRepeat(st, true);
            break;
        default:
            break;
    }
    if (solve) {
        arrprint(st.fills);
        cout << "Solved\n";
    }
    else {
        cout << "Failed to solve, shouldn't happen";
    }
}

void playerLoop(grid choice) { //for gameplay
    bool won;
    initGrid(choice);
    State ai = initState();
    State s = initState();
    aiDepth(ai, INT_MAX, false, false); //first ai solves it, to keep their list of moves for tips (depth used has its shown to be the best)
    do {
        arrprint(s.fills);
        printCrosses(s.blocksCrossed);
        proccessInput(s, makeVec(ai.plMoves));
        won = win(s.fills, s.blocksCrossed);
    } while (!won);
    arrprint(s.fills);
    cout << "\n\nYou won!!!\n\n";
}

int main() {

#ifdef _WIN32
    activateVirtualTerminal();
#endif

    vector<grid> grids = { grid0, grid1, grid2, grid3, grid4, grid5, grid6, grid7, grid8, grid9, grid10, grid11,grid12, grid13,
    grid14, grid15, grid16, grid17, grid18, grid19 };
    cout << "Play (P), AI Play (C), Uninformed Analysis (A), Informed Heuristics Analysis (H)\n";
    char choice;
    
    while (true) {
        cin >> choice;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (choice != 'P' && choice != 'C' && choice != 'A' && choice != 'H') {
            cout << "Invalid input\n";
        }
        else {
            break;
        }
    }
    if (choice == 'P' || choice == 'C') {
        printgrids(grids);
        int chosengrid;
        while (true) {
            cout << "Choose board\n";
            cin >> chosengrid;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (chosengrid < 0 || chosengrid >= grids.size()) {
                cout << "Invalid input\n";
            }
            else {
                break;
            }
        }
        if (choice == 'P') {
            playerLoop(grids[chosengrid]);
        }
        else {
            choosingAI(grids[chosengrid]);
        }
    }
    else if(choice == 'A') {
        aiAnalysis(grids);
    }
    else {
        heuristicAiAnalysis(grids);
    }
    return 0;
}
