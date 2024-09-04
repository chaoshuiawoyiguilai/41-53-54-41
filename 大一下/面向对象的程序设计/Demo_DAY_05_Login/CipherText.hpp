//
//  CipherText.hpp
//  DEMO_DAY_04_USER_XCODE
//
//  Created by Jingtao Fan on 2021/7/29.
//

#ifndef CipherText_hpp
#define CipherText_hpp
#include <string>
#include <ostream>
using namespace std;

#include "MD5.hpp"

class CipherText : public MD5 {
public:
    CipherText(const string& Plainext);
    bool operator==(const string& Plaintext);
    bool operator!=(const string& Plaintext);
    CipherText operator= (const string& Plaintext);
    friend ostream& operator<<(ostream& stream, const CipherText& CipherText);
    static CipherText MakeFromCipherText(const string& CipherText);
};
//using CipherText = string;


#endif /* CipherText_hpp */
