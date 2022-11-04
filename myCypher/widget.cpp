#include "widget.h"
//#include "./ui_widget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFile>
#include <QMessageBox>
#include <QDir>
#include <QFileDialog>
#include "adgfvxalgo.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
//    , ui(new Ui::Widget)
{
//    ui->setupUi(this);


    QVBoxLayout * layout = new QVBoxLayout(this);
    QHBoxLayout * inputLayout = new QHBoxLayout;
    QHBoxLayout * outputLayout = new QHBoxLayout;
    QHBoxLayout * buttons = new QHBoxLayout;
    QHBoxLayout * cargoLayout = new QHBoxLayout;

    layout->addLayout(inputLayout);
    layout->addLayout(outputLayout);
    layout->addLayout(cargoLayout);
    layout->addLayout(buttons);

    QLabel * inputLabel = new QLabel("input:");
    QLineEdit * inputEdit = new QLineEdit;
    QLabel * outputLabel = new QLabel("output:");
    QLineEdit * outputEdit = new QLineEdit;
    QLabel * cargoLabel = new QLabel("key:");
    QLineEdit * cargoEdit = new QLineEdit("CARGO");
    QPushButton * enbutton = new QPushButton("Encrypt");
    QPushButton * debutton = new QPushButton("Decrypt");
    QPushButton * alphabet = new QPushButton("Change alphabet");

    inputEdit->setFixedWidth(200);
    outputEdit->setFixedWidth(200);
    cargoEdit->setFixedWidth(200);

    inputLayout->addWidget(inputLabel);
    inputLayout->addWidget(inputEdit);
    outputLayout->addWidget(outputLabel);
    outputLayout->addWidget(outputEdit);
    cargoLayout->addWidget(cargoLabel);
    cargoLayout->addWidget(cargoEdit);
    buttons->addWidget(enbutton);
    buttons->addWidget(debutton);
    buttons->addWidget(alphabet);

    ADGFVXalgo * ad = new ADGFVXalgo(cargoEdit->text().toStdString());

    connect(enbutton, &QPushButton::clicked, outputEdit, [=]() {
        if(!inputEdit->text().isEmpty()) {
            if(!cargoEdit->text().isEmpty()) {
                cargoEdit->setText(cargoEdit->text().toUpper());
                ad->setCargo(cargoEdit->text().toStdString());
            }
            else {
                cargoEdit->setText("CARGO");
                ad->setCargo(cargoEdit->text().toStdString());
            }
            inputEdit->setText(inputEdit->text().toLower());
            ad->setMessage(inputEdit->text().toStdString());
            ad->encrypt();
            outputEdit->setText(QString::fromStdString(ad->getCypher()));
        }
    });
    connect(debutton, &QPushButton::clicked, outputEdit, [=]() {
        if(!inputEdit->text().isEmpty()) {
            if(!cargoEdit->text().isEmpty()) {
                cargoEdit->setText(cargoEdit->text().toUpper());
                ad->setCargo(cargoEdit->text().toStdString());
            }
            else {
                cargoEdit->setText("CARGO");
                ad->setCargo(cargoEdit->text().toStdString());
            }
            ad->setCypher(inputEdit->text().toStdString());
            ad->decrypt();
            outputEdit->setText(QString::fromStdString(ad->getMessage()));
        }
    });

    //connect(alphabet, &QPushButton::clicked, this, &Widget::open);

    connect(alphabet, &QPushButton::clicked, this, [=](){
        open();
        ad->setADGFVXinput(this->ADGFVXinput.toStdString());
    });
}

void Widget::open()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if(!fileName.isEmpty())
        loadAlphabet(fileName);
}

void Widget::loadAlphabet(const QString fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("MyCypher"), tr("Cannot read file %1:\n%2.")
                .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }
    QTextStream in(&file);
    this->ADGFVXinput = in.readAll();
}

Widget::~Widget()
{
//    delete ui;
}

