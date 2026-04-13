#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

// ============================================================
// MainWindow — top-level shell for the Battle Arena
// Commit 1 (Apr 13): skeleton only, no game logic yet
// ============================================================
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;

private slots:
    void onStartGame();
    void onExitGame();

private:
    void buildMenuScreen();

    // Central widget holds the current "screen"
    QWidget     *m_centralWidget  = nullptr;

    // Menu screen widgets
    QPushButton *m_startBtn  = nullptr;
    QPushButton *m_exitBtn   = nullptr;
    QLabel      *m_titleLabel = nullptr;
};
