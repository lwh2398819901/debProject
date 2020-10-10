#ifndef PUBLISHERFUNC_H
#define PUBLISHERFUNC_H

#include <QString>
#include <QDir>
namespace publisherFunc
{
    bool createFile(const QString &filePath,const QString &text);
    QString readFile(const QString &filePath);
    QStringList getDirFileNames(const QString& dirPath,QDir::Filters flag=QDir::Files,QStringList suffix=QStringList());
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

    ApkInfo()
    {

    }

    ApkInfo(const ApkInfo &apk)
    {
        apkName   =apk.apkName;
        debName   =apk.debName;
        debVersion=apk.debVersion;
        platform  =apk.platform;
        appDesktop=apk.appDesktop;
        appIcon   =apk.appIcon;
        androidName=apk.androidName;
    }

    bool operator!=(const ApkInfo &apk)const
    {
        return  apkName   !=apk.apkName||
                debName   !=apk.debName||
                debVersion!=apk.debVersion||
                platform  !=apk.platform||
                appDesktop!=apk.appDesktop||
                appIcon   !=apk.appIcon||
                androidName!=apk.androidName;
    }
    bool operator==(const ApkInfo &apk)const
    {
        return !(*this!=apk);
    }

};

#endif // PUBLISHERFUNC_H
