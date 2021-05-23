#include "myopenglwidget.h"
#include "graphpainter.h"
#include <QPainter>

MyOpenGLWidget::MyOpenGLWidget(QWidget* parent) : QOpenGLWidget(parent)
{
    m_painter = new graph_painter;

    QSurfaceFormat format = QSurfaceFormat::defaultFormat();
    format.setSamples(4);
    this->setFormat(format);
}

MyOpenGLWidget::~MyOpenGLWidget()
{
    if (m_painter != nullptr)
        delete m_painter;
}

void MyOpenGLWidget::redraw()
{
    this->update();
}

void MyOpenGLWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter;

    painter.begin(this);

    m_painter->draw(&painter,event);
    painter.end();
}

void MyOpenGLWidget::SetGraphPresenter(graph_painter *presenter)
{
    if (presenter != nullptr)
        m_painter = presenter;
}

void MyOpenGLWidget::ConnectIntermediary(pivot *intermediary)
{
    if (intermediary != nullptr)
    {
        m_pivot = intermediary;
        CopyIntermediry();
    }
}

void MyOpenGLWidget::CopyIntermediry()
{
    if (m_pivot != nullptr || m_painter != nullptr)
        m_painter->new_pivot(m_pivot);
}
