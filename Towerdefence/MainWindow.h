#pragma once

#include <QtWidgets/QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QSound>
#include <QTimer>
#include <QPushButton>
#include <QLabel>
#include "Radish.h"
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);
    void mousePressEvent(QMouseEvent* ev) override;
    void start();
    void level();
    void Game1();
    void Game2();
    void AddEnemy();
    void AddEnemy2();
    void check();
    void Boom();

private:
    //Ui::MainWindowClass ui;
    QGraphicsScene* scene;
    QGraphicsView* view;
    QSound* sound;
    QTimer* timer;
    Radish* r[3];
    int state = 0;
    QPushButton* button;
    QPushButton* lv1, * lv2;
    QLabel* title;
    QPushButton* back;
};
