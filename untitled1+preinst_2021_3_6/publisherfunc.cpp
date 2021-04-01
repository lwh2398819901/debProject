#include "publisherfunc.h"
#include <QFile>
#include <QImage>

namespace  publisherFunc{

bool createFile(const QString &filePath, const QString &text){
    QFile file(filePath);
    if(file.open(QIODevice::WriteOnly)){
        file.write(text.toLocal8Bit());
        file.close();
        return true;
    }
    return  false;
}

QString readFile(const QString &filePath){
    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly)){
        QString str=file.readAll();
        file.close();
        return str;
    }
    return QString();
}

QStringList getDirFileNames(const QString& dirPath,QDir::Filters flag,QStringList suffix){
    //获取加载文件夹内所有文件名
    QDir dir(dirPath);
    if (dir.exists()){
        dir.setFilter(flag);    //设置文件类型 文件夹 文件 软连接
        dir.setNameFilters(suffix);//设置文件后缀
        return dir.entryList();
    }
    return QStringList();
}

QString getImagePixel(QString imagePath){
    QImage image(imagePath);
    return  QString("%1x%2").arg(image.width()).arg(image.height());
}

}


