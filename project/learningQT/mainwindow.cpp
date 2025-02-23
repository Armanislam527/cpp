#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLineEdit>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    inputLayout = qobject_cast<QVBoxLayout *>(ui->scrollAreaWidgetContents->layout());
    connect(ui->spinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::updateInputBoxes);

    // Set initial boxes
    updateInputBoxes(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateInputBoxes(int value)
{
    clearLayout(inputLayout);

    for (int i = 0; i < value; ++i)
    {
        QLineEdit *input = new QLineEdit(this);
        input->setPlaceholderText(QString("Input %1").arg(i + 1));
        input->setValidator(new QIntValidator(1, 8, this));
        inputLayout->addWidget(input);
    }
}

void MainWindow::clearLayout(QLayout *layout)
{
    QLayoutItem *item;
    while ((item = layout->takeAt(0)))
    {
        if (item->widget())
        {
            delete item->widget();
        }
        delete item;
    }
}