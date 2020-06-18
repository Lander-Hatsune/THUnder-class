#ifndef ODBCEXCEL_H
#define ODBCEXCEL_H

#include <QObject>
#include <QStringList>

#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>

#include <QTableView>

/**
 * @brief The OdbcExcel class
 * @author 郑泽桐
 */

class OdbcExcel
{
public:
    OdbcExcel();
    //将数据保存为excel
    bool static save(QString filePath,QStringList headers,QList<QStringList> data,QString comment="");
    //将QTableView保存为excel
    bool static saveFromTable(QString filePath,QTableView *tableView,QString comment="");
    //获取错误信息
    QString static getError(){return error;}
private:
    void static printError( QSqlError error);
    bool static insert(QSqlQuery& query, QString sheetName, QStringList slist);
    static QString error;
};


#endif // ODBCEXCEL_H
