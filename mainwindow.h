
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
//, because you're using QString, your mainwindow.h should have access to Qt's string class. QMainWindow generally brings in the necessary Qt infrastructure,

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    void numberClicked();//displays when 1to 9 clicked and stores in expression
    void operatorClicked();//displays when operators clicked and stores in expression
    void decimalClicked();//for decimals
    void updateDisplay();//because we are storing operators as *  and/ and not ×5÷3 which are strings

    QString expression;//Create a variable capable of storing the expression the user is building.

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H