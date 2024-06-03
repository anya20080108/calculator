#include "poland.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QPainterPath>
#include <QPainter>
#include <math.h>
#include <QColor>
#include <QPen>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(800, 600);
    button = new QPushButton(this);
    button->setGeometry(width() - 5 - 100, 5, 100, 20);
    button->setText("push me");
    connect(button, SIGNAL(clicked()), this, SLOT(myClicked()));
    ui->label_2->setGeometry(width() - 5 - 100, 65, 100, 20);
    ui->label_2->setText("xmin");

    ui->label_3->setGeometry(width() - 5 - 100, 105, 100, 20);
    ui->label_3->setText("xmax");

    ui->label_4->setGeometry(width() - 5 - 100, 25, 100, 20);
    ui->label_4->setText("f(x)");

    ui->label_5->setGeometry(width() - 5 - 100, 145, 100, 20);
    ui->label_5->setText("ymin");

    ui->label_6->setGeometry(width() - 5 - 100, 185, 100, 20);
    ui->label_6->setText("ymax");

    ui->lineEdit->setGeometry(width() - 5 - 100, 45, 100, 20);
    ui->lineEdit_2->setGeometry(width() - 5 - 100, 85, 100, 20);
    ui->lineEdit_3->setGeometry(width() - 5 - 100, 125, 100, 20);
    ui->lineEdit_4->setGeometry(width() - 5 - 100, 165, 100, 20);
    ui->lineEdit_5->setGeometry(width() - 5 - 100, 205, 100, 20);
}


void MainWindow::myClicked(){
    ui->label->setGeometry(5, 5, width() - 5 -5 -100 -5, height() -5 - 5);
    QPixmap pm(width() - 5 -5 -100 -5, height() -5 - 5);
    pm.fill(QColor(188, 143, 143));

    QPainter painter;
    painter.begin(&pm);
    ui->label->setPixmap(pm);


    double pi = 3.141592;
    double xmin = (ui->lineEdit_2->text()).toDouble(), xmax = (ui->lineEdit_3->text()).toDouble();
    double ymin = (ui->lineEdit_4->text()).toDouble(), ymax = (ui->lineEdit_5->text()).toDouble();
    int xgmin = 0, xgmax = pm.width();
    int ygmin = 0, ygmax = pm.height();

    double step = ((xmax - xmin) / (xgmax - xgmin)) * 0.1;
    double kx = (xgmax - xgmin) / (xmax - xmin);
    double ky = (ygmin - ygmax) / (ymax - ymin);
    double x = xmin, y = 0;

    QPainterPath path;
    double long ans = 0;
    QString s = ui->lineEdit->text();
    for (int i = 0; i < s.size(); i++) {
        s.replace('x', '('+QString::number(x)+')');
    }
    string l = s.toStdString();
    bool q = calculate(l, ans);
    if (q == true) {
        y = ans;
        double xg = xgmin + kx * (x - xmin);
        double yg = ygmin + ky * (y - ymax);
        path.moveTo(xg, yg);
    }
    painter.setPen(QPen(Qt::white, 1, Qt::SolidLine));
    painter.drawLine(xgmin - kx * xmin, ygmin, xgmin - kx * xmin, ygmax);
    painter.drawLine(xgmin, ygmin - ky * ymax, xgmax, ygmin - ky * ymax);

    for (double x = xmin; x < xmax; x+=step) {
        s = ui->lineEdit->text();
        for (double i = 0; i < s.size(); i++) {
            s.replace('x', '('+QString::number(x)+')');
        }
        l = s.toStdString();
        q = calculate(l, ans);

        y = ans;
        double xg = xgmin + kx * (x - xmin);
        double yg = ygmin + ky * (y - ymax);
        if (q == true && ymin < y && ymax > y) {
            path.lineTo(xg, yg);
        }
        else {
            path.moveTo(xg, yg);
        }


    }
    painter.setPen(QPen(QColor(0, 0, 0), 1, Qt::SolidLine));
    painter.drawPath(path);
    ui->label->setPixmap(pm);
}


MainWindow::~MainWindow()
{
    delete ui;
}
