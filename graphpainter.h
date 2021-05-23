#ifndef MYPAINTER_H
#define MYPAINTER_H

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>

#include "pivot.h"

class graph_painter
{
public:
    graph_painter();

public:
    void draw(QPainter *painter, QPaintEvent *event);
    void new_matrix();
    void new_pivot(pivot* pivot);

    void draw_graph(QPainter* painter, QPaintEvent* event);

private:
    pivot* m_pivot;
    QVector<QVector<int>> graph_matrix;
};

#endif //MYPAINTER_H
