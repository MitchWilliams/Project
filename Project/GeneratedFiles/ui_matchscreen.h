/********************************************************************************
** Form generated from reading UI file 'matchscreen.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATCHSCREEN_H
#define UI_MATCHSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MatchScreen
{
public:
    QTextBrowser *matchText;
    QPushButton *playButton;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QLabel *teamOnePGLabel;
    QLabel *teamOneSGLabel;
    QLabel *teamOneSFLabel;
    QLabel *teamOnePFLabel;
    QLabel *teamOneCLabel;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *teamOnePGStats;
    QLabel *teamOneSGStats;
    QLabel *teamOneSFStats;
    QLabel *teamOnePFStats;
    QLabel *teamOneCStats;
    QLabel *TeamOnePlayersLabel;
    QLabel *TeamTwoPlayersLabel;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QLabel *teamTwoPGLabel;
    QLabel *teamTwoSGLabel;
    QLabel *teamTwoSFLabel;
    QLabel *teamTwoPFLabel;
    QLabel *teamTwoCLabel;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_2;
    QLabel *teamTwoPGStats;
    QLabel *teamTwoSGStats;
    QLabel *teamTwoSFStats;
    QLabel *teamTwoPFStats;
    QLabel *teamTwoCStats;
    QGraphicsView *gameView;
    QLabel *teamOneLabel;
    QLabel *teamTwoLabel;
    QLabel *teamOneScoreLabel;
    QLabel *teamTwoScoreLabel;
    QLabel *timeRemainingLabel;
    QLabel *quarterLabel;

    void setupUi(QWidget *MatchScreen)
    {
        if (MatchScreen->objectName().isEmpty())
            MatchScreen->setObjectName(QStringLiteral("MatchScreen"));
        MatchScreen->resize(1038, 685);
        matchText = new QTextBrowser(MatchScreen);
        matchText->setObjectName(QStringLiteral("matchText"));
        matchText->setGeometry(QRect(30, 20, 321, 401));
        matchText->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        playButton = new QPushButton(MatchScreen);
        playButton->setObjectName(QStringLiteral("playButton"));
        playButton->setGeometry(QRect(470, 500, 75, 23));
        layoutWidget = new QWidget(MatchScreen);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(110, 580, 101, 91));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        teamOnePGLabel = new QLabel(layoutWidget);
        teamOnePGLabel->setObjectName(QStringLiteral("teamOnePGLabel"));

        verticalLayout_3->addWidget(teamOnePGLabel);

        teamOneSGLabel = new QLabel(layoutWidget);
        teamOneSGLabel->setObjectName(QStringLiteral("teamOneSGLabel"));

        verticalLayout_3->addWidget(teamOneSGLabel);

        teamOneSFLabel = new QLabel(layoutWidget);
        teamOneSFLabel->setObjectName(QStringLiteral("teamOneSFLabel"));

        verticalLayout_3->addWidget(teamOneSFLabel);

        teamOnePFLabel = new QLabel(layoutWidget);
        teamOnePFLabel->setObjectName(QStringLiteral("teamOnePFLabel"));

        verticalLayout_3->addWidget(teamOnePFLabel);

        teamOneCLabel = new QLabel(layoutWidget);
        teamOneCLabel->setObjectName(QStringLiteral("teamOneCLabel"));

        verticalLayout_3->addWidget(teamOneCLabel);

        layoutWidget_2 = new QWidget(MatchScreen);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(210, 580, 301, 91));
        verticalLayout_4 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        teamOnePGStats = new QLabel(layoutWidget_2);
        teamOnePGStats->setObjectName(QStringLiteral("teamOnePGStats"));

        verticalLayout_4->addWidget(teamOnePGStats);

        teamOneSGStats = new QLabel(layoutWidget_2);
        teamOneSGStats->setObjectName(QStringLiteral("teamOneSGStats"));

        verticalLayout_4->addWidget(teamOneSGStats);

        teamOneSFStats = new QLabel(layoutWidget_2);
        teamOneSFStats->setObjectName(QStringLiteral("teamOneSFStats"));

        verticalLayout_4->addWidget(teamOneSFStats);

        teamOnePFStats = new QLabel(layoutWidget_2);
        teamOnePFStats->setObjectName(QStringLiteral("teamOnePFStats"));

        verticalLayout_4->addWidget(teamOnePFStats);

        teamOneCStats = new QLabel(layoutWidget_2);
        teamOneCStats->setObjectName(QStringLiteral("teamOneCStats"));

        verticalLayout_4->addWidget(teamOneCStats);

        TeamOnePlayersLabel = new QLabel(MatchScreen);
        TeamOnePlayersLabel->setObjectName(QStringLiteral("TeamOnePlayersLabel"));
        TeamOnePlayersLabel->setGeometry(QRect(205, 540, 191, 20));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        TeamOnePlayersLabel->setFont(font);
        TeamTwoPlayersLabel = new QLabel(MatchScreen);
        TeamTwoPlayersLabel->setObjectName(QStringLiteral("TeamTwoPlayersLabel"));
        TeamTwoPlayersLabel->setGeometry(QRect(670, 530, 191, 20));
        TeamTwoPlayersLabel->setFont(font);
        layoutWidget1 = new QWidget(MatchScreen);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(527, 580, 111, 91));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        teamTwoPGLabel = new QLabel(layoutWidget1);
        teamTwoPGLabel->setObjectName(QStringLiteral("teamTwoPGLabel"));

        verticalLayout->addWidget(teamTwoPGLabel);

        teamTwoSGLabel = new QLabel(layoutWidget1);
        teamTwoSGLabel->setObjectName(QStringLiteral("teamTwoSGLabel"));

        verticalLayout->addWidget(teamTwoSGLabel);

        teamTwoSFLabel = new QLabel(layoutWidget1);
        teamTwoSFLabel->setObjectName(QStringLiteral("teamTwoSFLabel"));

        verticalLayout->addWidget(teamTwoSFLabel);

        teamTwoPFLabel = new QLabel(layoutWidget1);
        teamTwoPFLabel->setObjectName(QStringLiteral("teamTwoPFLabel"));

        verticalLayout->addWidget(teamTwoPFLabel);

        teamTwoCLabel = new QLabel(layoutWidget1);
        teamTwoCLabel->setObjectName(QStringLiteral("teamTwoCLabel"));

        verticalLayout->addWidget(teamTwoCLabel);

        layoutWidget2 = new QWidget(MatchScreen);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(640, 580, 291, 91));
        verticalLayout_2 = new QVBoxLayout(layoutWidget2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        teamTwoPGStats = new QLabel(layoutWidget2);
        teamTwoPGStats->setObjectName(QStringLiteral("teamTwoPGStats"));

        verticalLayout_2->addWidget(teamTwoPGStats);

        teamTwoSGStats = new QLabel(layoutWidget2);
        teamTwoSGStats->setObjectName(QStringLiteral("teamTwoSGStats"));

        verticalLayout_2->addWidget(teamTwoSGStats);

        teamTwoSFStats = new QLabel(layoutWidget2);
        teamTwoSFStats->setObjectName(QStringLiteral("teamTwoSFStats"));

        verticalLayout_2->addWidget(teamTwoSFStats);

        teamTwoPFStats = new QLabel(layoutWidget2);
        teamTwoPFStats->setObjectName(QStringLiteral("teamTwoPFStats"));

        verticalLayout_2->addWidget(teamTwoPFStats);

        teamTwoCStats = new QLabel(layoutWidget2);
        teamTwoCStats->setObjectName(QStringLiteral("teamTwoCStats"));

        verticalLayout_2->addWidget(teamTwoCStats);

        gameView = new QGraphicsView(MatchScreen);
        gameView->setObjectName(QStringLiteral("gameView"));
        gameView->setGeometry(QRect(380, 20, 595, 352));
        teamOneLabel = new QLabel(MatchScreen);
        teamOneLabel->setObjectName(QStringLiteral("teamOneLabel"));
        teamOneLabel->setGeometry(QRect(415, 390, 111, 20));
        QFont font1;
        font1.setPointSize(16);
        teamOneLabel->setFont(font1);
        teamTwoLabel = new QLabel(MatchScreen);
        teamTwoLabel->setObjectName(QStringLiteral("teamTwoLabel"));
        teamTwoLabel->setGeometry(QRect(785, 390, 111, 20));
        teamTwoLabel->setFont(font1);
        teamOneScoreLabel = new QLabel(MatchScreen);
        teamOneScoreLabel->setObjectName(QStringLiteral("teamOneScoreLabel"));
        teamOneScoreLabel->setGeometry(QRect(530, 390, 46, 21));
        teamOneScoreLabel->setFont(font1);
        teamTwoScoreLabel = new QLabel(MatchScreen);
        teamTwoScoreLabel->setObjectName(QStringLiteral("teamTwoScoreLabel"));
        teamTwoScoreLabel->setGeometry(QRect(910, 390, 51, 21));
        teamTwoScoreLabel->setFont(font1);
        timeRemainingLabel = new QLabel(MatchScreen);
        timeRemainingLabel->setObjectName(QStringLiteral("timeRemainingLabel"));
        timeRemainingLabel->setGeometry(QRect(660, 390, 71, 21));
        timeRemainingLabel->setFont(font1);
        quarterLabel = new QLabel(MatchScreen);
        quarterLabel->setObjectName(QStringLiteral("quarterLabel"));
        quarterLabel->setGeometry(QRect(610, 390, 41, 21));
        quarterLabel->setFont(font1);

        retranslateUi(MatchScreen);

        QMetaObject::connectSlotsByName(MatchScreen);
    } // setupUi

    void retranslateUi(QWidget *MatchScreen)
    {
        MatchScreen->setWindowTitle(QApplication::translate("MatchScreen", "MatchScreen", 0));
        playButton->setText(QApplication::translate("MatchScreen", "Play", 0));
        teamOnePGLabel->setText(QString());
        teamOneSGLabel->setText(QString());
        teamOneSFLabel->setText(QString());
        teamOnePFLabel->setText(QString());
        teamOneCLabel->setText(QString());
        teamOnePGStats->setText(QString());
        teamOneSGStats->setText(QString());
        teamOneSFStats->setText(QString());
        teamOnePFStats->setText(QString());
        teamOneCStats->setText(QString());
        TeamOnePlayersLabel->setText(QApplication::translate("MatchScreen", "Team One Player Stats", 0));
        TeamTwoPlayersLabel->setText(QApplication::translate("MatchScreen", "Team Two Player Stats", 0));
        teamTwoPGLabel->setText(QString());
        teamTwoSGLabel->setText(QString());
        teamTwoSFLabel->setText(QString());
        teamTwoPFLabel->setText(QString());
        teamTwoCLabel->setText(QString());
        teamTwoPGStats->setText(QString());
        teamTwoSGStats->setText(QString());
        teamTwoSFStats->setText(QString());
        teamTwoPFStats->setText(QString());
        teamTwoCStats->setText(QString());
        teamOneLabel->setText(QApplication::translate("MatchScreen", "Team One:", 0));
        teamTwoLabel->setText(QApplication::translate("MatchScreen", "Team Two:", 0));
        teamOneScoreLabel->setText(QString());
        teamTwoScoreLabel->setText(QString());
        timeRemainingLabel->setText(QString());
        quarterLabel->setText(QApplication::translate("MatchScreen", "Q1", 0));
    } // retranslateUi

};

namespace Ui {
    class MatchScreen: public Ui_MatchScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATCHSCREEN_H
