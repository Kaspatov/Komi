#ifndef PIVOT_H
#define PIVOT_H

#include <QString>
#include <QBrush>
#include <QPen>

class pivot
{
public:
    pivot();

    int SalesmanRootLength = -1;
    QString SalesmanRoute;
    QVector<QVector<int>> AdjacencyMatrix =
    {
        { 0, 14, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 42, 23 },
        { 19, 0, 0, 9, 0, 0 },
        { 0, 0, 0, 0, 0, 31 },
        { 0, 0, 18, 0, 0, 0 },
        { 28, 23, 0, 0, 0, 0}
    };

    void SetSalesmanRoot(QVector<int> route);
};

#endif // PIVOT_H
