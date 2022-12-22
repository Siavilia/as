#include "mainwin.h"
#include "ui_mainwin.h"
#include "prog.cpp"
#include "prog.h"
#include <QStringList>
#include <QTableWidgetItem>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

MainWin::MainWin(QWidget *parent): QWidget(parent), ui(new Ui::MainWin)
{
    ui->setupUi(this);
    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table->setHorizontalHeaderLabels(QStringList() << "Наимнование"<< "Объём сделки"<<"Год"<<"Страна"<<"Нарпавление");
    if (Check()) {
        fillTable();
        fillBox(0, ui->chart_box);
    };
    //ui->cho_define->setDuplicatesEnabled(false);

    connect(ui->add_but, SIGNAL(clicked(bool)), this, SLOT(addRecord()));
    connect(ui->define_but, SIGNAL(clicked(bool)), this, SLOT(defCalc()));
    connect(ui->del_but, SIGNAL(clicked(bool)), this, SLOT(delRecord()));
    connect(ui->define_box, SIGNAL(currentIndexChanged(int)), this, SLOT(define()));
    connect(ui->chart_but, SIGNAL(clicked(bool)), this, SLOT(task4()));
    connect(ui->exit_but, SIGNAL(clicked(bool)), this, SLOT(close()));
};

bool MainWin::Check(){
    CFile baza;
    if (!baza.readZap())
    {    // если файл пустой , то создаем сообщение
        QMessageBox mesg(QMessageBox::Critical, "Нет данных", "База пуста", QMessageBox::Ok,0);
        mesg.exec(); // выводим сообщение
        return false;
    }
    return true;
};

MainWin::~MainWin()
{
    delete ui;
};

void MainWin::addRecord()
{
    CFile baza;
    CZap_data zap;
    zap.name=ui->name_ed->text();
    zap.volum=(ui->vol_ed->text()).toFloat();
    zap.year=(ui->year_ed->text()).toInt();
    zap.country=ui->country_ed->text();
    if (ui->imp_ed->isChecked()) {
        zap.direction="импорт";
    }
    else if (ui->exp_ed->isChecked()) {
        zap.direction="экспорт";
    }
    ui->name_ed->clear();
    ui->vol_ed->clear();
    ui->year_ed->clear();
    ui->country_ed->clear();
    baza.addZap(zap);
    addRow((ui->table->rowCount()), zap);
    fillBox(0, ui->chart_box);
};

void MainWin::addRow(int i, CZap_data azap)
{
    ui->table->setRowCount(i+1);
    ui->table->setItem(i,0, new QTableWidgetItem(azap.name));
    ui->table->setItem(i,1, new QTableWidgetItem((tr("%1").arg(azap.volum))));
    ui->table->setItem(i,2, new QTableWidgetItem(tr("%1").arg(azap.year)));
    ui->table->setItem(i,3, new QTableWidgetItem(azap.country));
    ui->table->setItem(i,4, new QTableWidgetItem(azap.direction));

};

void MainWin::fillTable()
{
    CFile baza;
        int i=0;
        while (baza.readZap()) {
           addRow(i,baza.zap);
           i++;
        }
};

void MainWin::delRecord()
{
    CFile baza;
    CZap_data zap;
    zap.name = (ui->table->item(ui->table->currentRow(), 0)->text());
    zap.volum = (ui->table->item(ui->table->currentRow(), 1)->text()).toFloat();
    zap.year = (ui->table->item(ui->table->currentRow(), 2)->text()).toInt();
    zap.country = (ui->table->item(ui->table->currentRow(), 3)->text());
    zap.direction = (ui->table->item(ui->table->currentRow(), 4)->text());
    baza.Del(zap);
    ui->table->removeRow(ui->table->currentRow());
}

void MainWin::fillBox(int j, QComboBox *box)
{
    box->clear();
    QStringList list;
    for (int i=0; i<ui->table->rowCount(); i++) {
        if (ui->table->item(i, 4)->text()=="импорт")
            list.append(ui->table->item(i, j)->text());
    };
    list.removeDuplicates();
    box->addItems(list);
    list.clear();
};

void MainWin::define()
{
    switch((ui->define_box->currentIndex())) {
    case 1: {
        ui->def_lab->clear();
        ui->cho_define->setEnabled(false);
        break;};
    case 0: {
        ui->cho_define->setEnabled(true);
        ui->def_lab->setText("Выберите страну");
        fillBox(3, ui->cho_define);
        break;};
    case 2: {
        ui->cho_define->setEnabled(true);
        ui->def_lab->setText("Выберите товар");
        fillBox(0, ui->cho_define);
        break;};
    }
}

void MainWin::defCalc(){
    ui->textEdit->clear();
    CFile baza;
    switch((ui->define_box->currentIndex())) {
    case 0: {
        task1(ui->cho_define->currentText());
        break;};
    case 1: {
        task2();
        break;};
    case 2: {
        task3(ui->cho_define->currentText());
        break;};
    }
}

void MainWin::task1(QString acountry)
{
   CFile baza;
   QStringList list;
   int sum = 0;
   while(baza.readZap()) {
    if ((baza.zap.country == acountry) && (baza.zap.direction == "импорт")) {
        sum += baza.zap.volum;
        list.append(baza.zap.name);
    }
   }
   list.removeDuplicates();
   QString str = list.join("");
   ui->textEdit->append(str);
   ui->textEdit->append("Суммарный объём сделок = "+tr("%1").arg(sum));
};

void MainWin::task2()
{
    CFile baza;
    int max = 0;
    QString country;
    while(baza.readZap()) {
        if ((baza.zap.volum > max) && (baza.zap.direction == "экспорт")) {
            max = baza.zap.volum;
            country = baza.zap.country;
        }
    }
    ui->textEdit->append(country);
};

void MainWin::task3(QString aname) {
    CFile baza;
    while(baza.readZap()) {
     if ((baza.zap.name == aname) && (baza.zap.direction == "импорт")) {
         ui->textEdit->append(baza.zap.country + " - " + tr("%1").arg(baza.zap.volum) );
     };
    };
}
bool prefLessThan(const QPoint &p1, const QPoint &p2)
{
    return p1.x()< p2.x();
}
void MainWin::task4()
{
    QVector<double> x, y;
    QString aname = ui->chart_box->currentText();
    CFile baza;
    while(baza.readZap()) {
     if ((baza.zap.name == aname) && (baza.zap.direction == "экспорт"))
     {
        x.push_back(baza.zap.year);
        y.push_back(baza.zap.volum);
     }
    }
    ui->chart->xAxis->setRange(x.at(0), x.at(x.size()-1));
    ui->chart->yAxis->setRange(y.at(0), y.at(x.size()-1));
    ui->chart->addGraph()->setData(x, y);
    ui->chart->replot();
    x.clear();
    y.clear();
};
