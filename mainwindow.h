#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <editvertexdialog.h>
#include <deletevertexdialog.h>

#include "myopenglwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;

    MyOpenGLWidget* _presentWidget;
    pivot*  _intermediary;

    QVector<QVector<int>> add_new_node(QVector<QVector<int>> node_matrix);

    void get_route_and_length();

private slots:
    void AddVertexOnClick();
    void EditVertexOnClick();
    void DeleteVertexOnClick();
    void on_pushButton_clicked();
};
#endif // MAINWINDOW_H
