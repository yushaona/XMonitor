#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    initData();
    ui->setupUi(this);
    /*
    Qt::WindowStaysOnTopHint
    Qt::WA_Hover
    */

    this->setAttribute(Qt::WA_TranslucentBackground, true); //整个窗口透明，但是控件不会跟着透明,用来做异形窗口
    this->setAttribute(Qt::WA_Hover, true);
    /*
     setWindowFlags(windowFlags() | Qt::X11BypassWindowManagerHint);
     取消置顶：
     setWindowFlags(windowFlags() &~ Qt::BypassWindowManagerHint);
    */
    this->setWindowFlags(Qt::X11BypassWindowManagerHint | Qt::FramelessWindowHint | Qt::Tool | windowFlags());//去除边框
    this->setAttribute(Qt::WA_QuitOnClose); //最后一个窗口hide的时候，整个进程自动全部结束
    this->resize(QSize(330, 41));
    this->setWindowOpacity(1.0);
    move(300,300);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::initData()
{
    setBGImage();
}

void MainWidget::setBGImage(int flag)
{
    bgimage = QImage(QString(":/bgimage/skins/0%1/background.bmp").arg(flag));
}

void MainWidget::drawBGImage(QPainter *painter)
{
    painter->save();
    qreal x = (width() - bgimage.width()) * 0.5;
    qreal y = (height() - bgimage.height()) * 0.5;
    painter->drawImage(QPoint(x, y),bgimage);
    painter->restore();
}

void MainWidget::paintEvent(QPaintEvent *event)
{
    qDebug() << "begin:paintEvent";
    QPainter painter(this);
    //绘制准备工作,启用反锯齿,启用图片平滑缩放
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    //绘制背景
    drawBGImage(&painter);

    qDebug() << "end:paintEvent";
}

