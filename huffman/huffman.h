#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <cstring>
#include <string>
#include <queue>
#include <stdlib.h>
#include <iostream>
#include <QString>
using namespace std;
struct tnode* Creatnode(char ch,double fre);
struct tnode* init();
void search(struct tnode* T, QCharRef name,QString &str,bool &flag);
void encode();
QString readcode();
QString readtext();
void decode();

#endif // HUFFMAN_H
