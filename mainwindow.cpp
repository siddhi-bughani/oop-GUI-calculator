#include "mainwindow.h"
#include "ui_mainwindow.h"
//because we are using qpush button explicitly
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //connecting buttons to function numberclicked from 0 to 9
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


//connecting operators to operator clicked function

connect(ui->plus, &QPushButton::clicked,
        this, &MainWindow::operatorClicked);

connect(ui->minus, &QPushButton::clicked,
        this, &MainWindow::operatorClicked);

connect(ui->into, &QPushButton::clicked,
        this, &MainWindow::operatorClicked);

connect(ui->divide, &QPushButton::clicked,
        this, &MainWindow::operatorClicked);

//connecting decimal functions
connect(ui->dot, &QPushButton::clicked,
        this, &MainWindow::decimalClicked);
}







MainWindow::~MainWindow()
{
    delete ui;
}

//making buttons work from 0 to 9

//for the button clicked function in header

//
void MainWindow::numberClicked()
{
    QPushButton *button =
        qobject_cast<QPushButton *>(sender());

    if (!button)
        return;

    QString number = button->text();

    expression += number;

    updateDisplay();
}
//operator clicked function
void MainWindow::operatorClicked()
{
    QPushButton *button =
        qobject_cast<QPushButton *>(sender());

    if (!button)
        return;

    QString op = button->text();

    if (op == "×")
    {
        expression += "*";
    }
    else if (op == "÷")
    {
        expression += "/";
    }
    else
    {
        expression += op;
    }

    updateDisplay();
}

//decimal clicked function to handle the cases like 5.5.6

void MainWindow::decimalClicked()
{
    // Find the last number in the expression
    int lastOperator = -1;

    for (int i = expression.length() - 1; i >= 0; i--)
    {
        if (expression[i] == '+' ||
            expression[i] == '-' ||
            expression[i] == '*' ||
            expression[i] == '/')
        {
            lastOperator = i;
            break;
        }
    }

    QString currentNumber =
        expression.mid(lastOperator + 1);

    // Don't allow another decimal point
    // if the current number already has one
    if (currentNumber.contains('.'))
        return;

    // If starting a new number, add 0 first
    if (currentNumber.isEmpty())
    {
        expression += "0";
    }

    expression += ".";

    updateDisplay();
}


//update display
void MainWindow::updateDisplay()
{
    QString displayExpression = expression;

    displayExpression.replace("*", "×");
    displayExpression.replace("/", "÷");

    ui->display->setText(displayExpression);
}