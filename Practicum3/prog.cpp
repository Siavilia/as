#include <QFile>
#include <QMessageBox>
#include "prog.h"
#include "mainwin.h"
CFile::CFile() {
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
       file = new QFile ("data.txt"); // создаем объект-файл
       if(!file->exists()) // если файл не существует
       {
           QMessageBox mesg(QMessageBox::Critical, codec->toUnicode("Файл не найден"), codec->toUnicode("Файл book.txt создан"), QMessageBox::Ok,0);
           mesg.exec();
       }
       file->open(QFile::ReadWrite);
};

CFile::~CFile() {
    file->close();
    delete file;
};

// добавление записи в файл
bool CFile::addZap(CZap_data azap) {
    file->seek(file->size());
    QDataStream out(file);
    out<<azap.name<<azap.volum<<azap.year<<azap.country<<azap.direction; // выводим данные в файл
    return true;
};

//получение записи из файла
bool CFile::readZap() {
    QDataStream in(file);
    if (in.atEnd()) return false;
    else {
            in>>zap.name>>zap.volum>>zap.year>>zap.country>>zap.direction; // получаем данные
            return true;
         };
};

int CFile::SearchZap(CZap_data azap) {
    CFile baza;
    int num = -1;
    while (baza.readZap()) {
        if ((zap.name==azap.name) && (zap.country==azap.country) && (zap.direction==azap.direction) &&
         (zap.volum==azap.volum) && (zap.year==azap.year))
        {
            return (file->pos());
        }
    }
    return num;
};

void CFile::Del(CZap_data ourzap){
    QDataStream in(file);
    file->seek(file->size());
    CZap_data dop;
    in>>dop.name>>dop.volum>>dop.year>>dop.country>>dop.direction;

    int num = SearchZap(ourzap);
    file->seek(num);
    QDataStream out(file);
    out<<dop.name<<dop.volum<<dop.year<<dop.country<<dop.direction;
    file->resize(file->size()-1);
};
