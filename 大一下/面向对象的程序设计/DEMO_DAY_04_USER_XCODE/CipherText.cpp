//
//  CipherText.cpp
//  DEMO_DAY_04_USER_XCODE
//
//  Created by Jingtao Fan on 2021/7/29.
//
#include <string>
using namespace std;
#include "CipherText.hpp"

CipherText::CipherText(const string& Plainext) : MD5(Plainext){
 
}

bool CipherText::operator==(const string& Plaintext) {
    return m_CipherText == MD5::Encrypt(Plaintext);
}

bool CipherText::operator!=(const string& Plaintext) {
    return !operator==(Plaintext);
}

ostream& operator<<(ostream& stream, const CipherText& CipherText){
    stream << CipherText.m_CipherText;
    return stream;
}

CipherText CipherText::MakeFromCipherText(const string& CipherText){
    class CipherText P1("123");
    P1.m_CipherText = CipherText;
    return P1;
}
