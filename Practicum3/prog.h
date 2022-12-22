#ifndef PROG_H
#define PROG_H

#include <QString>
#include <QFile>
using namespace std;
struct CZap_data {
    QString name;   //намименование товара
    int volum;    //объём сделки
    int year;       //год заключения сделки
    QString country; //страна
    QString direction; //направление (импорт или экспорт)
};

class CFile {
    QFile * file;
        //bool k1,k2,k3,k4,ff; // ключи поиска
    public:
        CZap_data zap;
        CFile();
        ~CFile();
        bool addZap(CZap_data azap); // добавление записи в файл
        bool readZap();
        int SearchZap(CZap_data azap);
        void Del(CZap_data azap);
        void task1(QString acountry);
        void task2();
        void task3(QString aname);
};

#endif // PROG_H
