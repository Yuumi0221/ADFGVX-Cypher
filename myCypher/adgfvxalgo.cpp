#include "adgfvxalgo.h"

ADGFVXalgo::ADGFVXalgo(string cargo)
{
    this->ADGFVXinput = "xyzdefghiklmnopqrstuvwcba0123456789j";
    if(cargo.empty())
        this->CARGOinput = "CARGO";
    else
        this->CARGOinput = cargo;
}

void ADGFVXalgo::encrypt() {
    vector<char> input;         // 明文
    vector<char> ADGFVXtable;   // 密码表
    input.assign(enInput.begin(), enInput.end());
    ADGFVXtable.assign(ADGFVXinput.begin(), ADGFVXinput.end());

    // 建表
    multimap<char, pair<char, char>> table;
    char charList[6] = {'A', 'D', 'F', 'G', 'V', 'X'};
    int i=0, j=0, pos=0;
    for(i = 0; i < 6; i++) {
        for(j = 0; j < 6; j++) {
            table.insert({ADGFVXtable[pos], {charList[i], charList[j]}});
            pos++;
        }
    }

    // polybius密码
    vector<char> midCypher;
    for (auto alpha: input){
        auto iter = table.find(alpha);
        midCypher.push_back(iter->second.first);
        midCypher.push_back(iter->second.second);
    }

    // 置换密码
    cypher.clear();     // 清空输入输出
    if (midCypher.size()%CARGOinput.length() == 0) {    // 置换表格可以填满
        string str = CARGOinput;
        sort(str.begin(), str.end());
        pos = 0;
        for (auto ch: str){
            pos = CARGOinput.find(ch);
            for (i=0; i < midCypher.size()/CARGOinput.length(); i++)
                cypher.push_back(midCypher[i * CARGOinput.length() + pos]);
//                cout << cypher[i*CARGO.length() + pos];
        }
    } else {    // 置换表格不能填满
        int remainder = midCypher.size()%CARGOinput.length();
        string str = CARGOinput;
        sort(str.begin(), str.end());
        pos = 0;
        for (auto ch: str){
            pos = CARGOinput.find(ch);
            if (pos < remainder)
                for (i=0; i < midCypher.size()/CARGOinput.length()+1; i++)
                    cypher.push_back(midCypher[i * CARGOinput.length() + pos]);
//                    cout << cypher[i*CARGO.length() + pos];
            else
                for (i=0; i < midCypher.size()/CARGOinput.length(); i++)
                    cypher.push_back(midCypher[i * CARGOinput.length() + pos]);
//                    cout << cypher[i*CARGO.length() + pos];
        }
    }
}

void ADGFVXalgo::decrypt() {
    //类型转换
    vector<char> input;         // 密文
    vector<char> ADGFVXtable;   // 密码表
    input.assign(cypher.begin(), cypher.end());
    ADGFVXtable.assign(ADGFVXinput.begin(), ADGFVXinput.end());

    // 建表
    multimap<pair<char, char>, char> table;
    char charList[6] = {'A', 'D', 'F', 'G', 'V', 'X'};
    int i=0, j=0, pos=0;
    for(i=0; i<6; i++) {
        for(j=0; j<6; j++) {
            table.insert({{charList[i], charList[j]}, ADGFVXtable[pos]});
            pos++;
        }
    }

    // 置换解密
    vector<char> midCypher;
    if (cypher.size()%CARGOinput.length() == 0) {
        string str = CARGOinput;
        sort(str.begin(), str.end());
        pos = 0;
        for (i=0; i<cypher.size()/CARGOinput.length(); i++){
            for (auto ch: CARGOinput){
                pos = str.find(ch);
                midCypher.push_back(cypher[pos * (cypher.size()/CARGOinput.length()) + i]);
            }
        }
    } else {
        int remainder = cypher.size()%CARGOinput.length();
        string str = CARGOinput;
        sort(str.begin(), str.end());
        pos = 0;
        vector<int> temp;
        for (i=0; i<remainder; i++) {
            pos = str.find(CARGOinput[i]);
            temp.push_back(pos);
        }
        for (i=0; i<CARGOinput.length(); i++){
            if (find(temp.begin(), temp.end(), i) != temp.end())
                continue;
            input.insert(input.begin() + (i * (cypher.size()/CARGOinput.length()+1)) + cypher.size()/CARGOinput.length(), '0');
        }
        for (i=0; i<input.size()/CARGOinput.length(); i++){
            for (auto ch: CARGOinput){
                pos = str.find(ch);
                char tempChar = input[pos * (input.size()/CARGOinput.length()) + i];
                if (tempChar == '0') continue;
                else    midCypher.push_back(tempChar);
            }
        }
    }

    // polybius解密
    enInput.clear();
    vector<char> output;
    for (i=0; i<midCypher.size(); i+=2){
        auto iter = table.find({midCypher[i], midCypher[i+1]});
        output.push_back(iter->second);
    }
    for (auto ch: output)
        enInput.push_back(ch);
}

void ADGFVXalgo::setMessage(std::string str) {
    this->enInput = str;
}

void ADGFVXalgo::setCypher(std::string str) {
    this->cypher = str;
}

void ADGFVXalgo::setCargo(std::string str) {
    this->CARGOinput = str;
}

void ADGFVXalgo::setADGFVXinput(std::string str) {
    this->ADGFVXinput = str;
}

string ADGFVXalgo::getCypher() {
    return this->cypher;
}

string ADGFVXalgo::getMessage() {
    return this->enInput;
}
