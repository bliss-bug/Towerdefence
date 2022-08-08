#pragma execution_character_set("utf-8")
#include "MainWindow.h"
#include "Path.h"
#include "Map.h"
#include "Shop.h"
#include "Shovel.h"
#include "CherryBomb.h"
#include "GroundEnemy1.h"
#include "FlyingEnemy1.h"
#include "GroundEnemy2.h"
#include "FlyingEnemy2.h"
#include "FlyingEnemy3.h"
#include "GroundEnemy3.h"
#include "GroundEnemy4.h"
#include "BackButton.h"
#include <QTime>

const int MAX_ENEMY_NUM = 70;
const int MAXTIME = 150;
const int MINTIME = 50;
int creatednum = 0;
int killnum = 0;
int curtime = MAXTIME;
extern Path path[3];

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(1600, 1000);
    this->setWindowTitle("Ëþ·ÀÓÎÏ·");
    state = 0;
    sound = nullptr;
    button = nullptr;
    lv1 = nullptr;
    lv2 = nullptr;
    back = nullptr;

    QLabel* bg = new QLabel(this);
    bg->setPixmap(QPixmap(":/image/Bg.png"));
    bg->setScaledContents(true);
    bg->resize(this->size());

    title = new QLabel(this);
    title->setPixmap(QPixmap(":/image/title1.png"));
    title->setScaledContents(true);
    title->resize(800, 203);
    start();
}

void MainWindow::mousePressEvent(QMouseEvent* ev)
{
    if (state == 1)
    {
        //scene->clear();
        delete scene;
        delete view;
        state = 0;
        curtime = MAXTIME;
        killnum = 0;
        creatednum = 0;
        if (sound)
        {
            delete sound;
            sound = new QSound(":/music/mapmusic.wav", this);
            sound->setLoops(QSound::Infinite);
            sound->play();
        }
    }
    else if (state == 2 && ev->x() + ev->y() >= 50 && ev->x() + ev->y() < 150 && abs(ev->x() - ev->y()) <= 50)
    {
        state = 0;
        creatednum = 0;
        killnum = 0;
        curtime = MAXTIME;
        delete scene;
        delete timer;
        delete view;
        delete sound;
        sound = new QSound(":/music/mapmusic.wav", this);
        sound->setLoops(QSound::Infinite);
        sound->play();
    }
}

void MainWindow::start()
{
    if (back)
        delete back;
    if (lv1 && lv2)
    {
        delete lv1;
        delete lv2;
    }

    title->move(400, 125);

    button = new QPushButton(this);
    button->resize(315, 160);
    button->setIcon(QIcon(QString(":/image/Button.png")));
    button->setIconSize(QSize(320, 188));
    button->move(640, 700);
    button->show();

    if (sound)
        delete sound;
    sound = new QSound(":/music/startbgmusic.wav", this);
    sound->setLoops(QSound::Infinite);
    sound->play();

    connect(button, &QPushButton::clicked, this, &MainWindow::level);
}

void MainWindow::level()
{
    if (button)
        delete button;
    if (sound)
        delete sound;
    sound = new QSound(":/music/mapmusic.wav", this);
    sound->setLoops(QSound::Infinite);
    sound->play();

    title->move(400, 100);

    lv1 = new QPushButton(this);
    lv1->resize(230, 230);
    lv1->setIcon(QIcon("image/levelbtn1.png"));
    lv1->setIconSize(QSize(248, 248));
    lv1->move(400, 600);
    lv1->show();

    lv2 = new QPushButton(this);
    lv2->resize(230, 230);
    lv2->setIcon(QIcon("image/levelbtn2.png"));
    lv2->setIconSize(QSize(248, 248));
    lv2->move(950, 600);
    lv2->show();

    back = new QPushButton(this);
    back->resize(170, 128);
    back->setIcon(QIcon(":/image/back-button.png"));
    back->setIconSize(QSize(170, 128));
    back->move(50, 50);
    back->show();

    connect(lv1, &QPushButton::clicked, this, &MainWindow::Game1);
    connect(lv2, &QPushButton::clicked, this, &MainWindow::Game2);
    connect(back, &QPushButton::clicked, this, &MainWindow::start);
}

void MainWindow::Game1()
{
    state = 2;
    if (sound)
        delete sound;
    sound = new QSound(":/music/backgroundmusic.wav", this);
    sound->setLoops(QSound::Infinite);
    sound->play();

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 1600, 1000);

    Map* map = new Map;
    scene->addItem(map);

    Shop* shop = new Shop;
    shop->setPos(13 * 90 + 50, 90);
    scene->addItem(shop);

    Shovel* shovel = new Shovel;
    shovel->setPos(15 * 90 + 20, 90);
    scene->addItem(shovel);

    view = new QGraphicsView(scene, this);
    view->resize(1602, 1002);
    view->setRenderHint(QPainter::Antialiasing);
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    view->setBackgroundBrush(QPixmap(":/image/background.png"));

    for (int i = 0; i < 3; i++)
        r[i] = new Radish();
    r[0]->setPos(100, 4 * 90);
    r[1]->setPos(100, 7 * 90);
    r[2]->setPos(100, 8 * 90);
    for (int i = 0; i < 3; i++)
        scene->addItem(r[i]);

    BackButton* bb = new BackButton;
    scene->addItem(bb);

    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    connect(timer, &QTimer::timeout, this, &MainWindow::AddEnemy);
    connect(timer, &QTimer::timeout, this, &MainWindow::check);
    //connect(timer, &QTimer::timeout, this, &MainWindow::Boom);
    timer->start(25);

    import_path();
    view->show();
}

void MainWindow::Game2()
{
    state = 2;
    if (sound)
        delete sound;
    sound = new QSound(":/music/backgroundmusic.wav", this);
    sound->setLoops(QSound::Infinite);
    sound->play();

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 1600, 1000);

    Map* map = new Map;
    scene->addItem(map);

    Shop* shop = new Shop;
    shop->setPos(13 * 90 + 50, 90);
    scene->addItem(shop);

    Shovel* shovel = new Shovel;
    shovel->setPos(15 * 90 + 20, 90);
    scene->addItem(shovel);

    view = new QGraphicsView(scene, this);
    view->resize(1602, 1002);
    view->setRenderHint(QPainter::Antialiasing);
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    view->setBackgroundBrush(QPixmap(":/image/background2.png"));

    for (int i = 0; i < 3; i++)
        r[i] = new Radish();
    r[0]->setPos(100, 3 * 90);
    r[1]->setPos(100, 5 * 90);
    r[2]->setPos(100, 8 * 90);
    for (int i = 0; i < 3; i++)
        scene->addItem(r[i]);

    BackButton* bb = new BackButton;
    scene->addItem(bb);

    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    connect(timer, &QTimer::timeout, this, &MainWindow::AddEnemy2);
    connect(timer, &QTimer::timeout, this, &MainWindow::check);
    timer->start(25);

    import_path2();
    view->show();
}

void MainWindow::AddEnemy()
{
    static int cnt = 0;
    static int ccnt = 0;
    if (creatednum >= MAX_ENEMY_NUM)
        return;
    if (++cnt >= curtime)
    {
        cnt = 0;
        ccnt++;
        if (ccnt % 5 == 0 && curtime > MINTIME)
        {
            curtime -= 10;
            ccnt = 0;
        }
        int p = qrand() % 10;
        int p2 = qrand() % 10;
        if (p < 4)
        {
            if (p2 < 3)
            {
                GroundEnemy1* e = new GroundEnemy1(0);
                e->setPos(11 * 90 + 100, 90);
                scene->addItem(e);
            }
            else if (p2 < 5)
            {
                GroundEnemy2* e = new GroundEnemy2(0);
                e->setPos(11 * 90 + 100, 90);
                scene->addItem(e);
            }
            else if (p2 < 7)
            {
                GroundEnemy3* e = new GroundEnemy3(0);
                e->setPos(11 * 90 + 100, 90);
                scene->addItem(e);
            }
            else
            {
                GroundEnemy4* e = new GroundEnemy4(0);
                e->setPos(11 * 90 + 100, 90);
                scene->addItem(e);
            }
        }
        else if (p < 7)
        {
            if (p2 < 3)
            {
                GroundEnemy1* e = new GroundEnemy1(1);
                e->setPos(11 * 90 + 100, 90 + 5 * 90);
                scene->addItem(e);
            }
            else if (p2 < 6)
            {
                GroundEnemy2* e = new GroundEnemy2(1);
                e->setPos(11 * 90 + 100, 90 + 5 * 90);
                scene->addItem(e);
            }
            else if (p2 < 8)
            {
                GroundEnemy3* e = new GroundEnemy3(1);
                e->setPos(11 * 90 + 100, 90 + 5 * 90);
                scene->addItem(e);
            }
            else
            {
                GroundEnemy4* e = new GroundEnemy4(1);
                e->setPos(11 * 90 + 100, 90 + 5 * 90);
                scene->addItem(e);
            }
        }
        else
        {
            if (p2 < 4)
            {
                FlyingEnemy1* e = new FlyingEnemy1(2);
                e->setPos(11 * 90 + 100, 90 + 7 * 90);
                scene->addItem(e);
            }
            else if (p2 < 7)
            {
                FlyingEnemy2* e = new FlyingEnemy2(2);
                e->setPos(11 * 90 + 100, 90 + 7 * 90);
                scene->addItem(e);
            }
            else
            {
                FlyingEnemy3* e = new FlyingEnemy3(2);
                e->setPos(11 * 90 + 100, 90 + 7 * 90);
                scene->addItem(e);
            }
        }
        creatednum++;
    }
}

void MainWindow::AddEnemy2()
{
    static int cnt = 0;
    static int ccnt = 0;
    if (creatednum >= MAX_ENEMY_NUM)
        return;

    if (++cnt >= curtime)
    {
        cnt = 0;
        ccnt++;
        if (ccnt % 5 == 0 && curtime > MINTIME)
        {
            curtime -= 10;
            ccnt = 0;
        }
        int p = qrand() % 10;
        int p2 = qrand() % 10;
        if (p < 4)
        {
            if (p2 < 3)
            {
                GroundEnemy1* e = new GroundEnemy1(0);
                e->setPos(11 * 90 + 100, 3 * 90);
                scene->addItem(e);
            }
            else if (p2 < 6)
            {
                GroundEnemy2* e = new GroundEnemy2(0);
                e->setPos(11 * 90 + 100, 3 * 90);
                scene->addItem(e);
            }
            else if (p2 < 8)
            {
                GroundEnemy3* e = new GroundEnemy3(0);
                e->setPos(11 * 90 + 100, 3 * 90);
                scene->addItem(e);
            }
            else
            {
                GroundEnemy4* e = new GroundEnemy4(0);
                e->setPos(11 * 90 + 100, 3 * 90);
                scene->addItem(e);
            }
        }
        else if (p < 7)
        {
            if (p2 < 3)
            {
                GroundEnemy1* e = new GroundEnemy1(2);
                e->setPos(11 * 90 + 100, 90 + 5 * 90);
                scene->addItem(e);
            }
            else if (p2 < 5)
            {
                GroundEnemy2* e = new GroundEnemy2(2);
                e->setPos(11 * 90 + 100, 90 + 5 * 90);
                scene->addItem(e);
            }
            else if (p2 < 7)
            {
                GroundEnemy3* e = new GroundEnemy3(2);
                e->setPos(11 * 90 + 100, 90 + 5 * 90);
                scene->addItem(e);
            }
            else
            {
                GroundEnemy4* e = new GroundEnemy4(2);
                e->setPos(11 * 90 + 100, 90 + 5 * 90);
                scene->addItem(e);
            }
        }
        else
        {
            if (p2 < 4)
            {
                FlyingEnemy1* e = new FlyingEnemy1(1);
                e->setPos(11 * 90 + 100, 90 + 3 * 90);
                scene->addItem(e);
            }
            else if (p2 < 7)
            {
                FlyingEnemy2* e = new FlyingEnemy2(1);
                e->setPos(11 * 90 + 100, 90 + 3 * 90);
                scene->addItem(e);
            }
            else
            {
                FlyingEnemy3* e = new FlyingEnemy3(1);
                e->setPos(11 * 90 + 100, 90 + 3 * 90);
                scene->addItem(e);
            }
        }
        creatednum++;
    }
}

void MainWindow::check()
{
    static int cnt = 0;
    if (++cnt >= 40)
    {
        cnt = 0;
        for (int i = 0; i < 3; i++)
            if (r[i]->isdeath())
            {
                delete timer;
                delete sound;
                scene->addPixmap(QPixmap(":/image/Lose.png"));
                sound = new QSound(":/music/losemusic.wav", this);
                sound->play();
                state = 1;
                return;
            }
        if (killnum >= MAX_ENEMY_NUM)
        {
            delete timer;
            delete sound;
            scene->addPixmap(QPixmap(":/image/Win.png"));
            sound = new QSound(":/music/winmusic.wav", this);
            sound->play();
            state = 1;
        }
    }
}

void MainWindow::Boom()
{
    static int cnt = 0;
    if (++cnt >= 40)
    {
        CherryBomb* c1 = new CherryBomb;
        int x = qrand() % 12, y = qrand() % 8;
        c1->setPos(105 + 90 * x, 100 + y * 90);
        scene->addItem(c1);
        cnt = 0;
    }
}
