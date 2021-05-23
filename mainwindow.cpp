#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _intermediary = new pivot;

    _presentWidget = new MyOpenGLWidget(this);
    _presentWidget->ConnectIntermediary(_intermediary);

     ui->GraphicsLayout->addWidget(_presentWidget);

    _presentWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _presentWidget->redraw();

    connect(ui->AddVertexPushButton, SIGNAL(clicked()), this, SLOT(AddVertexOnClick()));
    connect(ui->EditVertexPushButton, SIGNAL(clicked()), this, SLOT(EditVertexOnClick()));
    connect(ui->DeleteVertexPushButton, SIGNAL(clicked()), this, SLOT(DeleteVertexOnClick()));
}

int ticks = 0;

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AddVertexOnClick()
{
    _intermediary->AdjacencyMatrix = add_new_node(_intermediary->AdjacencyMatrix);
    _presentWidget->GetPresenter()->new_matrix();
    _presentWidget->redraw();
}

void MainWindow::EditVertexOnClick()
{
    EditVertexDialog* dialog = new EditVertexDialog;
    dialog->new_pivot(_intermediary);
    dialog->new_paint_widget(_presentWidget);

    dialog->show();
}

void MainWindow::DeleteVertexOnClick()
{
    DeleteVertexDialog* dialog = new DeleteVertexDialog;
    dialog->new_pivot(_intermediary);
    dialog->new_paint_widget(_presentWidget);

    dialog->show();
}

QVector<QVector<int>> MainWindow::add_new_node(QVector<QVector<int>> node_matrix)
{
    QVector<int> newRow;
    newRow.push_back(0);

    for (int i = 0; i < node_matrix.count(); i++)
    {
        node_matrix[i].push_back(0);
        newRow.push_back(0);
    }

    node_matrix.push_back(newRow);
    return node_matrix;
}


void MainWindow::on_pushButton_clicked()
{
    get_route_and_length();
}

void MainWindow::get_route_and_length()
{
    try
    {
        QVector<int> result_arr_1;
        QVector<int> result_arr_2;
        QVector<int> valueRoutes;

        int sum = 0,
            steps = 0;
        bool flag = true;
        QVector<QVector<int>> data = _intermediary->AdjacencyMatrix;

        for (int i = 0; i < data.size(); i++)
        {
            for (int k = 0; k < data.size(); k++)
            {
                if (i == k || data[i][k] == 0)
                    data[i][k] = INT_MAX;
            }
        }

        int len = data[0].size();

        while (flag)
        {
            steps++;
            if (steps > 1000)
            {
                throw 1;
            }

            QVector<int> row(len);
            std::fill(row.begin(), row.end(), INT_MAX);

            QVector<int> column(len);
            std::fill(column.begin(), column.end(), INT_MAX);

            for (int i = 0; i < len; i++)
                for (int k = 0; k < len; k++)
                    row[i] = qMin(row[i], data[i][k]);

            for (int i = 0; i < len; i++)
                for (int k = 0; k < len; k++)
                    if (row[i] != INT_MAX && data[i][k] != INT_MAX)
                        data[i][k] -= row[i];

            for (int i = 0; i < len; i++)
                for (int k = 0; k < len; k++)
                    column[k] = qMin(column[k], data[i][k]);

            for (int i = 0; i < len; i++)
                for (int k = 0; k < len; k++)
                    if (column[k] != INT_MAX && data[i][k] != INT_MAX)
                        data[i][k] -= column[k];

            int max_mark_x,
                max_mark_y,
                max_mark = -1;

            for (int i = 0; i < len; i++)
            {
                for (int k = 0; k < len; k++)
                {
                    if (data[i][k] == 0)
                    {
                        int min1 = INT_MAX;
                        int min2 = INT_MAX;

                        for (int j = 0; j < len; j++)
                            if (j != k)
                                min1 = qMin(min1, data[i][j]);

                        for (int j = 0; j < len; j++)
                            if (j != i)
                                min2 = qMin(min2, data[j][k]);

                        if (min1 == INT_MAX || min2 == INT_MAX || min1 + min2 > max_mark)
                        {
                            max_mark = min1 + min2;
                            max_mark_x = i;
                            max_mark_y = k;
                        }
                    }
                }
            }

            sum += _intermediary->AdjacencyMatrix[max_mark_x][max_mark_y];
            data[max_mark_y][max_mark_x] = INT_MAX;

            for (int i = 0; i < len; i++)
            {
                data[max_mark_x][i] = INT_MAX;
                data[i][max_mark_y] = INT_MAX;
            }

            result_arr_1.push_back(max_mark_x + 1);
            result_arr_2.push_back(max_mark_y + 1);

            flag = false;
            int counter = 0;

            for (int i = 0; i < len; i++)
                for (int k = 0; k < len; k++)
                    if (data[i][k] != INT_MAX)
                        flag = true;
        }

        valueRoutes.push_back(result_arr_1[0]);
        valueRoutes.push_back(result_arr_2[0]);

        int x = result_arr_2[0];

        result_arr_1.erase(result_arr_1.begin());
        result_arr_2.erase(result_arr_2.begin());

        while (result_arr_1.size() != 0)
        {
            steps++;
            if (steps > 1000)
            {
                throw 1;
            }

            for (int i = 0; i < result_arr_1.size(); i++)
            {
                if (result_arr_1[i] == x)
                {
                    valueRoutes.push_back(result_arr_2[i]);
                    x = result_arr_2[i];

                    result_arr_1.erase(result_arr_1.begin() + i);
                    result_arr_2.erase(result_arr_2.begin() + i);
                    break;
                }
            }
        }

        int length = sum;
        QVector<int> route = valueRoutes;

        ui->GotRouteLengthLineEdit->setText(QString::number(length));
        QString route_text = "";

        for (int x = 0; x < route.count(); x++)
            route_text += QString::number(route[x]) + " ";
        ui->GotRouteLineEdit->setText(route_text);

    }

    catch (...)
    {
        ui->GotRouteLengthLineEdit->setText("");
        ui->GotRouteLineEdit->setText("");
    }
}
