/********************************************************************************
** Form generated from reading UI file 'MainSetting.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINSETTING_H
#define UI_MAINSETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainSettingDialogSetup
{
public:
    QGridLayout *gridLayout;
    QDialogButtonBox *buttonBox;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGroupBox *groupBox;
    QListWidget *rasterList;
    QGroupBox *groupBox_2;
    QListWidget *curveList;
    QGroupBox *groupBox_3;
    QTreeWidget *classifyTree;
    QPushButton *addClassify;
    QPushButton *removeClassify;
    QWidget *tab_2;
    QListWidget *allList;
    QWidget *tab_3;
    QListWidget *symbolList;

    void setupUi(QDialog *MainSettingDialogSetup)
    {
        if (MainSettingDialogSetup->objectName().isEmpty())
            MainSettingDialogSetup->setObjectName(QStringLiteral("MainSettingDialogSetup"));
        MainSettingDialogSetup->resize(534, 483);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainSettingDialogSetup->sizePolicy().hasHeightForWidth());
        MainSettingDialogSetup->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(MainSettingDialogSetup);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        buttonBox = new QDialogButtonBox(MainSettingDialogSetup);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 1, 1, 1);

        tabWidget = new QTabWidget(MainSettingDialogSetup);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 241, 171));
        rasterList = new QListWidget(groupBox);
        rasterList->setObjectName(QStringLiteral("rasterList"));
        rasterList->setGeometry(QRect(10, 20, 221, 141));
        groupBox_2 = new QGroupBox(tab);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(260, 10, 241, 171));
        curveList = new QListWidget(groupBox_2);
        curveList->setObjectName(QStringLiteral("curveList"));
        curveList->setGeometry(QRect(10, 20, 221, 141));
        groupBox_3 = new QGroupBox(tab);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 220, 491, 181));
        classifyTree = new QTreeWidget(groupBox_3);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        classifyTree->setHeaderItem(__qtreewidgetitem);
        classifyTree->setObjectName(QStringLiteral("classifyTree"));
        classifyTree->setGeometry(QRect(10, 20, 471, 151));
        addClassify = new QPushButton(tab);
        addClassify->setObjectName(QStringLiteral("addClassify"));
        addClassify->setGeometry(QRect(180, 190, 75, 23));
        removeClassify = new QPushButton(tab);
        removeClassify->setObjectName(QStringLiteral("removeClassify"));
        removeClassify->setGeometry(QRect(260, 190, 75, 23));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        allList = new QListWidget(tab_2);
        allList->setObjectName(QStringLiteral("allList"));
        allList->setGeometry(QRect(10, 10, 491, 391));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        symbolList = new QListWidget(tab_3);
        symbolList->setObjectName(QStringLiteral("symbolList"));
        symbolList->setGeometry(QRect(10, 10, 491, 391));
        tabWidget->addTab(tab_3, QString());

        gridLayout->addWidget(tabWidget, 0, 1, 1, 1);


        retranslateUi(MainSettingDialogSetup);
        QObject::connect(buttonBox, SIGNAL(accepted()), MainSettingDialogSetup, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), MainSettingDialogSetup, SLOT(reject()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainSettingDialogSetup);
    } // setupUi

    void retranslateUi(QDialog *MainSettingDialogSetup)
    {
        MainSettingDialogSetup->setWindowTitle(QApplication::translate("MainSettingDialogSetup", "Dialog", 0));
        groupBox->setTitle(QApplication::translate("MainSettingDialogSetup", "\346\240\205\346\240\274\345\233\276\357\274\210\346\226\207\344\273\266\346\211\251\345\261\225\345\220\215\357\274\211", 0));
        groupBox_2->setTitle(QApplication::translate("MainSettingDialogSetup", "\346\233\262\347\272\277\345\233\276\357\274\210\346\226\207\344\273\266\346\211\251\345\261\225\345\220\215\357\274\211", 0));
        groupBox_3->setTitle(QApplication::translate("MainSettingDialogSetup", "\345\275\222\347\261\273", 0));
        addClassify->setText(QApplication::translate("MainSettingDialogSetup", "\357\270\276", 0));
        removeClassify->setText(QApplication::translate("MainSettingDialogSetup", "\357\270\275", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainSettingDialogSetup", "\346\211\251\345\261\225\345\220\215\345\222\214\345\275\222\347\261\273", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainSettingDialogSetup", "\347\273\274\345\220\210\350\256\276\347\275\256", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainSettingDialogSetup", "\347\254\246\345\217\267\346\240\267\345\274\217", 0));
    } // retranslateUi

};

namespace Ui {
    class MainSettingDialogSetup: public Ui_MainSettingDialogSetup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINSETTING_H
