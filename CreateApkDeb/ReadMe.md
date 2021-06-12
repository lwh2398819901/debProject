#１.安装caja-image-converter
sudo apt install caja-image-converter
#2.安装private
sudo apt install qtbase5-private-dev
#3.安装qtxlsx
unzip QtXlsxWriter-master.zip;
cd QtXlsxWriter-master;
qmake;make;sudo make install
#4. 安装kbox
sudo apt install kbox
#5.选择apk文件
#6.启动后生成配置文件


确认kbox程序为kbox用户 否则icon生成失败

QString iconPath = QString("/home/Kbox/icons/%2").arg(apk.appIcon);