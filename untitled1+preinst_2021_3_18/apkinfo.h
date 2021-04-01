#ifndef APKINFO_H
#define APKINFO_H

#include <QString>
#define DoNothing()

struct ApkInfo
{
    QString apkName;
    QString debName;
    QString debVersion;
    QString platform;
    QString appDesktop;
    QString appIcon;
    QString androidName;
    QString zhName;
    QString description;

    ApkInfo(){
        DoNothing()
    }

    ApkInfo(const ApkInfo &apk){
        apkName   =apk.apkName;
        debName   =apk.debName;
        debVersion=apk.debVersion;
        platform  =apk.platform;
        appDesktop=apk.appDesktop;
        appIcon   =apk.appIcon;
        androidName=apk.androidName;
        zhName     =apk.zhName;
        description=apk.description;
    }

    bool operator!=(const ApkInfo &apk)const{
        return  apkName     !=apk.apkName||
                debName     !=apk.debName||
                debVersion  !=apk.debVersion||
                platform    !=apk.platform||
                appDesktop  !=apk.appDesktop||
                appIcon     !=apk.appIcon||
                androidName !=apk.androidName||
                zhName      !=apk.zhName||
                description !=apk.description;
    }
    bool operator==(const ApkInfo &apk)const{
        return !(*this!=apk);
    }

};

#endif // APKINFO_H
