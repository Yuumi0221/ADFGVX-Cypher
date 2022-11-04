#ifndef ADGFVXALGO_H
#define ADGFVXALGO_H
#include "string"
#include "vector"
#include "map"
#include "algorithm"

using namespace std;

class ADGFVXalgo
{
private:
    string enInput;
    string deInput;
    string ADGFVXinput;
    string CARGOinput;
    string cypher;

public:
    ADGFVXalgo(string cargo);   //构造函数
    void encrypt();     // 加密操作
    void decrypt();     // 解密操作
    void setMessage(string str);    // 设置明文
    void setCypher(string str);     // 设置密文
    void setCargo(string str);      // 设置密钥
    void setADGFVXinput(string str);    // 设置密码表
    string getCypher();     // 获取密文
    string getMessage();    // 获取明文
};

#endif // ADGFVXALGO_H
