#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "huffman.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QPushButton qb1= ui->pushButton;
    //connect()
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    bool isok;
    QString n1= QInputDialog::getText(this, "选择字母个数",
                                     "请输入字母个数",
                                     QLineEdit::Normal,
                                     "5");
    int n=n1.toInt();
    QString alp,fre;
    QString tmp;
    tmp.append(QString(QString::number(n)+"\n"));
    while(n--)
    {
        alp = QInputDialog::getText(this, "建立一个新节点",
                                                       "请输入字母",
                                                       QLineEdit::Normal,
                                                       "a",
                                                       &isok);
        tmp.append(QString(alp+" "));
    if(isok){
        fre = QInputDialog::getText(this, "建立一个新节点",
                                                           "请输入对应的频率",
                                                           QLineEdit::Normal,
                                                           "0.01",
                                                           &isok);
        tmp.append(QString(fre+"\n"));
    }
    writetree(tmp);
    string s=alp.toStdString();
    Creatnode(s[0],fre.toDouble());
    }
    init();

}

void MainWindow::on_pushButton_2_clicked()
{
    encode();
    QMessageBox::information(this,"成功","已经成功写入codefile");
}

void MainWindow::on_pushButton_3_clicked()
{
    QString s=readcode();

    QMessageBox::information(this,"Codefile",s);
}

void MainWindow::on_pushButton_4_clicked()
{
    decode();
}

void MainWindow::on_pushButton_5_clicked()
{
    QString s=readtext();
    QMessageBox::information(this,"TextFile",s);
}
