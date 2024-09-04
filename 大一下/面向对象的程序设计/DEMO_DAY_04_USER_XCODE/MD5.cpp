//
//  MD5.cpp
//  DEMO_DAY_04_USER_XCODE
//
//  Created by Jingtao Fan on 2021/7/29.
//
//改写以下链接，版权声明如下
//版权声明：本文为CSDN博主「haroroda」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
//原文链接：https://blog.csdn.net/haroroda/article/details/45935099

#include "MD5.hpp"
#include <stdexcept>
using namespace std;

const char MD5::T_INIT_VALUE[64][8] {
    { 'd', '7', '6', 'a', 'a', '4', '7', '8' },
    { 'e', '8', 'c', '7', 'b', '7', '5', '6' },
    { '2', '4', '2', '0', '7', '0', 'd', 'b' },
    { 'c', '1', 'b', 'd', 'c', 'e', 'e', 'e' },
    { 'f', '5', '7', 'c', '0', 'f', 'a', 'f' },
    { '4', '7', '8', '7', 'c', '6', '2', 'a' },
    { 'a', '8', '3', '0', '4', '6', '1', '3' },
    { 'f', 'd', '4', '6', '9', '5', '0', '1' },
    { '6', '9', '8', '0', '9', '8', 'd', '8' },
    { '8', 'b', '4', '4', 'f', '7', 'a', 'f' },
    { 'f', 'f', 'f', 'f', '5', 'b', 'b', '1' },
    { '8', '9', '5', 'c', 'd', '7', 'b', 'e' },
    { '6', 'b', '9', '0', '1', '1', '2', '2' },
    { 'f', 'd', '9', '8', '7', '1', '9', '3' },
    { 'a', '6', '7', '9', '4', '3', '8', 'e' },
    { '4', '9', 'b', '4', '0', '8', '2', '1' },
    { 'f', '6', '1', 'e', '2', '5', '6', '2' },
    { 'c', '0', '4', '0', 'b', '3', '4', '0' },
    { '2', '6', '5', 'e', '5', 'a', '5', '1' },
    { 'e', '9', 'b', '6', 'c', '7', 'a', 'a' },
    { 'd', '6', '2', 'f', '1', '0', '5', 'd' },
    { '0', '2', '4', '4', '1', '4', '5', '3' },
    { 'd', '8', 'a', '1', 'e', '6', '8', '1' },
    { 'e', '7', 'd', '3', 'f', 'b', 'c', '8' },
    { '2', '1', 'e', '1', 'c', 'd', 'e', '6' },
    { 'c', '3', '3', '7', '0', '7', 'd', '6' },
    { 'f', '4', 'd', '5', '0', 'd', '8', '7' },
    { '4', '5', '5', 'a', '1', '4', 'e', 'd' },
    { 'a', '9', 'e', '3', 'e', '9', '0', '5' },
    { 'f', 'c', 'e', 'f', 'a', '3', 'f', '8' },
    { '6', '7', '6', 'f', '0', '2', 'd', '9' },
    { '8', 'd', '2', 'a', '4', 'c', '8', 'a' },
    { 'f', 'f', 'f', 'a', '3', '9', '4', '2' },
    { '8', '7', '7', '1', 'f', '6', '8', '1' },
    { '6', 'd', '9', 'd', '6', '1', '2', '2' },
    { 'f', 'd', 'e', '5', '3', '8', '0', 'c' },
    { 'a', '4', 'b', 'e', 'e', 'a', '4', '4' },
    { '4', 'b', 'd', 'e', 'c', 'f', 'a', '9' },
    { 'f', '6', 'b', 'b', '4', 'b', '6', '0' },
    { 'b', 'e', 'b', 'f', 'b', 'c', '7', '0' },
    { '2', '8', '9', 'b', '7', 'e', 'c', '6' },
    { 'e', 'a', 'a', '1', '2', '7', 'f', 'a' },
    { 'd', '4', 'e', 'f', '3', '0', '8', '5' },
    { '0', '4', '8', '8', '1', 'd', '0', '5' },
    { 'd', '9', 'd', '4', 'd', '0', '3', '9' },
    { 'e', '6', 'd', 'b', '9', '9', 'e', '5' },
    { '1', 'f', 'a', '2', '7', 'c', 'f', '8' },
    { 'c', '4', 'a', 'c', '5', '6', '6', '5' },
    { 'f', '4', '2', '9', '2', '2', '4', '4' },
    { '4', '3', '2', 'a', 'f', 'f', '9', '7' },
    { 'a', 'b', '9', '4', '2', '3', 'a', '7' },
    { 'f', 'c', '9', '3', 'a', '0', '3', '9' },
    { '6', '5', '5', 'b', '5', '9', 'c', '3' },
    { '8', 'f', '0', 'c', 'c', 'c', '9', '2' },
    { 'f', 'f', 'e', 'f', 'f', '4', '7', 'd' },
    { '8', '5', '8', '4', '5', 'd', 'd', '1' },
    { '6', 'f', 'a', '8', '7', 'e', '4', 'f' },
    { 'f', 'e', '2', 'c', 'e', '6', 'e', '0' },
    { 'a', '3', '0', '1', '4', '3', '1', '4' },
    { '4', 'e', '0', '8', '1', '1', 'a', '1' },
    { 'f', '7', '5', '3', '7', 'e', '8', '2' },
    { 'b', 'd', '3', 'a', 'f', '2', '3', '5' },
    { '2', 'a', 'd', '7', 'd', '2', 'b', 'b' },
    { 'e', 'b', '8', '6', 'd', '3', '9', '1' }
};

const int MD5::M_INIT_VALUE[4][16] {
    { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 },
    { 1, 6, 11, 0, 5, 10, 15, 4, 9, 14, 3, 8, 13, 2, 7, 12 },
    { 5, 8, 11, 14, 1, 4, 7, 10, 13, 0, 3, 6, 9, 12, 15, 2 },
    { 0, 7, 14, 5, 12, 3, 10, 1, 8, 15, 6, 13, 4, 11, 2, 9 }
};

const int MD5::A_INIT_VALUE[2][32] {
    { 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1,
      0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1,
      0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1 }
};

const int MD5::B_INIT_VALUE[2][32] {
    { 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1,
      1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 },
    { 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1,
      1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 }
};

const int MD5::C_INIT_VALUE[2][32]{
    { 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0,
      1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0 },
    { 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0,
      1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0 }
};

const int MD5::D_INIT_VALUE[2][32] ={
    { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0,
      0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0 },
    { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0,
      0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0 }
};

MD5::MD5(const string& PlainText){
    m_CipherText = Process(PlainText);
}

MD5::~MD5(){
}

string MD5::Encrypt(const string& Plaintext){
    MD5 Encryptor(Plaintext);
    return Encryptor.m_CipherText;
}

string MD5::Process(const string& PlainText) const{
    int n{0};
    int i{0};
    int addup;
    int md5[512]{0};
    char t[64][8];
    int m[4][16];
    int a[2][32];
    int b[2][32];
    int c[2][32];
    int d[2][32];
    //初始化
    memcpy(t, T_INIT_VALUE, sizeof(t));
    memcpy(m, M_INIT_VALUE, sizeof(m));
    memcpy(a, A_INIT_VALUE, sizeof(a));
    memcpy(b, B_INIT_VALUE, sizeof(b));
    memcpy(c, C_INIT_VALUE, sizeof(c));
    memcpy(d, D_INIT_VALUE, sizeof(d));

    if (PlainText.length() > 56) {
        throw invalid_argument("需加密的明文长度不可以大于56");
    }
    //ASCII码值向二进制转换
    unsigned long long  StrLen = PlainText.length();
    for(n = 0; n < StrLen; n++) {
        DecToBin(PlainText[n], n, md5);
    }
    i = 0;
    addup = n;
    //长度不是4的倍数，补一个1和0直到长度为4的倍数,，最终实现用1与0使其长度模512与448同于，在这个程序里也就是448
    while (n % 4 != 0 && n < 56) {
        int s, w, j;
        s = n / 4 + 1;
        w = n % 4;
        j = 1;
        do {
            md5[32 * s - 8 * w - j] = 0;
            j++;
        } while (j<=7);
        if (i == 0) {
            md5[32 * s - 8 * w - j] = 1;
            i = 1;
        }
        n++;
    }
    //长度不是4的倍数，补一个1和31个0
    if (i == 0) {
        for (int j = 0; j < 32; j++) {
            md5[n * 8 + j] = 0;
        }
        md5[8 * n + 24] = 1;
    }
    //补零，任何不为1的数都设为0
    for (i = 0; i < 512; i++) {
        if (md5[i] != 1) {
            md5[i] = 0;
        }
    }
    //64位数填充
    DecToBin_Coefficient(addup * 8, md5);
    /* 第一、二、三、四大轮，每一大轮下有16小轮 */
    round(a[0], b[0], c[0], d[0], m[0], md5, 1, t);
    round(a[0], b[0], c[0], d[0], m[1], md5, 2, t + 16);
    round(a[0], b[0], c[0], d[0], m[2], md5, 3, t + 32);
    round(a[0], b[0], c[0], d[0], m[3], md5, 4, t + 48);
    // 最终的a、b、c、d分别与最初的a、b、c、d相加
    ADD(a[0], a[1], a[0]);
    ADD(b[0], b[1], b[0]);
    ADD(c[0], c[1], c[0]);
    ADD(d[0], d[1], d[0]);
    //密文生成
    return c_out(a[0]) + c_out(b[0]) + c_out(c[0]) +c_out(d[0]);

}

/*十进制转二进制函数*/
void MD5::DecToBin(int in, int n, int* md5) const
{
    int j, s, w;
    s = n / 4 + 1;  //s是md5里面组的排位数，w是该组里面的位数
    w = n % 4;
    j = 1;
    do
    {
        md5[32 * s - 8 * w - j] = in % 2;
        in = in / 2;
        j++;
    } while (in != 0);
    while (j <=8)  //二进制不够八位时补零
    {
        md5[32 * s - 8 * w - j] = 0;
        j++;
    }
}

/* 位数填充时所用到的十进制转二进制函数 */
void MD5::DecToBin_Coefficient(int in, int* md5) const
{
    int i,j,temp, a[64];
    for (i = 0; in!= 0; i++)
    {
        a[i] = in % 2;
        in = in / 2;
    }
    while (i % 8 != 0)  //二进制位数不够八的整数倍时补零
    {
        a[i] = 0;
        i++;
    }
    for (j = 0; j <i/2; j++)
    {
        temp = a[i - j - 1];
        a[i - j-1] = a[j];
        a[j] = temp;
        
    }
    temp = i/8;
    for (i=i-1; i < 64; i++)
        a[i] = 0;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 8; j++)
            md5[512 - temp * 8 + j - 32] = a[i * 8 + j];
        temp = temp - 1;
    }
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 8; j++)
            md5[512 - (i + 1) * 8 + j ] = a[i * 8 + j+32];
    }
}

/* 十六进制转二进制函数 */
void MD5::HexToBin(char* t, int* temp) const
{
    int i;
    for (i = 0; i < 8; i++)
    {
        switch (t[i])
        {
            case '0':{temp[4 * i] = 0; temp[4 * i + 1] = 0; temp[4 * i + 2] = 0; temp[4 * i + 3] = 0; }break;
            case '1':{temp[4 * i] = 0; temp[4 * i + 1] = 0; temp[4 * i + 2] = 0; temp[4 * i + 3] = 1; }break;
            case '2':{temp[4 * i] = 0; temp[4 * i + 1] = 0; temp[4 * i + 2] = 1; temp[4 * i + 3] = 0; }break;
            case '3':{temp[4 * i] = 0; temp[4 * i + 1] = 0; temp[4 * i + 2] = 1; temp[4 * i + 3] = 1; }break;
            case '4':{temp[4 * i] = 0; temp[4 * i + 1] = 1; temp[4 * i + 2] = 0; temp[4 * i + 3] = 0; }break;
            case '5':{temp[4 * i] = 0; temp[4 * i + 1] = 1; temp[4 * i + 2] = 0; temp[4 * i + 3] = 1; }break;
            case '6':{temp[4 * i] = 0; temp[4 * i + 1] = 1; temp[4 * i + 2] = 1; temp[4 * i + 3] = 0; }break;
            case '7':{temp[4 * i] = 0; temp[4 * i + 1] = 1; temp[4 * i + 2] = 1; temp[4 * i + 3] = 1; }break;
            case '8':{temp[4 * i] = 1; temp[4 * i + 1] = 0; temp[4 * i + 2] = 0; temp[4 * i + 3] = 0; }break;
            case '9':{temp[4 * i] = 1; temp[4 * i + 1] = 0; temp[4 * i + 2] = 0; temp[4 * i + 3] = 1; }break;
            case 'a':{temp[4 * i] = 1; temp[4 * i + 1] = 0; temp[4 * i + 2] = 1; temp[4 * i + 3] = 0; }break;
            case 'b':{temp[4 * i] = 1; temp[4 * i + 1] = 0; temp[4 * i + 2] = 1; temp[4 * i + 3] = 1; }break;
            case 'c':{temp[4 * i] = 1; temp[4 * i + 1] = 1; temp[4 * i + 2] = 0; temp[4 * i + 3] = 0; }break;
            case 'd':{temp[4 * i] = 1; temp[4 * i + 1] = 1; temp[4 * i + 2] = 0; temp[4 * i + 3] = 1; }break;
            case 'e':{temp[4 * i] = 1; temp[4 * i + 1] = 1; temp[4 * i + 2] = 1; temp[4 * i + 3] = 0; }break;
            case 'f':{temp[4 * i] = 1; temp[4 * i + 1] = 1; temp[4 * i + 2] = 1; temp[4 * i + 3] = 1; }break;
        }
    }
}

/* 密文输出函数 */
string MD5::c_out(int* a) const
{
    int i,add;
    string Res{};
    //二进制转换成十六进制输出
    for (i = 1; i <= 4; i++) {
        add = a[32 - i * 8] * 8 + a[32 - i * 8 + 1] * 4 + a[32 - i * 8 + 2] * 2 + a[32 - i * 8 + 3];
        if (add >= 10) {
            Res += string(1, 'A' + add - 10);
        }
        else{
            Res += string(1, '0' + add);
        }
        add = a[32 - i * 8+4] * 8 + a[32 - i * 8 + 5] * 4 + a[32 - i * 8 + 6] * 2 + a[32 - i * 8 + 7];
        if (add >= 10) {
            Res += string(1, 'A' + add - 10);
        }
        else {
            Res += string(1, '0' + add);
        }
    }
    return Res;
}


/* 与函数 */
void MD5::AND(int* a, int* b,int* temp) const
{
    int i;
    for (i = 0; i < 32; i++)  //同为1为1，否则为0
    {
        if (a[i] == 1 && b[i] == 1)
            temp[i] = 1;
        else
            temp[i] = 0;
    }
}

/* 或函数 */
void MD5::OR(int* a, int* b, int* temp) const
{
    int i;
    for (i = 0; i < 32; i++)  //同0为0，否则为1
    {
        if (a[i] == 0 && b[i] == 0)
            temp[i] = 0;
        else
            temp[i] = 1;
    }
}

/* 非函数 */
void MD5::NOT(int* a, int* temp) const
{
    int i;
    for (i = 0; i < 32; i++)
    {
        if (a[i] == 0)
            temp[i] = 1;
        else
            temp[i] = 0;
    }
}

/*异或函数*/
void MD5::XOR(int* a, int* b, int* temp) const
{
    int i;
    for (i = 0; i < 32; i++)  //相同为0，不同为1
    {
        if (a[i] != b[i])
            temp[i] = 1;
        else
            temp[i] = 0;
    }
}

/* 模二的32次加 */
void MD5::ADD(int* a, int* b, int* temp) const
{
    int i,jin;
    jin = 0;
    for (i = 0; i < 32; i++)
    {
        if (a[31 - i] + b[31 - i] + jin>1)
        {
            temp[31 - i] = a[31 - i] + b[31 - i] + jin - 2;
            jin = 1;
        }
        else
        {
            temp[31 - i] = a[31 - i] + b[31 - i]+jin;
            jin = 0;
        }
    }
}

/* F函数 */
void MD5::F(int* b, int* c, int* d,int* temp1,int* temp2) const
{
    /* F(x,y,z)=(x∧y)∨(¬x∧z) */
    AND(b, c, temp1);
    NOT(b, temp2);
    AND(temp2, d, temp2);
    OR(temp1, temp2, temp2);
}

/* G函数 */
void MD5::G(int* b, int* c, int* d, int* temp1, int* temp2) const
{
    /* G(x,y,z)=(x∧z)∨(y∧¬z) */
    AND(b, d, temp1);
    NOT(d, temp2);
    AND(temp2, c, temp2);
    OR(temp1, temp2, temp2);
}

/* H函数 */
void MD5::H(int* b, int* c, int* d, int* temp) const
{
    /* H(x,y,z)=x⊕y⊕z */
    XOR(b, c, temp);
    XOR(temp, d, temp);
}

/* I函数 */
void MD5::I(int* b, int* c, int* d, int* temp) const
{
    /* I(x,y,z)=y⊕(x∨¬z) */
    NOT(d, temp);
    OR(b, temp, temp);
    XOR(c, temp, temp);
}

/*左移函数*/
void MD5::move(int step, int* temp1, int* temp2) const
{
    int i;
    for (i = 0; i < 32 - step; i++)
        temp2[i] = temp1[i + step];
    for (i = 0; i < step; i++)
        temp2[32 - step + i] = temp1[i];
}

/*每一大轮的16小轮循环函数*/
void MD5::round(int* a, int* b, int* c, int* d, int* m, int* md5, int r, char t[16][8]) const
{
    int i, j, in, step = 0 , temp1[32], temp2[32];
    for (i = 0; i < 16; i++)
    {
        switch (r)  //根据r判断所选的逻辑函数
        {
            case 1:F(b, c, d, temp1, temp2); break;
            case 2:G(b, c, d, temp1, temp2); break;
            case 3:H(b, c, d, temp2); break;
            case 4:I(b, c, d, temp2); break;
        }
        in = m[i];
        for (j = 0; j < 32; j++)
            temp1[j] = md5[in * 32 + j];
        ADD(temp2, temp1, temp2);
        HexToBin(t[i], temp1);
        ADD(temp2, temp1, temp2);
        ADD(temp2, a, temp2);
        switch(r)  //根据r为左移步数step赋值
        {
            case 1:switch (i % 4 + 1){ case 1:step = 7; break; case 2:step = 12; break; case 3:step = 17; break; case 4:step = 22; break; }break;
            case 2:switch (i % 4 + 1){ case 1:step = 5; break; case 2:step = 9; break; case 3:step = 14; break; case 4:step = 20; break; }break;
            case 3:switch (i % 4 + 1){ case 1:step = 4; break; case 2:step = 11; break; case 3:step = 16; break; case 4:step = 23; break; }break;
            case 4:switch (i % 4 + 1){ case 1:step = 6; break; case 2:step = 10; break; case 3:step = 15; break; case 4:step = 21; break; }break;
        }
        move(step, temp2, temp1);
        ADD(temp1, b, temp2);
        for (j = 0; j < 32; j++)
        {
            a[j] = d[j];
            d[j] = c[j];
            c[j] = b[j];
            b[j] = temp2[j];
        }
    }
}
