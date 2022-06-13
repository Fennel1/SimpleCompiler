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
        QT.push_back(QT_Node("funcbegin", t1, "_", "_"));
        int func_type;
        for (unsigned int i = 0; i < TYPEL.size(); i++){
            if (TYPEL[i].type == t1){
                func_type = i;
                break;
            }
        }
        if (!Variable())    return false;
        string func_name= SEM.top(); SEM.pop();
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
            if (name_ == "")    return SYNBL[i].type;
            else if(name_ == "[]"){
                return TYPEL[SYNBL[i].type].tpoint;
            }
            else{
                for (unsigned int j=0; j<SYNBL.size(); j++){
                    if (SYNBL[j].name == name_){
                        return SYNBL[j].type;
                    }
                }
                return -1;
            }
        }
    }
    return -1;
}

bool CheckType(string t1, string t2)    //检查标识符类型
{
    string t1_, t2_, t1__, t2__;
    int t1_type=-1, t2_type=-1;
    if (t1[0] == 't'){                          //临时变量
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
    if (t1_type == -1){
        cout << "Error: 未定义的变量 " << t1_ << endl;
        return false;
    }
    if (t2_type == -1){
        cout << "Error: 未定义的变量 " << t2_ << endl;
        return false;
    }
    if (t1_type != t2_type){
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
                        QT.push_back(QT_Node("=", string(1,temp[i]), "_", name_+"["+to_string(i)+"]"));
                    }
                    for (int i=temp.size(); i<num; i++){
                        QT.push_back(QT_Node("=", " ", "_", name_+"["+to_string(i)+"]"));
                    }
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
            QT.push_back(QT_Node("=", t1, "_", t2));
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
        QT.push_back(QT_Node("=", t1, "_", t2));
        if (token.type == "P" && token.value == ";"){
            token = nextw();
            return true;
        }
        else{
            return false;
        }
    }
    else if (token.type == "P" && token.value == "("){
        token = nextw();
        if (!ParameterList())   return false;
        if (token.type == "P" && token.value == ")"){
            token = nextw();
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
    else{
        return false;
    }
}

bool ParameterList()                    //参数列表
{
    if (token.type == "I"){
        if (!Parameter())   return false;
        if (!ParameterClosure())   return false;
        return true;
    }
    else{
        return true;
    }
}

bool Parameter()                        //参数
{
    if (token.type == "I"){
       token = nextw();
       return true;
    }
    else if (token.type == "CI"){
        token = nextw();
        return true;
    }
    else if (token.type == "CF"){
        token = nextw();
        return true;
    }
    else if (token.type == "CC"){
        token = nextw();
        return true;
    }
    else if (token.type == "CS"){
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
        else if(QT[i].op == "ifend")      begin[i] = 1;
        else if(QT[i].op == "elif")       begin[i+1] = 1;
        else if(QT[i].op == "elifend")    begin[i] = 1;
        else if(QT[i].op == "else")       begin[i+1] = 1;
        else if(QT[i].op == "elseend")    begin[i] = 1;
        else if(QT[i].op == "while")      begin[i+1] = 1;
        else if(QT[i].op == "whend")      begin[i+1] = 1;
        else if(QT[i].op == "for")        begin[i+1] = 1;
        else if(QT[i].op == "forend")     begin[i+1] = 1;
        else if(QT[i].op == "do")         begin[i+1] = 1;

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

int main()
{
    ifstream inFile("test2.txt");
    while (getline(inFile, t_str))  str += t_str + '\n';
    str += "#\n";
    cout << str << endl;

    init_TYPEL();       //初始化类型表

    token = nextw();
    // bool flag = FunctionDefinition();
    bool flag = Program();
    if (flag) cout << "语法分析成功" << endl;
    else{
        cout << token.type << " " << token.value << endl;
        cout << "语法分析失败" << endl;
    }

    show_SYNBL();       //显示符号表
    show_QT();          //显示四元式

    while(!SEM.empty()){
        cout << SEM.top() << endl;
        SEM.pop();
    }

    BaseBlock();        //基本块划分
    ConstEasy();        //常值表达式节省
    show_QT();          //显示四元式


    return 0;
}