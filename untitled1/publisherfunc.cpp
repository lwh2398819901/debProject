#include "publisherfunc.h"
#include <QFile>

namespace  publisherFunc{

bool createFile(const QString &filePath, const QString &text)
{
    QFile file(filePath);
    if(file.open(QIODevice::WriteOnly))
    {
        file.write(text.toLocal8Bit());
        file.close();
        return true;
    }
    return  false;
}

QString readFile(const QString &filePath)
{
    QString str;
    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly))
    {
        str=file.readAll();
        file.close();
        return str;
    }
    return QString();
}

QStringList getDirFileNames(const QString& dirPath,QDir::Filters flag,QStringList suffix)
{
    //获取加载文件夹内所有文件名
    QDir dir(dirPath);
    if (dir.exists())
    {
        dir.setFilter(flag);    //设置文件类型 文件夹 文件 软连接
        dir.setNameFilters(suffix);//设置文件后缀
        return dir.entryList();
    }
    return QStringList();
}

}


