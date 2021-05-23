#ifndef DELETEVERTEXDIALOG_H
#define DELETEVERTEXDIALOG_H

#include <QDialog>
#include "myopenglwidget.h"

namespace Ui {
class DeleteVertexDialog;
}

class DeleteVertexDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteVertexDialog(QWidget *parent = nullptr);
    ~DeleteVertexDialog();

    void new_pivot(pivot* intermedary) { m_pivot = intermedary; }
    void new_paint_widget(MyOpenGLWidget* widget) { m_widget = widget; }

private slots:
    void on_CancelPushButton_clicked();

    void on_ApplySettingsPushButton_clicked();

private:
    Ui::DeleteVertexDialog *ui;

    pivot* m_pivot;
    QVector<QVector<int>> node_matrix;
    MyOpenGLWidget* m_widget;
};

#endif // DELETEVERTEXDIALOG_H
