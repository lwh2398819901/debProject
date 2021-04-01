#ifndef PUBLISHERFUNC_H
#define PUBLISHERFUNC_H

#include <QString>
#include <QDir>
namespace publisherFunc
{
    bool    createFile(const QString &filePath,const QString &text);
    QString readFile(const QString &filePath);
    QString getImagePixel(QString imagePath);
    QStringList getDirFileNames(const QString& dirPath,QDir::Filters flag=QDir::Files,QStringList suffix=QStringList());
};

#endif // PUBLISHERFUNC_H
