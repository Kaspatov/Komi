#include "graphpainter.h"

#include <QPaintEvent>
#include <QPainter>
#include <QWidget>
#include <QtCore/qmath.h>
#include <QObject>

double pi = 3.1415;
double angl = pi / 8;

int xp;
int yp;

QBrush node_back = QBrush(QColor(87, 229, 44));
QBrush back = QBrush(QColor(167, 226, 0));
QBrush num_back = QBrush(QColor(255, 255, 255));
QPen border_pen = QPen(QColor(0, 0, 0));

QString schrift = "times new roman";
int schrift_size = 28;
int graph_radius = 300;
int node_radius = 44;
int edge_leng = 15;

graph_painter::graph_painter() {}

void graph_painter::new_matrix() { graph_matrix = m_pivot->AdjacencyMatrix; }
void graph_painter::draw(QPainter *painter, QPaintEvent *event) { draw_graph(painter, event); }

void graph_painter::draw_graph(QPainter *painter, QPaintEvent* event)
{
    int node_count = graph_matrix[0].size();
    graph_radius = qMax(painter->window().width() / 5, 100);

    yp = painter->window().height() / 2;
    xp = painter->window().width() / 2;

    painter->fillRect(event->rect(), back);
    painter->setBrush(node_back);
    painter->setPen(border_pen);
    painter->setFont(QFont(schrift, schrift_size * 0.8));

    border_pen.setWidth(5);

    for (int i = 0; i < node_count; i++)
    {
        double polarAngle = pi * 3 / 2 + pi * 2 / node_count * i;

        int xc = cos(polarAngle) * graph_radius + xp;
        int yc = sin(polarAngle) * graph_radius + yp;

        int p1 = xc - 20;
        int p2 = yc - schrift_size / 2;
        int p3 = 40;
        int p4 = schrift_size;

        QString text; text.setNum(i + 1);
        painter->drawEllipse(QRectF(xc - node_radius, yc - node_radius, 2 * node_radius, 2 * node_radius));
        painter->drawText(QRect(p1, p2, p3, p4), Qt::AlignCenter, text);

        for (int k = 0; k < node_count; k++)
        {
            if (graph_matrix[i][k] != 0)
            {
                double a2 = pi * 3 / 2 + pi * 2 / node_count * k;
                double xp2 = cos(a2) * graph_radius + xp;
                double yp2 = sin(a2) * graph_radius + yp;
                double l = sqrt((xp2 - xc) * (xp2 - xc) + (yp2 - yc) * (yp2 - yc));

                int xl1 = (xp2 - xc) / l * node_radius + xc;
                int yl1 = (yp2 - yc) / l * node_radius + yc;
                int xl2 = xp2 - (xp2 - xc) / l * node_radius;
                int yl2 = yp2 - (yp2 - yc) / l * node_radius;

                painter->drawLine(xl1, yl1, xl2, yl2);

                double edge_angle;

                if (xp2 == xl2 && yl2 < yp2) edge_angle = pi * 3 / 2;
                else if (yp2 == yl2 && xl2 < xp2) edge_angle = pi;
                else if (xp2 == xl2 && yl2 > yp2) edge_angle = pi / 2;
                else if (yp2 == yl2 && xl2 > xp2) edge_angle = 0;
                else if (xl2 > xp2 && yl2 < yp2) edge_angle = atan((yp2 - yl2) / (xp2 - xl2)) + pi * 2;
                else if (xl2 < xp2 && yl2 < yp2) edge_angle = atan((yp2 - yl2) / (xp2 - xl2)) + pi;
                else if (xl2 < xp2 && yl2 > yp2) edge_angle = atan((yp2 - yl2) / (xp2 - xl2)) + pi;
                else if (xl2 > xp2 && yl2 > yp2) edge_angle = atan((yp2 - yl2) / (xp2 - xl2));

                int xs1 = cos(edge_angle + angl) * edge_leng + xl2;
                int ys1 = sin(edge_angle + angl) * edge_leng + yl2;
                int xs2 = cos(edge_angle - angl) * edge_leng + xl2;
                int ys2 = sin(edge_angle - angl) * edge_leng + yl2;

                painter->drawLine(xl2, yl2, xs1, ys1);
                painter->drawLine(xl2, yl2, xs2, ys2);

                int txt_w = 40;
                int txt_h = schrift_size + 5;
                int line_half_x = (xl2 + xl1) / 2;
                int line_half_y = (yl2 + yl1) / 2;

                QString mark_txt = QString::number(graph_matrix[i][k]);

                if (graph_matrix[i][k] != graph_matrix[k][i] && graph_matrix[i][k] != 0 && i != k
                        && graph_matrix[k][i] != 0)
                {
                    txt_w += 24;
                    mark_txt += "; " + QString::number(graph_matrix[k][i]);
                }

                painter->setBrush(back);
                painter->drawEllipse(line_half_x - txt_w / 2, line_half_y - txt_h / 2, txt_w, txt_h);

                painter->setBrush(node_back);
                painter->drawText(QRect(line_half_x - txt_w / 2, line_half_y - txt_h / 2, txt_w, txt_h), Qt::AlignCenter, mark_txt);
            }
        }
    }
}

void graph_painter::new_pivot(pivot *pivot)
{
    if (pivot != nullptr)
    {
        m_pivot = pivot;
        new_matrix();
    }
}
