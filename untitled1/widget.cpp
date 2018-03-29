#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QString str=ui->lineEdit->text();//
    int a= str.toInt();
    QString str2=ui->lineEdit_2->text();

    QString str3=ui->lineEdit_3->text();
    int b=str3.toInt();
    int c=0;
    if(str2=="+"){
        c=a+b;
    }

    if(str2=="-")
        c=a-b;
    if(str2=="*")
        c=a*b;
    if(str2=="/"){
        if(b!=0){
            c=a/b;
        }
    }
    ui->label->setText(QString::number(c));

}
