/********************************************************************************
** Form generated from reading UI file 'MainWindowUI.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOWUI_H
#define UI_MAINWINDOWUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *OpenFile;
    QAction *Export;
    QAction *CurrentFile;
    QAction *Exit;
    QAction *TileWindowsAction;
    QAction *CascadeWindowsAction;
    QAction *OpenDir;
    QAction *ExportAll;
    QAction *ColorTable;
    QAction *MainSettings;
    QAction *CloseDirAction;
    QAction *CloseAllWinAction;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *File;
    QMenu *window;
    QMenu *menu_S;
    QMenu *help;
    QToolBar *toolBar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout;
    QTreeView *treeView;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(817, 616);
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        OpenFile = new QAction(MainWindow);
        OpenFile->setObjectName(QStringLiteral("OpenFile"));
        Export = new QAction(MainWindow);
        Export->setObjectName(QStringLiteral("Export"));
        CurrentFile = new QAction(MainWindow);
        CurrentFile->setObjectName(QStringLiteral("CurrentFile"));
        Exit = new QAction(MainWindow);
        Exit->setObjectName(QStringLiteral("Exit"));
        TileWindowsAction = new QAction(MainWindow);
        TileWindowsAction->setObjectName(QStringLiteral("TileWindowsAction"));
        CascadeWindowsAction = new QAction(MainWindow);
        CascadeWindowsAction->setObjectName(QStringLiteral("CascadeWindowsAction"));
        OpenDir = new QAction(MainWindow);
        OpenDir->setObjectName(QStringLiteral("OpenDir"));
        ExportAll = new QAction(MainWindow);
        ExportAll->setObjectName(QStringLiteral("ExportAll"));
        ColorTable = new QAction(MainWindow);
        ColorTable->setObjectName(QStringLiteral("ColorTable"));
        MainSettings = new QAction(MainWindow);
        MainSettings->setObjectName(QStringLiteral("MainSettings"));
        CloseDirAction = new QAction(MainWindow);
        CloseDirAction->setObjectName(QStringLiteral("CloseDirAction"));
        CloseAllWinAction = new QAction(MainWindow);
        CloseAllWinAction->setObjectName(QStringLiteral("CloseAllWinAction"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 817, 23));
        File = new QMenu(menubar);
        File->setObjectName(QStringLiteral("File"));
        window = new QMenu(menubar);
        window->setObjectName(QStringLiteral("window"));
        menu_S = new QMenu(window);
        menu_S->setObjectName(QStringLiteral("menu_S"));
        help = new QMenu(menubar);
        help->setObjectName(QStringLiteral("help"));
        MainWindow->setMenuBar(menubar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        dockWidget = new QDockWidget(MainWindow);
        dockWidget->setObjectName(QStringLiteral("dockWidget"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        gridLayout = new QGridLayout(dockWidgetContents);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        treeView = new QTreeView(dockWidgetContents);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->setRootIsDecorated(true);

        gridLayout->addWidget(treeView, 0, 0, 1, 1);

        dockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(File->menuAction());
        menubar->addAction(window->menuAction());
        menubar->addAction(help->menuAction());
        File->addAction(OpenFile);
        File->addAction(OpenDir);
        File->addAction(Export);
        File->addAction(ExportAll);
        File->addSeparator();
        File->addAction(CloseDirAction);
        File->addAction(Exit);
        window->addAction(TileWindowsAction);
        window->addAction(CascadeWindowsAction);
        window->addSeparator();
        window->addAction(CloseAllWinAction);
        window->addAction(menu_S->menuAction());
        menu_S->addAction(MainSettings);
        menu_S->addAction(ColorTable);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        OpenFile->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266(&O)", 0));
        Export->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\345\233\276\347\211\207(&P)", 0));
        CurrentFile->setText(QApplication::translate("MainWindow", "\346\234\200\350\277\221\347\232\204\346\226\207\344\273\266", 0));
        Exit->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272(&E)", 0));
        TileWindowsAction->setText(QApplication::translate("MainWindow", "\345\271\263\351\223\272(&P)", 0));
        CascadeWindowsAction->setText(QApplication::translate("MainWindow", "\345\261\202\345\217\240(&O)", 0));
        OpenDir->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\347\233\256\345\275\225(&D)", 0));
        ExportAll->setText(QApplication::translate("MainWindow", "\345\205\250\351\203\250\345\255\230\345\233\276(A)", 0));
        ColorTable->setText(QApplication::translate("MainWindow", "\345\210\233\345\273\272\350\211\262\345\215\241(&C)", 0));
        MainSettings->setText(QApplication::translate("MainWindow", "\351\246\226\351\200\211\351\241\271(&M)", 0));
        CloseDirAction->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255\347\233\256\345\275\225(&I)", 0));
        CloseAllWinAction->setText(QApplication::translate("MainWindow", "\345\205\250\351\203\250\345\205\263\351\227\255(&C)", 0));
        File->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266(&F)", 0));
        window->setTitle(QApplication::translate("MainWindow", "\347\252\227\345\217\243(&W)", 0));
        menu_S->setTitle(QApplication::translate("MainWindow", "\350\256\276\347\275\256(&S)", 0));
        help->setTitle(QApplication::translate("MainWindow", "\345\270\256\345\212\251(&H)", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOWUI_H
