#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <Windows.h>
#include <stdlib.h>

using namespace std;

unordered_map<string,vector<string>> mymap;
vector<string> logs;

ifstream is("logs.txt");
ofstream os("logs.txt",ios_base::app);

void readFromFile();
void showMainMenu();
void waitForEnter();
void choose();
void addLog();
void showPath();
void showContri();
void showLog();
void exitSys();
vector<string> split(const string& s, char c);
void mapAdd(string pathName,string log);
string getTime();

int main(){
    system("chcp 65001");
    cout<<"欢迎使用多路径人生管理系统"<<endl;
    cout<<"正在读取数据 请稍候……"<<endl;
    readFromFile();
    showMainMenu();
    choose();
}
void readFromFile(){
    string line;
    while(getline(is,line)){
        auto strings = split(line, ' ');
        string pathName=strings[2];
        string day=strings[0];
        string time=strings[1];
        string message = strings[3];
        string log = day + " " + time + " " + message;
        mapAdd(pathName,log);
    }
}
void showMainMenu(){
    cout<<"1.记录日志"<<endl;
    cout<<"2.查看路径"<<endl;
    cout<<"3.查看日志分布情况"<<endl;
    cout<<"4.查看日志"<<endl;
    cout<<"5.退出使用"<<endl;
}

void waitForEnter() {
    cout << "按回车键(Enter)继续";
    cin.ignore();
    cin.get();
}

void choose(){
    while(true){
        cout<<"请输入选择对应的数字(选择6显示菜单)"<<endl;
        char choice;
        cin >> choice;
        switch (choice) {
            case '1': addLog(); waitForEnter(); break;
            case '2': showPath(); waitForEnter(); break;
            case '3': showContri(); waitForEnter(); break;
            case '4': showLog(); waitForEnter(); break;
            case '5': exitSys(); break;
            case '6': showMainMenu(); break;
            default: cerr << "请输入一个有效的选择" << endl; break;
        }
    }
}
void addLog(){
    cout<<"请输入路径名称(输入1返回):"<<endl;
    string pathName;
    cin>>pathName;

    if(pathName == "1") return ;

    cout<<"请输入日志信息(输入1返回):"<<endl;
    string message;
    cin>>message;

    if(message == "1") return ;

    string time = getTime();

    string log1 = time + message;
    mapAdd(pathName,log1);

    string log2 = time + " " + pathName + " " + message + "\n" ;
    os << log2 ;

}
void showPath(){
    cout<< "目前的路径有：\n";
    for(auto it = mymap.begin();it!=mymap.end();++it){
        cout<< it->first <<endl;
    }
}
void showContri(){
    cout<<"各个路径的日志数量："<<endl;
    for(auto it=mymap.begin();it!=mymap.end();++it){
        cout << it->first << ":" <<it->second.size()<<endl;
    }
}
void showLog(){
    if (!is.is_open()) {
        cerr << "无法打开日志文件，请检查文件是否存在或路径是否正确。" << endl;
    }

    is.clear();
    is.seekg(0); 
    
    string line;
    while(getline(is,line)){
        cout<<line <<endl;
    }
}
void exitSys(){
    cout<<"感谢使用本系统\n";
    exit(0);
}
vector<string> split(const string& s , char c){
    vector<string> ans;
    string temp;
    for(char ch : s){
        if(ch == c){
            ans.push_back(temp);
            temp.clear();
        } else {
            temp += ch;
        }
    }
    ans.push_back(temp);
    return ans;
}

string getTime(){
    SYSTEMTIME t;
    GetLocalTime(&t); // 获取当前系统时间
    string time = to_string(t.wYear) + "/" + to_string(t.wMonth) + "/" + to_string(t.wDay) + " " +
                    to_string(t.wHour) + ":" + to_string(t.wMinute) + ":" + to_string(t.wSecond);
    return time ;
}

void mapAdd(string pathName,string log){
    if(mymap.count(pathName)==0){
            vector<string> mylog;
            mylog.push_back(log);
            mymap.emplace(pathName,mylog);
        }
        else{
            mymap.at(pathName).push_back(log);
        }
}
