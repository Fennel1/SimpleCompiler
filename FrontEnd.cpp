#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <fstream>
using namespace std;

#define INT 0
#define FLOAT 1
#define DOUBLE 2
#define CHAR 3


struct Token{
    string type;
    string value;
    Token(string type, string value){
        this->type = type;
        this->value = value;
    }
};

struct SYNBL_Node{      // 符号表主表结点
    string name;    // 名称
    int type;       // 类型
    string cat;     // 种类
    int addr;       // 地址
    SYNBL_Node(string name, int type, string cat, int addr){
        this->name = name;
        this->type = type;
        this->cat = cat;
        this->addr = addr;
    }
};

struct TYPEL_Node{      // 类型表结点
    string type;    // 类型
    int tpoint;     // 类型地址
    TYPEL_Node(string type, int tpoint){
        this->type = type;
        this->tpoint = tpoint;
    }
};

struct PFINFL_Node{     // 函数表结点
    int fn;       // 参数数量
    int param;    // 参数地址
    PFINFL_Node(int fn, int param){
        this->fn = fn;
        this->param = param;
    }
};

struct PARAML_Node{     // 参数表结点
    string name;    // 参数名称
    int type;       // 参数类型
    PARAML_Node(string name, int type){
        this->name = name;
        this->type = type;
    }
};

struct AINFL_Node{      // 数组表结点
    int len;     // 数组长度
    int type;    // 元素类型
    int type_len;// 元素类型长度
    AINFL_Node(int len, int type, int type_len){
        this->len = len;
        this->type = type;
        this->type_len = type_len;
    }
};

struct RINFL_Node{      //结构表结点
    string name;    // 名称
    int off;       // 区距
    int type;
    RINFL_Node(string name, int off, int type){
        this->name = name;
        this->off = off;
        this->type = type;
    }
};

vector<SYNBL_Node> SYNBL;       // 符号表
vector<TYPEL_Node> TYPEL;       // 类型表
vector<PFINFL_Node> PFINFL;     // 函数表
vector<PARAML_Node> PARAML;     // 参数表
vector<AINFL_Node> AINFL;       // 数组表
vector<RINFL_Node> RINFL;       // 结构表
vector<int> LEN;                // 长度表
vector<int> CONSL_INT;          // 整型常量表
vector<float> CONSL_FLOAT;      // 浮点型常量表
vector<char> CONSL_CHAR;        // 字符型常量表
vector<string> CONSL_STRING;    // 字符串型常量表
int SYNBL_addr = 0, TYPEL_addr = 0, PFINFL_addr = 0, PARAML_addr = 0, AINFL_addr = 0, RINFL_addr = 0;

bool find_I(string ID){
    for(unsigned int i = 0; i < SYNBL.size(); i++){
        if(SYNBL[i].name == ID) return true;
    }
    return false;
}

bool find_CI(int ID){
    for(unsigned int i = 0; i < CONSL_INT.size(); i++){
        if(CONSL_INT[i] == ID) return true;
    }
    return false;
}

bool find_CF(float ID){
    for(unsigned int i = 0; i < CONSL_FLOAT.size(); i++){
        if(CONSL_FLOAT[i] == ID) return true;
    }
    return false;
}

bool find_CC(char ID){
    for(unsigned int i = 0; i < CONSL_CHAR.size(); i++){
        if(CONSL_CHAR[i] == ID) return true;
    }
    return false;
}

bool find_CS(string ID){
    for(unsigned int i = 0; i < CONSL_STRING.size(); i++){
        if(CONSL_STRING[i] == ID) return true;
    }
    return false;
}

void init_TYPEL()
{
    TYPEL.push_back(TYPEL_Node("int", 2));
    TYPEL.push_back(TYPEL_Node("float", 4));
    TYPEL.push_back(TYPEL_Node("double", 4));
    TYPEL.push_back(TYPEL_Node("char", 1));
}

void show_SYNBL()
{
    cout << "————————————————————————符号表————————————————————————" << endl;
    cout << "符号表主表：" << endl;
    for(unsigned int i = 0; i < SYNBL.size(); i++){
        cout << i << "\t" << SYNBL[i].name << "\t" << SYNBL[i].type << "\t" << SYNBL[i].cat << "\t" << SYNBL[i].addr << endl;
    }
    cout << "类型表：" << endl;
    for(unsigned int i = 0; i < TYPEL.size(); i++){
        cout << i << "\t" << TYPEL[i].type << "\t" << TYPEL[i].tpoint << endl;
    }
    cout << "函数表：" << endl;
    for(unsigned int i = 0; i < PFINFL.size(); i++){
        cout << i << "\t" << PFINFL[i].fn << "\t" << PFINFL[i].param << endl;
    }
    cout << "参数表：" << endl;
    for(unsigned int i = 0; i < PARAML.size(); i++){
        cout << i << "\t" << PARAML[i].name << "\t" << PARAML[i].type << endl;
    }
    cout << "数组表：" << endl;
    for(unsigned int i = 0; i < AINFL.size(); i++){
        cout << i << "\t" << AINFL[i].len << "\t" << AINFL[i].type << "\t" << AINFL[i].type_len << endl;
    }
    cout << "结构表：" << endl;
    for(unsigned int i = 0; i < RINFL.size(); i++){
        cout << i << "\t" << RINFL[i].name << "\t" << RINFL[i].off << "\t" << RINFL[i].type << endl;
    }
    cout << "长度表：" << endl;
    for(unsigned int i = 0; i < LEN.size(); i++){
        cout << i << "\t" << LEN[i] << endl;
    }
    cout << "整型常量表：" << endl;
    for(unsigned int i = 0; i < CONSL_INT.size(); i++){
        cout << i << "\t" << CONSL_INT[i] << endl;
    }
    cout << "浮点型常量表：" << endl;
    for(unsigned int i = 0; i < CONSL_FLOAT.size(); i++){
        cout << i << "\t" << CONSL_FLOAT[i] << endl;
    }
    cout << "字符型常量表：" << endl;
    for(unsigned int i = 0; i < CONSL_CHAR.size(); i++){
        cout << i << "\t" << CONSL_CHAR[i] << endl;
    }
    cout << "字符串型常量表：" << endl;
    for(unsigned int i = 0; i < CONSL_STRING.size(); i++){
        cout << i << "\t" << CONSL_STRING[i] << endl;
    }
}

map<string, int> K = {{"int",1},{"char",2},{"float",3},{"double",4},{"long",5},{"if",6},{"for",7},
                     {"while",8},{"break",9},{"continue",10},{"return",11},{"case",12},{"default",13},{"else",14},
                     {"struct", 15}, {"const", 16}};
map<string, int> P = {{"+", 1},{"-",2},{"*",3},{"/",4},{"=",5},{"(",6},{")",7},{"{",8},
                     {"}",9},{"==",10},{"!=",11},{">",12},{">=",13},{"<",14},{"<=",15},{",",16},
                     {";",17}, {"++",18},{"--",19},{"[",20},{"]",21}, {".",22}, };

string str="", t_str="";
unsigned int str_i=0;
string ErrorMessage="";

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
        else if(ch=='.')    state = 35;
        else if(ch=='[')    state = 36;
        else if(ch==']')    state = 37;
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

Token token("", "");        //当前读取的token

Token nextw()
{
    // cout << token.type << " " << token.value << endl;
    char c;
    int state = 1;
    string s="";
    for (; str_i < str.length(); str_i++){
        c = str[str_i];
        while(1){
            int state_old = state;
            state_change(state, c);
            if (state == -1){
                cout << "ERROR" << endl;
                return Token("ERROR", "");
            }
            else if(state == 0){
                if (state_old == 2){            //关键字、标识符
                    if (K.count(s) > 0)     return Token("K", s);
                    else{
                        if (find_I(s)){
                            return Token("I", s);
                        }
                        else{
                            // for (unsigned int i = 0; i < SYNBL.size(); i++){
                            //     if (s == SYNBL[i].name){
                            //         cout << "重复定义变量" << s << endl;
                            //         return Token("ERROR", "");
                            //     }
                            // }
                            SYNBL.push_back(SYNBL_Node(s, -1, " ", -1));
                            return Token("I", s);
                        }
                    }
                }
                else if (state_old == 3){       //整数
                    if (find_CI(stoi(s))){
                        return Token("CI", s);
                    }
                    else{
                        // SYNBL.push_back(SYNBL_Node(s, INT, "C", CONSL_INT.size()));
                        CONSL_INT.push_back(stoi(s));
                        return Token("CI", s);
                    }
                }
                else if (state_old == 4){       // 16进制整数
                    s = s.substr(2, s.length());
                    int num = 0;
                    for (unsigned int i = 0; i < s.length(); i++){
                        num = num * 16 + (s[i] >= '0' && s[i] <= '9' ? s[i] - '0' : (s[i] >= 'a' && s[i] <= 'f' ? s[i] - 'a' + 10 : s[i] - 'A' + 10));
                    }
                    s = to_string(num);
                    if (find_CI(num)){
                        return Token("CI", s);
                    }
                    else{
                        // SYNBL.push_back(SYNBL_Node(s, INT, "C", CONSL_INT.size()));
                        CONSL_INT.push_back(num);
                        return Token("CI", s);
                    }
                }
                else if (state_old == 5){       //十进制整数
                    if (find_CI(stoi(s))){
                        return Token("CI", s);
                    }
                    else{
                        // SYNBL.push_back(SYNBL_Node(s, INT, "C", CONSL_INT.size()));
                        CONSL_INT.push_back(stoi(s));
                        return Token("CI", s);
                    }
                }
                else if (state_old == 7 || state_old == 9){ //小数、e指数
                    if (find_CF(stof(s))){
                        return Token("CF", s);
                    }
                    else{
                        // SYNBL.push_back(SYNBL_Node(s, FLOAT, "C", CONSL_FLOAT.size()));
                        CONSL_FLOAT.push_back(stof(s));
                        return Token("CF", s);
                    }
                }
                else if (state_old == 13){      //字符
                    s = s.substr(1, s.length() - 2);
                    if (find_CS(s)){
                        return Token("CC", s);
                    }
                    else{
                        // SYNBL.push_back(SYNBL_Node(s, CHAR, "C", CONSL_CHAR.size()));
                        CONSL_CHAR.push_back(s[0]);
                        return Token("CC", s);
                    }
                }
                else if (state_old == 16){      //字符串
                    s = s.substr(1, s.length() - 2);
                    if (find_CS(s)){
                        return Token("CS", s);
                    }
                    else{
                        // SYNBL.push_back(SYNBL_Node(s, TYPEL.size(), "C", CONSL_STRING.size()));
                        // TYPEL.push_back(TYPEL_Node("a", AINFL.size()));
                        // AINFL.push_back(AINFL_Node(s.length(), CHAR, 1));
                        CONSL_STRING.push_back(s);
                        return Token("CS", s);
                    }
                }
                else if (P.count(s) > 0){
                    return Token("P", s);
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
        if (c == '#')   return Token("#", "");
    }
    return Token("ERROR", "");
}

struct QT_Node{     //四元式节点
    int block_id;
    string op;              //操作符
    string num1, num2;      //操作数
    string res;             //结果
    QT_Node(string op, string num1, string num2, string res){
        this->op = op;
        this->num1 = num1;
        this->num2 = num2;
        this->res = res;
        this->block_id = 0;
    }
    QT_Node(const QT_Node& other){
        this->op = other.op;
        this->num1 = other.num1;
        this->num2 = other.num2;
        this->res = other.res;
        this->block_id = other.block_id;
    }
};

struct SEM_Node{    //语义分析节点
    string name;
    string type;
    SEM_Node(string name, string type){
        this->name = name;
        this->type = type;
    }
};

vector<QT_Node> QT;         //四元式
stack<string> SEM;          //语义分析栈
map<string, int> T_type;    //临时变量类型

int QT_index = 0;

void show_QT(){
    cout << "————————————————————————————————————————————————四元式————————————————————————————————————————————————" << endl;
    for (unsigned int i = 0; i < QT.size(); i++){
        cout.width(10);
        cout << i+1;
        cout.width(10);
        cout << QT[i].op;
        cout.width(15);
        cout << QT[i].num1;
        cout.width(15);
        cout << QT[i].num2;
        cout.width(15);
        cout << QT[i].res;
        cout.width(10);
        cout << QT[i].block_id << endl;
    }
}

bool Program();                     //程序
bool ExternalVariable();            //外部变量
bool FunctionDefinitionClosure();   //函数定义闭包
bool FunctionDefinition();          //函数定义
bool Variable();                    //变量
bool VariableSuffix();              //变量后缀
bool MutiFactor();                  //因子
bool Expression();                  //表达式
bool Factor();                      //因子
bool Term();                        //项
bool MutiFactorRecurr();            //因子递归
bool DeclarationParameterList();    //声明参数列表
bool Declaration();                 //声明
bool InitialValue();                //初值
bool RightValue();                  //右值
bool MutiVariable();                //多变量
bool DigitClosure();                //数字闭包
bool DeclarationClosure();          //声明闭包
bool FunctionBlock();               //函数块
bool DeclarationStatementClosure(); //声明语句闭包
bool DeclarationStatement();        //声明语句
bool FunctionBlockClosure();        //函数块闭包
bool AssignmentStatement();         //赋值语句
bool AssignmentOrCall();            //赋值或函数调用
bool ParameterList();               //参数列表
bool Parameter();                   //参数
bool ParameterClosure();            //参数闭包
bool ForStatement();                //for语句
bool LogicalExpression();           //逻辑表达式
bool PostfixExpression();           //后缀表达式
bool IfStatement();                 //if语句
bool ElseIfStatement();             //else if语句
bool ElseStatement();               //else语句
bool WhileStatement();              //while语句
bool ReturnStatement();             //return语句


bool Program()                          //程序
{
    // if (!ExternalVariable())   return false;
    if (!FunctionDefinitionClosure())  return false;
    return true;
}

bool ExternalVariable()                 //外部变量
{
    if (!DeclarationStatementClosure())  return false;
    return true;
}

bool FunctionDefinitionClosure()       //函数定义闭包
{
    if (token.type == "K" && (token.value == "int" || token.value == "float" || token.value == "double" || token.value == "char")){
        if (!FunctionDefinition())   return false;
        QT.push_back(QT_Node("funcend", "_", "_", "_"));
        if (!FunctionDefinitionClosure())   return false;
        return true;
    }
    else{
        return true;
    }
}

bool FunctionDefinition()               //函数定义
{
    if (token.type == "K" && (token.value == "int" || token.value == "float" || token.value == "double" || token.value == "char")){
        token = nextw();
        string t1 = token.value;
        QT.push_back(QT_Node("funcbegin", "_", "_", t1));
        int func_type;
        for (unsigned int i = 0; i < TYPEL.size(); i++){
            if (TYPEL[i].type == t1){
                func_type = i;
                break;
            }
        }
        if (!Variable())    return false;
        string func_name = SEM.top(); SEM.pop();
        func_name = func_name.substr(0, func_name.length()-2);
        if (token.type == "P" && token.value == "("){
            token = nextw();
            int stack_size = SEM.size();
            if (!DeclarationParameterList())   return false;
            int func_param_num = (SEM.size() - stack_size) / 2;
            stack<string> param_name_st, param_type_st;
            for (int i=0; i<func_param_num; i++){
                param_name_st.push(SEM.top());SEM.pop();
                param_type_st.push(SEM.top());SEM.pop();
            }
            for (unsigned int i = 0; i < SYNBL.size(); i++){
                if (SYNBL[i].name == func_name){
                    SYNBL[i].type = func_type;
                    SYNBL[i].cat = "F";
                    SYNBL[i].addr = PFINFL.size();
                    PFINFL.push_back(PFINFL_Node(func_param_num, PARAML.size()));
                }
            }
            while(!param_name_st.empty()){
                string param_name = param_name_st.top(); param_name_st.pop();
                string param_type = param_type_st.top(); param_type_st.pop();
                int param_type_index;
                for (unsigned int i = 0; i < TYPEL.size(); i++){
                    if (TYPEL[i].type == param_type){
                        param_type_index = i;
                        break;
                    }
                }
                for (unsigned int i = 0; i < SYNBL.size(); i++){
                    if (SYNBL[i].name == param_name){
                        SYNBL[i].type = param_type_index;
                        SYNBL[i].cat = "Vf";
                    }
                }
                PARAML.push_back(PARAML_Node(param_name, param_type_index));
            }
            
            if (token.type == "P" && token.value == ")"){
                token = nextw();
                if (token.type == "P" && token.value == "{"){
                    token = nextw();
                    if (!FunctionBlock())   return false;
                    if (token.type == "P" && token.value == "}"){
                        token = nextw();
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

bool Variable()                         //变量
{
    if (token.type == "I"){
        SEM.push(token.value);
        token = nextw();
        if (!VariableSuffix())   return false;
        string t1 = SEM.top(); SEM.pop();
        string t2;
        if (t1[0] == '['){
            t2 = SEM.top(); SEM.pop();
            SEM.push(t2+t1);
        }
        else if(t1[0] == '.'){
            t2 = SEM.top(); SEM.pop();
            SEM.push(t2+t1);
        }
        else{
            SEM.push(t1);
        }
        return true;
    }
    else{
        return false;
    }
}

bool VariableSuffix()                   //变量后缀
{
    if (token.type == "P" && token.value == "["){       //数组
        token = nextw();
        if (!MutiFactor())  return false;
        if (token.type == "P" && token.value == "]"){
            token = nextw();
            string t1= SEM.top(); SEM.pop();
            SEM.push("["+t1+"]");
            return true;
        }
        else{
            return false;
        }
    }
    else if(token.type == "P" && token.value == "."){   //结构体
        token = nextw();
        if (!Variable())    return false;
        string t1 = SEM.top(); SEM.pop();
        SEM.push("."+t1);
        return true;
    }
    else if (token.type == "P" && token.value == "("){  //函数调用
        string t1= SEM.top(); SEM.pop();
        SEM.push(t1+"()");
        return true;
    }
    else{
        return true;
    }
}

bool MutiFactor()                           //因式
{
    if (token.type == "I"){         //标识符
        if (!Variable())    return false;
        return true;
    }
    else if (token.type == "CI"){   //整型常量
        SEM.push(token.value);
        token = nextw();
        return true;
    }
    else if (token.type == "CF"){   //浮点型常量
        SEM.push(token.value);
        token = nextw();
        return true;
    }
    else if (token.type == "CC"){   //字符型常量
        SEM.push(token.value);
        token = nextw();
        return true;
    }
    else if (token.type == "P" && token.value == "("){  //括号表达式
        token = nextw();
        if (!Expression())   return false;
        if (token.type == "P" && token.value == ")"){
            token = nextw();
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

bool Expression()                       //表达式    
{
    if (!Factor())  return false;
    if (!Term())    return false;
    return true;
}

bool Factor()                           //因子
{
    if (!MutiFactor())  return false;
    if (!MutiFactorRecurr())    return false;
    return true;
}

pair<string, string> GetName(string name)             //获取标识符名称
{
    string name_="";
    for (unsigned int i=0; i<name.length(); i++){
        if (name[i] == '['){
            name = name.substr(0, i);
            name_ = "[]";
        }
        else if (name[i] == '.'){
            name_ = name.substr(i+1);
            name = name.substr(0,i);
        }
    }
    return make_pair(name, name_);
}

int GetType(string name, string name_)                //获取标识符类型
{
    for (unsigned int i=0; i<SYNBL.size(); i++){
        if (SYNBL[i].name == name){
            if (SYNBL[i].type == -1)    return -77;
            if (name_ == "")    return SYNBL[i].type;
            else if(name_ == "[]"){
                return TYPEL[SYNBL[i].type].tpoint;
            }
            else{
                if (SYNBL[i].cat != "V")    return -2;
                for (unsigned int j=TYPEL[SYNBL[i].type].tpoint; j<RINFL.size(); j++){
                    if (RINFL[j].name == name_){
                        return RINFL[j].type;
                    }
                    if (j != 0 && RINFL[j].off < RINFL[j-1].off)    break;
                }
                return -1;
            }
        }
    }
    return -1;
}

bool CheckType(string t1, string t2)    //检查标识符类型
{
    string t1_="", t2_="", t1__="", t2__="";
    int t1_type=-1, t2_type=-1;
    if (t1[0] == 't'){                          //临时变量
        if (T_type.find(t1) == T_type.end()){
            ErrorMessage = "Error: 使用未定义变量 " + t1;
            cout << "Error: 使用未定义变量 " << t1 << endl;
            return false;
        }
        t1_ = t1;
        t1_type = T_type[t1_];
    }
    else if (t1[0] <= '9' && t1[0] >= '0'){     //数字常量
        t1_ = t1;
        for (unsigned int i=0; i<t1.length(); i++){
            if (t1[i] == '.'){
                t1_type = 1;
            }
        }
        if (t1_type == -1)  t1_type = 0;
    }
    else{                                       //标识符
        tie(t1_, t1__) = GetName(t1);
        t1_type = GetType(t1_, t1__);
    }
    if (t2[0] == 't'){
        t2_ = t2;
        t2_type = T_type[t2_];
    }
    else if (t2[0] <= '9' && t2[0] >= '0'){
        t2_ = t2;
        for (unsigned int i=0; i<t2.length(); i++){
            if (t2[i] == '.'){
                t2_type = 1;
            }
        }
        if (t2_type == -1)  t2_type = 0;
    }
    else{
        tie(t2_, t2__) = GetName(t2);
        t2_type = GetType(t2_, t2__);
    }
    // cout << t1_ << " " << t1_type << " " << t2_ << " " << t2_type << endl;
    if (t1_type == -1 || t1_type == -77){
        if (t1__ != "" && t1__ != "[]") t1_ = t1_ + "." + t1__;
        else if (t1__ != "")    t1_ = t1__+"[]";
        ErrorMessage = "Error: 使用未定义变量 " + t1_;
        cout << "Error: 未定义的变量 " << t1_ << endl;
        return false;
    }
    if (t2_type == -1 || t2_type == -77){
        if (t2__ != "" && t2__ != "[]") t2_ = t2_ + "." + t2__;
        else if (t2__ != "")    t2_ = t2__+"[]";
        ErrorMessage = "Error: 使用未定义变量 " + t2_;
        cout << "Error: 未定义的变量 " << t2_ << endl;
        return false;
    }
    if (t1_type != t2_type){
        if (t1__ != "" && t1__ != "[]") t1_ = t1_ + "." + t1__;
        else if (t1__ != "")    t1_ = t1_+"[]";
        if (t2__ != "" && t2__ != "[]") t2_ = t2_ + "." + t2__;
        else if (t2__ != "")    t2_ = t2__+"[]";
        ErrorMessage = "Error: 两个标识符类型不匹配 " + t1_ + " " + t2_;
        cout << "Error: 类型不匹配 " << t1_ << " " << t2_ << endl;
        return false;
    }
    return true;
}

int GetTType(string name)                //获取临时变量类型
{
    string name_, name__;
    int type=-1;
    if (name[0] == 't'){                          //临时变量
        name_ = name;
        type = T_type[name_];
    }
    else if (name[0] <= '9' && name[0] >= '0'){     //数字常量
        name_ = name;
        for (unsigned int i=0; i<name.length(); i++){
            if (name[i] == '.'){
                type = 1;
            }
        }
        if (type == -1)  type = 0;
    }
    else{                                       //标识符
        tie(name_, name__) = GetName(name);
        type = GetType(name_, name__);
    }
    return type;
}

bool Term()                             //项
{
    if (token.type == "P" && token.value == "+"){
        token = nextw();
        if (!Factor()) return false;
        string t1 = SEM.top(); SEM.pop();
        string t2 = SEM.top(); SEM.pop();
        if (!CheckType(t1, t2)) return false;
        QT_index++;
        QT.push_back(QT_Node("+", t2, t1, "t"+to_string(QT_index)));
        T_type["t"+to_string(QT_index)] = GetTType(t1);
        SEM.push("t"+to_string(QT_index));
        if (!Term()) return false;
        return true;
    }
    else if (token.type == "P" && token.value == "-"){
        token = nextw();
        if (!Factor()) return false;
        string t1 = SEM.top(); SEM.pop();
        string t2 = SEM.top(); SEM.pop();
        if (!CheckType(t1, t2)) return false;
        QT_index++;
        QT.push_back(QT_Node("-", t2, t1, "t"+to_string(QT_index)));
        T_type["t"+to_string(QT_index)] = GetTType(t1);
        SEM.push("t"+to_string(QT_index));
        if (!Term()) return false;
        return true;
    }
    else{
        return true;
    }
}

bool MutiFactorRecurr()                 //因式递归
{
    if (token.type == "P" && token.value == "*"){
        token = nextw();
        if (!MutiFactor())  return false;
        string t1 = SEM.top(); SEM.pop();
        string t2 = SEM.top(); SEM.pop();
        string t1_t="", t2_t="";
        if (!CheckType(t1, t2)) return false;
        QT_index++;
        QT.push_back(QT_Node("*", t2, t1, "t"+to_string(QT_index)));
        T_type["t"+to_string(QT_index)] = GetTType(t1);
        SEM.push("t"+to_string(QT_index));
        if (!MutiFactorRecurr())    return false;
        return true;
    }
    else if (token.type == "P" && token.value == "/"){
        token = nextw();
        if (!MutiFactor())  return false;
        string t1 = SEM.top(); SEM.pop();
        string t2 = SEM.top(); SEM.pop();
        if (!CheckType(t1, t2)) return false;
        QT_index++;
        QT.push_back(QT_Node("/", t2, t1, "t"+to_string(QT_index)));
        T_type["t"+to_string(QT_index)] = GetTType(t1);
        SEM.push("t"+to_string(QT_index));
        if (!MutiFactorRecurr())    return false;
        return true;
    }
    else{
        return true;
    }
}

bool DeclarationParameterList()                    //参数列表
{
    if (token.type == "K" && (token.value == "int" || token.value == "float" || token.value == "double" 
        || token.value == "char" || token.value == "struct" || token.value == "const")){
        if (!Declaration())   return false;
        if (!DeclarationClosure())    return false;
        return true;
    }
    else{
        return true;
    }
}

bool Declaration()                      //声明
{
    if (token.type == "K" && token.value == "const"){
        token = nextw();
        if (token.type == "K" && token.value == "int"){
            SEM.push(token.value);
            token = nextw();
            if (!Variable())   return false;
            string name = SEM.top(); SEM.pop();
            string type = SEM.top(); SEM.pop();
            // cout << name << " " << type << endl;
            if (name[name.size()-1] != ']'){        // 如果不是数组
                for (unsigned int i=0; i<SYNBL.size(); i++){
                    if (SYNBL[i].name == name){
                        if (SYNBL[i].type == -1){
                            SYNBL[i].type = INT;
                            SYNBL[i].cat = "V";
                            break;
                        }
                        else{
                            ErrorMessage = "Error: 变量重复定义 " + name;
                            cout << "Error: " << name << " 重复定义" << endl;
                            return false;
                        }
                    }
                }
            }
            else{                                   // 如果是数组
                int lens;
                string name_;
                for (unsigned int i=0; i<name.size(); i++){
                    if (name[i] == '['){
                        lens = stoi(name.substr(i+1, name.size()-i-2));
                        name_ = name.substr(0, i);
                        break;
                    }
                }
                for (unsigned int i=0; i<SYNBL.size(); i++){
                    if (SYNBL[i].name == name_){
                        if (SYNBL[i].type == -1){
                            SYNBL[i].type = TYPEL.size();
                            SYNBL[i].cat = "a";
                            SYNBL[i].addr = LEN.size();
                            LEN.push_back(lens*TYPEL[INT].tpoint);
                            TYPEL.push_back(TYPEL_Node("a", AINFL.size()));
                            AINFL.push_back(AINFL_Node(lens, INT, TYPEL[INT].tpoint));
                            break;
                        }
                        else{
                            ErrorMessage = "Error: 变量重复定义 " + name_;
                            cout << "Error: " << name_ << " 重复定义" << endl;
                            return false;
                        }
                    }
                }
            }
            SEM.push(type);
            SEM.push(name);
            if (!InitialValue())    return false;
            return true;
        }
        else if (token.type == "K" && token.value == "float"){
            SEM.push(token.value);
            token = nextw();
            if (!Variable())   return false;
            string name = SEM.top(); SEM.pop();
            string type = SEM.top(); SEM.pop();
            // cout << name << " " << type << endl;
            if (name[name.size()-1] != ']'){        // 如果不是数组
                for (unsigned int i=0; i<SYNBL.size(); i++){
                    if (SYNBL[i].name == name){
                        if (SYNBL[i].type == -1){
                            SYNBL[i].type = FLOAT;
                            SYNBL[i].cat = "V";
                            break;
                        }
                        else{
                            ErrorMessage = "Error: 变量重复定义 " + name;
                            cout << "Error: " << name << " 重复定义" << endl;
                            return false;
                        }
                    }
                }
            }
            else{                                   // 如果是数组
                int lens;
                string name_;
                for (unsigned int i=0; i<name.size(); i++){
                    if (name[i] == '['){
                        lens = stoi(name.substr(i+1, name.size()-i-2));
                        name_ = name.substr(0, i);
                        break;
                    }
                }
                for (unsigned int i=0; i<SYNBL.size(); i++){
                    if (SYNBL[i].name == name_){
                        if (SYNBL[i].type == -1){
                            SYNBL[i].type = TYPEL.size();
                            SYNBL[i].cat = "a";
                            SYNBL[i].addr = LEN.size();
                            LEN.push_back(lens*TYPEL[FLOAT].tpoint);
                            TYPEL.push_back(TYPEL_Node("a", AINFL.size()));
                            AINFL.push_back(AINFL_Node(lens, FLOAT, TYPEL[FLOAT].tpoint));
                            break;
                        }
                        else{
                            ErrorMessage = "Error: 变量重复定义 " + name_;
                            cout << "Error: " << name_ << " 重复定义" << endl;
                            return false;
                        }
                    }
                }
            }
            SEM.push(type);
            SEM.push(name);
            if (!InitialValue())    return false;
            return true;
        }
        else if (token.type == "K" && token.value == "double"){
            SEM.push(token.value);
            token = nextw();
            if (!Variable())   return false;
            string name = SEM.top(); SEM.pop();
            string type = SEM.top(); SEM.pop();
            // cout << name << " " << type << endl;
            if (name[name.size()-1] != ']'){        // 如果不是数组
                for (unsigned int i=0; i<SYNBL.size(); i++){
                    if (SYNBL[i].name == name){
                        if (SYNBL[i].type == -1){
                            SYNBL[i].type = DOUBLE;
                            SYNBL[i].cat = "V";
                            break;
                        }
                        else{
                            ErrorMessage = "Error: 变量重复定义 " + name;
                            cout << "Error: " << name << " 重复定义" << endl;
                            return false;
                        }
                    }
                }
            }
            else{                                   // 如果是数组
                int lens;
                string name_;
                for (unsigned int i=0; i<name.size(); i++){
                    if (name[i] == '['){
                        lens = stoi(name.substr(i+1, name.size()-i-2));
                        name_ = name.substr(0, i);
                        break;
                    }
                }
                for (unsigned int i=0; i<SYNBL.size(); i++){
                    if (SYNBL[i].name == name_){
                        if (SYNBL[i].type == -1){
                            SYNBL[i].type = TYPEL.size();
                            SYNBL[i].cat = "a";
                            SYNBL[i].addr = LEN.size();
                            LEN.push_back(lens*TYPEL[DOUBLE].tpoint);
                            TYPEL.push_back(TYPEL_Node("a", AINFL.size()));
                            AINFL.push_back(AINFL_Node(lens, DOUBLE, TYPEL[DOUBLE].tpoint));
                            break;
                        }
                        else{
                            ErrorMessage = "Error: 变量重复定义 " + name_;
                            cout << "Error: " << name_ << " 重复定义" << endl;
                            return false;
                        }
                    }
                }
            }
            SEM.push(type);
            SEM.push(name);
            if (!InitialValue())    return false;
            return true;
        }
        else if (token.type == "K" && token.value == "char"){
            SEM.push(token.value);
            token = nextw();
            if (!Variable())   return false;
            string name = SEM.top(); SEM.pop();
            string type = SEM.top(); SEM.pop();
            // cout << name << " " << type << endl;
            if (name[name.size()-1] != ']'){        // 如果不是数组
                for (unsigned int i=0; i<SYNBL.size(); i++){
                    if (SYNBL[i].name == name){
                        if (SYNBL[i].type == -1){
                            SYNBL[i].type = CHAR;
                            SYNBL[i].cat = "V";
                            break;
                        }
                        else{
                            ErrorMessage = "Error: 变量重复定义 " + name;
                            cout << "Error: " << name << " 重复定义" << endl;
                            return false;
                        }
                    }
                }
            }
            else{                                   // 如果是数组
                int lens;
                string name_;
                for (unsigned int i=0; i<name.size(); i++){
                    if (name[i] == '['){
                        lens = stoi(name.substr(i+1, name.size()-i-2));
                        name_ = name.substr(0, i);
                        break;
                    }
                }
                for (unsigned int i=0; i<SYNBL.size(); i++){
                    if (SYNBL[i].name == name_){
                        if (SYNBL[i].type == -1){
                            SYNBL[i].type = TYPEL.size();
                            SYNBL[i].cat = "a";
                            SYNBL[i].addr = LEN.size();
                            LEN.push_back(lens*TYPEL[CHAR].tpoint);
                            TYPEL.push_back(TYPEL_Node("a", AINFL.size()));
                            AINFL.push_back(AINFL_Node(lens, CHAR, TYPEL[CHAR].tpoint));
                            break;
                        }
                        else{
                            ErrorMessage = "Error: 变量重复定义 " + name_;
                            cout << "Error: " << name_ << " 重复定义" << endl;
                            return false;
                        }
                    }
                }
            }
            SEM.push(type);
            SEM.push(name);
            if (!InitialValue())    return false;
            return true;
        }
        else{
            return false;
        }
    }
    else if (token.type == "K" && token.value == "int"){
        SEM.push(token.value);
        token = nextw();
        if (!Variable())   return false;
        string name = SEM.top(); SEM.pop();
        string type = SEM.top(); SEM.pop();
        // cout << name << " " << type << endl;
        if (name[name.size()-1] != ']'){        // 如果不是数组
            for (unsigned int i=0; i<SYNBL.size(); i++){
                if (SYNBL[i].name == name){
                    if (SYNBL[i].type == -1){
                        SYNBL[i].type = INT;
                        SYNBL[i].cat = "V";
                        break;
                    }
                    else{
                        ErrorMessage = "Error: 变量重复定义 " + name;
                        cout << "Error: " << name << " 重复定义" << endl;
                        return false;
                    }
                }
            }
        }
        else{                                   // 如果是数组
            int lens;
            string name_;
            for (unsigned int i=0; i<name.size(); i++){
                if (name[i] == '['){
                    lens = stoi(name.substr(i+1, name.size()-i-2));
                    name_ = name.substr(0, i);
                    break;
                }
            }
            for (unsigned int i=0; i<SYNBL.size(); i++){
                if (SYNBL[i].name == name_){
                    if (SYNBL[i].type == -1){
                        SYNBL[i].type = TYPEL.size();
                        SYNBL[i].cat = "a";
                        SYNBL[i].addr = LEN.size();
                        LEN.push_back(lens*TYPEL[INT].tpoint);
                        TYPEL.push_back(TYPEL_Node("a", AINFL.size()));
                        AINFL.push_back(AINFL_Node(lens, INT, TYPEL[INT].tpoint));
                        break;
                    }
                    else{
                        ErrorMessage = "Error: 变量重复定义 " + name_;
                        cout << "Error: " << name_ << " 重复定义" << endl;
                        return false;
                    }
                }
            }
        }
        SEM.push(type);
        SEM.push(name);
        if (!InitialValue())    return false;
        return true;
    }
    else if (token.type == "K" && token.value == "float"){
        SEM.push(token.value);
        token = nextw();
        if (!Variable())   return false;
        string name = SEM.top(); SEM.pop();
        string type = SEM.top(); SEM.pop();
        // cout << name << " " << type << endl;
        if (name[name.size()-1] != ']'){        // 如果不是数组
            for (unsigned int i=0; i<SYNBL.size(); i++){
                if (SYNBL[i].name == name){
                    if (SYNBL[i].type == -1){
                        SYNBL[i].type = FLOAT;
                        SYNBL[i].cat = "V";
                        break;
                    }
                    else{
                        ErrorMessage = "Error: 变量重复定义 " + name;
                        cout << "Error: " << name << " 重复定义" << endl;
                        return false;
                    }
                }
            }
        }
        else{                                   // 如果是数组
            int lens;
            string name_;
            for (unsigned int i=0; i<name.size(); i++){
                if (name[i] == '['){
                    lens = stoi(name.substr(i+1, name.size()-i-2));
                    name_ = name.substr(0, i);
                    break;
                }
            }
            for (unsigned int i=0; i<SYNBL.size(); i++){
                if (SYNBL[i].name == name_){
                    if (SYNBL[i].type == -1){
                        SYNBL[i].type = TYPEL.size();
                        SYNBL[i].cat = "a";
                        SYNBL[i].addr = LEN.size();
                        LEN.push_back(lens*TYPEL[FLOAT].tpoint);
                        TYPEL.push_back(TYPEL_Node("a", AINFL.size()));
                        AINFL.push_back(AINFL_Node(lens, FLOAT, TYPEL[FLOAT].tpoint));
                        break;
                    }
                    else{
                        ErrorMessage = "Error: 变量重复定义 " + name_;
                        cout << "Error: " << name_ << " 重复定义" << endl;
                        return false;
                    }
                }
            }
        }
        SEM.push(type);
        SEM.push(name);
        if (!InitialValue())    return false;
        return true;
    }
    else if (token.type == "K" && token.value == "double"){
        SEM.push(token.value);
        token = nextw();
        if (!Variable())   return false;
        string name = SEM.top(); SEM.pop();
        string type = SEM.top(); SEM.pop();
        // cout << name << " " << type << endl;
        if (name[name.size()-1] != ']'){        // 如果不是数组
            for (unsigned int i=0; i<SYNBL.size(); i++){
                if (SYNBL[i].name == name){
                    if (SYNBL[i].type == -1){
                        SYNBL[i].type = DOUBLE;
                        SYNBL[i].cat = "V";
                        break;
                    }
                    else{
                        ErrorMessage = "Error: 变量重复定义 " + name;
                        cout << "Error: " << name << " 重复定义" << endl;
                        return false;
                    }
                }
            }
        }
        else{                                   // 如果是数组
            int lens;
            string name_;
            for (unsigned int i=0; i<name.size(); i++){
                if (name[i] == '['){
                    lens = stoi(name.substr(i+1, name.size()-i-2));
                    name_ = name.substr(0, i);
                    break;
                }
            }
            for (unsigned int i=0; i<SYNBL.size(); i++){
                if (SYNBL[i].name == name_){
                    if (SYNBL[i].type == -1){
                        SYNBL[i].type = TYPEL.size();
                        SYNBL[i].cat = "a";
                        SYNBL[i].addr = LEN.size();
                        LEN.push_back(lens*TYPEL[DOUBLE].tpoint);
                        TYPEL.push_back(TYPEL_Node("a", AINFL.size()));
                        AINFL.push_back(AINFL_Node(lens, DOUBLE, TYPEL[DOUBLE].tpoint));
                        break;
                    }
                    else{
                        ErrorMessage = "Error: 变量重复定义 " + name_;
                        cout << "Error: " << name_ << " 重复定义" << endl;
                        return false;
                    }
                }
            }
        }
        SEM.push(type);
        SEM.push(name);
        if (!InitialValue())    return false;   
        return true;
    }
    else if (token.type == "K" && token.value == "char"){
        SEM.push(token.value);
        token = nextw();
        if (!Variable())   return false;
        string name = SEM.top(); SEM.pop();
        string type = SEM.top(); SEM.pop();
        // cout << name << " " << type << endl;
        if (name[name.size()-1] != ']'){        // 如果不是数组
            for (unsigned int i=0; i<SYNBL.size(); i++){
                if (SYNBL[i].name == name){
                    if (SYNBL[i].type == -1){
                        SYNBL[i].type = CHAR;
                        SYNBL[i].cat = "V";
                        break;
                    }
                    else{
                        ErrorMessage = "Error: 变量重复定义 " + name;
                        cout << "Error: " << name << " 重复定义" << endl;
                        return false;
                    }
                }
            }
        }
        else{                                   // 如果是数组
            int lens;
            string name_;
            for (unsigned int i=0; i<name.size(); i++){
                if (name[i] == '['){
                    lens = stoi(name.substr(i+1, name.size()-i-2));
                    name_ = name.substr(0, i);
                    break;
                }
            }
            for (unsigned int i=0; i<SYNBL.size(); i++){
                if (SYNBL[i].name == name_){
                    if (SYNBL[i].type == -1){
                        SYNBL[i].type = TYPEL.size();
                        SYNBL[i].cat = "a";
                        SYNBL[i].addr = LEN.size();
                        LEN.push_back(lens*TYPEL[CHAR].tpoint);
                        TYPEL.push_back(TYPEL_Node("a", AINFL.size()));
                        AINFL.push_back(AINFL_Node(lens, CHAR, TYPEL[CHAR].tpoint));
                        break;
                    }
                    else{
                        ErrorMessage = "Error: 变量重复定义 " + name_;
                        cout << "Error: " << name_ << " 重复定义" << endl;
                        return false;
                    }
                }
            }
        }
        SEM.push(type);
        SEM.push(name);
        if (!InitialValue())    return false;
        return true;
    }
    else if (token.type == "K" && token.value == "struct"){ //结构体
        SEM.push(token.value);
        token = nextw();
        if (token.type == "I"){
            SEM.push(token.value);
            token = nextw();
            int stack_num = SEM.size();
            if (token.type == "P" && token.value == "{"){   // 声明结构体
                token = nextw();
                if (!DeclarationStatementClosure())   return false;
                if (token.type == "P" && token.value == "}"){
                    token = nextw();
                    int struct_para_num = (SEM.size() - stack_num) / 2;
                    stack<string> struct_para_type, struct_para_name;
                    for (int i=0; i<struct_para_num; i++){
                        struct_para_name.push(SEM.top()); SEM.pop();
                        struct_para_type.push(SEM.top()); SEM.pop();
                    }
                    string struct_name = SEM.top(); SEM.pop();
                    string struct_type = SEM.top(); SEM.pop();
                    for (unsigned int i=0; i<SYNBL.size(); i++){
                        if (SYNBL[i].name == struct_name){
                            if (SYNBL[i].type == -1){
                                SYNBL[i].type = TYPEL.size();
                                SYNBL[i].cat = "t";
                                TYPEL.push_back(TYPEL_Node("d", RINFL.size()));
                                break;
                            }
                            else{
                                ErrorMessage = "Error: 变量重复定义 " + struct_name;
                                cout << "Error: " << struct_name << " 重复定义" << endl;
                                return false;
                            }
                        }
                    }
                    int struct_para_size = 0;
                    while(!struct_para_name.empty()){
                        string para_name = struct_para_name.top(); struct_para_name.pop();
                        string para_type = struct_para_type.top(); struct_para_type.pop();
                        int para_type_index;
                        for (unsigned int i=0; i<TYPEL.size(); i++){
                            if (TYPEL[i].type == para_type){
                                para_type_index = i;
                                break;
                            }
                        }
                        for (unsigned int i=0; i<SYNBL.size(); i++){
                            if (SYNBL[i].name == para_name){
                                SYNBL[i].type = para_type_index;
                                SYNBL[i].cat = "d";
                                SYNBL[i].addr = LEN.size();
                                LEN.push_back(TYPEL[para_type_index].tpoint);
                                break;
                            }
                        }
                        struct_para_size += TYPEL[para_type_index].tpoint;
                        RINFL.push_back(RINFL_Node(para_name, struct_para_size, para_type_index));
                    }
                    for (unsigned int i=0; i<SYNBL.size(); i++){
                        if (SYNBL[i].name == struct_name){
                            SYNBL[i].addr = LEN.size();
                            LEN.push_back(struct_para_size);
                            break;
                        }
                    }
                    return true;
                }
                else{
                    return false;
                }
            }
            else{       // 声明结构体变量
                string struct_name = SEM.top(); SEM.pop();
                string struct_type = SEM.top(); SEM.pop();
                // cout << struct_name << " " << struct_type << endl;
                for (unsigned int i=0; i<SYNBL.size(); i++){
                    if (SYNBL[i].name == struct_name && SYNBL[i].cat == "t" && TYPEL[SYNBL[i].type].type == "d"){
                        // cout << SYNBL[i].name << " " << SYNBL[i].cat << " " << TYPEL[SYNBL[i].type].type << endl;
                        if (token.type == "I"){
                            string name = token.value;
                            // cout << name << endl;
                            token = nextw();
                            for (unsigned int j=0; j<SYNBL.size(); j++){
                                if (SYNBL[j].name == name){
                                    SYNBL[j].cat = "V";
                                    SYNBL[j].type = SYNBL[i].type;
                                    SYNBL[j].addr = i;
                                    return true;
                                }
                            }
                            return false;
                        }
                        else{
                            return false;
                        }
                    }
                }
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

bool InitialValue()                     //赋初值
{
    if (token.type == "P" && token.value == "="){
        string t1="", t2="", t3="";
        if (!SEM.empty()){
            t1 = SEM.top(); SEM.pop();
            t2 = SEM.top(); SEM.pop();
            if (t1[t1.size()-1] != ']' && t1[0] != '.'){
                SEM.push(t2);
                SEM.push(t1);
                t1 = "";
                t2 = "";
            }
            else{
                t3 = " ";
            }
        }
        // cout << t1 << " " << t2 << endl;
        token = nextw();
        if (!RightValue())   return false;
        if (t3 == " "){
            if (t1[t1.size()-1] == ']'){        //数组
                int num = 0, i = 0;
                string name_;
                for (unsigned int i=0; i<t1.size(); i++){
                    if (t1[i] == '['){
                        num = stoi(t1.substr(i+1, t1.size()-i-2));
                        name_ = t1.substr(0, i);
                        break;
                    }
                }
                stack<string> temp_st;
                if (t2 == "int"){
                    for (int i=0; i<num; i++){
                        temp_st.push(SEM.top());
                        SEM.pop();
                    }
                    while(!temp_st.empty()){
                        QT.push_back(QT_Node("=", temp_st.top(), "_", name_+"["+to_string(i++)+"]"));
                        temp_st.pop();
                    }
                }
                else if(t2 == "float"){
                    for (int i=0; i<num; i++){
                        temp_st.push(SEM.top());
                        SEM.pop();
                    }
                    while(!temp_st.empty()){
                        QT.push_back(QT_Node("=", temp_st.top(), "_", name_+"["+to_string(i++)+"]"));
                        temp_st.pop();
                    }
                }
                else if(t2 == "double"){
                    for (int i=0; i<num; i++){
                        temp_st.push(SEM.top());
                        SEM.pop();
                    }
                    while(!temp_st.empty()){
                        QT.push_back(QT_Node("=", temp_st.top(), "_", name_+"["+to_string(i++)+"]"));
                        temp_st.pop();
                    }
                }
                else if(t2 == "char"){
                    string temp = SEM.top(); SEM.pop();
                    // cout << temp << endl;
                    for (unsigned int i=0; i<temp.size(); i++){
                        QT.push_back(QT_Node("=", "\'"+string(1,temp[i])+"\'", "_", name_+"["+to_string(i)+"]"));
                    }
                    // for (int i=temp.size(); i<num; i++){
                    //     QT.push_back(QT_Node("=", " ", "_", name_+"["+to_string(i)+"]"));
                    // }
                }
                else{
                    return false;
                }
            }
        }
        else{
            t1= SEM.top(); SEM.pop();
            t2 = SEM.top(); SEM.pop();
            t3 = SEM.top(); SEM.pop();
            // cout << t1 << " " << t2 << " " << t3 << endl;
            if (t3 == "char"){
                 QT.push_back(QT_Node("=", "\'"+t1+"\'", "_", t2));
            }
            else{
                QT.push_back(QT_Node("=", t1, "_", t2));
            }
        }
        return true;
    }
    else{
        // string t1= SEM.top(); SEM.pop();
        // string t2= SEM.top(); SEM.pop();
        // cout << t1 << " " << t2 << endl;
        // if (t1[0] == '['){
        //     SEM.pop();
        // }
        return true;
    }
}

bool RightValue()                       //右值
{
    if (token.type == "P" && token.value == "{"){       //数组
        token = nextw();
        if (!MutiVariable())   return false;
        if (token.type == "P" && token.value == "}"){
            token = nextw();
            return true;
        }
        else{
            return false;
        }
    }
    else if (token.type == "CC"){       //字符
        SEM.push(token.value);
        token = nextw();
        return true;
    }
    else if (token.type == "CS"){       //字符串
        SEM.push(token.value);
        token = nextw();
        return true;
    }
    else{                               //表达式
        if (!Expression())   return false;
        return true;
    }
}

bool MutiVariable()                     //多个数据
{
    if (token.type == "CI"){
        SEM.push(token.value);
        token = nextw();
        if (!DigitClosure())    return false;
        return true;
    }
    else if (token.type == "CF"){
        SEM.push(token.value);
        token = nextw();
        if (!DigitClosure())    return false;
        return true;
    }
    else{
        return false;
    }
}

bool DigitClosure()                     //数字闭包
{
    if (token.type == "P" && token.value == ","){
        token = nextw();
        if (token.type == "CI"){
            SEM.push(token.value);
            token = nextw();
            if (!DigitClosure())    return false;
            return true;
        }
        else if (token.type == "CF"){
            SEM.push(token.value);
            token = nextw();
            if (!DigitClosure())    return false;
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return true;
    }
}

bool DeclarationClosure()                //声明闭包
{
    if (token.type == "P" && token.value == ","){
        token = nextw();
        if (!Declaration())   return false;
        if (!DeclarationClosure())    return false;
        return true;
    }
    else{
        return true;
    }
}

bool FunctionBlock()                    //函数块
{
    if (!DeclarationStatementClosure())  return false;
    if (!FunctionBlockClosure())    return false;
    return true;
}

bool DeclarationStatementClosure()      //声明语句闭包
{
    if (token.type == "K" && (token.value == "int" || token.value == "float" || token.value == "double" 
        || token.value == "char" || token.value == "struct" || token.value == "const")){
        if (!DeclarationStatement())   return false;
        if (!DeclarationStatementClosure())   return false;
        return true;
    }
    else{
        return true;
    }   
}

bool DeclarationStatement()             //声明语句
{
    if (!Declaration())   return false;
    if (token.type == "P" && token.value == ";"){
        token = nextw();
        return true;
    }
    else{
        return false;
    }
    return true;
}

bool FunctionBlockClosure()             //函数块闭包
{
    if (token.type == "I"){
        if(!AssignmentStatement())   return false;
        if (!FunctionBlockClosure())    return false;
        return true;
    }
    else if (token.type == "K" && token.value == "for"){
        if(!ForStatement())   return false;
        if (!FunctionBlockClosure())    return false;
        return true;
    }
    else if (token.type == "K" && token.value == "if"){
        if(!IfStatement())   return false;
        if (!FunctionBlockClosure())    return false;
        return true;
    }
    else if (token.type == "K" && token.value == "while"){
        if(!WhileStatement())   return false;
        if (!FunctionBlockClosure())    return false;
        return true;
    }
    else if (token.type == "K" && token.value == "return"){
        if(!ReturnStatement())   return false;
        if (!FunctionBlockClosure())    return false;
        return true;
    }
    else{
        return true;
    }
}

bool AssignmentStatement()              //赋值语句
{
    if (token.type == "I"){
        if (!Variable())   return false;
        if (!AssignmentOrCall())   return false;
        return true;
    }
    else{
        return false;
    }
}

bool AssignmentOrCall()                //赋值或函数调用
{
    if (token.type == "P" && token.value == "="){
        token = nextw();
        if (!RightValue())   return false;
        string t1 = SEM.top();  SEM.pop();
        string t2 = SEM.top();  SEM.pop();
        // cout << t1 << " " << t2 << endl;
        if (t1[t1.size()-1] == ')'){
            if (token.type == "P" && token.value == "("){
                token = nextw();
                int SEM_num = SEM.size();
                if (!ParameterList())   return false;
                int param_num = (SEM.size() - SEM_num) / 2;
                string func_name = t1.substr(0, t1.size()-2);
                for (unsigned int i=0; i<SYNBL.size(); i++){
                    if (SYNBL[i].name == func_name){
                        if (SYNBL[i].cat == "F"){
                            if (param_num != PFINFL[SYNBL[i].type].fn){
                                ErrorMessage = "函数参数个数不匹配";
                                cout << "Error: " << func_name << " 有 " << PFINFL[SYNBL[i].type].fn << " 个参数, 但是提供了 " << param_num << " 个参数" << endl;
                                return false;
                            }
                            else{
                                int param_id = PFINFL[SYNBL[i].type].param;
                                for (int j=0; j<param_num; j++){
                                    string t3 = SEM.top();  SEM.pop();
                                    string t4 = SEM.top();  SEM.pop();
                                    // cout << t3 << " " << t4 << endl;
                                    QT.push_back(QT_Node("=", t3, "_", PARAML[param_id++].name));
                                }
                                QT_index++;
                                QT.push_back(QT_Node("=", t1, "_", "t"+to_string(QT_index)));
                                // T_type["t"+to_string(QT_index)] = GetTType(t1);
                                QT.push_back(QT_Node("=", "t"+to_string(QT_index), "_", t2));
                            }
                        }
                        else{
                            ErrorMessage = "Error: " + func_name + " 不是一个函数";
                            cout << "Error: " << func_name << " 不是一个函数" << endl;
                            return false;
                        }
                    }
                }
                if (token.type == "P" && token.value == ")"){
                    token = nextw();
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
            if (!CheckType(t1, t2))   return false;
            QT.push_back(QT_Node("=", t1, "_", t2));
        }

        if (token.type == "P" && token.value == ";"){
            token = nextw();
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

bool ParameterList()                    //参数列表
{
    // if (token.type == "I"){
    //     if (!Parameter())   return false;
    //     if (!ParameterClosure())   return false;
    //     return true;
    // }
    // else{
    //     return true;
    // }
    if (!Parameter())   return false;
    if (!ParameterClosure())   return false;
    return true;
}

bool Parameter()                        //参数
{
    if (token.type == "I"){
        SEM.push(token.type);
        SEM.push(token.value);
        token = nextw();
        return true;
    }
    else if (token.type == "CI"){
        SEM.push(token.type);
        SEM.push(token.value);
        token = nextw();
        return true;
    }
    else if (token.type == "CF"){
        SEM.push(token.type);
        SEM.push(token.value);
        token = nextw();
        return true;
    }
    else if (token.type == "CC"){
        SEM.push(token.type);
        SEM.push(token.value);
        token = nextw();
        return true;
    }
    else if (token.type == "CS"){
        SEM.push(token.type);
        SEM.push(token.value);
        token = nextw();
        return true;
    }
    else{
        return false;
    }
}

bool ParameterClosure()                 //参数闭包
{
    if (token.type == "P" && token.value == ","){
        token = nextw();
        if (!Parameter())   return false;
        if (!ParameterClosure())   return false;
        return true;
    }
    else{
        return true;
    }
}

bool ForStatement()                     //for语句
{
    if (token.type == "K" && token.value == "for"){
        token = nextw();
        if (token.type == "P" && token.value == "("){
            token = nextw();
            if (!AssignmentStatement())   return false;
            QT.push_back(QT_Node("for", "_", "_", "_"));
            if (!LogicalExpression())   return false;
            string t1= SEM.top();  SEM.pop();
            QT.push_back(QT_Node("do", t1, "_", "_"));
            if (token.type == "P" && token.value == ";"){
                token = nextw();
                if (!PostfixExpression())   return false;
                if (token.type == "P" && token.value == ")"){
                    token = nextw();
                    if (token.type == "P" && token.value == "{"){
                        token = nextw();
                        if (!FunctionBlock())   return false;

                        if (token.type == "P" && token.value == "}"){
                            QT.push_back(QT_Node("forend", "_", "_", "_"));
                            token = nextw();
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

bool LogicalExpression()                //逻辑表达式
{
    if (!Expression())   return false;
    if (token.type == "P" && token.value == "=="){
        token = nextw();
        if (!Expression())   return false;
        string t1 = SEM.top();  SEM.pop();
        string t2 = SEM.top();  SEM.pop();
        if (!CheckType(t1, t2)) return false;
        QT_index++;
        QT.push_back(QT_Node("==", t2, t1, "t"+to_string(QT_index)));
        T_type["t"+to_string(QT_index)] = GetTType(t1);
        SEM.push("t"+to_string(QT_index));
        return true;
    }
    else if (token.type == "P" && token.value == "!="){
        token = nextw();
        if (!Expression())   return false;
        string t1 = SEM.top();  SEM.pop();
        string t2 = SEM.top();  SEM.pop();
        if (!CheckType(t1, t2)) return false;
        QT_index++;
        QT.push_back(QT_Node("!=", t2, t1, "t"+to_string(QT_index)));
        T_type["t"+to_string(QT_index)] = GetTType(t1);
        SEM.push("t"+to_string(QT_index));
        return true;
    }
    else if (token.type == "P" && token.value == ">"){
        token = nextw();
        if (!Expression())   return false;
        string t1 = SEM.top();  SEM.pop();
        string t2 = SEM.top();  SEM.pop();
        if (!CheckType(t1, t2)) return false;
        QT_index++;
        QT.push_back(QT_Node(">", t2, t1, "t"+to_string(QT_index)));
        T_type["t"+to_string(QT_index)] = GetTType(t1);
        SEM.push("t"+to_string(QT_index));
        return true;
    }
    else if (token.type == "P" && token.value == ">="){
        token = nextw();
        if (!Expression())   return false;
        string t1 = SEM.top();  SEM.pop();
        string t2 = SEM.top();  SEM.pop();
        if (!CheckType(t1, t2)) return false;
        QT_index++;
        QT.push_back(QT_Node(">=", t2, t1, "t"+to_string(QT_index)));
        T_type["t"+to_string(QT_index)] = GetTType(t1);
        SEM.push("t"+to_string(QT_index));
        return true;
    }
    else if (token.type == "P" && token.value == "<"){
        token = nextw();
        if (!Expression())   return false;
        string t1 = SEM.top();  SEM.pop();
        string t2 = SEM.top();  SEM.pop();
        if (!CheckType(t1, t2)) return false;
        QT_index++;
        QT.push_back(QT_Node("<", t2, t1, "t"+to_string(QT_index)));
        T_type["t"+to_string(QT_index)] = GetTType(t1);
        SEM.push("t"+to_string(QT_index));
        return true;
    }
    else if (token.type == "P" && token.value == "<="){
        token = nextw();
        if (!Expression())   return false;
        string t1 = SEM.top();  SEM.pop();
        string t2 = SEM.top();  SEM.pop();
        if (!CheckType(t1, t2)) return false;
        QT_index++;
        QT.push_back(QT_Node("<=", t2, t1, "t"+to_string(QT_index)));
        T_type["t"+to_string(QT_index)] = GetTType(t1);
        SEM.push("t"+to_string(QT_index));
        return true;
    }
    else{
        return true;
    }
}

bool PostfixExpression()                //后缀表达式
{
    if (!Variable())   return false;
    if (token.type == "P" && token.value == "++"){
        string t1 = SEM.top();  SEM.pop();
        QT.push_back(QT_Node("+", t1, "1", t1));
        token = nextw();
        return true;
    }
    else if (token.type == "P" && token.value == "--"){
        string t1 = SEM.top();  SEM.pop();
        QT.push_back(QT_Node("-", t1, "1", t1));
        token = nextw();
        return true;
    }
    else{
        return false;
    }
}

bool IfStatement()                     //if语句
{
    if (token.type == "K" && token.value == "if"){
        token = nextw();
        if (token.type == "P" && token.value == "("){
            token = nextw();
            if (!LogicalExpression())   return false;
            if (token.type == "P" && token.value == ")"){
                string t1=SEM.top(); SEM.pop();
                QT.push_back(QT_Node("if", t1, "_", "_"));
                token = nextw();
                if (token.type == "P" && token.value == "{"){
                    token = nextw();
                    if (!FunctionBlock())   return false;
                    if (token.type == "P" && token.value == "}"){
                        QT.push_back(QT_Node("ifend", "_", "_", "_"));
                        token = nextw();
                        if (!ElseIfStatement())  return false;
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

bool ElseIfStatement()                 //else if语句
{
    if (token.type == "K" && token.value == "else"){
        token = nextw();
        if (token.type == "K" && token.value == "if"){
            token = nextw();
            if (token.type == "P" && token.value == "("){
                token = nextw();
                if (!LogicalExpression())   return false;
                if (token.type == "P" && token.value == ")"){
                    string t1=SEM.top(); SEM.pop();
                    QT.push_back(QT_Node("elif", t1, "_", "_"));
                    token = nextw();
                    if (token.type == "P" && token.value == "{"){
                        token = nextw();
                        if (!FunctionBlock())   return false;
                        if (token.type == "P" && token.value == "}"){
                            token = nextw();
                            QT.push_back(QT_Node("elifend", "_", "_", "_"));
                            if (!ElseIfStatement())  return false;
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
                else{
                    return false;
                }
            }
            else{
                return false;
            }
        }
        else{
            if (!ElseStatement())  return false;
            return true;
        }
    }
    else{
        return true;
    }
}

bool ElseStatement()                   //else语句
{
    if (token.type == "P" && token.value == "{"){
        QT.push_back(QT_Node("else", "_", "_", "_"));
        token = nextw();
        if (!FunctionBlock())   return false;
        if (token.type == "P" && token.value == "}"){
            QT.push_back(QT_Node("elseend", "_", "_", "_"));
            token = nextw();
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return true;
    }
}

bool WhileStatement()                   //while语句
{
    if (token.type == "K" && token.value == "while"){
        QT.push_back(QT_Node("while", "_", "_", "_"));
        token = nextw();
        if (token.type == "P" && token.value == "("){
            token = nextw();
            if (!LogicalExpression())   return false;
            if (token.type == "P" && token.value == ")"){
                string t1= SEM.top();  SEM.pop();
                QT.push_back(QT_Node("do", t1, "_", "_"));
                token = nextw();
                if (token.type == "P" && token.value == "{"){
                    token = nextw();
                    if (!FunctionBlock())   return false;
                    if (token.type == "P" && token.value == "}"){
                        QT.push_back(QT_Node("whend", "_", "_", "_"));
                        token = nextw();
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

bool ReturnStatement()                 //return语句
{
    if (token.type == "K" && token.value == "return"){
        token = nextw();
        if (!MutiFactor())   return false;
        if (token.type == "P" && token.value == ";"){
            string t1 = SEM.top();  SEM.pop();
            QT.push_back(QT_Node("return", t1, "_", "_"));
            token = nextw();
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

bool BaseBlock()                    //基本块划分
{
    int bs = QT.size();              
    int begin[bs+1] = {0};            //数组用作标记开始语句
    begin[0] = 1;
    int tempid=0;

    for(unsigned int i=1; i<QT.size(); i++){       //查找开始语句
        if(QT[i].op == "if")              begin[i+1] = 1;
        else if(QT[i].op == "ifend")      begin[i+1] = 1;
        else if(QT[i].op == "elif")       begin[i+1] = 1;
        else if(QT[i].op == "elifend")    begin[i+1] = 1;
        // else if(QT[i].op == "elifend" && QT[i+1].op != "else")    begin[i+1] = 1;
        else if(QT[i].op == "else")       begin[i+1] = 1;
        else if(QT[i].op == "elseend")    begin[i] = 1;
        else if(QT[i].op == "while")      begin[i+1] = 1;
        else if(QT[i].op == "whend")      begin[i+1] = 1;
        else if(QT[i].op == "for")        begin[i+1] = 1;
        else if(QT[i].op == "forend")     begin[i+1] = 1;
        else if(QT[i].op == "do")         begin[i+1] = 1;
        else if(QT[i].op == "funcbegin")  begin[i] = 1;
        // else if(QT[i].op == "return")     begin[i+1] = 1;
        else if(QT[i].num1[QT[i].num1.size()-1] == ')')begin[i] = 1;
    }
    for(unsigned int i=0; i<QT.size(); i++){
        if(begin[i] == 1)  tempid++;
        QT[i].block_id=tempid;
    }
    return true;
}

bool IsNumber(string s)            //判断是否为数字
{
    for(unsigned int i=0; i<s.length(); i++){
        if(s[i] < '0' || s[i] > '9')    return false;
    }
    return true;
}

bool ConstEasy()                    //常值表达式节省
{
    int temp;
    for(unsigned int i=0; i<QT.size(); i++){
        if(QT[i].op == "+" || QT[i].op == "-" || QT[i].op == "/" || QT[i].op == "*"){
            if(IsNumber(QT[i].num1) && IsNumber(QT[i].num2)){
                if (QT[i].op == "+") {
                    temp = atof(QT[i].num1.c_str()) + atof(QT[i].num2.c_str());
                    QT[i].op = "=";
                    QT[i].num1 = to_string(temp);
                    QT[i].num2 = "_";
                }
                else if (QT[i].op == "-") {
                    temp = atof(QT[i].num1.c_str()) - atof(QT[i].num2.c_str());
                    QT[i].op = "=";
                    QT[i].num1 = to_string(temp);
                    QT[i].num2 = "_";
                }
                else if (QT[i].op == "*") {
                    temp = atof(QT[i].num1.c_str()) * atof(QT[i].num2.c_str());
                    QT[i].op = "=";
                    QT[i].num1 = to_string(temp);
                    QT[i].num2 = "_";
                }
                else if (QT[i].op == "/") {
                    temp = atof(QT[i].num1.c_str()) / atof(QT[i].num2.c_str());
                    QT[i].op = "=";
                    QT[i].num1 = to_string(temp);
                    QT[i].num2 = "_";
                }
            }
        }
    }
    return true;
}

struct QT_Token{
    string name;
    string type;
    int active;
    QT_Token(){
        name = "_";
        type = "_";
        active = false;
    }
    QT_Token(string n, string t, int a){
        name = n;
        type = t;
        active = a;
    }
    QT_Token(const QT_Token& qt){
        name = qt.name;
        type = qt.type;
        active = qt.active;
    }
    void operator =(const QT_Token& qt){
        name = qt.name;
        type = qt.type;
        active = qt.active;
    }
};

struct QT_ACT_Node{
    int block_id;
    string op;
    QT_Token num1;
    QT_Token num2;
    QT_Token res;
    QT_ACT_Node(int b, string o, QT_Token n1, QT_Token n2, QT_Token r){
        block_id = b;
        op = o;
        num1 = n1;
        num2 = n2;
        res = r;
    }
    QT_ACT_Node(const QT_ACT_Node& qt){
        block_id = qt.block_id;
        op = qt.op;
        num1 = qt.num1;
        num2 = qt.num2;
        res = qt.res;
    }
    QT_ACT_Node(){
        block_id = 0;
        op = "";
        num1 = QT_Token();
        num2 = QT_Token();
        res = QT_Token();
    }
};

struct ACT_SYNBL_Node
{
    string name;
    int active;
    ACT_SYNBL_Node(string a, int b){
        name = a;
        active = b;
    }
};

vector<QT_ACT_Node> QT_ACT;
vector<ACT_SYNBL_Node> ACT_SYNBL;

string GetQTType(string s)
{
    if (s[0] == '_')    return "_";
    else if (s[0] == 't')    return "temp";
    else if (s[0] >= '0' && s[0] <= '9')    return "constant";
    else    return "variable";
}

void GetACT()
{
    int last_block_p = 0;
    for (unsigned int i = 0; i < QT_ACT.size(); i++) {
        if (i == 0 || QT_ACT[i].block_id != QT_ACT[i-1].block_id){
            if (i == 0) continue;
            else{
                for (int j = i-1; j >= last_block_p; j--) {
                    for (unsigned int k = 0; k < ACT_SYNBL.size(); k++) {
                        if (QT_ACT[j].num1.name == ACT_SYNBL[k].name) {
                            QT_ACT[j].num1.active = ACT_SYNBL[k].active;
                            ACT_SYNBL[k].active = true;
                        }
                        if (QT_ACT[j].num2.name == ACT_SYNBL[k].name) {
                            QT_ACT[j].num2.active = ACT_SYNBL[k].active;
                            ACT_SYNBL[k].active = true;
                        }
                        if (QT_ACT[j].res.name == ACT_SYNBL[k].name) {
                            QT_ACT[j].res.active = ACT_SYNBL[k].active;
                            ACT_SYNBL[k].active = false;
                        }
                    }
                }
                last_block_p = i;
                ACT_SYNBL.clear();
            }
        }
        bool flag = false;
        if (QT_ACT[i].num1.type == "temp") {
            for (unsigned int j = 0; j < ACT_SYNBL.size(); j++) {
                if (ACT_SYNBL[j].name == QT_ACT[i].num1.name) {
                    flag = true;
                    break;
                }
            }
            if (flag == false) ACT_SYNBL.push_back(ACT_SYNBL_Node(QT_ACT[i].num1.name, false));
        }
        else if (QT_ACT[i].num1.type == "variable") {
            for (unsigned int j = 0; j < ACT_SYNBL.size(); j++) {
                if (ACT_SYNBL[j].name == QT_ACT[i].num1.name) {
                    flag = true;
                    break;
                }
            }
            if (flag == false) ACT_SYNBL.push_back(ACT_SYNBL_Node(QT_ACT[i].num1.name, true));
        }
        flag = false;
        if (QT_ACT[i].num2.type == "temp") {
            for (unsigned int j = 0; j < ACT_SYNBL.size(); j++) {
                if (ACT_SYNBL[j].name == QT_ACT[i].num2.name) {
                    flag = true;
                    break;
                }
            }
            if (flag == false) ACT_SYNBL.push_back(ACT_SYNBL_Node(QT_ACT[i].num2.name, false));
        }
        else if (QT_ACT[i].num2.type == "variable") {
            for (unsigned int j = 0; j < ACT_SYNBL.size(); j++) {
                if (ACT_SYNBL[j].name == QT_ACT[i].num2.name) {
                    flag = true;
                    break;
                }
            }
            if (flag == false) ACT_SYNBL.push_back(ACT_SYNBL_Node(QT_ACT[i].num2.name, true));
        }
        flag = false;
        if (QT_ACT[i].res.type == "temp") {
            for (unsigned int j = 0; j < ACT_SYNBL.size(); j++) {
                if (ACT_SYNBL[j].name == QT_ACT[i].res.name) {
                    flag = true;
                    break;
                }
            }
            if (flag == false) ACT_SYNBL.push_back(ACT_SYNBL_Node(QT_ACT[i].res.name, false));
        }
        else if (QT_ACT[i].res.type == "variable") {
            for (unsigned int j = 0; j < ACT_SYNBL.size(); j++) {
                if (ACT_SYNBL[j].name == QT_ACT[i].res.name) {
                    flag = true;
                    break;
                }
            }
            if (flag == false) ACT_SYNBL.push_back(ACT_SYNBL_Node(QT_ACT[i].res.name, true));
        }
    }
    for (int j = QT_ACT.size()-1; j >= last_block_p; j--) {
        for (unsigned int k = 0; k < ACT_SYNBL.size(); k++){
            if (QT_ACT[j].num1.name == ACT_SYNBL[k].name){
                QT_ACT[j].num1.active = ACT_SYNBL[k].active;
                ACT_SYNBL[k].active = true;
            }
            if (QT_ACT[j].num2.name == ACT_SYNBL[k].name){
                QT_ACT[j].num2.active = ACT_SYNBL[k].active;
                ACT_SYNBL[k].active = true;
            }
            if (QT_ACT[j].res.name == ACT_SYNBL[k].name){
                QT_ACT[j].res.active = ACT_SYNBL[k].active;
                ACT_SYNBL[k].active = false;
            }
        }
    }
}

void show_ACT()
{
    cout << "————————————————————————————————————————————————带活跃信息的四元式————————————————————————————————————————————————" << endl;
    for (unsigned int i = 0; i < QT_ACT.size(); i++) {
        cout.width(10);
        cout << i+1;
        cout.width(10);
        cout << QT_ACT[i].block_id;
        cout.width(10);
        cout << QT_ACT[i].op;
        cout.width(15);
        cout << QT_ACT[i].num1.name + "(" + to_string(QT_ACT[i].num1.active) + ")";
        cout.width(10);
        cout << QT_ACT[i].num1.type;
        cout.width(15);
        cout << QT_ACT[i].num2.name + "(" + to_string(QT_ACT[i].num2.active) + ")";
        cout.width(10);
        cout << QT_ACT[i].num2.type;
        cout.width(15);
        cout << QT_ACT[i].res.name + "(" + to_string(QT_ACT[i].res.active) + ")";
        cout.width(10);
        cout << QT_ACT[i].res.type;
        cout << endl;
    }
}

struct OBJFUNC_Node{
    string name;
    string returnName;
    string returnType;
    int funcBegin;
    int funcEnd;
    OBJFUNC_Node(string name, string returnName, string returnType, int funcBegin, int funcEnd) {
        this->name = name;
        this->returnName = returnName;
        this->returnType = returnType;
        this->funcBegin = funcBegin;
        this->funcEnd = funcEnd;
    }
};
struct OBJStruct_Node{
    string name;
    vector<pair<string, int>> param;
    OBJStruct_Node(string name, vector<pair<string, int>> param){
        this->name = name;
        this->param = param;
    }
};

struct OBJDate_Node{
    string name;
    string type;
    string content;
    OBJDate_Node(string name, string type, string content){
        this->name = name;
        this->type = type;
        this->content = content;
    }
};

struct OBJ_Node{
    int id;
    string op;
    string num1;
    string num2;
    OBJ_Node(int id, string op, string num1, string num2){
        this->id = id;
        this->op = op;
        this->num1 = num1;
        this->num2 = num2;
    }
};

struct RDL_Node{
    bool active;
    string name;
    RDL_Node(string name, bool active){
        this->name = name;
        this->active = active;
    }
    RDL_Node(){
        this->name = "";
        this->active = false;
    }
    void clear(){
        active = false;
        name = "";
    }
};

vector<OBJFUNC_Node> OBJ_FUNC;
vector<OBJStruct_Node> OBJ_STRUCT;
vector<OBJDate_Node> OBJ_DATE;
vector<OBJ_Node> OBJ;
RDL_Node RDL;
stack<int> OBJ_SEM;
int OBJ_id = 0;


void show_OBJ()
{
    cout << "————————————————————————————————————————————————目标代码————————————————————————————————————————————————" << endl;
    cout << "结构体：" << endl;
    for (unsigned int i = 0; i < OBJ_STRUCT.size(); i++) {
        cout <<  OBJ_STRUCT[i].name  << " STRUC" << endl;
        for (unsigned int j = 0; j < OBJ_STRUCT[i].param.size(); j++) {
            if (OBJ_STRUCT[i].param[j].second == 0) cout << OBJ_STRUCT[i].param[j].first << " int " << "DW 0" << endl;
            else if (OBJ_STRUCT[i].param[j].second == 1) cout << OBJ_STRUCT[i].param[j].first << " float " << "DW 0" << endl;
            else if (OBJ_STRUCT[i].param[j].second == 2) cout << OBJ_STRUCT[i].param[j].first << " double " << "DW 0" << endl;
            else if (OBJ_STRUCT[i].param[j].second == 3) cout << OBJ_STRUCT[i].param[j].first << " char " << "DW \' \'" << endl;
        }
        cout <<  OBJ_STRUCT[i].name  << " ENDS" << endl;
    }
    cout << "函数：" << endl;
    for (unsigned int i = 0; i < OBJ_FUNC.size(); i++) {
        cout << OBJ_FUNC[i].name << " FUNC" << endl;
        cout << "RETURN " << OBJ_FUNC[i].returnName << " " << OBJ_FUNC[i].returnType << endl;
        cout << OBJ_FUNC[i].funcBegin << " " << OBJ_FUNC[i].funcEnd << endl;
    }
    cout << "数据段：" << endl;
    for (unsigned int i = 0; i < OBJ_DATE.size(); i++) {
        cout.width(10);
        // cout <<i+1;
        cout.width(10);
        cout << OBJ_DATE[i].name;
        cout.width(20);
        cout << OBJ_DATE[i].type;
        cout.width(20);
        
        cout << OBJ_DATE[i].content;
        cout << endl;
    }
    cout << "代码段：" << endl;
    for (unsigned int i=0; i<OBJ.size(); i++) {
        cout.width(10);
        cout << ".L"<<OBJ[i].id<<":";
        cout.width(10);
        cout << OBJ[i].op;
        cout.width(15);
        if(OBJ[i].num1!=""&&OBJ[i].num2!="")
        {
            cout << OBJ[i].num1;
            // cout.width(15);
            cout<<" , ";
            cout << OBJ[i].num2 << endl;
        }
        else{
            cout << OBJ[i].num1;
            cout<<"  ";
            cout << OBJ[i].num2 << endl;
        }
    }
}

void InsertTemp(string name)
{
    if (name[0] == 't'){
        bool flag = true;
        for (unsigned int j = 0; j < OBJ_DATE.size(); j++){
            if (OBJ_DATE[j].name == name){
                flag = false;
                break;
            }
        }
        if (flag)   OBJ_DATE.push_back(OBJDate_Node(name, "temp", "DW 0"));
    }
}

void GetOBJ()
{
    for (unsigned int i=0; i<SYNBL.size(); i++){
        if (SYNBL[i].cat == "V" && (SYNBL[i].type >=0 && SYNBL[i].type <=3)) {
            if (SYNBL[i].type == 0)         OBJ_DATE.push_back(OBJDate_Node(SYNBL[i].name, "int", "DW 0"));
            else if (SYNBL[i].type == 1)    OBJ_DATE.push_back(OBJDate_Node(SYNBL[i].name, "float", "DW 0"));
            else if (SYNBL[i].type == 2)    OBJ_DATE.push_back(OBJDate_Node(SYNBL[i].name, "double", "DW 0"));
            else if (SYNBL[i].type == 3)    OBJ_DATE.push_back(OBJDate_Node(SYNBL[i].name, "char", "DB \' \'"));
        }
        else if (SYNBL[i].cat == "Vf" && (SYNBL[i].type >=0 && SYNBL[i].type <=3)) {
            if (SYNBL[i].type == 0)         OBJ_DATE.push_back(OBJDate_Node(SYNBL[i].name, "int", "DW 0"));
            else if (SYNBL[i].type == 1)    OBJ_DATE.push_back(OBJDate_Node(SYNBL[i].name, "float", "DW 0"));
            else if (SYNBL[i].type == 2)    OBJ_DATE.push_back(OBJDate_Node(SYNBL[i].name, "double", "DW 0"));
            else if (SYNBL[i].type == 3)    OBJ_DATE.push_back(OBJDate_Node(SYNBL[i].name, "char", "DB \' \'"));
        }
        else if (SYNBL[i].cat == "a"){
            if (AINFL[TYPEL[SYNBL[i].type].tpoint].type == 0)         OBJ_DATE.push_back(OBJDate_Node(SYNBL[i].name, "Arrayint", "DW " +to_string(AINFL[TYPEL[SYNBL[i].type].tpoint].len)+ " DUP (0)"));
            else if (AINFL[TYPEL[SYNBL[i].type].tpoint].type == 1)    OBJ_DATE.push_back(OBJDate_Node(SYNBL[i].name, "Arrayfloat", "DW " +to_string(AINFL[TYPEL[SYNBL[i].type].tpoint].len)+ " DUP (0)"));
            else if (AINFL[TYPEL[SYNBL[i].type].tpoint].type == 2)    OBJ_DATE.push_back(OBJDate_Node(SYNBL[i].name, "Arraydouble", "DW " +to_string(AINFL[TYPEL[SYNBL[i].type].tpoint].len)+ " DUP (0)"));
            else if (AINFL[TYPEL[SYNBL[i].type].tpoint].type == 3)    OBJ_DATE.push_back(OBJDate_Node(SYNBL[i].name, "Arraychar", "DB " +to_string(AINFL[TYPEL[SYNBL[i].type].tpoint].len)+ " DUP (\' \')"));
        }
        else if (SYNBL[i].cat == "t"){
            OBJ_STRUCT.push_back(OBJStruct_Node(SYNBL[i].name, vector<pair<string, int>>()));
            for (unsigned int j=TYPEL[SYNBL[i].type].tpoint; j<RINFL.size(); j++){
                OBJ_STRUCT[OBJ_STRUCT.size()-1].param.push_back(make_pair(RINFL[j].name, RINFL[j].type));
                if (j !=0 && RINFL[j].off < RINFL[j-1].off) break;
            }
        }
        else if (SYNBL[i].cat == "V" && TYPEL[SYNBL[i].type].type == "d"){
            for (unsigned int j=0; j<OBJ_STRUCT.size(); j++){
                if (OBJ_STRUCT[j].name == SYNBL[SYNBL[i].addr].name){
                    OBJ_DATE.push_back(OBJDate_Node(SYNBL[i].name, SYNBL[SYNBL[i].addr].name, ""));
                    OBJ_DATE[OBJ_DATE.size()-1].content += "<";
                    for (unsigned int k=0; k<OBJ_STRUCT[j].param.size(); k++){
                        if (k != OBJ_STRUCT[j].param.size()-1) OBJ_DATE[OBJ_DATE.size()-1].content += ",";
                    }
                    OBJ_DATE[OBJ_DATE.size()-1].content += ">";
                }
            }
        }
    }

    int tmp = 0;
    for (unsigned int i=0; i<QT_ACT.size(); i++){
        // cout << "QT_ACT[" << i << "] = " << QT_ACT[i].op << " " << QT_ACT[i].res.name << endl;
        string bx; 
        int si;
        if(QT_ACT[i].num1.name[QT_ACT[i].num1.name.size()-1]==']')//数组数据
        {
            // cout << QT_ACT[i].num1.name << endl;
            for (unsigned int j=0; j<QT_ACT[i].num1.name.size(); j++){
                if (QT_ACT[i].num1.name[j] == '['){
                    bx = QT_ACT[i].num1.name.substr(0, j);
                    si = stoi(QT_ACT[i].num1.name.substr(j+1, QT_ACT[i].num1.name.size()-j-2));
                    // cout << bx << " " << si << endl;
                    // break;
                }
            }
            OBJ.push_back(OBJ_Node(++OBJ_id,"lea","bx",bx));
            if(si)
            {
                QT_ACT[i].num1.name="[bx+"+to_string(si*4)+"]";
            }
            else
            {
                QT_ACT[i].num1.name="[bx]";
            }
        }
        else if(QT_ACT[i].num2.name[QT_ACT[i].num2.name.size()-1]==']')//数组数据
        {
            // cout << QT_ACT[i].num2.name << endl;
            for (unsigned int j=0; j<QT_ACT[i].num2.name.size(); j++){
                if (QT_ACT[i].num2.name[j] == '['){
                    bx = QT_ACT[i].num2.name.substr(0, j);
                    si = stoi(QT_ACT[i].num2.name.substr(j+1, QT_ACT[i].num2.name.size()-j-2));
                    // cout << bx << " " << si << endl;
                    // break;
                }
            }
            OBJ.push_back(OBJ_Node(++OBJ_id,"lea","bx",bx));
            if(si)
            {
                QT_ACT[i].num2.name="[bx+"+to_string(si*4)+"]";
            }
            else
            {
                QT_ACT[i].num2.name="[bx]";
            }
        }
        else if(QT_ACT[i].res.name[QT_ACT[i].res.name.size()-1]==']')//数组数据
        {
            // cout << QT_ACT[i].res.name << endl;
            for (unsigned int j=0; j<QT_ACT[i].res.name.size(); j++){
                if (QT_ACT[i].res.name[j] == '['){
                    bx = QT_ACT[i].res.name.substr(0, j);
                    si = stoi(QT_ACT[i].res.name.substr(j+1, QT_ACT[i].res.name.size()-j-2));
                    // cout << bx << " " << si << endl;
                    // break;
                }
            }
            OBJ.push_back(OBJ_Node(++OBJ_id,"lea","bx",bx));
            if(si)
            {
                QT_ACT[i].res.name="[bx+"+to_string(si*4)+"]";
            }
            else
            {
                QT_ACT[i].res.name="[bx]";
            }
        }

        // 判断结构体
        if ((QT_ACT[i].num1.name[0]<'0' || QT_ACT[i].num1.name[0]>'9')&&QT_ACT[i].num1.name.find('.')){
            for (unsigned int j=0; j<QT_ACT[i].num1.name.size(); j++){
                if (QT_ACT[i].num1.name[j] == '.'){
                    OBJ.push_back(OBJ_Node(++OBJ_id, "lea", "bx", QT_ACT[i].num1.name.substr(0,j)));
                    // OBJ.push_back(OBJ_Node(++OBJ_id, "mov", "[bx]", QT_ACT[i].num1.name.substr(j+1,QT_ACT[i].num1.name.size())));
                    QT_ACT[i].num1.name="[bx]."+QT_ACT[i].num1.name.substr(j+1,QT_ACT[i].num1.name.size());
                    break;
                } 
            }
        }
        if((QT_ACT[i].num2.name[0]<'0' || QT_ACT[i].num2.name[0]>'9')&&QT_ACT[i].num2.name.find('.'))
        {
            for (unsigned int j=0; j<QT_ACT[i].num2.name.size(); j++){
                if(QT_ACT[i].num2.name[j] == '.')//有.则为结构体
                {
                    OBJ.push_back(OBJ_Node(++OBJ_id, "lea", "bx", QT_ACT[i].num2.name.substr(0,j)));
                    // OBJ.push_back(OBJ_Node(++OBJ_id, "mov", "[bx]", QT_ACT[i].num2.name.substr(j+1,QT_ACT[i].num2.name.size())));
                    QT_ACT[i].num2.name="[bx]."+QT_ACT[i].num2.name.substr(j+1,QT_ACT[i].num2.name.size());
                    break;
                }
            }
        }
        if((QT_ACT[i].res.name[0]<'0' || QT_ACT[i].res.name[0]>'9')&&QT_ACT[i].res.name.find('.'))
        {
            for (unsigned int j=0; j<QT_ACT[i].res.name.size(); j++){
                if(QT_ACT[i].res.name[j] == '.')//有.则为结构体
                {
                    OBJ.push_back(OBJ_Node(++OBJ_id, "lea", "bx", QT_ACT[i].res.name.substr(0,j)));
                    // OBJ.push_back(OBJ_Node(++OBJ_id, "mov", "[bx]", QT_ACT[i].res.name.substr(j+1,QT_ACT[i].res.name.size())));
                    QT_ACT[i].res.name="[bx]."+QT_ACT[i].res.name.substr(j+1,QT_ACT[i].res.name.size());
                    break;
                }
            }
        }

        if (i == 0 || QT_ACT[i].block_id != QT_ACT[i-1].block_id){
            if (i == 0) ;
            else{
                if (RDL.name != "" && RDL.active){
                    OBJ.push_back(OBJ_Node(++OBJ_id,"mov",RDL.name,"ax"));
                    InsertTemp(RDL.name);
                }
                RDL.clear();
            }
        }

        if (QT_ACT[i].op == "-" || QT_ACT[i].op == "/" || QT_ACT[i].op == ">" || QT_ACT[i].op == "<" ||
            QT_ACT[i].op == ">=" || QT_ACT[i].op == "<="){
            if (RDL.name == ""){
                OBJ.push_back(OBJ_Node(++OBJ_id, "mov", "ax", QT_ACT[i].num1.name));
            }
            else{
                if (RDL.name != "" && RDL.name != QT_ACT[i].num1.name){
                    if (RDL.active){
                        OBJ.push_back(OBJ_Node(++OBJ_id, "mov", RDL.name, "ax"));
                        InsertTemp(RDL.name);
                        OBJ.push_back(OBJ_Node(++OBJ_id, "mov", "ax", QT_ACT[i].num1.name));
                    }
                    else{
                        OBJ.push_back(OBJ_Node(++OBJ_id, "mov", "ax", QT_ACT[i].num1.name));
                    }
                }
                else if (RDL.name == QT_ACT[i].num1.name && RDL.name == QT_ACT[i].num2.name){
                    OBJ.push_back(OBJ_Node(++OBJ_id, "mov", QT_ACT[i].num1.name ,"ax"));
                    InsertTemp(QT_ACT[i].num1.name);
                }
            }

            if (QT_ACT[i].op == "-")    OBJ.push_back(OBJ_Node(++OBJ_id, "sub", "ax", QT_ACT[i].num2.name));
            else if (QT_ACT[i].op == "/"){
                OBJ.push_back(OBJ_Node(++OBJ_id, "mov", "cx", QT_ACT[i].num2.name));
                OBJ.push_back(OBJ_Node(++OBJ_id, "xor", "dx", "dx"));
                OBJ.push_back(OBJ_Node(++OBJ_id, "div", "", "cx"));
            }
            // else if (QT_ACT[i].op == ">") OBJ.push_back(OBJ_Node(++OBJ_id, "GT", "ax", QT_ACT[i].num2.name));
            // else if (QT_ACT[i].op == "<") OBJ.push_back(OBJ_Node(++OBJ_id, "LT", "ax", QT_ACT[i].num2.name));
            // else if (QT_ACT[i].op == ">=") OBJ.push_back(OBJ_Node(++OBJ_id, "GE", "ax", QT_ACT[i].num2.name));
            // else if (QT_ACT[i].op == "<=") OBJ.push_back(OBJ_Node(++OBJ_id, "LE", "ax", QT_ACT[i].num2.name));
            else if (QT_ACT[i].op == ">")OBJ.push_back(OBJ_Node(++OBJ_id, "cmp", "ax", QT_ACT[i].num2.name));
            else if (QT_ACT[i].op == "<") OBJ.push_back(OBJ_Node(++OBJ_id, "cmp", "ax", QT_ACT[i].num2.name));
            else if (QT_ACT[i].op == ">=")OBJ.push_back(OBJ_Node(++OBJ_id, "cmp", "ax", QT_ACT[i].num2.name));
            else if (QT_ACT[i].op == "<=") OBJ.push_back(OBJ_Node(++OBJ_id, "cmp", "ax", QT_ACT[i].num2.name));

            RDL.name = QT_ACT[i].res.name;
            RDL.active = QT_ACT[i].res.active;
        }
        else if (QT_ACT[i].op == "+" || QT_ACT[i].op == "*"){
            if (RDL.name == ""){
                OBJ.push_back(OBJ_Node(++OBJ_id, "mov", "ax", QT_ACT[i].num1.name));
                if (QT_ACT[i].op == "+")    OBJ.push_back(OBJ_Node(++OBJ_id, "add", "ax", QT_ACT[i].num2.name));
                else if (QT_ACT[i].op == "*"){
                    OBJ.push_back(OBJ_Node(++OBJ_id, "mov", "cx", QT_ACT[i].num2.name));
                    OBJ.push_back(OBJ_Node(++OBJ_id, "mul", "", "cx"));
                }
            }
            else if (RDL.name == QT_ACT[i].num1.name && RDL.name == QT_ACT[i].num2.name){
                OBJ.push_back(OBJ_Node(++OBJ_id, "mov", RDL.name, "ax"));
                InsertTemp(RDL.name);
                if (QT_ACT[i].op == "+")    OBJ.push_back(OBJ_Node(++OBJ_id, "add", "ax", QT_ACT[i].num2.name));
                else if (QT_ACT[i].op == "*"){
                    OBJ.push_back(OBJ_Node(++OBJ_id, "mov", "cx", QT_ACT[i].num2.name));
                    OBJ.push_back(OBJ_Node(++OBJ_id, "mul", "", "cx"));
                }
            }
            else if (RDL.name == QT_ACT[i].num1.name || RDL.name == QT_ACT[i].num2.name){
                if (RDL.name == QT_ACT[i].num1.name){
                    if (QT_ACT[i].num1.active) OBJ.push_back(OBJ_Node(++OBJ_id, "mov", RDL.name, "ax"));
                    InsertTemp(RDL.name);
                    if (QT_ACT[i].op == "+")    OBJ.push_back(OBJ_Node(++OBJ_id, "add", "ax", QT_ACT[i].num2.name));
                    else if (QT_ACT[i].op == "*"){
                        OBJ.push_back(OBJ_Node(++OBJ_id, "mov", "cx", QT_ACT[i].num2.name));
                        OBJ.push_back(OBJ_Node(++OBJ_id, "mul", "", "cx"));
                    }
                }
                else if (RDL.name == QT_ACT[i].num2.name){
                    if (QT_ACT[i].num2.active) OBJ.push_back(OBJ_Node(++OBJ_id, "mov", RDL.name, "ax"));
                    InsertTemp(RDL.name);
                    if (QT_ACT[i].op == "+")    OBJ.push_back(OBJ_Node(++OBJ_id, "add", "ax", QT_ACT[i].num1.name));
                    else if (QT_ACT[i].op == "*"){
                        OBJ.push_back(OBJ_Node(++OBJ_id, "mov", "cx", QT_ACT[i].num2.name));
                        OBJ.push_back(OBJ_Node(++OBJ_id, "mul", "", "cx"));
                    }
                }
            }
            else{
                if (RDL.name != "" && RDL.active)     OBJ.push_back(OBJ_Node(++OBJ_id, "mov", RDL.name, "ax"));
                InsertTemp(RDL.name);
                OBJ.push_back(OBJ_Node(++OBJ_id, "mov", "ax", QT_ACT[i].num1.name));
                if (QT_ACT[i].op == "+")    OBJ.push_back(OBJ_Node(++OBJ_id, "add", "ax", QT_ACT[i].num2.name));
                else if (QT_ACT[i].op == "*"){
                        OBJ.push_back(OBJ_Node(++OBJ_id, "mov", "cx", QT_ACT[i].num2.name));
                        OBJ.push_back(OBJ_Node(++OBJ_id, "mul", "", "cx"));
                    }
            }

            RDL.name = QT_ACT[i].res.name;
            RDL.active = QT_ACT[i].res.active;
        }
        //跳转指令
		else if(QT_ACT[i].op == "if" || QT_ACT[i].op=="elif")
		{
				if(RDL.name==""){
					// OBJ.push_back(OBJ_Node(++OBJ_id,"mov","ax",QT_ACT[i].num1.name));//移进
                    // OBJ.push_back(OBJ_Node(++OBJ_id,"fj","ax",""));
                    if(QT_ACT[i-1].op=="<")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"jna","",""));
                    else if(QT_ACT[i-1].op==">")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"jnb","",""));
                    else if(QT_ACT[i-1].op=="<=")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"ja","",""));
                    else if(QT_ACT[i-1].op==">=")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"jb","",""));

					OBJ_SEM.push(OBJ_id);
				}
				else if(RDL.name==QT_ACT[i].num1.name)
				{
					if(RDL.active){
						// OBJ.push_back(OBJ_Node(++OBJ_id,"mov",RDL.name,"ax"));//移出
						// OBJ.push_back(OBJ_Node(++OBJ_id,"fj","ax",""));
                    if(QT_ACT[i-1].op=="<")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"jna","",""));
                    else if(QT_ACT[i-1].op==">")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"jnb","",""));
                    else if(QT_ACT[i-1].op=="<=")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"ja","",""));
                    else if(QT_ACT[i-1].op==">=")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"jb","",""));
					}
					else{
						// OBJ.push_back(OBJ_Node(++OBJ_id,"fj","ax",""));
                    if(QT_ACT[i-1].op=="<")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"jna","",""));
                    else if(QT_ACT[i-1].op==">")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"jnb","",""));
                    else if(QT_ACT[i-1].op=="<=")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"ja","",""));
                    else if(QT_ACT[i-1].op==">=")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"jb","",""));
					}
					OBJ_SEM.push(OBJ_id);
					RDL.name="";
					RDL.active = false;
				}
				else{
					if(RDL.active)
					{
						// OBJ.push_back(OBJ_Node(++OBJ_id,"mov",RDL.name,"ax"));
						// OBJ.push_back(OBJ_Node(++OBJ_id,"mov","ax",QT_ACT[i].num1.name));
						// OBJ.push_back(OBJ_Node(++OBJ_id,"fj","ax",""));
                    if(QT_ACT[i-1].op=="<")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"jna","",""));
                    else if(QT_ACT[i-1].op==">")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"jnb","",""));
                    else if(QT_ACT[i-1].op=="<=")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"ja","",""));
                    else if(QT_ACT[i-1].op==">=")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"jb","",""));
                    }
					else {
						// OBJ.push_back(OBJ_Node(++OBJ_id,"mov","ax",QT_ACT[i].num1.name));
						// OBJ.push_back(OBJ_Node(++OBJ_id,"fj","ax",""));
                    if(QT_ACT[i-1].op=="<")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"jna","",""));
                    else if(QT_ACT[i-1].op==">")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"jnb","",""));
                    else if(QT_ACT[i-1].op=="<=")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"ja","",""));
                    else if(QT_ACT[i-1].op==">=")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"jb","",""));
					}
					OBJ_SEM.push(OBJ_id);
					RDL.name="";
                    RDL.active = false;
				}
		}
		else if(QT_ACT[i].op=="else")
		{
			if(RDL.active&&RDL.name!=""){
				OBJ.push_back(OBJ_Node(++OBJ_id,"mov",RDL.name,"ax"));
                InsertTemp(RDL.name);
            }
			tmp = OBJ_SEM.top();
			OBJ_SEM.pop();
			OBJ[tmp-1].num2 = ".L"+to_string(OBJ_id+2);
            OBJ.push_back(OBJ_Node(++OBJ_id,"jmp","",""));
            OBJ_SEM.push(OBJ_id);
		}
        else if(QT_ACT[i].op=="elseend")
        {
            if(RDL.active&&RDL.name!=""){
				OBJ.push_back(OBJ_Node(++OBJ_id,"mov",RDL.name,"ax"));
                InsertTemp(RDL.name);
            }
            tmp = OBJ_SEM.top();
			OBJ_SEM.pop();
			OBJ[tmp-1].num2 = ".L"+to_string(OBJ_id+1);
        }
        else if(QT_ACT[i].op=="ifend")
        {
            if(RDL.active&&RDL.name!=""){
				OBJ.push_back(OBJ_Node(++OBJ_id,"mov",RDL.name,"ax"));
                InsertTemp(RDL.name);
            }
            tmp = OBJ_SEM.top();
			OBJ_SEM.pop();
			OBJ[tmp-1].num2 = ".L"+to_string(OBJ_id+1);
        }
        else if(QT_ACT[i].op=="while")
            OBJ_SEM.push(OBJ_id);
        else if(QT_ACT[i].op=="do")
        {
            if(RDL.name==""){
                // OBJ.push_back(OBJ_Node(++OBJ_id,"mov","ax",QT_ACT[i].num1.name));
                // OBJ.push_back(OBJ_Node(++OBJ_id,"fj","ax",""));
                    if(QT_ACT[i-1].op=="<")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"jna","",""));
                    else if(QT_ACT[i-1].op==">")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"jnb","",""));
                    else if(QT_ACT[i-1].op=="<=")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"ja","",""));
                    else if(QT_ACT[i-1].op==">=")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"jb","",""));
                OBJ_SEM.push(OBJ_id);
            }
            else if(RDL.name==QT_ACT[i].num1.name)
            {
                if(RDL.active)
                {
                    // OBJ.push_back(OBJ_Node(++OBJ_id,"mov",RDL.name,"ax"));//移出
					// OBJ.push_back(OBJ_Node(++OBJ_id,"fj","ax",""));
                    if(QT_ACT[i-1].op=="<")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"jna","",""));
                    else if(QT_ACT[i-1].op==">")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"jnb","",""));
                    else if(QT_ACT[i-1].op=="<=")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"ja","",""));
                    else if(QT_ACT[i-1].op==">=")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"jb","",""));
                }
                else
                {
                    // OBJ.push_back(OBJ_Node(++OBJ_id,"fj","ax",""));
                    if(QT_ACT[i-1].op=="<")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"jna","",""));
                    else if(QT_ACT[i-1].op==">")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"jnb","",""));
                    else if(QT_ACT[i-1].op=="<=")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"ja","",""));
                    else if(QT_ACT[i-1].op==">=")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"jb","",""));   
                }
                OBJ_SEM.push(OBJ_id);
                RDL.name="";
                RDL.active = false;
            }
            else{
                if(RDL.active)
                {
                    // OBJ.push_back(OBJ_Node(++OBJ_id,"mov",RDL.name,"ax"));
					// OBJ.push_back(OBJ_Node(++OBJ_id,"mov","ax",QT_ACT[i].num1.name));
					// OBJ.push_back(OBJ_Node(++OBJ_id,"fj","ax",""));
                    if(QT_ACT[i-1].op=="<")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"jna","",""));
                    else if(QT_ACT[i-1].op==">")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"jnb","",""));
                    else if(QT_ACT[i-1].op=="<=")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"ja","",""));
                    else if(QT_ACT[i-1].op==">=")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"jb","",""));
                }
                else {
					// OBJ.push_back(OBJ_Node(++OBJ_id,"mov","ax",QT_ACT[i].num1.name));
					// OBJ.push_back(OBJ_Node(++OBJ_id,"fj","ax",""));
                    if(QT_ACT[i-1].op=="<")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"jna","",""));
                    else if(QT_ACT[i-1].op==">")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"jnb","",""));
                    else if(QT_ACT[i-1].op=="<=")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"ja","",""));
                    else if(QT_ACT[i-1].op==">=")
                        OBJ.push_back(OBJ_Node(++OBJ_id,"jb","",""));
                }
				OBJ_SEM.push(OBJ_id);
				RDL.name="";
                RDL.active = false;
            }
        }
        else if(QT_ACT[i].op=="whend")
        {
            if(RDL.active&&RDL.name!=""){
				OBJ.push_back(OBJ_Node(++OBJ_id,"mov",RDL.name,"ax"));
                InsertTemp(RDL.name);
            }
            RDL.name="";
            RDL.active = false;
            tmp = OBJ_SEM.top();
			OBJ_SEM.pop();
			OBJ[tmp-1].num2 = ".L"+to_string(OBJ_id+2);
            OBJ.push_back(OBJ_Node(++OBJ_id,"jmp","",".L"+to_string(tmp-2)));
        }
        else if(QT_ACT[i].op=="for")
            OBJ_SEM.push(OBJ_id);
        else if(QT_ACT[i].op=="forend")
        {
            if(RDL.active&&RDL.name!=""){
				OBJ.push_back(OBJ_Node(++OBJ_id,"mov",RDL.name,"ax"));
                InsertTemp(RDL.name);
            }
            RDL.name="";
            RDL.active = false;
            tmp = OBJ_SEM.top();
			OBJ_SEM.pop();
			OBJ[tmp-1].num2 = ".L"+to_string(OBJ_id+2);
            OBJ.push_back(OBJ_Node(++OBJ_id,"jmp","",".L"+to_string(tmp)));
        }
        //赋值语句
        else if(QT_ACT[i].op=="=")
        {
            if(QT_ACT[i].num1.name.find('.')!=string::npos&&QT_ACT[i].num1.name[0]>'0' && QT_ACT[i].num1.name[0]<'9')
            {
                // OBJ.push_back(OBJ_Node(++OBJ_id,"fld","",QT_ACT[i].num1.name));
                // cout<<QT_ACT[i].num1.name.find('.')<<endl;
            }
            else if (QT_ACT[i].num1.name[QT_ACT[i].num1.name.size()-1] == ')'){
                OBJ.push_back(OBJ_Node(++OBJ_id,"call","",QT_ACT[i].num1.name.substr(0,QT_ACT[i].num1.name.size()-2)));
                OBJ.push_back(OBJ_Node(++OBJ_id,"mov", QT_ACT[i].res.name, "ax"));
            }
            else
            {
                if(RDL.name=="")
                {
                    if (QT_ACT[i].num1.name[0] == '\''){
                        OBJ.push_back(OBJ_Node(++OBJ_id,"mov","al",QT_ACT[i].num1.name));//移进
                        OBJ.push_back(OBJ_Node(++OBJ_id,"mov",QT_ACT[i].res.name,"al")); 
                        InsertTemp(QT_ACT[i].res.name);
                    }
                    else{
                        OBJ.push_back(OBJ_Node(++OBJ_id,"mov","ax",QT_ACT[i].num1.name));//移进
                        OBJ.push_back(OBJ_Node(++OBJ_id,"mov",QT_ACT[i].res.name,"ax")); 
                        InsertTemp(QT_ACT[i].res.name);
                    }
                    // OBJ.push_back(OBJ_Node(++OBJ_id,"mov","ax",QT_ACT[i].num1.name));//移进
                    // OBJ.push_back(OBJ_Node(++OBJ_id,"mov",QT_ACT[i].res.name,"ax"));
                    // InsertTemp(QT_ACT[i].res.name);
                }
                else if(RDL.name == QT_ACT[i].num1.name)
                {
                    if(RDL.name != "" && RDL.active)
                    {   
                        OBJ.push_back(OBJ_Node(++OBJ_id,"mov",RDL.name,"ax"));//移出
                        InsertTemp(RDL.name);
                        if (QT_ACT[i].num1.name[0] == '\''){
                            OBJ.push_back(OBJ_Node(++OBJ_id,"mov","al",QT_ACT[i].num1.name));//移进
                            OBJ.push_back(OBJ_Node(++OBJ_id,"mov",QT_ACT[i].res.name,"al")); 
                            InsertTemp(QT_ACT[i].res.name);
                        }
                        else{
                            OBJ.push_back(OBJ_Node(++OBJ_id,"mov","ax",QT_ACT[i].num1.name));//移进
                            OBJ.push_back(OBJ_Node(++OBJ_id,"mov",QT_ACT[i].res.name,"ax")); 
                            InsertTemp(QT_ACT[i].res.name);
                        }
                        // OBJ.push_back(OBJ_Node(++OBJ_id,"mov","ax",QT_ACT[i].num1.name));
                        // OBJ.push_back(OBJ_Node(++OBJ_id,"mov",QT_ACT[i].res.name,"ax"));
                        // InsertTemp(QT_ACT[i].res.name);
                    }
                }
                else
                {
                    if(RDL.name != "" && RDL.active)
                    {
                        OBJ.push_back(OBJ_Node(++OBJ_id,"mov",RDL.name,"ax"));//移出
                        InsertTemp(RDL.name);
                        if (QT_ACT[i].num1.name[0] == '\''){
                            OBJ.push_back(OBJ_Node(++OBJ_id,"mov","al",QT_ACT[i].num1.name));//移进
                            OBJ.push_back(OBJ_Node(++OBJ_id,"mov",QT_ACT[i].res.name,"al")); 
                            InsertTemp(QT_ACT[i].res.name);
                        }
                        else{
                            OBJ.push_back(OBJ_Node(++OBJ_id,"mov","ax",QT_ACT[i].num1.name));//移进
                            OBJ.push_back(OBJ_Node(++OBJ_id,"mov",QT_ACT[i].res.name,"ax")); 
                            InsertTemp(QT_ACT[i].res.name);
                        }
                    }
                    else
                    {
                       if (QT_ACT[i].num1.name[0] == '\''){
                            OBJ.push_back(OBJ_Node(++OBJ_id,"mov","al",QT_ACT[i].num1.name));//移进
                            OBJ.push_back(OBJ_Node(++OBJ_id,"mov",QT_ACT[i].res.name,"al")); 
                            InsertTemp(QT_ACT[i].res.name);
                        }
                        else{
                            OBJ.push_back(OBJ_Node(++OBJ_id,"mov","ax",QT_ACT[i].num1.name));//移进
                            OBJ.push_back(OBJ_Node(++OBJ_id,"mov",QT_ACT[i].res.name,"ax")); 
                            InsertTemp(QT_ACT[i].res.name);
                        }
                    }
                }
                RDL.name=QT_ACT[i].res.name;
            }
        }
        else if (QT_ACT[i].op == "funcbegin")
        {
            OBJ_FUNC.push_back(OBJFUNC_Node(QT_ACT[i].res.name, "", "", OBJ_id+1, 0));
        }
        else if (QT_ACT[i].op == "funcend"){
            // cout << OBJ_FUNC.size() << endl;
            OBJ_FUNC[OBJ_FUNC.size()-1].returnName = QT_ACT[i].num1.name;
            for (unsigned int j=0; j<OBJ_DATE.size(); j++)
            {
                if (OBJ_DATE[j].name == QT_ACT[i].num1.name)
                {
                    OBJ_FUNC[OBJ_FUNC.size()-1].returnType = OBJ_DATE[j].type;
                    break;
                }
            }
            OBJ_FUNC[OBJ_FUNC.size()-1].funcEnd = OBJ_id+1;
        }
    }
    OBJ.push_back(OBJ_Node(++OBJ_id,"mov","ah","4ch"));
    OBJ.push_back(OBJ_Node(++OBJ_id,"int","","21h"));
}

struct DGA_Node
{   
    int id;
    int left;
    int right;
    string op;
    pair<string, string> main_sign;
    vector<pair<string, string>> addi_sign;
    DGA_Node(int _id, int _left, int _right, string _op, pair<string, string> _main_sign, vector<pair<string, string>> _addi_sign)
    {
        id = _id;
        left = _left;
        right = _right;
        op = _op;
        main_sign = _main_sign;
        addi_sign = _addi_sign;
    }
    // DGA_Node()
    // {
    //     id = 0;
    //     left = 0;
    //     right = 0;
    //     op = "";
    //     main_sign = make_pair("","");
    //     addi_sign.clear();
    // }
};

vector<DGA_Node> DGA;
vector<QT_ACT_Node> QT_ACT_EASY;
int DGA_id = 0;

void show_QT_EASY()
{
    cout << "————————————————————————————————————————————————优化后的四元式————————————————————————————————————————————————" << endl;
    for (unsigned int i = 0; i < QT_ACT_EASY.size(); i++) {
        cout.width(10);
        cout << i;
        cout.width(10);
        cout << QT_ACT_EASY[i].block_id;
        cout.width(10);
        cout << QT_ACT_EASY[i].op;
        cout.width(15);
        cout << QT_ACT_EASY[i].num1.name ;
        cout.width(15);
        cout << QT_ACT_EASY[i].num2.name ;
        cout.width(15);
        cout << QT_ACT_EASY[i].res.name  << endl;
    }
}

void show_DGA()
{
    cout << "DGA" << endl;
    for (unsigned int i = 0; i < DGA.size(); i++) {
        cout.width(10);
        cout << i;
        cout.width(10);
        cout << DGA[i].id;
        cout.width(10);
        cout << DGA[i].left-1;
        cout.width(15);
        cout << DGA[i].right-1;
        cout.width(15);
        cout << DGA[i].op;
        cout.width(15);
        cout << DGA[i].main_sign.first;
        cout.width(15);
        cout << DGA[i].main_sign.second;
        cout.width(15);
        for(unsigned int j=0;j<DGA[i].addi_sign.size();j++){
            cout.width(15);
            cout << DGA[i].addi_sign[j].first;
            cout.width(15);
            cout << DGA[i].addi_sign[j].second;
        }
        cout << endl;
    }
}

int GetDGANode(string B)    //获取对应的DGA节点
{
    int n=0;
    for(unsigned int i=0;i<DGA.size();i++)
    {
        if(DGA[i].main_sign.first==B)
        {
            n=i+1;
        }
        for(unsigned int j=0;j<DGA[i].addi_sign.size();j++)
        {
            if(DGA[i].addi_sign[j].first==B)
            {
                n=i+1;
            }
        }
    }
    return n;
}

void MakeDGALeaf(string B, string type)   //创建叶子节点
{
    // DGA_Node temp;
    // temp.id=DGA.size();
    // temp.main_sign.name=B;
    // temp.main_sign.type=type;
    DGA.push_back(DGA_Node(DGA.size(),0,0,"_",make_pair(B,type),vector<pair<string, string>>()));
}

int MakeDGANode(string op, string B, string C)
{
    // DGA_Node temp;
    // temp.id=DGA.size();
    // temp.op=op;
    // temp.left=GetDGANode(B);
    // temp.right=GetDGANode(C);
    DGA.push_back(DGA_Node(DGA.size(),GetDGANode(B),GetDGANode(C),op,make_pair("_","_"),vector<pair<string, string>>()));
    return DGA.size();
}

void DeleteDGANode(int id)              //删除DGA节点
{
    DGA[id-1].main_sign.first="_";
    DGA[id-1].id=0;
    for(unsigned int i=id-1;i<DGA.size()-1;i++)
    {
        DGA[i].id=DGA[i+1].id;
        DGA[i].main_sign.first=DGA[i+1].main_sign.first;
        DGA[i].main_sign.second=DGA[i+1].main_sign.second;
        DGA[i].left=DGA[i+1].left;
        DGA[i].right=DGA[i+1].right;
        DGA[i].op=DGA[i+1].op;
        DGA[i].addi_sign.clear();
        for(unsigned int j=0;j<DGA[i+1].addi_sign.size();j++) {
            DGA[i].addi_sign.push_back(make_pair(DGA[i+1].addi_sign[j].first,DGA[i+1].addi_sign[j].second));
        }
    }
    DGA.pop_back();
}

int FindDGANode(string op, string B, string C)
{
    int n=0;
    int lt,rt;
    lt=GetDGANode(B);
    rt=GetDGANode(C);
    for(unsigned int i=0;i<DGA.size();i++)
    {
        if (DGA[i].op == op && DGA[i].left == lt && DGA[i].right == rt)
        {
            n=i+1;
            break;
        }
    }
    return n;
}

void DGAaddition(int id, string A, string type)         //为DGA结点添加附加标记
{
 
    int k;
    QT_Token temp;
    k=GetDGANode(A);
    if(k!=0){
        for(unsigned j=0;j<DGA[k-1].addi_sign.size();j++)
        {
            if(DGA[k-1].addi_sign[j].first==A)
            {
                // DGA[k-1].addi_sign.erase(DGA[k-1].addi_sign.begin()+j-1);
                DGA[k-1].addi_sign[j].first = "_"+DGA[k-1].addi_sign[j].first;
                DGA[k-1].addi_sign[j].second = "_";
            }
        }
    }
    if(DGA[id-1].main_sign.first!="_"){
        // cout << DGA[id-1].addi_sign.size() << endl;
        temp.name=A;
        temp.type=type;
        DGA[id-1].addi_sign.push_back(make_pair(A,type));
    }
    else{
        DGA[id-1].main_sign.first=A;
        DGA[id-1].main_sign.second=type;
    }

    if(DGA[id-1].main_sign.second=="temp"){
        for(unsigned j=0;j<DGA[id-1].addi_sign.size();j++)
        {
            if(DGA[id-1].addi_sign[j].second=="variable")
            {
                string tempname;
                tempname=DGA[id-1].addi_sign[j].first;
                DGA[id-1].addi_sign[j].first=DGA[id-1].main_sign.first;
                DGA[id-1].main_sign.first=tempname;
                DGA[id-1].main_sign.second="variable";
                DGA[id-1].addi_sign[j].second="temp";
            }
        }
    }


}

int JudgeType(string op)
{
    if(op=="=")return 0;
    else if(op==">"||op=="<"||op=="+"||op=="-"||op=="*"||op=="/")return 1;
    else if(op=="while"||op=="whend"||op=="do"||op=="if"||op=="ifend"||op=="for"||
            op=="forend"||op=="elif"||op=="elifend"||op=="else"||op=="elseend"||
            op=="funcbegin"||op=="funcend"||op=="return"||op=="break"||op=="continue")return 2;
    else return -1;
}

string CoutValue(string op, string B, string C)
{
    string p;
    if(op=="+") p=to_string(atoi(B.c_str())+atoi(C.c_str()));
    if(op=="-") p=to_string(atoi(B.c_str())-atoi(C.c_str()));
    if(op=="*") p=to_string(atoi(B.c_str())*atoi(C.c_str()));
    if(op=="/") p=to_string(atoi(B.c_str())/atoi(C.c_str()));
    return p;
}

void MakeEasyQT(int block)
{

    QT_ACT_Node tempNode;
    int left,right;
    for(unsigned int i=0;i<DGA.size();i++){
        if(DGA[i].op=="_"){
            for(unsigned int j=0;j<DGA[i].addi_sign.size();j++){
                if(DGA[i].addi_sign[j].second=="variable"){
                    tempNode.block_id = block;
                    tempNode.op = "=";
                    tempNode.num2.name = "_";
                    tempNode.num2.type = "_";
                    tempNode.num1.name = DGA[i].main_sign.first;
                    tempNode.num1.type = DGA[i].main_sign.second;
                    tempNode.res.name = DGA[i].addi_sign[j].first;
                    tempNode.res.type = DGA[i].addi_sign[j].second;
                    QT_ACT_EASY.push_back(tempNode);
                }
            }
        }
        else{
            left=DGA[i].left;
            right=DGA[i].right;
            tempNode.res.name=DGA[i].main_sign.first;
            tempNode.res.type=DGA[i].main_sign.second;
            tempNode.block_id=block;
            tempNode.op=DGA[i].op;
            tempNode.num1.name=DGA[left-1].main_sign.first;
            tempNode.num1.type=DGA[left-1].main_sign.second;
            tempNode.num2.name=DGA[right-1].main_sign.first;
            tempNode.num2.type=DGA[right-1].main_sign.second;
            QT_ACT_EASY.push_back(tempNode);
        
        }
    }

}

void OptimizeDGA()
{
    int i=0;
    int j=0;
    int blockmax=QT_ACT[QT_ACT.size()-1].block_id;
    int nleft,nright;
    int bn;
    int n;
    string p,B,C,A;

    for(bn=1;bn<=blockmax;bn++){
        if(JudgeType(QT_ACT[i].op)==2){
            QT_ACT_EASY.push_back(QT_ACT[i]);
            i++;
            bn=QT_ACT[i].block_id;
        }

        while(i != int(QT_ACT.size()) && QT_ACT[i].op!="_" && QT_ACT[i].block_id==bn){
            // show_DGA();

            A=QT_ACT[i].res.name;
            B=QT_ACT[i].num1.name;
            C=QT_ACT[i].num2.name;
            nleft=0;
            nright=0;
            // cout << A << " " << B << " " << C << endl;
            if((JudgeType(QT_ACT[i].op)!=2)&&GetDGANode(B)==0){
                MakeDGALeaf(B,QT_ACT[i].num1.type);
                nleft=GetDGANode(B);
            }
            switch(JudgeType(QT_ACT[i].op)){
                case 0:     
                            n=GetDGANode(B);
                            DGAaddition(n,A,QT_ACT[i].res.type);
                            break;
                case 1:     
                            if(GetDGANode(C)==0){
                                MakeDGALeaf(C,QT_ACT[i].num2.type);
                                nright=GetDGANode(C);
                            }
                            
                            j=0;
                            if((QT_ACT[i].op=="*")||(QT_ACT[i].op=="/")||
                               (QT_ACT[i].op=="+")||(QT_ACT[i].op=="-")){
                                j=1;
                            }
                            if((QT_ACT[i].num1.type=="constant" || DGA[GetDGANode(QT_ACT[i].num1.name)-1].main_sign.second=="constant") &&
                               (QT_ACT[i].num2.type=="constant" || DGA[GetDGANode(QT_ACT[i].num2.name)-1].main_sign.second=="constant")
                               &&(j==1)){
                                if (QT_ACT[i].num1.type!="constant" && DGA[GetDGANode(QT_ACT[i].num1.name)-1].main_sign.second=="constant") B = DGA[GetDGANode(QT_ACT[i].num1.name)-1].main_sign.first;
                                if (QT_ACT[i].num2.type!="constant" && DGA[GetDGANode(QT_ACT[i].num2.name)-1].main_sign.second=="constant") C = DGA[GetDGANode(QT_ACT[i].num2.name)-1].main_sign.first;
                                p=CoutValue(QT_ACT[i].op,B,C);
                                if(nright!=0) DeleteDGANode(nright);
                                if(nleft!=0) DeleteDGANode(nleft);
                                if((n=GetDGANode(p))==0){
                                    MakeDGALeaf(p,"constant");
                                    n=GetDGANode(p);
                                }
                            }
                            else{
                                if((n=FindDGANode(QT_ACT[i].op,B,C))==0){
                                    n=MakeDGANode(QT_ACT[i].op,B,C);
                                }
                            }
                            DGAaddition(n,A,QT_ACT[i].res.type);
                            break;
                case 2:  
                            break;                 
            }
            i++;
        }
        MakeEasyQT(bn);
        if(JudgeType(QT_ACT[i-1].op)==2){
            QT_ACT_EASY.push_back(QT_ACT[i-1]);
        }

        // show_DGA();
        // show_QT_EASY();
        DGA.clear();
    }
}

void WriteASM()
{
    ofstream outFile("ans.txt");
    outFile << "DSEG SEGMENT" << endl;

    for (unsigned int i = 0; i < OBJ_STRUCT.size(); i++) {
        outFile <<  OBJ_STRUCT[i].name  << "\tSTRUC" << endl;
        for (unsigned int j = 0; j < OBJ_STRUCT[i].param.size(); j++) {
            if (OBJ_STRUCT[i].param[j].second == 0) outFile << OBJ_STRUCT[i].param[j].first  << "\tDW 0" << endl;
            else if (OBJ_STRUCT[i].param[j].second == 1) outFile << OBJ_STRUCT[i].param[j].first  << "\tDW 0" << endl;
            else if (OBJ_STRUCT[i].param[j].second == 2) outFile << OBJ_STRUCT[i].param[j].first  << "\ttDW 0" << endl;
            else if (OBJ_STRUCT[i].param[j].second == 3) outFile << OBJ_STRUCT[i].param[j].first  << "\tDW \' \'" << endl;
        }
        outFile <<  OBJ_STRUCT[i].name  << "\tENDS" << endl << endl;
    }
    
    for (unsigned int i = 0; i < OBJ_DATE.size(); i++) {
        if (OBJ_DATE[i].content[0] == '<'){
            outFile << OBJ_DATE[i].name << "\t" << OBJ_DATE[i].type << '\t' << OBJ_DATE[i].content << endl;
        }
        else{
            outFile << OBJ_DATE[i].name << "\t" << OBJ_DATE[i].content << endl;
        }
    }
    outFile << "DSEG ENDS" << endl << endl;
    outFile << "SSEG SEGMENT STACK" << endl;
    outFile << "SKTOP DB 20 DUP(0)" << endl;
    outFile << "SSEG ENDS" << endl << endl;
    outFile << "CSEG SEGMENT" << endl;
    outFile << "ASSUME CS:CSEG ,DS:DSEG, SS:SSEG" << endl;
    for (unsigned int i=0; i<OBJ_FUNC.size()-1; i++) {
        outFile << OBJ_FUNC[i].name << "\tPROC" << endl;
        for (int j=OBJ_FUNC[i].funcBegin-1; j<OBJ_FUNC[i].funcEnd; j++) {
            outFile << ".L" << j+1 << ":\t\t";
            outFile << OBJ[j].op << " ";
            if(OBJ[j].num1 != "" && OBJ[j].num2 != ""){
                outFile << OBJ[j].num1 << ",\t" << OBJ[j].num2 << endl;
            }
            else{
                outFile << OBJ[j].num1 << "\t" << OBJ[j].num2 << endl;
            }
        }
        outFile << "\t\tRET" << endl;
        outFile << OBJ_FUNC[i].name << "\tENDP" << endl << endl;
    }
    outFile << "START:" << endl;
    outFile << "\t\tmov ax,\tDSEG" << endl;
    outFile << "\t\tmov ds,\tax" << endl;
    outFile << "\t\tmov ax,\tSSEG" << endl;
    outFile << "\t\tmov ss,\tax" << endl;
    outFile << "\t\tmov sp,\tLENGTH SKTOP" << endl;
    for (unsigned int i=OBJ_FUNC[OBJ_FUNC.size()-1].funcBegin-1; i<OBJ.size(); i++) {
        outFile << ".L" << OBJ[i].id << ":\t\t";
        outFile << OBJ[i].op << " ";
        if(OBJ[i].num1 != "" && OBJ[i].num2 != ""){
            outFile << OBJ[i].num1 << ",\t" << OBJ[i].num2 << endl;
        }
        else{
            outFile << OBJ[i].num1 << "\t" << OBJ[i].num2 << endl;
        }
    }
    outFile << "CSEG ENDS" << endl;
    outFile << "END START" << endl;
    outFile.close();
}

int main()
{
    ifstream inFile("test.txt");
    while (getline(inFile, t_str))  str += t_str + '\n';
    str += "#\n";
    cout << str << endl;

    init_TYPEL();       //初始化类型表

    token = nextw();
    // bool flag = FunctionDefinition();
    bool flag = Program();
    if (flag){
        cout << "语法分析成功" << endl;
    }
    else{
        cout << token.type << " " << token.value << endl;
        cout << "语法分析失败" << endl;
        return 0;
    }

    show_SYNBL();       //显示符号表

    // while(!SEM.empty()){
    //     cout << SEM.top() << endl;
    //     SEM.pop();
    // }

    BaseBlock();        //基本块划分
    show_QT();          //显示四元式

    for (unsigned int i=0; i<QT.size(); i++){           //四元式添加活跃信息
        QT_ACT.push_back(QT_ACT_Node(QT[i].block_id, QT[i].op,
        QT_Token(QT[i].num1, GetQTType(QT[i].num1), -1),
        QT_Token(QT[i].num2, GetQTType(QT[i].num2), -1),
        QT_Token(QT[i].res,  GetQTType(QT[i].res), -1)));
    }

    OptimizeDGA();  //优化DGA
    show_QT_EASY(); //显示优化后的四元式

    QT_ACT.clear();
    for (unsigned int i=0; i<QT_ACT_EASY.size(); i++){           //四元式添加活跃信息
        QT_ACT.push_back(QT_ACT_Node(QT_ACT_EASY[i].block_id, QT_ACT_EASY[i].op,
        QT_Token(QT_ACT_EASY[i].num1.name, GetQTType(QT_ACT_EASY[i].num1.name), -1),
        QT_Token(QT_ACT_EASY[i].num2.name, GetQTType(QT_ACT_EASY[i].num2.name), -1),
        QT_Token(QT_ACT_EASY[i].res.name, GetQTType(QT_ACT_EASY[i].res.name), -1)));
    }

    GetACT();       //获取活跃信息
    show_ACT();     //显示带活跃信息的四元式

    GetOBJ();       //获取目标代码
    show_OBJ();     //显示目标代码

    // cout << OBJ_SEM.size() << endl;

    WriteASM();     //写入ASM文件

    return 0;
}