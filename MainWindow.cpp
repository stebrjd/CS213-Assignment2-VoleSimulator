#include "MainWindow.h"

#include <QAbstractItemView>
#include <QFileDialog>
#include <QFileInfo>
#include <QFont>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QStringList>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include <QWidget>

#include <cstdint>

namespace {
bool parseHex(const QString& text, int maximum, int& value) {
    QString digits = text.trimmed();
    if (digits.startsWith(QStringLiteral("0x"), Qt::CaseInsensitive)) {
        digits.remove(0, 2);
    }
    if (digits.isEmpty()) {
        return false;
    }

    bool valid = false;
    const uint parsed = digits.toUInt(&valid, 16);
    if (!valid || parsed > static_cast<uint>(maximum)) {
        return false;
    }

    value = static_cast<int>(parsed);
    return true;
}

QString hexByte(int value) {
    return QStringLiteral("%1").arg(value, 2, 16, QLatin1Char('0')).toUpper();
}

QTableWidgetItem* readOnlyItem(const QString& text) {
    QTableWidgetItem* item = new QTableWidgetItem(text);
    item->setTextAlignment(Qt::AlignCenter);
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    return item;
}
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      programLoaded(false),
      filenameEdit(new QLineEdit),
      startAddressEdit(new QLineEdit(QStringLiteral("00"))),
      registerIndexEdit(new QLineEdit),
      registerValueEdit(new QLineEdit),
      memoryAddressEdit(new QLineEdit),
      memoryValueEdit(new QLineEdit),
      cpuStateLabel(new QLabel),
      screenOutputLabel(new QLabel),
      statusLabel(new QLabel),
      registerTable(new QTableWidget(2, 8)),
      memoryTable(new QTableWidget(16, 16)),
      runButton(new QPushButton(tr("Run all"))),
      stepButton(new QPushButton(tr("Step"))) {
    setWindowTitle(tr("Vole Machine Simulator"));
    resize(920, 760);

    QWidget* central = new QWidget(this);
    QVBoxLayout* page = new QVBoxLayout(central);

    QLabel* title = new QLabel(tr("Vole Machine Simulator"));
    QFont titleFont = title->font();
    titleFont.setPointSize(titleFont.pointSize() + 5);
    titleFont.setBold(true);
    title->setFont(titleFont);
    page->addWidget(title);

    QGroupBox* programGroup = new QGroupBox(tr("Program"));
    QGridLayout* programLayout = new QGridLayout(programGroup);
    filenameEdit->setPlaceholderText(tr("Select a program file"));
    QPushButton* browseButton = new QPushButton(tr("Browse..."));
    startAddressEdit->setMaxLength(4);
    startAddressEdit->setMaximumWidth(90);
    QPushButton* loadButton = new QPushButton(tr("Load program"));
    programLayout->addWidget(new QLabel(tr("File:")), 0, 0);
    programLayout->addWidget(filenameEdit, 0, 1);
    programLayout->addWidget(browseButton, 0, 2);
    programLayout->addWidget(new QLabel(tr("Start address (hex):")), 1, 0);
    programLayout->addWidget(startAddressEdit, 1, 1);
    programLayout->addWidget(loadButton, 1, 2);
    page->addWidget(programGroup);

    QHBoxLayout* controls = new QHBoxLayout;
    runButton->setEnabled(false);
    stepButton->setEnabled(false);
    QPushButton* resetButton = new QPushButton(tr("Reset"));
    controls->addWidget(runButton);
    controls->addWidget(stepButton);
    controls->addWidget(resetButton);
    controls->addStretch();
    page->addLayout(controls);

    QHBoxLayout* stateLayout = new QHBoxLayout;
    QGroupBox* cpuGroup = new QGroupBox(tr("CPU registers"));
    QVBoxLayout* cpuLayout = new QVBoxLayout(cpuGroup);
    cpuStateLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    cpuLayout->addWidget(cpuStateLabel);
    registerTable->setHorizontalHeaderLabels(
        QStringList() << "0" << "1" << "2" << "3" << "4" << "5" << "6" << "7");
    registerTable->setVerticalHeaderLabels(QStringList() << tr("R0-R7") << tr("R8-RF"));
    registerTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    registerTable->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    registerTable->setMaximumHeight(110);
    cpuLayout->addWidget(registerTable);
    stateLayout->addWidget(cpuGroup, 1);

    QGroupBox* editGroup = new QGroupBox(tr("Edit machine state"));
    QGridLayout* editLayout = new QGridLayout(editGroup);
    registerIndexEdit->setMaxLength(1);
    registerValueEdit->setMaxLength(4);
    memoryAddressEdit->setMaxLength(4);
    memoryValueEdit->setMaxLength(4);
    registerIndexEdit->setPlaceholderText(tr("0-F"));
    registerValueEdit->setPlaceholderText(tr("00-FF"));
    memoryAddressEdit->setPlaceholderText(tr("00-FF"));
    memoryValueEdit->setPlaceholderText(tr("00-FF"));
    QPushButton* setRegisterButton = new QPushButton(tr("Set register"));
    QPushButton* setMemoryButton = new QPushButton(tr("Set memory"));
    editLayout->addWidget(new QLabel(tr("Register:")), 0, 0);
    editLayout->addWidget(registerIndexEdit, 0, 1);
    editLayout->addWidget(registerValueEdit, 0, 2);
    editLayout->addWidget(setRegisterButton, 0, 3);
    editLayout->addWidget(new QLabel(tr("Memory address:")), 1, 0);
    editLayout->addWidget(memoryAddressEdit, 1, 1);
    editLayout->addWidget(memoryValueEdit, 1, 2);
    editLayout->addWidget(setMemoryButton, 1, 3);
    stateLayout->addWidget(editGroup, 1);
    page->addLayout(stateLayout);

    QGroupBox* memoryGroup = new QGroupBox(tr("Memory (hexadecimal)"));
    QVBoxLayout* memoryLayout = new QVBoxLayout(memoryGroup);
    memoryTable->setHorizontalHeaderLabels(
        QStringList() << "0" << "1" << "2" << "3" << "4" << "5" << "6" << "7"
                      << "8" << "9" << "A" << "B" << "C" << "D" << "E" << "F");
    QStringList memoryRows;
    for (int row = 0; row < 16; ++row) {
        memoryRows << hexByte(row * 16);
    }
    memoryTable->setVerticalHeaderLabels(memoryRows);
    memoryTable->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    memoryTable->verticalHeader()->setDefaultSectionSize(22);
    memoryTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    memoryTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    memoryTable->setSelectionMode(QAbstractItemView::NoSelection);
    memoryLayout->addWidget(memoryTable);
    page->addWidget(memoryGroup, 1);

    QGroupBox* outputGroup = new QGroupBox(tr("Screen output"));
    QVBoxLayout* outputLayout = new QVBoxLayout(outputGroup);
    screenOutputLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    screenOutputLabel->setWordWrap(true);
    outputLayout->addWidget(screenOutputLabel);
    page->addWidget(outputGroup);
    page->addWidget(statusLabel);
    setCentralWidget(central);

    connect(browseButton, &QPushButton::clicked, this, [this]() {
        const QString file = QFileDialog::getOpenFileName(
            this, tr("Open Vole program"), QString(),
            tr("Program files (*.txt *.asm *.vole);;All files (*)"));
        if (!file.isEmpty()) {
            filenameEdit->setText(file);
        }
    });
    connect(loadButton, &QPushButton::clicked, this, [this]() { loadProgram(); });
    connect(runButton, &QPushButton::clicked, this, [this]() { runProgram(); });
    connect(stepButton, &QPushButton::clicked, this, [this]() { stepProgram(); });
    connect(resetButton, &QPushButton::clicked, this, [this]() { resetMachine(); });
    connect(setRegisterButton, &QPushButton::clicked, this, [this]() { setRegister(); });
    connect(setMemoryButton, &QPushButton::clicked, this, [this]() { setMemory(); });

    refreshState();
    setStatus(tr("Choose a program file to get started."));
}

void MainWindow::loadProgram() {
    const QString filename = filenameEdit->text().trimmed();
    int startAddress = 0;
    if (filename.isEmpty()) {
        setStatus(tr("Select a program file first."), true);
        return;
    }
    if (!parseHex(startAddressEdit->text(), 0xFE, startAddress)
        || startAddress % 2 != 0) {
        setStatus(tr("Start address must be an even hexadecimal value from 00 to FE."), true);
        return;
    }

    machine.reset();
    programLoaded = machine.loadProgram(filename.toStdString(), startAddress);
    runButton->setEnabled(programLoaded);
    stepButton->setEnabled(programLoaded);
    refreshState();
    if (programLoaded) {
        setStatus(tr("Loaded %1 at address %2.")
                      .arg(QFileInfo(filename).fileName(), hexByte(startAddress)));
    } else {
        setStatus(tr("Could not load the program. Check the file and its instruction format."),
                  true);
    }
}

void MainWindow::runProgram() {
    if (!programLoaded) {
        setStatus(tr("Load a program before running it."), true);
        return;
    }
    machine.runAll();
    refreshState();
    setStatus(machine.getCPU().isHalted() ? tr("Execution halted.")
                                          : tr("Program finished."));
}

void MainWindow::stepProgram() {
    if (!programLoaded) {
        setStatus(tr("Load a program before stepping."), true);
        return;
    }
    const bool canContinue = machine.step();
    refreshState();
    setStatus(canContinue ? tr("Executed one instruction.")
                          : tr("Execution halted or finished."));
}

void MainWindow::resetMachine() {
    machine.reset();
    programLoaded = false;
    runButton->setEnabled(false);
    stepButton->setEnabled(false);
    refreshState();
    setStatus(tr("Machine reset. Load a program to run it."));
}

void MainWindow::setRegister() {
    int index = 0;
    int value = 0;
    if (!parseHex(registerIndexEdit->text(), 0x0F, index)
        || !parseHex(registerValueEdit->text(), 0xFF, value)) {
        setStatus(tr("Enter a register from 0 to F and a value from 00 to FF."),
                  true);
        return;
    }
    machine.setRegister(index, static_cast<uint8_t>(value));
    refreshState();
    setStatus(tr("Register %1 updated.").arg(hexByte(index).right(1)));
}

void MainWindow::setMemory() {
    int address = 0;
    int value = 0;
    if (!parseHex(memoryAddressEdit->text(), 0xFF, address)
        || !parseHex(memoryValueEdit->text(), 0xFF, value)) {
        setStatus(tr("Enter a memory address and value from 00 to FF."), true);
        return;
    }
    machine.setMemory(address, static_cast<uint8_t>(value));
    refreshState();
    setStatus(tr("Memory address %1 updated.").arg(hexByte(address)));
}

void MainWindow::refreshState() {
    const CPU& cpu = machine.getCPU();
    cpuStateLabel->setText(
        tr("PC: %1    IR: %2    Status: %3")
            .arg(hexByte(cpu.getPC()),
                 QStringLiteral("%1").arg(cpu.getIR(), 4, 16, QLatin1Char('0')).toUpper(),
                 cpu.isHalted() ? tr("Halted") : tr("Ready")));

    for (int index = 0; index < 16; ++index) {
        const int row = index / 8;
        const int column = index % 8;
        registerTable->setItem(
            row, column, readOnlyItem(hexByte(cpu.getRegister(index))));
    }

    const Memory& memory = machine.getMemory();
    for (int address = 0; address < 256; ++address) {
        const int row = address / 16;
        const int column = address % 16;
        memoryTable->setItem(
            row, column,
            readOnlyItem(hexByte(memory.read(static_cast<uint8_t>(address)))));
    }

    const QString output = QString::fromStdString(machine.getScreen().getOutput());
    screenOutputLabel->setText(output.isEmpty() ? tr("(No output yet)") : output);
}

void MainWindow::setStatus(const QString& message, bool isError) {
    statusLabel->setText(message);
    statusLabel->setStyleSheet(isError ? QStringLiteral("color: #b00020;")
                                        : QString());
}
