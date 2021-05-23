#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H
#include "graphpainter.h"
#include <QOpenGLWidget>

class MyOpenGLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    MyOpenGLWidget(QWidget *parent);
    ~MyOpenGLWidget();

    void SetGraphPresenter(graph_painter* presenter);
    void ConnectIntermediary(pivot* intermediary);
    graph_painter* GetPresenter() { return m_painter; };

public slots:
    void redraw();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    graph_painter* m_painter;
    pivot*   m_pivot;

    void CopyIntermediry();
};

#endif // MYOPENGLWIDGET_H
