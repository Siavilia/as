#ifndef MAINWIN_H
#define MAINWIN_H

#include <QWidget>
#include <QTextCodec>
#include <QComboBox>
#include <QtAlgorithms>
#include "qcustomplot.h"
#include "prog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWin; }
QT_END_NAMESPACE

class MainWin : public QWidget
{
    Q_OBJECT

public:
    MainWin(QWidget *parent = nullptr);
    ~MainWin();

private:
    Ui::MainWin *ui;
    QTextCodec *codec;

public slots:
    void addRecord();
    void delRecord();
    void addRow(int i, CZap_data azap);
    void define();
    bool Check();
    void fillTable();
    void fillBox(int j, QComboBox *box);
    void defCalc();
    void task1(QString acountry);
    void task2();
    void task3(QString aname);
    void task4();
};
#endif // MAINWIN_H
