#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <fstream>
using namespace std;

map<string, int> K = {{"int",1},{"char",2},{"float",3},{"double",4},{"long",5},{"if",6},{"for",7},
                     {"while",8},{"break",9},{"continue",10},{"return",11},{"case",12},{"default",13},{"else",14}};
map<string, int> P = {{"+", 1},{"-",2},{"*",3},{"/",4},{"=",5},{"(",6},{")",7},{"{",8},
                     {"}",9},{"==",10},{"!=",11},{">",12},{">=",13},{"<",14},{"<=",15},{",",16},
                     {";",17}};
map<string, int> I, C1, C2, CT, ST;
vector<pair<string, int>> print_I, print_C1, print_C2, print_CT, print_ST;
vector<pair<string, int>> token;

struct Node{
    string op;
    string num1, num2;
    string res;
    Node(string op, string num1, string num2, string res){
        this->op = op;
        this->num1 = num1;
        this->num2 = num2;
        this->res = res;
    }
    Node(const Node& other){
        this->op = other.op;
        this->num1 = other.num1;
        this->num2 = other.num2;
        this->res = other.res;
    }
};

vector<Node> QT;
stack<string> SEM;
int QT_index = 1;

void state_change(int &state, char ch){
    if(state == 1){
        if(ch=='_' || (ch>='a' && ch<='z') || (ch>='A' && ch<='Z')) state = 2;
        else if(ch=='0') state = 3;
        else if(ch>='0' && ch<='9') state = 5;
        else if(ch=='\'')   state = 11;
        else if(ch=='\"')   state = 14;
        else if(ch=='>')    state = 17;
        else if(ch=='<')    state = 19;
        else if(ch=='=')    state = 21;
        else if(ch=='+')    state = 23;
        else if(ch=='-')    state = 25;
        else if(ch=='/')    state = 27;
        else if(ch=='(')    state = 28;
        else if(ch==')')    state = 29;
        else if(ch=='*')    state = 30;
        else if(ch==',')    state = 31;
        else if(ch==';')    state = 32;
        else if(ch=='{')    state = 33;
        else if(ch=='}')    state = 34;
    }
    else if(state == 2){
        if(ch=='_' || (ch>='a' && ch<='z') || (ch>='A' && ch<='Z') || (ch>='0' && ch<='9')) state = 2;
        else state = 0;
    }
    else if(state == 3){
        if(ch=='x' || ch=='X') state = 4;
        else if(ch=='.')    state = 6;
        else if(ch=='e' || ch=='E') state = 8;
        else state = 0;
    }
    else if(state == 4){
        if((ch>='0' && ch<='9') || (ch>='a' && ch<='f') || (ch>='A' && ch<='F')) state = 4;
        else    state = 0;
    }
    else if(state == 5){
        if(ch>='0' && ch<='9') state = 5;
        else if(ch=='.')    state = 6;
        else if(ch=='e' || ch=='E') state = 8;
        else state = 0;
    }
    else if(state == 6){
        if(ch>='0' && ch<='9') state = 7;
        else state = -1;
    }
    else if(state == 7){
        if(ch>='0' && ch<='9') state = 7;
        else if(ch=='e' || ch=='E') state = 8;
        else state = 0;
    }
    else if(state == 8){
        if(ch>='0' && ch<='9') state = 9;
        else if(ch=='+' || ch=='-') state = 10;
        else state = -1;
    }
    else if(state==9){
        if(ch>='0' && ch<='9') state = 9;
        else state = 0;
    }
    else if(state==10){
        if(ch>='0' && ch<='9') state = 9;
        else state = -1;
    }
    else if (state == 11){
        if(ch=='\'') state = 13;
        else    state = 12;
    }
    else if(state == 12){
        if(ch=='\'') state = 13;
        else state = -1;
    }
    else if (state == 14){
        if(ch=='\"') state = 16;
        else state = 15;
    }
    else if(state == 15){
        if(ch=='\"') state = 16;
        else state = 15;
    }
    else if(state == 17){
        if(ch=='=') state = 18;
        else state = 0;
    }
    else if(state == 19){
        if(ch=='=') state = 20;
        else state = 0;
    }
    else if(state == 21){
        if(ch=='=') state = 22;
        else state = 0;
    }
    else if(state == 23){
        if(ch=='+') state = 24;
        else state = 0;
    }
    else if(state == 25){
        if(ch=='-') state = 26;
        else state = 0;
    }
    else{
        state = 0;
    }
}

void show_token()
{
    cout << "Token :";
    for (auto x : token)    cout << "(" << x.first << " " << x.second << ")";
    cout << endl;
    cout << "I :";
    if (print_I.size() > 0){
        auto p = print_I.begin();
        cout << p->first;
        p++;
        while (p != print_I.end()){
            cout << " " << p->first;
            p++;
        }
    }
    cout << endl;
    cout << "C1 :";
    if (print_C1.size() > 0){
        auto p = print_C1.begin();
        cout << p->first;
        p++;
        while (p != print_C1.end()){
            cout << " " << p->first;
            p++;
        }
    }
    cout << endl;
    cout << "C2 :";
    if (print_C2.size() > 0){
        auto p = print_C2.begin();
        cout << p->first;
        p++;
        while (p != print_C2.end()){
            cout << " " << p->first;
            p++;
        }
    }
    cout << endl;
    cout << "CT :";
    if (print_CT.size() > 0){
        auto p = print_CT.begin();
        cout << p->first;
        p++;
        while (p != print_CT.end()){
            cout << " " << p->first;
            p++;
        }
    }
    cout << endl;
    cout << "ST :";
    if (print_ST.size() > 0){
        auto p = print_ST.begin();
        cout << p->first;
        p++;
        while (p != print_ST.end()){
            cout << " " << p->first;
            p++;
        }
    }
    cout << endl;
}


void nextw(int &i){
    i++;
}
bool func_define(int &i);
bool func_name(int &i);
bool param_list(int &i);
bool com_sentence(int &i);
bool sentence_table(int &i);
bool sentence(int &i);
bool declare_sentence(int &i);
bool exp_sentence(int &i);
bool eva_sentence(int &i);
bool arithmetic_exp(int &i);
bool type_def(int &i);
bool relate_exp(int &i);
bool E(int &i);
bool T(int &i);
bool F(int &i);


bool func_define(int &i)  // 函数定义
{
    if (!type_def(i))   return false;
    if (!func_name(i))  return false;
    if (token[i].first == "P" && token[i].second == 6){
        nextw(i);
        if (!param_list(i)) return false;
        if (token[i].first == "P" && token[i].second == 7){
            nextw(i);
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
    if (!com_sentence(i)) return false;
    return true;
}

bool func_name(int &i)    // 函数名
{
    if (token[i].first == "I"){
        nextw(i);
        return true;
    }
    else{
        return false;
    }
}

bool param_list(int &i)   // 参数列表
{
    while(true){
        if (!type_def(i)) return true;
        if (token[i].first == "I"){
            nextw(i);
        }
        else{
            return false;
        }
    }
}

bool com_sentence(int &i) // 复合语句
{
    if (token[i].first == "P" && token[i].second == 8){
        nextw(i);
        if (!sentence_table(i)) return false;
        if (token[i].first == "P" && token[i].second == 9){
            nextw(i);
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

bool sentence_table(int &i)   // 语句表
{
    while(true){
        if (token[i].first == "K" && token[i].second == 6){ // if
            QT.push_back(Node("if", "_", "_", "_"));
            nextw(i);
            if (token[i].first == "P" && token[i].second == 6){ // (
                nextw(i);
                if (!relate_exp(i)) return false;
                if (token[i].first == "P" && token[i].second == 7){ // )
                    nextw(i);
                    if (!com_sentence(i)) return false;
                    QT.push_back(Node("ifend", "_", "_", "_")); // ifend
                }
                else{
                    return false;
                }
            }
            else{
                return false;
            }
        }
        else if (token[i].first == "K" && token[i].second == 7){ // for
            QT.push_back(Node("for", "_", "_", "_"));
            nextw(i);
            if (token[i].first == "P" && token[i].second == 6){ // (
                nextw(i);
                if (token[i].first == "I"){
                    SEM.push(print_I[token[i].second].first);
                    nextw(i);
                    if(!eva_sentence(i)) return false;
                    QT.push_back(Node("forbegin", "_", "_", "_"));
                    if (token[i].first == "P" && token[i].second == 17){ // ;
                        nextw(i);
                        if (!relate_exp(i)) return false;
                        QT.push_back(Node("do", "t"+to_string(QT_index-1), "_", "_"));
                        if (token[i].first == "P" && token[i].second == 17){ // ;
                            nextw(i);
                            if (token[i].first == "I"){
                                SEM.push(print_I[token[i].second].first);
                                nextw(i);
                                if (!eva_sentence(i)) return false;
                                if (token[i].first == "P" && token[i].second == 7){ // )
                                    nextw(i);
                                    if (!com_sentence(i)) return false;
                                    QT.push_back(Node("forend", "_", "_", "_")); // forend
                                }
                                else{
                                    return false;
                                }
                            }
                            else{
                                return false;
                            }
                        }
                        else{
                            return false;
                        }
                    }
                    else{
                        return false;
                    }
                }
                else{
                    return false;
                }
            }
            else{
                return false;
            }
        }
        else if(token[i].first == "K" && token[i].second == 8){ // while
            QT.push_back(Node("while", "_", "_", "_"));
            nextw(i);
            if (token[i].first == "P" && token[i].second == 6){ // (
                nextw(i);
                if (!relate_exp(i)) return false;
                if (token[i].first == "P" && token[i].second == 7){ // )
                    nextw(i);
                    QT.push_back(Node("do", "t"+to_string(QT_index-1), "_", "_"));
                    if (!com_sentence(i)) return false;
                    QT.push_back(Node("whileend", "_", "_", "_"));
                }
                else{
                    return false;
                }
            }
            else{
                return false;
            }
        }
        else{
            if (!sentence(i)) return true;
            if (token[i].first == "P" && token[i].second == 17){    // ;
                nextw(i);
            }
            else{
                return false;
            }
        }
    }
}

bool sentence(int &i)     // 语句
{
    if (token[i].first == "I"){
        SEM.push(print_I[token[i].second].first);
        nextw(i);
        if (!exp_sentence(i)) return false;
    }
    else if (token[i].first == "C1" || token[i].first == "C2"){
        if (token[i].first == "C1") SEM.push(print_C1[token[i].second].first);
        else    SEM.push(print_C2[token[i].second].first);
        nextw(i);
        if (!exp_sentence(i)) return false;
    }
    else{
        if (!declare_sentence(i)) return false;
    }
    return true;
}

bool declare_sentence(int &i) // 声明语句
{
    if(!type_def(i))   return false;
    if (token[i].first == "I"){
        string t1 = SEM.top(); SEM.pop();
        QT.push_back(Node(t1, print_I[token[i].second].first, "_", "_"));
        nextw(i);
        return true;
    }
    else{
        return false;
    }
}

bool exp_sentence(int &i)     // 表达式语句
{
    if(!eva_sentence(i)) return false;
    return true;
}

bool eva_sentence(int &i)     // 赋值表达式, 关系表达式
{
    if (token[i].first == "P" && token[i].second == 5){
        nextw(i);
        if (!arithmetic_exp(i)) return false;
        string t1 = SEM.top(); SEM.pop();
        string t2 = SEM.top(); SEM.pop();
        QT.push_back(Node("=", t1, "_", t2));
    }
    else if (token[i].first == "P" && token[i].second == 10){
        nextw(i);
        if (token[i].first == "I"){
            SEM.push(print_I[token[i].second].first);
            nextw(i);
        }
        else if(token[i].first == "C1" || token[i].first == "C2"){
            if (token[i].first == "C1") SEM.push(print_C1[token[i].second].first);
            else    SEM.push(print_C2[token[i].second].first);
            nextw(i);
        }
        else{
            return false;
        }
        string t1 = SEM.top(); SEM.pop();
        string t2 = SEM.top(); SEM.pop();
        QT.push_back(Node("==", t2, t1, "t"+to_string(QT_index)));
        SEM.push("t"+to_string(QT_index));
        QT_index++;
    }
    else if (token[i].first == "P" && token[i].second == 11){
        nextw(i);
        if (token[i].first == "I"){
            SEM.push(print_I[token[i].second].first);
            nextw(i);
        }
        else if(token[i].first == "C1" || token[i].first == "C2"){
            if (token[i].first == "C1") SEM.push(print_C1[token[i].second].first);
            else    SEM.push(print_C2[token[i].second].first);
            nextw(i);
        }
        else{
            return false;
        }
        string t1 = SEM.top(); SEM.pop();
        string t2 = SEM.top(); SEM.pop();
        QT.push_back(Node("!=", t2, t1, "t"+to_string(QT_index)));
        SEM.push("t"+to_string(QT_index));
        QT_index++;
    }
    else if (token[i].first == "P" && token[i].second == 12){
        nextw(i);
        if (token[i].first == "I"){
            SEM.push(print_I[token[i].second].first);
            nextw(i);
        }
        else if(token[i].first == "C1" || token[i].first == "C2"){
            if (token[i].first == "C1") SEM.push(print_C1[token[i].second].first);
            else    SEM.push(print_C2[token[i].second].first);
            nextw(i);
        }
        else{
            return false;
        }
        string t1 = SEM.top(); SEM.pop();
        string t2 = SEM.top(); SEM.pop();
        QT.push_back(Node(">", t2, t1, "t"+to_string(QT_index)));
        SEM.push("t"+to_string(QT_index));
        QT_index++;
    }
    else if (token[i].first == "P" && token[i].second == 13){
        nextw(i);
        if (token[i].first == "I"){
            SEM.push(print_I[token[i].second].first);
            nextw(i);
        }
        else if(token[i].first == "C1" || token[i].first == "C2"){
            if (token[i].first == "C1") SEM.push(print_C1[token[i].second].first);
            else    SEM.push(print_C2[token[i].second].first);
            nextw(i);
        }
        else{
            return false;
        }
        string t1 = SEM.top(); SEM.pop();
        string t2 = SEM.top(); SEM.pop();
        QT.push_back(Node(">=", t2, t1, "t"+to_string(QT_index)));
        SEM.push("t"+to_string(QT_index));
        QT_index++;
    }
    else if (token[i].first == "P" && token[i].second == 14){
        nextw(i);
        if (token[i].first == "I"){
            SEM.push(print_I[token[i].second].first);
            nextw(i);
        }
        else if(token[i].first == "C1" || token[i].first == "C2"){
            if (token[i].first == "C1") SEM.push(print_C1[token[i].second].first);
            else    SEM.push(print_C2[token[i].second].first);
            nextw(i);
        }
        else{
            return false;
        }
        string t1 = SEM.top(); SEM.pop();
        string t2 = SEM.top(); SEM.pop();
        QT.push_back(Node("<", t2, t1, "t"+to_string(QT_index)));
        SEM.push("t"+to_string(QT_index));
        QT_index++;
    }
    else if (token[i].first == "P" && token[i].second == 15){
        nextw(i);
        if (token[i].first == "I"){
            SEM.push(print_I[token[i].second].first);
            nextw(i);
        }
        else if(token[i].first == "C1" || token[i].first == "C2"){
            if (token[i].first == "C1") SEM.push(print_C1[token[i].second].first);
            else    SEM.push(print_C2[token[i].second].first);
            nextw(i);
        }
        else{
            return false;
        }
        string t1 = SEM.top(); SEM.pop();
        string t2 = SEM.top(); SEM.pop();
        QT.push_back(Node("<=", t2, t1, "t"+to_string(QT_index)));
        SEM.push("t"+to_string(QT_index));
        QT_index++;
    }
    else{
        return false;
    }
    
    return true;
}

bool relate_exp(int &i)
{
    if (!arithmetic_exp(i)) return false;
    if (token[i].first == "P" && token[i].second == 10){
        nextw(i);
        if (!arithmetic_exp(i)) return false;
        string t1 = SEM.top(); SEM.pop();
        string t2 = SEM.top(); SEM.pop();
        QT.push_back(Node("==", t2, t1, "t"+to_string(QT_index)));
        SEM.push("t"+to_string(QT_index));
        QT_index++;
    }
    else if (token[i].first == "P" && token[i].second == 11){
        nextw(i);
        if (!arithmetic_exp(i)) return false;
        string t1 = SEM.top(); SEM.pop();
        string t2 = SEM.top(); SEM.pop();
        QT.push_back(Node("!=", t2, t1, "t"+to_string(QT_index)));
        SEM.push("t"+to_string(QT_index));
        QT_index++;
    }
    else if (token[i].first == "P" && token[i].second == 12){
        nextw(i);
        if (!arithmetic_exp(i)) return false;
        string t1 = SEM.top(); SEM.pop();
        string t2 = SEM.top(); SEM.pop();
        QT.push_back(Node(">", t2, t1, "t"+to_string(QT_index)));
        SEM.push("t"+to_string(QT_index));
        QT_index++;
    }
    else if (token[i].first == "P" && token[i].second == 13){
        nextw(i);
        if (!arithmetic_exp(i)) return false;
        string t1 = SEM.top(); SEM.pop();
        string t2 = SEM.top(); SEM.pop();
        QT.push_back(Node(">=", t2, t1, "t"+to_string(QT_index)));
        SEM.push("t"+to_string(QT_index));
        QT_index++;
    }
    else if (token[i].first == "P" && token[i].second == 14){
        nextw(i);
        if (!arithmetic_exp(i)) return false;
        string t1 = SEM.top(); SEM.pop();
        string t2 = SEM.top(); SEM.pop();
        QT.push_back(Node("<", t2, t1, "t"+to_string(QT_index)));
        SEM.push("t"+to_string(QT_index));
        QT_index++;
    }
    else if (token[i].first == "P" && token[i].second == 15){
        nextw(i);
        if (!arithmetic_exp(i)) return false;
        string t1 = SEM.top(); SEM.pop();
        string t2 = SEM.top(); SEM.pop();
        QT.push_back(Node("<=", t2, t1, "t"+to_string(QT_index)));
        SEM.push("t"+to_string(QT_index));
        QT_index++;
    }
    return true;
}

bool arithmetic_exp(int &i)   // 算术表达式    
{
    if(!E(i)) return false;
    return true;
}

bool type_def(int &i)       // 类型定义
{
    if (token[i].first == "K" && token[i].second == 1){
        nextw(i);
        SEM.push("int");
        return true;
    }
    else if(token[i].first == "K" && token[i].second == 2){
        nextw(i);
        SEM.push("char");
        return true;
    }
    else if(token[i].first == "K" && token[i].second == 3){
        nextw(i);
        SEM.push("float");
        return true;
    }
    else if(token[i].first == "K" && token[i].second == 4){
        nextw(i);
        SEM.push("double");
        return true;
    }
    else if(token[i].first == "K" && token[i].second == 5){
        nextw(i);
        SEM.push("long");
        return true;
    }
    else{
        return false;
    }
}

bool E(int &i){
    if(!T(i))   return false;
    while(1){
        if(token[i].first == "P" && token[i].second == 1){
            // cout << "+";
            nextw(i);
            if(!T(i))   return false;
            string t1 = SEM.top(); SEM.pop();
            string t2 = SEM.top(); SEM.pop();
            QT.push_back(Node("+", t2, t1, "t"+to_string(QT_index)));
            SEM.push("t"+to_string(QT_index));
            QT_index++;
        }
        else if(token[i].first == "P" && token[i].second == 2){
            // cout << "-";
            nextw(i);
            if(!T(i))   return false;
            string t1 = SEM.top(); SEM.pop();
            string t2 = SEM.top(); SEM.pop();
            QT.push_back(Node("-", t2, t1, "t"+to_string(QT_index)));
            SEM.push("t"+to_string(QT_index));
            QT_index++;
        }
        else    return true;
    }
}

bool T(int &i){
    if(!F(i))   return false;
    while(1){
        if(token[i].first == "P" && token[i].second == 3){
            // cout << "*";
            nextw(i);
            if(!F(i))   return false;
            string t1 = SEM.top(); SEM.pop();
            string t2 = SEM.top(); SEM.pop();
            QT.push_back(Node("*", t2, t1, "t"+to_string(QT_index)));
            SEM.push("t"+to_string(QT_index));
            QT_index++;
        }
        else if(token[i].first == "P" && token[i].second == 4){
            // cout << "/";
            nextw(i);
            if(!F(i))   return false;
            string t1 = SEM.top(); SEM.pop();
            string t2 = SEM.top(); SEM.pop();
            QT.push_back(Node("/", t2, t1, "t"+to_string(QT_index)));
            SEM.push("t"+to_string(QT_index));
            QT_index++;
        }
        else    return true;
    }
}

bool F(int &i){
    if(token[i].first=="I" || token[i].first=="C1" || token[i].first=="C2"){
        if (token[i].first=="I"){
            SEM.push(print_I[token[i].second].first);
        }
        else if (token[i].first=="C1"){
            SEM.push(print_C1[token[i].second].first);
        }
        else if (token[i].first=="C2"){
            SEM.push(print_C2[token[i].second].first);
        }
        nextw(i);
        return true;
    }
    else if(token[i].first == "P" && token[i].second==6){
        // cout << "(";
        nextw(i);
        if(!E(i))   return false;
        if(token[i].first == "P" && token[i].second==7){
            // cout << ")";
            nextw(i);
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

void show_QT()
{
    for (unsigned int i = 0; i < QT.size(); i++){
        cout << QT[i].op << " " << QT[i].num1 << " " << QT[i].num2 << " " << QT[i].res << endl;
    }
}

int main(){
    string str="", t_str;
    ifstream inFile("test2.txt");
    while (getline(inFile, t_str)){
        str += t_str + '\n';
    }
    // while(getline(cin,t_str)){
    //     str += t_str+'\n';
    // }
    int state = 1;
    char c;
    str += "#\n";
    cout << str << endl;
    string s;
    for (unsigned int i = 0; i < str.length(); i++){
        c = str[i];
        while (1){
            int state_before = state;
            state_change(state, c);
            if (state == -1){
                cout << "ERROR" << endl;
                return 0;
            }
            if (state == 0){
                if (state_before == 2){ //关键字、标识符
                    if (K.count(s) > 0)
                        token.push_back(make_pair("K", K[s]));
                    else{
                        if (I.count(s) > 0){
                            token.push_back(make_pair("I", I[s]));
                        }
                        else{
                            I[s] = I.size();
                            print_I.push_back(make_pair(s, I[s]));
                            token.push_back(make_pair("I", I[s]));
                        }
                    }
                }
                else if (state_before == 3){
                    if (C1.count(s) > 0){
                        token.push_back(make_pair("C1", C1[s]));
                    }
                    else{
                        C1[s] = C1.size();
                        print_C1.push_back(make_pair(s, C1[s]));
                        token.push_back(make_pair("C1", C1[s]));
                    }
                }
                else if (state_before == 4){ // 16进制整数
                    s = s.substr(2, s.length());
                    int num = 0;
                    for (unsigned int i = 0; i < s.length(); i++){
                        num = num * 16 + (s[i] >= '0' && s[i] <= '9' ? s[i] - '0' : (s[i] >= 'a' && s[i] <= 'f' ? s[i] - 'a' + 10 : s[i] - 'A' + 10));
                    }
                    s = to_string(num);
                    if (C1.count(s) > 0){
                        token.push_back(make_pair("C1", C1[s]));
                    }
                    else{
                        C1[s] = C1.size();
                        print_C1.push_back(make_pair(s, C1[s]));
                        token.push_back(make_pair("C1", C1[s]));
                    }
                }
                else if (state_before == 5){ //十进制整数
                    if (C1.count(s) > 0){
                        token.push_back(make_pair("C1", C1[s]));
                    }
                    else{
                        C1[s] = C1.size();
                        print_C1.push_back(make_pair(s, C1[s]));
                        token.push_back(make_pair("C1", C1[s]));
                    }
                }
                else if (state_before == 7 || state_before == 9){ //小数、e指数
                    if (C2.count(s) > 0){
                        token.push_back(make_pair("C2", C2[s]));
                    }
                    else{
                        C2[s] = C2.size();
                        print_C2.push_back(make_pair(s, C2[s]));
                        token.push_back(make_pair("C2", C2[s]));
                    }
                }
                else if (state_before == 13){ //字符
                    s = s.substr(1, s.length() - 2);
                    if (CT.count(s) > 0){
                        token.push_back(make_pair("CT", CT[s]));
                    }
                    else{
                        CT[s] = CT.size();
                        print_CT.push_back(make_pair(s, CT[s]));
                        token.push_back(make_pair("CT", CT[s]));
                    }
                }
                else if (state_before == 16){ //字符串
                    s = s.substr(1, s.length() - 2);
                    if (ST.count(s) > 0){
                        token.push_back(make_pair("ST", ST[s]));
                    }
                    else{
                        ST[s] = ST.size();
                        print_ST.push_back(make_pair(s, ST[s]));
                        token.push_back(make_pair("ST", ST[s]));
                    }
                }
                else if (P.count(s) > 0){
                    token.push_back(make_pair("P", P[s]));
                }
                s = "";
                state = 1;
            }
            else{
                if (s == " " || s == "\n" || s == "\t") s = "";
                s += c;
                break;
            }
        }
        if (c == '#')   break;
    }

    show_token();

    int i=-1;
    token.push_back(make_pair("#", 0));
    nextw(i);
    bool flag = func_define(i);
    if(flag){
        cout << "该程序是函数定义语言" << endl; 
        show_QT();
    }
    else{
        cout << "该程序不是函数定义语言" << endl;
        cout << i << " " << token[i].first << " " << token[i].second << endl;
        show_QT();
    }

    return 0;
}
