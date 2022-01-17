#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QThread>
#include <QDebug>
#include <QPaintEvent>
#include <QTime>
#include <QTimer>
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Point
{
    public:
        Point(int x, int y) : _x(x), _y(y) {}
        double getX(void) { return this->_x; }
        double   getY(void) { return this->_y; }
    private:
        double _x;
        double _y;
};

class Line
{
    public:
        Line(Point a, Point b) : _a(a), _b(b) { }
        void draw(QPainter &painter, QColor color) { painter.setPen(color); painter.drawLine(this->_a.getX(), this->_a.getY(), this->_b.getX(), this->_b.getY()); }
        Point getMiddle(void) { return Point((this->_a.getX() + this->_b.getX()) / 2.0, (this->_a.getY() + this->_b.getY()) / 2.0); }
    private:
        Point _a;
        Point _b;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public slots:
        void updateToMiddles(void);

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

private slots:
        void on_pushButton_clicked();

private:
        void paintEvent(QPaintEvent *event);
        void pointsToLines(std::vector<Point> &points);
        QTimer _timer;
        std::vector<Line> _lines;
        Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
