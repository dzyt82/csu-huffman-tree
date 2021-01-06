#include "huffman.h"
#include <QFile>
#include <QTextStream>

#define NULL 0
struct tnode
{
    double fre;
    char name;
    tnode* lchild;
    tnode* rchild;
    bool operator<(const tnode& a)const
    {
        return fre  > a.fre;
    }
};
struct tnode* head=NULL;
bool therearetree=false;
priority_queue<struct tnode>q;
class huffman
{
public:
    huffman();

};
struct tnode* Creatnode(char ch,double fre)
{
    struct tnode* T;
    //getchar();
    T = (struct tnode*)malloc(sizeof(tnode));
    T->name = ch;
    T->fre = fre;
    T->lchild = NULL;
    T->rchild = NULL;
    q.push(*T);

    return (T);
}
struct tnode* creat()
{
    struct tnode* T;
    //char ch;
    //float fre;
    T = (struct tnode*)malloc(sizeof(tnode));
    T->name = 0;
    T->fre = 0;
    T->lchild = NULL;
    T->rchild = NULL;
    return(T);
}
struct tnode* init()
{
    struct tnode* T=NULL;
    while (q.size()!=1)
    {
        struct tnode *a,*b;
        struct tnode x, y;
        a = creat();
        b = creat();
        x = q.top(); q.pop();
        y = q.top(); q.pop();
        *a = x;
        *b = y;
        T = (struct tnode*)malloc(sizeof(tnode));
        T->lchild = a;
        T->rchild = b;
        T->name = 0;
        T->fre = a->fre + b->fre;
        q.push(*T);
    }
    head=T;
    therearetree=true;

    return T;
}
void search(struct tnode* T, QCharRef name,QString &str,bool &flag)//i是层数，cod为字符的编码
{
    if (flag)
        return;
    if (T->name == name)
    {
        flag=1;
        return;
    }
    if (T->lchild != NULL)
    {
        if (flag)
            return;
        str.append("0");
        search(T->lchild, name, str,flag);
        if(!flag)
            str.chop(1);
    }
    if (T->rchild != NULL)
    {
        if (flag)
            return;
        str.append("1");
        search(T->rchild, name, str,flag);
        if(!flag)
            str.chop(1);
    }
}
void writetree(QString tmp)
{
    QFile tobewrite("D:/huffman/htmTree.txt");
    tobewrite.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream ou(&tobewrite);
    ou<<tmp;
    tobewrite.close();
}
void read()
{
    QFile htm("D:/huffman/htmTree.txt");
    htm.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&htm);
    QString N=in.readLine();
    int n=N.toInt();
    QString tmp;
    while(n--)
    {
        tmp=in.readLine();
        QStringList ans=tmp.split(" ");
        string alp1=ans[0].toStdString();
        char alp=alp1[0];
        double fre=ans[1].toDouble();
        Creatnode(alp,fre);
    }
    init();
    htm.close();
}

void encode()//编码
{
    if(!therearetree)
    {
        read();
    }
    struct tnode* T=head;
    QFile file("D:/huffman/ToBeTran.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    QString str=in.readLine();//读取一行
    QString cod;
    for(int i=0;i<str.size();i++)
       {bool flag=0;search(T, str[i], cod,flag);}
    QFile tobewrite("D:/huffman/CodeFile.txt");
    tobewrite.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream ou(&tobewrite);
    ou<<cod;
    file.close();
    tobewrite.close();
}
QString readcode()
{
    QString fileName = "D:/huffman/CodeFile.txt";QString str;QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);str=in.readLine();
    for(int i=1;i*50<=str.size();i++)
    {
        str.insert(i*50-1,QString("\n"));
    }
    QFile tobewrite("D:/huffman/CodePrint.txt");
    tobewrite.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream ou(&tobewrite);
    ou<<str;
    tobewrite.close();
    file.close();
    return str;
}
QString readtext()
{
    QString fileName = "D:/huffman/TextFile.txt";QString str;QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);str=in.readLine();
    file.close();
    return str;
}
void decode()//译码
{
    struct tnode* T=head;
    QString fileName = "D:/huffman/CodeFile.txt";QString str;QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);str=in.readLine();
    freopen("TextFile.txt", "w", stdout);
    struct tnode* P = T;
    QString towrite;
    for(int i=0;i<str.size();i++)
    {
        if (P->lchild == NULL)
        {
            towrite.append(P->name);
            P = T;
            i--;
            continue;
        }
        if (str[i] == '0')
            P = P->lchild;
        else
            P = P->rchild;
    }
    QFile tobewrite("D:/huffman/TextFile.txt");
    tobewrite.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream ou(&tobewrite);
    ou<<towrite;
    file.close();
    tobewrite.close();
}
/*huffman::huffman()
{

}*/
