#include <cstring>
#include <iostream>
#include <queue>
#define LOG(x) std::cout << x << std::endl;

char start[5], end[5];
static const char minFile = 'A';
static const char maxFile = 'H';
static const char minRank = '1';
static const char maxRank = '8';

// position
class Position
{
    public:
    char rank, file;
    int move;

    // constructor
    Position() {}
    Position(int r, int f, int m): rank(r), file(f), move(m) {}
};

// checks
bool isValid(int rank, int file)
{
    return rank >= 1 && rank <= 8 && file >= 1 && file <= 8;
}

bool isValidFile( char f )
{
    return f >= minFile && f <= maxFile;
}

bool isValidRank( char r )
{
    return r >= minRank && r <= maxRank;
}

int minStep()
{
    // starting knight position
    int posFile = toupper(start[0]) - 'A';
    int posRank = start[1] - '1';

    if ( !( isValidFile(toupper(start[0])) && isValidRank(start[1]) ))
        throw std::invalid_argument( "invalid file and/or rank" );

    // target knight position
    int tarFile = toupper(end[0]) - 'A';
    int tarRank = end[1] - '1';

    if ( !( isValidFile(toupper(end[0])) && isValidRank(end[1]) ))
        throw std::invalid_argument( "invalid file and/or rank" );

    // all knight's possible moves
    int x[] = { -2, -1, 1, 2, -2, -1, 1, 2 };
    int y[] = { -1, -2, -2, -1, 1, 2, 2, 1 };

    //create queue
    std::queue<Position> q;

    // taking knight's position (move 0)
    q.push( Position( posFile, posRank, 0) );

    Position t;
    int rank, file;
    int N = 8;
    bool visit [N + 1] [ N + 1];

    // unvisit all points
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            visit[i][j] = false;

    // visit first state
    visit[posFile][posRank] = true;

    // loop until queue is not empty
    while (!q.empty())
    {
        t = q.front();
        q.pop();

        // return distance if target reached
        if (t.rank == tarFile && t.file == tarRank)
        {
                return t.move;
        }

        // loop all possible moves
        for (int i= 0; i < 8; i++)
        {
            rank = t.rank + x[i];
            file = t.file + y[i];

            if ( isValid(rank, file)  && !visit[rank][file])
            {
                visit[rank][file] = true;
                q.push( Position(rank, file, t.move + 1));
            }
        }
    }
    return 0;
}

int main()
{
    int step;
    try
    {
        LOG("Welcome to the Knight Travails project.(Press Enter to Continue)")
        std::cin.get();

        LOG("Enter initial location using chess notations(A1, B2, H8): ")
        std::cin >> start;
        LOG("Enter target location using chess notations(A1, B2, H8): ")
        std::cin >> end;

        step = minStep();

        std::cout << "To get from " << start << " to " << end << " takes " << step << " knight moves." << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}
