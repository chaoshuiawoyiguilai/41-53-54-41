//
//  MD5.hpp
//  DEMO_DAY_04_USER_XCODE
//
//  Created by Jingtao Fan on 2021/7/29.
//
//改写以下链接，版权声明如下
//版权声明：本文为CSDN博主「haroroda」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
//原文链接：https://blog.csdn.net/haroroda/article/details/45935099
#ifndef MD5_hpp
#define MD5_hpp

#include <string>
using namespace std;
class MD5 {
public:
    MD5(const string& PlainText);
    MD5() = delete;
    virtual ~MD5();
    static string Encrypt(const string& Plaintext);
protected:
    string Process(const string& PlainText) const;
    string m_CipherText;
private:
    string c_out(int* a) const;
    void DecToBin(int in, int n, int* md5) const;
    void DecToBin_Coefficient(int in, int* md5) const;
    void HexToBin(char* t, int* temp) const;
    void F(int* b, int* c, int* d, int* temp1, int* temp2) const;
    void G(int* b, int* c, int* d, int* temp1, int* temp2) const;
    void H(int* b, int* c, int* d, int* temp) const;
    void I(int* b, int* c, int* d, int* temp) const;
    void AND(int* a, int* b, int* temp) const;
    void OR(int* a, int* b, int* temp) const;
    void NOT(int* a, int* temp) const;
    void XOR(int* a, int* b, int* temp) const;
    void ADD(int* a, int* b, int* temp) const;
    void move(int step, int* temp1, int* temp2) const;
    void round(int* a, int* b, int* c, int* d, int* m, int* md5, int r, char t[16][8]) const;
    
    static const char T_INIT_VALUE[64][8];
    static const int  M_INIT_VALUE[4][16];
    static const int  A_INIT_VALUE[2][32];
    static const int  B_INIT_VALUE[2][32];
    static const int  C_INIT_VALUE[2][32];
    static const int  D_INIT_VALUE[2][32];
};
#endif /* MD5_hpp */
