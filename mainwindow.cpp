#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(0));
}

void MainWindow::updateToMiddles(void)
{
    std::vector<Point> points;
    for (auto &line : this->_lines)
        points.push_back(line.getMiddle());
    this->_lines.clear();
    pointsToLines(points);

    update();
}

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    for (auto &line : this->_lines)
        line.draw(painter, Qt::blue);
}

void MainWindow::pointsToLines(std::vector<Point> &points)
{
    for (size_t i = 0; i < points.size(); i++)
        if (i != points.size() - 1)
            this->_lines.push_back(Line(points[i], points[i+1]));
    this->_lines.push_back(Line(points[0], points[points.size() - 1]));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    disconnect(&this->_timer, SIGNAL(timeout()), this, SLOT(updateToMiddles()));
    this->_lines.clear();
    std::vector<Point> points;
    for (int i = 0; i < this->ui->pointsEdit->text().toInt(); i++)
        points.push_back(Point(rand() % 600, rand() % 600));
    pointsToLines(points);

    connect(&this->_timer, SIGNAL(timeout()), this, SLOT(updateToMiddles()));
    this->_timer.start(this->ui->delayEdit->text().toInt());
}

