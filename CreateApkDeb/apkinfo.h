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
    bool isOld{false};

    ApkInfo() = default;
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
        isOld      =apk.isOld;
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

    QString toString(){
        QString str = QString("apkName:%1\n"
                              "debName:%2\n"
                              "debVersion:%3\n"
                              "platform:%4\n"
                              "appDesktop:%5\n"
                              "appIcon:%6\n"
                              "androidName:%7\n"
                              "zhName:%8\n"
                              "description:%9\n").arg(apkName).arg(debName).arg(debVersion)
                                            .arg(platform).arg(appDesktop).arg(appIcon)
                                            .arg(androidName).arg(zhName).arg(description);

        return str;
    }

};

#endif // APKINFO_H
