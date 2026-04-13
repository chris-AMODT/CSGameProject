#include "mainwindow.h"
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    buildMenuScreen();
}

void MainWindow::buildMenuScreen()
{
    m_centralWidget = new QWidget(this);
    setCentralWidget(m_centralWidget);

    auto *layout = new QVBoxLayout(m_centralWidget);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(20);

    // Title
    m_titleLabel = new QLabel("⚔  BATTLE ARENA  ⚔", m_centralWidget);
    QFont titleFont = m_titleLabel->font();
    titleFont.setPointSize(28);
    titleFont.setBold(true);
    m_titleLabel->setFont(titleFont);
    m_titleLabel->setAlignment(Qt::AlignCenter);

    // Buttons
    m_startBtn = new QPushButton("Start Game", m_centralWidget);
    m_startBtn->setFixedSize(200, 50);

    m_exitBtn = new QPushButton("Exit", m_centralWidget);
    m_exitBtn->setFixedSize(200, 50);

    layout->addStretch();
    layout->addWidget(m_titleLabel);
    layout->addSpacing(40);
    layout->addWidget(m_startBtn, 0, Qt::AlignCenter);
    layout->addWidget(m_exitBtn,  0, Qt::AlignCenter);
    layout->addStretch();

    connect(m_startBtn, &QPushButton::clicked, this, &MainWindow::onStartGame);
    connect(m_exitBtn,  &QPushButton::clicked, this, &MainWindow::onExitGame);
}

void MainWindow::onStartGame()
{
    // TODO (commit 4): swap to battlefield widget
    m_titleLabel->setText("Game starting... (not implemented yet)");
}

void MainWindow::onExitGame()
{
    QApplication::quit();
}
