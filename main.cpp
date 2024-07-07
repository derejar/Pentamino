#include <iostream>
#include <iomanip>
#include "board.h"
#include "figure.h"

template <typename T>
using figures_t = std::vector<Figure<T>>;

template <typename T, std::size_t X, std::size_t Y>
using boards_t = std::vector<board_t<T, X, Y>>;

template <typename T>
figures_t<T> createFigures()
{
    figures_t<T> figures({
        Figure<T>({
            {1},
            {1},
            {1},
            {1},
            {1}
        }),
        Figure<T>({
            {1, 1},
            {1},
            {1}
        }),
        Figure<T>({
            {1, 1, 1, 1},
            {0, 1}
        }),
        Figure<T>({
            {0, 0, 1},
            {1, 1, 1}
        }),
        Figure<T>({
            {0, 1, 0},
            {1, 1, 1},
            {0, 1, 0}
        }),
        Figure<T>({
            {0, 1},
            {1, 1, 1},
            {0, 0, 1}
        }),
        Figure<T>({
            {1, 1},
            {0, 1},
            {0, 1}
        }),
        Figure<T>({
            {0, 1},
            {0, 1},
            {1, 1, 1}
        }),
        Figure<T>({
            {1},
            {1, 1},
            {0, 1, 1}
        }),
        Figure<T>({
            {1, 1},
            {0, 1, 1, 1}
        }),
        Figure<T>((std::vector<std::vector<T>>(1, std::vector<T>(1, 1))))
    });
    return figures;
}

template <typename T, std::size_t X, std::size_t Y>
void recursive(boards_t<T, X, Y>& boards, const board_t<T, X, Y> currentBoard, const figures_t<T>& figures, const unsigned int currentFigure)
{
    if(currentFigure == figures.size())
    {
        boards.push_back(currentBoard);
        return;
    }
    for(std::size_t i = 0; i < currentBoard.size(); ++i)
    {
        for(std::size_t j = 0; j < currentBoard[i].size(); ++j)
        {
            if(figures[currentFigure].isPlaceble(currentBoard, j, i))
                recursive(boards, figures[currentFigure].placeTo(currentBoard, j, i), figures, currentFigure + 1);
        }
    }
}

template <typename T, std::size_t X, std::size_t Y>
boards_t<T, X, Y> solve(const board_t<T, X, Y>& board, const figures_t<T>& figures)
{
    boards_t<T, X, Y> boards;
    recursive(boards, board, figures, 0);
    return boards;
}

template <typename T, std::size_t X, std::size_t Y>
std::ostream& operator<<(std::ostream& os, const board_t<T, X, Y>& board)
{
    for(std::size_t i = 0; i < board.size(); ++i)
    {
        for(std::size_t j = 0; j < board[i].size(); ++j)
            os << std::left << std::setw(2) << std::setfill(' ') << board[i][j] << " ";
        os << "\n";
    }
    return os;
}

int main()
{
    board_t<unsigned int, 8, 6> board({0});
    auto figures = createFigures<unsigned int>();
    boards_t<unsigned int, 8, 6> boards = solve(board, figures);
    for(const auto& board : boards)
        std::cout << board << "\n\n";
}
