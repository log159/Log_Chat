#include "galdialog.h"
#include "ui_galdialog.h"
#include <QDebug>
#include <QMouseEvent>


GalDialog::GalDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GalDialog)
{
    ui->setupUi(this);
    /*无边框设置*/
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    setWindowOpacity(0.8);
    /*内容初始化*/
    ui->pushButton->hide();
    ui->label_name->setText("你");
}

GalDialog::~GalDialog()
{
    delete ui;
}

/*信息交互相关*/
/*键盘相关事件*/
void GalDialog::keyReleaseEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Return)
    {
        emit signal_send_data_from_gal_to_main(ui->textEdit->toPlainText()); //获取lineEdit的输入并且传递到主界面
        ui->label_name->setText("她");
        ui->textEdit->setText("...");
        ui->textEdit->setEnabled(false);

    }
}
//接受信息
void GalDialog::slots_receive_data_from_widget_to_gal(QString data)
{
    qDebug()<<"Gal接受到来自Widget信息————>"<<data; //获取传递过来的数据
    ui->textEdit->setEnabled(true);
    ui->pushButton->show();
    ui->textEdit->setText(data);
}
//继续输入
void GalDialog::on_pushButton_clicked()
{
    ui->pushButton->hide();
    ui->textEdit->clear();
    ui->label_name->setText("你");
}


/*无边框相关*/
//三个鼠标事件的重写
//鼠标按下事件
void GalDialog::mousePressEvent(QMouseEvent *event)
{
    switch(event->button())
    {
    case Qt::LeftButton:
        isLeftPressDown = true;
        this->mouseGrabber(); //返回当前抓取鼠标输入的窗口
        m_movePoint = event->globalPos() - this->frameGeometry().topLeft();
        //globalPos()鼠标位置，topLeft()窗口左上角的位置
        break;
    case Qt::RightButton:
        this->destroy();
        break;
    default:
        GalDialog::mousePressEvent(event);
    }
}
//鼠标移动事件
void GalDialog::mouseMoveEvent(QMouseEvent *event)
{
    if(isLeftPressDown)  //没有按下左键时
    {
        move(event->globalPos() - m_movePoint); //移动窗口
        event->accept();
    }
}
//鼠标释放事件
void GalDialog::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        isLeftPressDown = false;
        this->releaseMouse(); //释放鼠标抓取
        this->setCursor(QCursor(Qt::ArrowCursor));
    }
}



