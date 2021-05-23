#include "deletevertexdialog.h"
#include "ui_deletevertexdialog.h"

DeleteVertexDialog::DeleteVertexDialog(QWidget *parent) : QDialog(parent), ui(new Ui::DeleteVertexDialog)
{
    ui->setupUi(this);
}

DeleteVertexDialog::~DeleteVertexDialog()
{
    delete ui;
}


void DeleteVertexDialog::on_CancelPushButton_clicked()
{
    hide();
}


void DeleteVertexDialog::on_ApplySettingsPushButton_clicked()
{
    QVector<QVector<int>> node_matrix = m_pivot->AdjacencyMatrix;
    node_matrix.removeAt(ui->DelitableVertexIndexLineEdit->text().toInt() - 1);
        for (int i = 0; i < node_matrix.count(); i++)
            node_matrix[i].removeAt(ui->DelitableVertexIndexLineEdit->text().toInt() - 1);

    m_pivot->AdjacencyMatrix = node_matrix;
    m_widget->GetPresenter()->new_matrix();
    m_widget->redraw();

    hide();
}

