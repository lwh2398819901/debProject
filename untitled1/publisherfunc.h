#ifndef PUBLISHERFUNC_H
#define PUBLISHERFUNC_H

#include <QString>

namespace publisherFunc
{
    bool createFile(const QString &filePath,const QString &text);
    QString readFile(const QString &filePath);
};


struct ApkInfo
{
    QString apkName;
    QString debName;
    QString debVersion;
    QString platform;
    QString appDesktop;
    QString appIcon;
    QString androidName;

};

#endif // PUBLISHERFUNC_H
