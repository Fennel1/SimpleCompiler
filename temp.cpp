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
    DGA_Node()
    {
        id = 0;
        left = 0;
        right = 0;
        op = "";
        main_sign = make_pair("","");
        addi_sign.clear();
    }
};

vector<DGA_Node> DGA[20];
vector<QT_ACT_Node> QT_ACT_EASY;
int DGA_id = 0;

void show_QT_EASY()
{
    cout << "easy" << endl;
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
    for (unsigned int i = 0; i < DGA[DGA_id].size(); i++) {
        cout.width(10);
        cout << i;
        cout.width(10);
        cout << DGA[DGA_id][i].id;
        cout.width(10);
        cout << DGA[DGA_id][i].left;
        cout.width(15);
        cout << DGA[DGA_id][i].right;
        cout.width(15);
        cout << DGA[DGA_id][i].op;
        cout.width(15);
        cout << DGA[DGA_id][i].main_sign.first;
        cout.width(15);
        cout << DGA[DGA_id][i].main_sign.second;
        cout.width(15);
        for(int j=0;j<DGA[DGA_id][i].addi_sign.size();j++){
            cout.width(15);
            cout << DGA[DGA_id][i].addi_sign[j].first;
            cout.width(15);
            cout << DGA[DGA_id][i].addi_sign[j].second;
        }
        cout << endl;
    }
}

int GetDGANode(string B)    //获取对应的DGA节点
{
    int n=0;
    for(int i=0;i<DGA[DGA_id].size();i++)
    {
        if(DGA[DGA_id][i].main_sign.first==B)
        {
            n=i+1;
        }
        for(int j=0;j<DGA[DGA_id][i].addi_sign.size();j++)
        {
            if(DGA[DGA_id][i].addi_sign[j].first==B)
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
    DGA[DGA_id].push_back(DGA_Node(DGA[DGA_id].size(),0,0,"_",make_pair(B,type),vector<pair<string, string>>()));
}

int MakeDGANode(string op, string B, string C)
{
    DGA_Node temp;
    temp.id=DGA[DGA_id].size();
    temp.op=op;
    temp.left=GetDGANode(B);
    temp.right=GetDGANode(C);
    DGA[DGA_id].push_back(DGA_Node(DGA[DGA_id].size(),temp.left,temp.right,op,make_pair("_","_"),vector<pair<string, string>>()));
    return DGA[DGA_id].size();
}

void DeleteDGANode(int id)              //删除DGA节点
{
    DGA[DGA_id][id-1].main_sign.first="_";
    DGA[DGA_id][id-1].id=0;
    for(int i=id-1;i<DGA[DGA_id].size();i++)
    {
        DGA[DGA_id][i].id=DGA[DGA_id][i+1].id;
        DGA[DGA_id][i].main_sign.first=DGA[DGA_id][i+1].main_sign.first;
        DGA[DGA_id][i].main_sign.second=DGA[DGA_id][i+1].main_sign.second;
        DGA[DGA_id][i].left=DGA[DGA_id][i+1].left;
        DGA[DGA_id][i].right=DGA[DGA_id][i+1].right;
        DGA[DGA_id][i].op=DGA[DGA_id][i+1].op;
        for(int j=0;j<DGA[DGA_id][i].addi_sign.size();j++)
        {
            DGA[DGA_id][i].addi_sign[j].first=DGA[DGA_id][i+1].addi_sign[j].first;
            DGA[DGA_id][i].addi_sign[j].second=DGA[DGA_id][i+1].addi_sign[j].second;
        }
    }
    DGA[DGA_id].pop_back();
}

int FindDGANode(string op, string B, string C)
{
    int n=0;
    int lt,rt,k=0;
    lt=GetDGANode(B);
    rt=GetDGANode(C);
    for(int i=0;i<DGA[DGA_id].size();i++)
    {
        k=0;
        if(DGA[DGA_id][i].op==op)
        {
            lt=DGA[DGA_id][i].left;
            for(int j=0;j<DGA[DGA_id][lt-1].addi_sign.size();j++)
            {
                if(DGA[DGA_id][lt-1].addi_sign[j].first==B)
                {
                    k=1;
                }
            }
            if((DGA[DGA_id][lt-1].main_sign.first==B)||(k==1))
            {
                n=i+1;
                break;
            }
        }
    }
    return n;
}

void DGAaddition(int id, string A, string type)         //为DGA结点添加附加标记
{
 
    int j,k;
    QT_Token temp;
    k=GetDGANode(A);
    if(k!=0){
        for(j=0;j<DGA[DGA_id][k-1].addi_sign.size();j++)
        {
            if(DGA[DGA_id][k-1].addi_sign[j].first==A)
            {
                DGA[DGA_id][k-1].addi_sign.erase(DGA[DGA_id][k-1].addi_sign.begin()+j-1);
            }
        }
    }
    if(DGA[DGA_id][id-1].main_sign.first!="_"){
        cout << DGA[DGA_id][id-1].addi_sign.size() << endl;
        temp.name=A;
        temp.type=type;
        DGA[DGA_id][id-1].addi_sign.push_back(make_pair(A,type));
    }
    else{
        DGA[DGA_id][id-1].main_sign.first=A;
        DGA[DGA_id][id-1].main_sign.second=type;
    }

    if(DGA[DGA_id][id-1].main_sign.second=="temp"){
        for(j=0;j<DGA[DGA_id][id-1].addi_sign.size();j++)
        {
            if(DGA[DGA_id][id-1].addi_sign[j].second=="variable")
            {
                string tempname;
                tempname=DGA[DGA_id][id-1].addi_sign[j].first;
                DGA[DGA_id][id-1].addi_sign[j].first=DGA[DGA_id][id-1].main_sign.first;
                DGA[DGA_id][id-1].main_sign.first=tempname;
                DGA[DGA_id][id-1].main_sign.second="variable";
                DGA[DGA_id][id-1].addi_sign[j].second="temp";
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
}

string CoutValue(string op, string B, string C)
{
    string p;
    if(op=="+")p=atof(B.c_str())+atof(C.c_str());
    if(op=="-")p=atof(B.c_str())-atof(C.c_str());
    if(op=="*")p=atof(B.c_str())*atof(C.c_str());
    if(op=="/")p=atof(B.c_str())/atof(C.c_str());
    return p;
}

void MakeEasyQT(int block)
{

    QT_ACT_Node tempNode;
    int numb,left,right;
    for(int i=0;i<DGA[DGA_id].size();i++){
 
        int k=0;
        if(DGA[DGA_id][i].op=="_"){
       
            for(int j=0;j<DGA[DGA_id][i].addi_sign.size();j++){
                if(DGA[DGA_id][i].addi_sign[j].second=="variable"){
       
                    k=1;
                    numb=j;
                }
            }
            if(DGA[DGA_id][i].main_sign.second=="constant" || DGA[DGA_id][i].main_sign.second=="variable"
               && k==1){
          
                tempNode.res.name=DGA[DGA_id][i].main_sign.first;
            
                tempNode.res.type=DGA[DGA_id][i].main_sign.second;
            
                tempNode.block_id=block;
             
                tempNode.op="=";

                if (!DGA[DGA_id][i].addi_sign.empty()){
                    tempNode.num1.name=DGA[DGA_id][i].addi_sign[numb].first;
                
                    tempNode.num1.type=DGA[DGA_id][i].addi_sign[numb].second;
                }
              
                tempNode.num2.name="_";
               
                tempNode.num2.type="_";
               
                QT_ACT_EASY.push_back(tempNode);
            
            }
        }
        else{
         
            left=DGA[DGA_id][i].left;
            right=DGA[DGA_id][i].right;
            tempNode.res.name=DGA[DGA_id][i].main_sign.first;
            tempNode.res.type=DGA[DGA_id][i].main_sign.second;
            tempNode.block_id=block;
            tempNode.op=DGA[DGA_id][i].op;
            tempNode.num1.name=DGA[DGA_id][left-1].main_sign.first;
            tempNode.num1.type=DGA[DGA_id][left-1].main_sign.second;
            tempNode.num2.name=DGA[DGA_id][right-1].main_sign.first;
            tempNode.num2.type=DGA[DGA_id][right-1].main_sign.second;
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

        while(QT_ACT[i].op!="_"&&QT_ACT[i].block_id==bn){
            // show_DGA();

            A=QT_ACT[i].res.name;
            B=QT_ACT[i].num1.name;
            C=QT_ACT[i].num2.name;
            nleft=0;
            nright=0;

            if(GetDGANode(B)==0&&(JudgeType(QT_ACT[i].op)!=2)){
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
                            if((QT_ACT[i].num1.type=="constant")&&(QT_ACT[i].num2.type=="constant")
                               &&(j==1)){
                                p=CoutValue(QT_ACT[i].op,B,C);
                                if(nleft!=0) DeleteDGANode(nleft);
                                if(nright!=0) DeleteDGANode(nright);
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

        show_DGA();
        show_QT_EASY();
        DGA_id++;
        cout << 11111111111111111 << endl;
        // DGA.clear();
        // while(!DGA.empty()) DGA.pop_back();
        
    }
    cout << 22222222222222222 << endl;
}