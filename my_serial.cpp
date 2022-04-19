
#include <string>
#include <iostream>
#include <cstdio>
//c++标准异常库
#include <exception>
//linux时钟库
#include <unistd.h>

#include "serial/serial.h"

using std::string;
using std::exception;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::cin;

void run()
{
    serial::Serial a("/dev/ttyUSB0",114500,serial::Timeout::simpleTimeout(1000));
    if(!a.isOpen()){
        throw("串口没打开");
    }
    int num{};
    for(int i=0;i<3;i++)
    {
        cout<<i<<endl;
        cout<<"请输入串口发送信息"<<endl;
        string send;
        cin>>send;
        a.write(send);
        cout<<"接受到的信息为"<<a.read(1024)<<endl;
        
    }

}


int main(int argc, char **argv) {
    try{
        run();
    }catch (exception &e) {
        cout<<e.what()<<endl;
    }
    
    return 0;
}