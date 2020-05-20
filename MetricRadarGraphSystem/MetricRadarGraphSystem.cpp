// MetricRadarGraphSystem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MDIMainWindow.h"

int main(int argc, char** argv)
{
	Py_Initialize();
	if (!Py_IsInitialized())
		return -1;
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./')");
	
	QApplication app(argc, argv);
	app.setWindowIcon(QIcon("./icon/app.png"));
	app.setStyle(QStyleFactory::create("WindowsXP"));
	//QApplication::setStyle("macintosh");

	MDIMainWindow* mmw = new MDIMainWindow();
	mmw->showMaximized();
	mmw->OpenMainConfig("./FileClassify.ini");
	QSettings fileList("filelist.ini", QSettings::IniFormat);
	QString strDefalutOpenDir = fileList.value("DEFALUTDIR/open_dir2").toString();
	mmw->DisplayDirFile("FileClassify.ini", strDefalutOpenDir);//获取文件扩展名和分类信息
	//mmw->OpenRasterFile(QString::fromLocal8Bit(argv[1]), QString::fromLocal8Bit("E:\\Project\\MetricRadarGraphSystem\\testdata\\radardata\\20140705\\20140705172616.AIR"));
	app.exec();

	// 关闭Python  
	Py_Finalize();
    return 0;
}