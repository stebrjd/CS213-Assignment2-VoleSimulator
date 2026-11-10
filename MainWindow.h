#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "Machine.h"

#include <QMainWindow>
#include <QString>

class QLabel;
class QLineEdit;
class QPushButton;
class QTableWidget;

class MainWindow : public QMainWindow {
public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    void loadProgram();
    void runProgram();
    void stepProgram();
    void resetMachine();
    void setRegister();
    void setMemory();
    void refreshState();
    void setStatus(const QString& message, bool isError = false);

    Machine machine;
    bool programLoaded;
    QLineEdit* filenameEdit;
    QLineEdit* startAddressEdit;
    QLineEdit* registerIndexEdit;
    QLineEdit* registerValueEdit;
    QLineEdit* memoryAddressEdit;
    QLineEdit* memoryValueEdit;
    QLabel* cpuStateLabel;
    QLabel* screenOutputLabel;
    QLabel* statusLabel;
    QTableWidget* registerTable;
    QTableWidget* memoryTable;
    QPushButton* runButton;
    QPushButton* stepButton;
};

#endif
