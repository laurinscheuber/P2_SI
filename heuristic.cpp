#include "heuristic.h"
#include <utility> // for std::make_pair

static unsigned int mi_contador_de_llamadas = 0;

unsigned int GetCalls()
{
    return mi_contador_de_llamadas;
}

float h(Player pl, Board b)
{
    mi_contador_de_llamadas++;
    return mi_contador_de_llamadas;
}

// Mobility Heuristic
float h1(Player pl, Board b)
{
    mi_contador_de_llamadas++;
    Sqlist moves = b.ValidMoves(pl);
    return static_cast<float>(moves.size());
}

// Corner Heuristic
float h2(Player pl, Board b)
{
    mi_contador_de_llamadas++;
    int score = 0;
    Square corners[4] = { std::make_pair('1', 'A'), std::make_pair('1', 'H'), std::make_pair('8', 'A'), std::make_pair('8', 'H') };
    for (Square corner : corners)
    {
        if (b.Content(corner) == Tk(pl))
        {
            score += 10; // Assign a high value for corners
        }
    }
    return static_cast<float>(score);
}

// Stability Heuristic
float h3(Player pl, Board b)
{
    mi_contador_de_llamadas++;
    int stable_disks = 0;
    // Implement a method to count stable disks
    // For simplicity, let's assume all disks on the edges are stable
    for (unsigned i = 0; i < BOARD_SIZE; i++)
    {
        if (b.Content(std::make_pair('1', 'A' + i)) == Tk(pl))
            stable_disks++;
        if (b.Content(std::make_pair('8', 'A' + i)) == Tk(pl))
            stable_disks++;
        if (b.Content(std::make_pair('1' + i, 'A')) == Tk(pl))
            stable_disks++;
        if (b.Content(std::make_pair('1' + i, 'H')) == Tk(pl))
            stable_disks++;
    }
    return static_cast<float>(stable_disks);
}

// Disk Difference Heuristic
float h4(Player pl, Board b)
{
    mi_contador_de_llamadas++;
    int my_disks = b.GetSquares(pl);
    int opponent_disks = b.GetSquares(Opponent(pl));
    return static_cast<float>(my_disks - opponent_disks);
}

// Positional Heuristic
float h5(Player pl, Board b)
{
    mi_contador_de_llamadas++;
    int score = 0;
    // Assign values to each position on the board
    int positional_values[BOARD_SIZE][BOARD_SIZE] = {
        {4, -3, 2, 2, 2, 2, -3, 4},
        {-3, -4, -1, -1, -1, -1, -4, -3},
        {2, -1, 1, 0, 0, 1, -1, 2},
        {2, -1, 0, 1, 1, 0, -1, 2},
        {2, -1, 0, 1, 1, 0, -1, 2},
        {2, -1, 1, 0, 0, 1, -1, 2},
        {-3, -4, -1, -1, -1, -1, -4, -3},
        {4, -3, 2, 2, 2, 2, -3, 4}};
    for (unsigned i = 0; i < BOARD_SIZE; i++)
    {
        for (unsigned j = 0; j < BOARD_SIZE; j++)
        {
            if (b.Content(std::make_pair('1' + i, 'A' + j)) == Tk(pl))
            {
                score += positional_values[i][j];
            }
        }
    }
    return static_cast<float>(score);
}
