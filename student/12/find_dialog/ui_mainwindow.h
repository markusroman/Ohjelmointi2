/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *fileLineEdit;
    QLabel *keyLabel;
    QLabel *findLabel;
    QCheckBox *matchCheckBox;
    QPushButton *findPushButton;
    QPushButton *closePushButton;
    QLineEdit *keyLineEdit;
    QLabel *label_5;
    QFrame *line;
    QTextBrowser *textBrowser;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(399, 316);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 10, 381, 131));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        fileLineEdit = new QLineEdit(gridLayoutWidget);
        fileLineEdit->setObjectName(QStringLiteral("fileLineEdit"));

        gridLayout->addWidget(fileLineEdit, 2, 1, 1, 1);

        keyLabel = new QLabel(gridLayoutWidget);
        keyLabel->setObjectName(QStringLiteral("keyLabel"));

        gridLayout->addWidget(keyLabel, 3, 0, 1, 1);

        findLabel = new QLabel(gridLayoutWidget);
        findLabel->setObjectName(QStringLiteral("findLabel"));

        gridLayout->addWidget(findLabel, 2, 0, 1, 1);

        matchCheckBox = new QCheckBox(gridLayoutWidget);
        matchCheckBox->setObjectName(QStringLiteral("matchCheckBox"));

        gridLayout->addWidget(matchCheckBox, 4, 0, 1, 1);

        findPushButton = new QPushButton(gridLayoutWidget);
        findPushButton->setObjectName(QStringLiteral("findPushButton"));

        gridLayout->addWidget(findPushButton, 2, 2, 1, 1);

        closePushButton = new QPushButton(gridLayoutWidget);
        closePushButton->setObjectName(QStringLiteral("closePushButton"));

        gridLayout->addWidget(closePushButton, 3, 2, 1, 1);

        keyLineEdit = new QLineEdit(gridLayoutWidget);
        keyLineEdit->setObjectName(QStringLiteral("keyLineEdit"));

        gridLayout->addWidget(keyLineEdit, 3, 1, 1, 1);

        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 6, 0, 1, 1);

        line = new QFrame(gridLayoutWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 5, 0, 1, 3);

        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(10, 140, 381, 191));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 399, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(closePushButton, SIGNAL(clicked()), MainWindow, SLOT(close()));
        QObject::connect(findPushButton, SIGNAL(clicked()), MainWindow, SLOT(changeText()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        keyLabel->setText(QApplication::translate("MainWindow", "Find what:", Q_NULLPTR));
        findLabel->setText(QApplication::translate("MainWindow", "Find from file:", Q_NULLPTR));
        matchCheckBox->setText(QApplication::translate("MainWindow", "Match case", Q_NULLPTR));
        findPushButton->setText(QApplication::translate("MainWindow", "Find", Q_NULLPTR));
        closePushButton->setText(QApplication::translate("MainWindow", "Close", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "Search status:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
