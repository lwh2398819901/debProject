#include "publisherfunc.h"
#include <QDir>
#include <QFile>
#include <QTime>
#include <QImage>
#include <QApplication>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>

namespace  publisherFunc{

bool createFile(const QString &filePath, const QString &text,QIODevice::OpenMode model)
{
    QFile file(filePath);
    if (file.open(model)){
        file.write(text.toLocal8Bit());
        file.close();
        return true;
    }
    return  false;
}

QString readFile(const QString &filePath)
{
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) {
        QString str=file.readAll();
        file.close();
        return str;
    }
    return QString();
}

QStringList getDirFileNames(const QString& dirPath,const QDir::Filters &flag,const QStringList &suffix)
{
    QDir dir(dirPath);              //获取文件夹内所有文件名
    if (dir.exists()) {
        dir.setFilter(flag);        //设置文件类型
        dir.setNameFilters(suffix); //设置文件后缀
        return dir.entryList();
    }
    return QStringList();
}

QString getImagePixel(const QString &imagePath)
{
    QImage image(imagePath);
    return  QString("%1x%2").arg(image.width()).arg(image.height());
}


void pause(const unsigned int &msec)
{
    if (msec!=0) {
        QTime dieTime = QTime::currentTime().addMSecs(static_cast<int>(msec));
        while ( QTime::currentTime() < dieTime ) {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
    }
}

QPair<int,QString> startPopen(const QString &cmd,const QString &model)
{
    QString res{};
    char buf[1024]{};
    FILE * p_file = popen(cmd.toLocal8Bit(), model.toLocal8Bit());
    if (p_file) {
        while (fgets(buf, 1024, p_file) != nullptr) {
           res += QString(buf);
           memset(buf,0,1024);
        }
    }
    int i = pclose(p_file);
    return  QPair<int,QString>(i,res);
}

void moveToWindowCenter(QWidget *widget)
{
    //获取主屏幕分辨率
    QRect screenRect = QApplication::desktop()->screenGeometry();
    widget->move(screenRect.width()/2-widget->width()/2,screenRect.height()/2-widget->height()/2-100);
}

QJsonDocument readJson(const QString& filePath)
{
    //创建json对象，读取json文件
    QByteArray allData =publisherFunc::readFile(filePath).toLocal8Bit();
    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &json_error));
    if (json_error.error != QJsonParseError::NoError) {
        return  QJsonDocument();
    }
    return  jsonDoc;
}

bool createDir(const QString &dir)
{
    QDir _dir(dir);
    if(_dir.exists(dir)) {
        return true;
    }
    return _dir.mkpath(dir);
}

void showTextBox(QString str)
{
    QMessageBox::warning(0,"",str);
}



}


