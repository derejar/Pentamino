#ifndef _FIGURE_H_
#define _FIGURE_H_

#include "board.h"
#include <vector>
#include <stdexcept>

template <typename T>
class Figure
{
    unsigned int id;
public:
    Figure(const std::vector<std::vector<T>>& figure) : m_figure(figure), m_maxWidth(0), m_maxHeight(figure.size())
    {
        if(m_figure.empty())
            throw std::logic_error("Figure cant be empty!");
        id = availableId++;
        for(auto& row : m_figure)
        {
            if(row.size() > m_maxWidth)
                m_maxWidth = row.size();
            for(auto& number : row)
                number = number != 0 ? id : 0;
        }
    }

    template <std::size_t X, std::size_t Y>
    bool isPlaceble(const board_t<T, X, Y>& board, T x, T y) const
    {
        if(x + m_maxWidth > X || y + m_maxHeight > Y)
            return false;
        for(std::size_t i = 0; i < m_figure.size(); ++i, ++y)
        {
            T currentX = x;
            for(std::size_t j = 0; j < m_figure[i].size(); ++j, ++currentX)
                if(m_figure[i][j] != 0 && board[y][currentX] != 0)
                    return false;
        }
        return true;
    }

    template <std::size_t X, std::size_t Y>
    board_t<T, X, Y> placeTo(board_t<T, X, Y> board, T x, T y) const
    {
        for(std::size_t i = 0; i < m_figure.size(); ++i, ++y)
        {
            T currentX = x;
            for(std::size_t j = 0; j < m_figure[i].size(); ++j, ++currentX)
                if(m_figure[i][j] != 0)
                    board[y][currentX] = m_figure[i][j];
        }
        return board;
    }

private:
    std::vector<std::vector<T>> m_figure;
    std::size_t m_maxWidth;
    std::size_t m_maxHeight;
    static unsigned int availableId;
};

template <typename T>
unsigned int Figure<T>::availableId = 2;

#endif
