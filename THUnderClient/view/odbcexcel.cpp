#include "odbcexcel.h"
#include <QDebug>

OdbcExcel::OdbcExcel()
{
}
QString OdbcExcel::error;

bool OdbcExcel::save(QString filePath, QStringList headers, QList<QStringList> data,QString comment)
{
    QString sheetName = "Sheet1";

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC","excelexport");
    if( !db.isValid())
    {
        error="driver error";
        return false;   //! type error
    }

    QString dsn = "DRIVER={Microsoft Excel Driver (*.xls)};"
            "DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\""+filePath+"\";DBQ="+filePath;
    db.setDatabaseName( dsn);

    // open connection
    if( !db.open())
    {
        error="unable to open database";
        return false;  //! db error
    }

    QSqlQuery query(db);
    QString sql;

    // drop the table if it's already exists
    sql = QString("DROP TABLE [%1]").arg(sheetName);
    query.exec( sql);
    //create the table (sheet in Excel file)
    sql = QString("CREATE TABLE [%1] (").arg(sheetName);
    foreach (QString name, headers) {
        sql +=QString("[%1] varchar(200)").arg(name);
        if(name!=headers.last())
            sql +=",";
    }
    sql += ")";
    query.prepare( sql);
    if( !query.exec()) {
        OdbcExcel::printError( query.lastError());
        db.close();
        return false;
    }
    foreach (QStringList slist, data) {
        insert(query,sheetName,slist);
    }

    if(!comment.isEmpty())
    {
        QStringList slist;
        slist<<comment;
        for(int i=0,n=headers.size()-1;i<n;i++)
        {
            slist<<"";
        }
        insert(query,sheetName,slist);
    }

    db.close();
    return true;
}

bool OdbcExcel::saveFromTable(QString filePath,QTableView *tableView, QString comment)
{
    QAbstractItemModel* model=tableView->model();
    const int column=model->columnCount();
    const int row=model->rowCount();

    //header
    QStringList headers;
    for(int i=0;i<column;i++)
    {
        //隐藏列
        if(tableView->isColumnHidden(i))
            continue;
        headers<<model->headerData(i,Qt::Horizontal).toString();
    }

    //data
    QStringList list;
    QList<QStringList> data;
    for(int i=0;i<row;i++)
    {
        if(model->index(i,0).data().isNull())
            continue;
        list.clear();
        for(int j=0;j<column;j++){
            //隐藏列
            if(tableView->isColumnHidden(j))
                continue;
            list<<model->index(i,j).data().toString();
        }
        data<<list;
    }
    return OdbcExcel::save(filePath,headers,data,comment);
}


void OdbcExcel::printError(QSqlError error)
{
    QString sqlerr = error.text();
    error=sqlerr;
    qCritical()<<sqlerr;
}

bool OdbcExcel::insert(QSqlQuery &query, QString sheetName, QStringList slist)
{
    QString sSql = QString("INSERT INTO [%1] VALUES(").arg( sheetName);
    for(int i=0,n=slist.size();i<n;i++)
    {
        sSql+=QString(":%1").arg(i);
        if(i!=n-1)
            sSql+=",";
        else
            sSql+=")";
    }
    query.prepare( sSql);
    for(int i=0,n=slist.size();i<n;i++)
    {
        query.bindValue(QString(":%1").arg(i),slist.at(i));
    }
    if( !query.exec()) {
        printError( query.lastError());
        return false;
    }
    return true;
}

