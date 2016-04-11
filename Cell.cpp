#include "Cell.hpp"

#include "Field.hpp"

Cell::Cell(Field *field, int x, int y)
{
    m_field = field;

    m_x = x;
    m_y = y;

    m_haveMine = false;
    m_open = false;
}

void Cell::reset(){
    m_haveMine = false;
    m_open = false;

}

int Cell::minesAround() const
{
    int mines = 0;
    for (Cell *cell : getNeighbors()) {
        if (cell->haveMine()) {
            ++mines;
        }
    }

    return mines;
}

void Cell::setHaveMine(bool haveMine)
{
    m_haveMine = haveMine;
}

void Cell::open()
{
    if (m_field->isGenerated()== 0){
       m_field->generate(m_x,m_y);
    }
    if (m_open){
        return;
    }
    m_open = true;
    if (minesAround() == 0){
        for(Cell *cell :getNeighbors()){
            cell->open();

        }
    }
    if (haveMine()){
        m_field->lose();
    }
    }


void maybeAddCell(QVector<Cell*> *vector, Cell *cell)
{
    if (cell) {
        vector->append(cell);
    }
}

QVector<Cell *> Cell::getNeighbors() const
{
    QVector<Cell*> neighbors;
    for (int x = m_x - 1; x <= m_x + 1; ++x) {
        maybeAddCell(&neighbors, m_field->cellAt(x, m_y - 1));
        maybeAddCell(&neighbors, m_field->cellAt(x, m_y + 1));
    }
    maybeAddCell(&neighbors, m_field->cellAt(m_x - 1, m_y));
    maybeAddCell(&neighbors, m_field->cellAt(m_x + 1, m_y));

    return neighbors;
}
