#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
#include <chrono>
#include <ctime>

#define LOG(x) std::cout << x << std::endl;

char start[5], end[5];
static const char minFile = 'A';
static const char maxFile = 'H';
static const char minRank = '1';
static const char maxRank = '8';

// position
class Cell
{
    public:
    char rank, file;
    int move;
    // constructor
    Cell() {}
    Cell(int r, int f, int m): rank(r), file(f), move(m) {}
};

// checks
bool isValid(int rank, int file)
{
    return rank >= 1 && rank <= 8 && file >= 1 && file <= 8;
}

bool isValid2(int x, int y)
{
    return (x >= 0 && x < 8 && y >= 0 && y < 8);
}

bool isValidFile( char f )
{
    return f >= minFile && f <= maxFile;
}

bool isValidRank( char r )
{
    return r >= minRank && r <= maxRank;
}

// convert from char to int
int convertFile(char position[])
{
    return toupper(position[0]) - 'A';
}

// convert from char to int
int convertRank(char position[])
{
    return position[1] - '1';
}

// bfs
int shortestPath()
{
    // starting knight position
    int posFile = convertFile(start);
    int posRank = convertRank(start);

    if ( !( isValidFile(toupper(start[0])) && isValidRank(start[1]) ))
        throw std::invalid_argument( "invalid file and/or rank" );

    // target knight position
    int tarFile = convertFile(end);
    int tarRank = convertRank(end);

    if ( !( isValidFile(toupper(end[0])) && isValidRank(end[1]) ))
        throw std::invalid_argument( "invalid file and/or rank" );

    // all knight's possible moves
    int x[] = { -2, -1, 1, 2, -2, -1, 1, 2 };
    int y[] = { -1, -2, -2, -1, 1, 2, 2, 1 };

    //create queue
    std::queue<Cell> q;

    // taking knight's position (move 0)
    q.push( Cell( posFile, posRank, 0) );

    Cell temp;
    int rank, file;
    int N = 8;
    bool visit [N + 1] [ N + 1];

    // unvisit all cells
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            visit[i][j] = false;

    // visit first cell
    visit[posFile][posRank] = true;

    // loop until queue is not empty
    while (!q.empty())
    {
        temp = q.front();
        q.pop();

        // return distance if target reached
        if (temp.rank == tarRank && temp.file == tarFile)
        {
            return temp.move;
        }

        // loop all possible moves
        for (int i= 0; i < 8; i++)
        {
            rank = temp.rank + x[i];
            file = temp.file + y[i];

            if ( isValid(rank, file)  && !visit[rank][file])
            {
                visit[rank][file] = true;
                q.push( Cell(rank, file, temp.move + 1));
            }
        }
    }
    return 0;
}
/*
void printMoves() {
    // starting knight position
    int posFile = convertFile(start);
    int posRank = convertRank(start);

    if ( !( isValidFile(toupper(start[0])) && isValidRank(start[1]) ))
        throw std::invalid_argument( "invalid file and/or rank" );

    // target knight position
    int tarFile = convertFile(end);
    int tarRank = convertRank(end);

    if ( !( isValidFile(toupper(end[0])) && isValidRank(end[1]) ))
        throw std::invalid_argument( "invalid file and/or rank" );

    // all knight's possible moves
    int deltax[] = {2, 1, -1, -2, -2, -1, 1, 2};
    int deltay[] = {1, 2, 2, 1, -1, -2, -2, -1};

    using namespace std;
    // use vector to print pairs easier
    vector <pair <int, int>> answer;
    answer.push_back(make_pair(tarFile, tarRank));

    queue <pair <int,int> > q;
    q.push(make_pair(tarFile, tarRank));

    int visit[8][8];
    memset(visit, -1, sizeof(visit));

    // logic is very similar with the previous algorithm
    while(!q.empty()) {
        pair <int, int> temp = q.front();
        q.pop();

        if (temp.first == posFile && temp.second == posRank)
        {
            for (auto i : answer)
                cout << i.first << " " << i.second << endl;
            return;
        }

        for (int i = 0; i < 8; i++)
        {
            int x = temp.first + deltax[i];
            int y = temp.second + deltay[i];

            if (isValid2(x, y) && (visit[x][y] == (visit[temp.first][temp.second] - 1)))
            {
                answer.push_back(make_pair(x,y));
                q.push(make_pair(x,y));
                break;
            }
        }
    }
}
*/

int main()
{
    using namespace std::chrono;
    int step;
    try
    {
        LOG("Welcome to the Knight Travails project.(Press Enter to Continue)")
        std::cin.get();

        LOG("Enter initial location using chess notations(A1, B2, H8): ")
        std::cin >> start;
        LOG("Enter target location using chess notations(A1, B2, H8): ")
        std::cin >> end;

        // Record start time
        auto startTime = steady_clock::now();

        step = shortestPath();

        // Record end time
        auto endTime = steady_clock::now();

        double elapsed_time = double(duration_cast<nanoseconds> (endTime - startTime).count());

        std::cout << "To get from " << start << " to " << end << " takes " << step << " knight moves." << std::endl;

        std::cout << "Elapsed time: " << elapsed_time << " nanoseconds." << std::endl;
        std::cout << "Elapsed time: " << elapsed_time * 1E-9 << " seconds." << std::endl;
        // Path printing is still not done implemented
        // printMoves();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}
