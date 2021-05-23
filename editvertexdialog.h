#ifndef EDITVERTEXDIALOG_H
#define EDITVERTEXDIALOG_H

#include <QDialog>
#include "myopenglwidget.h"

namespace Ui {
class EditVertexDialog;
}

class EditVertexDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditVertexDialog(QWidget *parent = nullptr);
    ~EditVertexDialog();

    void new_pivot(pivot* intermedary) { m_pivot = intermedary; }
    void new_paint_widget(MyOpenGLWidget* widget) { m_widget = widget; }

private slots:
    void on_ApplyPushButton_clicked();

    void on_CancelPushButton_clicked();

private:
    Ui::EditVertexDialog *ui;

    pivot* m_pivot;
    QVector<QVector<int>> node_matrix;
    MyOpenGLWidget* m_widget;
};

#endif // EDITVERTEXDIALOG_H
