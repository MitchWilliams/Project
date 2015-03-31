/********************************************************************************
** Form generated from reading UI file 'project.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECT_H
#define UI_PROJECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProjectClass
{
public:
    QWidget *centralWidget;
    QListWidget *playerPool;
    QPushButton *loadButton;
    QListWidget *teamTwoPlayers;
    QListWidget *teamOnePlayers;
    QLabel *playerPoolLabel;
    QLabel *teamTwoLabel;
    QLabel *teamOneLabel;
    QPushButton *teamTwoAdd;
    QPushButton *teamOneAdd;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *firstNameLabel;
    QLabel *firstNameField;
    QLabel *surnameLabel;
    QLabel *surnameField;
    QLabel *heightLabel;
    QLabel *heightField;
    QLabel *positionLabel;
    QLabel *positionField;
    QLabel *closeLabel;
    QLabel *closeField;
    QLabel *medLabel;
    QLabel *mediumField;
    QLabel *threeLabel;
    QLabel *threeField;
    QLabel *passingLabel;
    QLabel *passingField;
    QLabel *dribblingLabel;
    QLabel *dribblingField;
    QLabel *reboundingLabel;
    QLabel *reboundingField;
    QLabel *defendingLabel;
    QLabel *defendingField;
    QLabel *blockingLabel;
    QLabel *blockingField;
    QLabel *staminaLabel;
    QLabel *staminaField;
    QLabel *athleticismLabel;
    QLabel *athleticismField;
    QPushButton *playMatchButton;
    QPushButton *teamOneRemove;
    QPushButton *teamTwoRemove;
    QLabel *warningLabel;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ProjectClass)
    {
        if (ProjectClass->objectName().isEmpty())
            ProjectClass->setObjectName(QStringLiteral("ProjectClass"));
        ProjectClass->resize(1024, 768);
        centralWidget = new QWidget(ProjectClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        playerPool = new QListWidget(centralWidget);
        playerPool->setObjectName(QStringLiteral("playerPool"));
        playerPool->setGeometry(QRect(420, 40, 256, 192));
        loadButton = new QPushButton(centralWidget);
        loadButton->setObjectName(QStringLiteral("loadButton"));
        loadButton->setGeometry(QRect(510, 240, 75, 23));
        teamTwoPlayers = new QListWidget(centralWidget);
        teamTwoPlayers->setObjectName(QStringLiteral("teamTwoPlayers"));
        teamTwoPlayers->setGeometry(QRect(710, 40, 256, 192));
        teamOnePlayers = new QListWidget(centralWidget);
        teamOnePlayers->setObjectName(QStringLiteral("teamOnePlayers"));
        teamOnePlayers->setGeometry(QRect(130, 40, 256, 192));
        playerPoolLabel = new QLabel(centralWidget);
        playerPoolLabel->setObjectName(QStringLiteral("playerPoolLabel"));
        playerPoolLabel->setGeometry(QRect(490, 10, 111, 31));
        QFont font;
        font.setPointSize(16);
        playerPoolLabel->setFont(font);
        teamTwoLabel = new QLabel(centralWidget);
        teamTwoLabel->setObjectName(QStringLiteral("teamTwoLabel"));
        teamTwoLabel->setGeometry(QRect(750, 10, 131, 20));
        teamTwoLabel->setFont(font);
        teamOneLabel = new QLabel(centralWidget);
        teamOneLabel->setObjectName(QStringLiteral("teamOneLabel"));
        teamOneLabel->setGeometry(QRect(210, 10, 101, 20));
        teamOneLabel->setFont(font);
        teamTwoAdd = new QPushButton(centralWidget);
        teamTwoAdd->setObjectName(QStringLiteral("teamTwoAdd"));
        teamTwoAdd->setGeometry(QRect(600, 240, 75, 23));
        teamOneAdd = new QPushButton(centralWidget);
        teamOneAdd->setObjectName(QStringLiteral("teamOneAdd"));
        teamOneAdd->setGeometry(QRect(420, 240, 75, 23));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(430, 280, 241, 346));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        firstNameLabel = new QLabel(layoutWidget);
        firstNameLabel->setObjectName(QStringLiteral("firstNameLabel"));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        firstNameLabel->setFont(font1);

        gridLayout->addWidget(firstNameLabel, 0, 0, 1, 1);

        firstNameField = new QLabel(layoutWidget);
        firstNameField->setObjectName(QStringLiteral("firstNameField"));
        QFont font2;
        font2.setPointSize(10);
        firstNameField->setFont(font2);

        gridLayout->addWidget(firstNameField, 0, 1, 1, 1);

        surnameLabel = new QLabel(layoutWidget);
        surnameLabel->setObjectName(QStringLiteral("surnameLabel"));
        surnameLabel->setFont(font1);

        gridLayout->addWidget(surnameLabel, 1, 0, 1, 1);

        surnameField = new QLabel(layoutWidget);
        surnameField->setObjectName(QStringLiteral("surnameField"));
        surnameField->setFont(font2);

        gridLayout->addWidget(surnameField, 1, 1, 1, 1);

        heightLabel = new QLabel(layoutWidget);
        heightLabel->setObjectName(QStringLiteral("heightLabel"));
        heightLabel->setFont(font1);

        gridLayout->addWidget(heightLabel, 2, 0, 1, 1);

        heightField = new QLabel(layoutWidget);
        heightField->setObjectName(QStringLiteral("heightField"));
        heightField->setFont(font2);

        gridLayout->addWidget(heightField, 2, 1, 1, 1);

        positionLabel = new QLabel(layoutWidget);
        positionLabel->setObjectName(QStringLiteral("positionLabel"));
        positionLabel->setFont(font1);

        gridLayout->addWidget(positionLabel, 3, 0, 1, 1);

        positionField = new QLabel(layoutWidget);
        positionField->setObjectName(QStringLiteral("positionField"));
        positionField->setFont(font2);

        gridLayout->addWidget(positionField, 3, 1, 1, 1);

        closeLabel = new QLabel(layoutWidget);
        closeLabel->setObjectName(QStringLiteral("closeLabel"));
        closeLabel->setFont(font1);

        gridLayout->addWidget(closeLabel, 4, 0, 1, 1);

        closeField = new QLabel(layoutWidget);
        closeField->setObjectName(QStringLiteral("closeField"));
        closeField->setFont(font2);

        gridLayout->addWidget(closeField, 4, 1, 1, 1);

        medLabel = new QLabel(layoutWidget);
        medLabel->setObjectName(QStringLiteral("medLabel"));
        medLabel->setFont(font1);

        gridLayout->addWidget(medLabel, 5, 0, 1, 1);

        mediumField = new QLabel(layoutWidget);
        mediumField->setObjectName(QStringLiteral("mediumField"));
        mediumField->setFont(font2);

        gridLayout->addWidget(mediumField, 5, 1, 1, 1);

        threeLabel = new QLabel(layoutWidget);
        threeLabel->setObjectName(QStringLiteral("threeLabel"));
        threeLabel->setFont(font1);

        gridLayout->addWidget(threeLabel, 6, 0, 1, 1);

        threeField = new QLabel(layoutWidget);
        threeField->setObjectName(QStringLiteral("threeField"));
        threeField->setFont(font2);

        gridLayout->addWidget(threeField, 6, 1, 1, 1);

        passingLabel = new QLabel(layoutWidget);
        passingLabel->setObjectName(QStringLiteral("passingLabel"));
        passingLabel->setFont(font1);

        gridLayout->addWidget(passingLabel, 7, 0, 1, 1);

        passingField = new QLabel(layoutWidget);
        passingField->setObjectName(QStringLiteral("passingField"));
        passingField->setFont(font2);

        gridLayout->addWidget(passingField, 7, 1, 1, 1);

        dribblingLabel = new QLabel(layoutWidget);
        dribblingLabel->setObjectName(QStringLiteral("dribblingLabel"));
        dribblingLabel->setFont(font1);

        gridLayout->addWidget(dribblingLabel, 8, 0, 1, 1);

        dribblingField = new QLabel(layoutWidget);
        dribblingField->setObjectName(QStringLiteral("dribblingField"));
        dribblingField->setFont(font2);

        gridLayout->addWidget(dribblingField, 8, 1, 1, 1);

        reboundingLabel = new QLabel(layoutWidget);
        reboundingLabel->setObjectName(QStringLiteral("reboundingLabel"));
        reboundingLabel->setFont(font1);

        gridLayout->addWidget(reboundingLabel, 9, 0, 1, 1);

        reboundingField = new QLabel(layoutWidget);
        reboundingField->setObjectName(QStringLiteral("reboundingField"));
        reboundingField->setFont(font2);

        gridLayout->addWidget(reboundingField, 9, 1, 1, 1);

        defendingLabel = new QLabel(layoutWidget);
        defendingLabel->setObjectName(QStringLiteral("defendingLabel"));
        defendingLabel->setFont(font1);

        gridLayout->addWidget(defendingLabel, 10, 0, 1, 1);

        defendingField = new QLabel(layoutWidget);
        defendingField->setObjectName(QStringLiteral("defendingField"));
        defendingField->setFont(font2);

        gridLayout->addWidget(defendingField, 10, 1, 1, 1);

        blockingLabel = new QLabel(layoutWidget);
        blockingLabel->setObjectName(QStringLiteral("blockingLabel"));
        blockingLabel->setFont(font1);

        gridLayout->addWidget(blockingLabel, 11, 0, 1, 1);

        blockingField = new QLabel(layoutWidget);
        blockingField->setObjectName(QStringLiteral("blockingField"));
        blockingField->setFont(font2);

        gridLayout->addWidget(blockingField, 11, 1, 1, 1);

        staminaLabel = new QLabel(layoutWidget);
        staminaLabel->setObjectName(QStringLiteral("staminaLabel"));
        staminaLabel->setFont(font1);

        gridLayout->addWidget(staminaLabel, 12, 0, 1, 1);

        staminaField = new QLabel(layoutWidget);
        staminaField->setObjectName(QStringLiteral("staminaField"));
        staminaField->setFont(font2);

        gridLayout->addWidget(staminaField, 12, 1, 1, 1);

        athleticismLabel = new QLabel(layoutWidget);
        athleticismLabel->setObjectName(QStringLiteral("athleticismLabel"));
        athleticismLabel->setFont(font1);

        gridLayout->addWidget(athleticismLabel, 13, 0, 1, 1);

        athleticismField = new QLabel(layoutWidget);
        athleticismField->setObjectName(QStringLiteral("athleticismField"));
        athleticismField->setFont(font2);

        gridLayout->addWidget(athleticismField, 13, 1, 1, 1);

        playMatchButton = new QPushButton(centralWidget);
        playMatchButton->setObjectName(QStringLiteral("playMatchButton"));
        playMatchButton->setGeometry(QRect(430, 630, 241, 51));
        QFont font3;
        font3.setPointSize(14);
        playMatchButton->setFont(font3);
        teamOneRemove = new QPushButton(centralWidget);
        teamOneRemove->setObjectName(QStringLiteral("teamOneRemove"));
        teamOneRemove->setGeometry(QRect(204, 240, 91, 23));
        teamTwoRemove = new QPushButton(centralWidget);
        teamTwoRemove->setObjectName(QStringLiteral("teamTwoRemove"));
        teamTwoRemove->setGeometry(QRect(790, 240, 91, 23));
        warningLabel = new QLabel(centralWidget);
        warningLabel->setObjectName(QStringLiteral("warningLabel"));
        warningLabel->setGeometry(QRect(370, 640, 381, 21));
        ProjectClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ProjectClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 21));
        ProjectClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ProjectClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ProjectClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ProjectClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ProjectClass->setStatusBar(statusBar);

        retranslateUi(ProjectClass);

        QMetaObject::connectSlotsByName(ProjectClass);
    } // setupUi

    void retranslateUi(QMainWindow *ProjectClass)
    {
        ProjectClass->setWindowTitle(QApplication::translate("ProjectClass", "Project", 0));
        loadButton->setText(QApplication::translate("ProjectClass", "Load Players", 0));
        playerPoolLabel->setText(QApplication::translate("ProjectClass", "Player Pool", 0));
        teamTwoLabel->setText(QApplication::translate("ProjectClass", "Team Two(AI)", 0));
        teamOneLabel->setText(QApplication::translate("ProjectClass", "Team One", 0));
        teamTwoAdd->setText(QApplication::translate("ProjectClass", ">> Add >>", 0));
        teamOneAdd->setText(QApplication::translate("ProjectClass", "<< Add <<", 0));
        firstNameLabel->setText(QApplication::translate("ProjectClass", "First Name", 0));
        firstNameField->setText(QApplication::translate("ProjectClass", "N/A", 0));
        surnameLabel->setText(QApplication::translate("ProjectClass", "Surname", 0));
        surnameField->setText(QApplication::translate("ProjectClass", "N/A", 0));
        heightLabel->setText(QApplication::translate("ProjectClass", "Height(cm)", 0));
        heightField->setText(QApplication::translate("ProjectClass", "N/A", 0));
        positionLabel->setText(QApplication::translate("ProjectClass", "Position", 0));
        positionField->setText(QApplication::translate("ProjectClass", "N/A", 0));
        closeLabel->setText(QApplication::translate("ProjectClass", "Close", 0));
        closeField->setText(QApplication::translate("ProjectClass", "0", 0));
        medLabel->setText(QApplication::translate("ProjectClass", "Medium", 0));
        mediumField->setText(QApplication::translate("ProjectClass", "0", 0));
        threeLabel->setText(QApplication::translate("ProjectClass", "Three Pt", 0));
        threeField->setText(QApplication::translate("ProjectClass", "0", 0));
        passingLabel->setText(QApplication::translate("ProjectClass", "Passing", 0));
        passingField->setText(QApplication::translate("ProjectClass", "0", 0));
        dribblingLabel->setText(QApplication::translate("ProjectClass", "Dribbling", 0));
        dribblingField->setText(QApplication::translate("ProjectClass", "0", 0));
        reboundingLabel->setText(QApplication::translate("ProjectClass", "Rebounding", 0));
        reboundingField->setText(QApplication::translate("ProjectClass", "0", 0));
        defendingLabel->setText(QApplication::translate("ProjectClass", "Defending", 0));
        defendingField->setText(QApplication::translate("ProjectClass", "0", 0));
        blockingLabel->setText(QApplication::translate("ProjectClass", "Blocking", 0));
        blockingField->setText(QApplication::translate("ProjectClass", "0", 0));
        staminaLabel->setText(QApplication::translate("ProjectClass", "Stamina", 0));
        staminaField->setText(QApplication::translate("ProjectClass", "0", 0));
        athleticismLabel->setText(QApplication::translate("ProjectClass", "Athleticism", 0));
        athleticismField->setText(QApplication::translate("ProjectClass", "0", 0));
        playMatchButton->setText(QApplication::translate("ProjectClass", "Go To Match", 0));
        teamOneRemove->setText(QApplication::translate("ProjectClass", ">> Remove >>", 0));
        teamTwoRemove->setText(QApplication::translate("ProjectClass", "<< Remove <<", 0));
        warningLabel->setText(QApplication::translate("ProjectClass", "The match cannot be played until each team has one player for each position", 0));
    } // retranslateUi

};

namespace Ui {
    class ProjectClass: public Ui_ProjectClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECT_H
