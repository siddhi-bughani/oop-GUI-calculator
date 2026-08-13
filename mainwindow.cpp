#include "mainwindow.h"
#include "ui_mainwindow.h"
//because we are using qpush button explicitly
#include <QPushButton>
#include <QStringList>
#include <QVector>

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


//connecting equal to sign with calculate result
connect(ui->equal, &QPushButton::clicked,
        this, &MainWindow::calculateResult);

// connecting AC button
connect(ui->ac, &QPushButton::clicked,
        this, &MainWindow::clearAll);
// connecting percentage button
connect(ui->percent, &QPushButton::clicked,
        this, &MainWindow::percentClicked);
// connecting backspace button
connect(ui->back, &QPushButton::clicked,
        this, &MainWindow::backspaceClicked);
//connecting square
connect(ui->sqr, &QPushButton::clicked,
        this, &MainWindow::squareClicked);
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

    // If answer is displayed, start a new number
    if (resultDisplayed)
    {
        expression.clear();
        resultDisplayed = false;
    }

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

    // Don't allow an operator as the first input
    if (expression.isEmpty())
        return;
    // Answer can be used for the next calculation


      resultDisplayed = false;

    // Don't allow two operators together
    QChar lastChar = expression[expression.length() - 1];

    if (lastChar == '+' ||
        lastChar == '-' ||
        lastChar == '*' ||
        lastChar == '/')
    {
        // Replace the previous operator
        if (op == "×")
        {
            expression[expression.length() - 1] = '*';
        }
        else if (op == "÷")
        {
            expression[expression.length() - 1] = '/';
        }
        else
        {
            expression[expression.length() - 1] = op[0];
        }
    }
    else
    {
        // Add operator normally
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
    if (expression.isEmpty())
    {
        ui->display->setText("0");
        return;
    }

    QString displayExpression = expression;

    displayExpression.replace("*", "×");
    displayExpression.replace("/", "÷");

    ui->display->setText(displayExpression);
}

//calculate result
void MainWindow::calculateResult()
{

        // Nothing to calculate
        if (expression.isEmpty())
            return;

        // Don't calculate again if answer is already displayed
        if (resultDisplayed)
            return;

        // Don't calculate if the expression ends with an operator
        QChar lastChar = expression[expression.length() - 1];

        if (lastChar == '+' ||
            lastChar == '-' ||
            lastChar == '*' ||
            lastChar == '/')
        {
            return;
        }



    QStringList numbers;
    QStringList operators;

    QString currentNumber;

    // Step 1: Separate numbers and operators
    for (int i = 0; i < expression.length(); i++)
    {
        QChar ch = expression[i];

        if (ch.isDigit() || ch == '.')
        {
            currentNumber += ch;
        }
        else if (ch == '+' || ch == '-' ||
                 ch == '*' || ch == '/')
        {
            numbers.append(currentNumber);
            currentNumber.clear();

            operators.append(ch);
        }
    }

    // Add the final number
    if (!currentNumber.isEmpty())
    {
        numbers.append(currentNumber);
    }

    // Step 2: Convert number strings into doubles
    QVector<double> values;

    for (const QString &number : numbers)
    {
        values.append(number.toDouble());
    }

    // Step 3: Handle multiplication and division first
    for (int i = 0; i < operators.size(); )
    {
        if (operators[i] == '*' || operators[i] == '/')
        {
            double left = values[i];
            double right = values[i + 1];

            double result;

            if (operators[i] == '*')
            {
                result = left * right;
            }
            else
            {
                if (right == 0)
                {
                    ui->display->setText("Error");
                    expression.clear();
                    return;
                }

                result = left / right;
            }

            values[i] = result;
            values.remove(i + 1);
            operators.remove(i);
        }
        else
        {
            i++;
        }
    }

    // Step 4: Handle addition and subtraction
    double result = values[0];

    for (int i = 0; i < operators.size(); i++)
    {
        if (operators[i] == '+')
        {
            result += values[i + 1];
        }
        else if (operators[i] == '-')
        {
            result -= values[i + 1];
        }
    }

    // Step 5: Store and display the answer
    expression = QString::number(result);
    resultDisplayed = true;
    updateDisplay();
}
//clear all

void MainWindow::clearAll()
{
    expression.clear();      // erase stored expression
    updateDisplay();         // refresh the display
}


// percentage button
void MainWindow::percentClicked()
{
    if (expression.isEmpty())
        return;

    // Find the beginning of the current number
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

    // Get the current number
    QString currentNumber =
        expression.mid(lastOperator + 1);

    if (currentNumber.isEmpty())
        return;

    // Convert it to percentage
    double number = currentNumber.toDouble();
    number = number / 100.0;

    // Replace current number with percentage value
    expression = expression.left(lastOperator + 1)
                 + QString::number(number);

    updateDisplay();
}
// Backspace button
void MainWindow::backspaceClicked()
{
    if (expression.isEmpty())
        return;

    // Remove the last character
    expression.chop(1);

    // Update the display
    updateDisplay();
}
///square clicked

void MainWindow::squareClicked()
{
    if (expression.isEmpty())
        return;

    // Find the beginning of the current number
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

    // Get the current number
    QString currentNumber =
        expression.mid(lastOperator + 1);

    if (currentNumber.isEmpty())
        return;

    double number = currentNumber.toDouble();

    // Square the number
    double result = number * number;

    // Replace current number with its square
    expression = expression.left(lastOperator + 1)
                 + QString::number(result);

    updateDisplay();
}



//keyboard functions
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_0:
        ui->btn0->click();
        break;

    case Qt::Key_1:
        ui->btn1->click();
        break;

    case Qt::Key_2:
        ui->btn2->click();
        break;

    case Qt::Key_3:
        ui->btn3->click();
        break;

    case Qt::Key_4:
        ui->btn4->click();
        break;

    case Qt::Key_5:
        ui->btn5->click();
        break;

    case Qt::Key_6:
        ui->btn6->click();
        break;

    case Qt::Key_7:
        ui->btn7->click();
        break;

    case Qt::Key_8:
        ui->btn8->click();
        break;

    case Qt::Key_9:
        ui->btn9->click();
        break;

    case Qt::Key_Plus:
        ui->plus->click();
        break;

    case Qt::Key_Minus:
        ui->minus->click();
        break;

    case Qt::Key_Asterisk:
        ui->into->click();
        break;

    case Qt::Key_Slash:
        ui->divide->click();
        break;

    case Qt::Key_Period:
        ui->dot->click();
        break;

    case Qt::Key_Enter:
    case Qt::Key_Return:
        ui->equal->click();
        break;

    case Qt::Key_Backspace:
        ui->back->click();
        break;

    case Qt::Key_Escape:
        ui->ac->click();
        break;

    default:
        QMainWindow::keyPressEvent(event);
        break;
    }
}





































