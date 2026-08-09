#include "mainwindow.h"
#include "ui_mainwindow.h"
//because we are using qpush button explicitly
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //connecting buttons to function from 0 to 9
    connect(ui->btn0, &QPushButton::clicked,
            this, &MainWindow::numberClicked);

    connect(ui->btn1, &QPushButton::clicked,
            this, &MainWindow::numberClicked);
    connect(ui->btn2, &QPushButton::clicked,
            this, &MainWindow::numberClicked);

    connect(ui->btn3, &QPushButton::clicked,
            this, &MainWindow::numberClicked);

    connect(ui->btn4, &QPushButton::clicked,
            this, &MainWindow::numberClicked);

    connect(ui->btn5, &QPushButton::clicked,
            this, &MainWindow::numberClicked);

    connect(ui->btn6, &QPushButton::clicked,
            this, &MainWindow::numberClicked);

    connect(ui->btn7, &QPushButton::clicked,
            this, &MainWindow::numberClicked);

    connect(ui->btn8, &QPushButton::clicked,
            this, &MainWindow::numberClicked);

    connect(ui->btn9, &QPushButton::clicked,
            this, &MainWindow::numberClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//making buttons work from 0 to 9

//for the button clicked function in header
void MainWindow::numberClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());

    QString number = button->text();
    QString current = ui->display->text();

    if (current == "0")
    {
        ui->display->setText(number);
    }
    else
    {
        ui->display->setText(current + number);
    }
}

