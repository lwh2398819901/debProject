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

}


