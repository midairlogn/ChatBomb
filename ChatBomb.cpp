#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

POINT cursorPos1, cursorPos2;
int x1,x2;
int y1,y2;

RECT desktop;
//调整发消息鼠标键盘操作的间隔，发消息间隔是其4倍，建议使用50-100。（单位：毫秒）
int sleeptime = 50;
int method = 1;
char ifinput;
string inputString;

int copymessage(){
    cout << "请选择是否要在此窗口内输入消息内容：\n1.\t输入1或Y或y代表要（不支持表情包、文件等）\n2.\t输入其他内容代表不要（我已经将消息复制到剪切板） ： ";
    cin >> ifinput;
    if (!( ifinput == '1' || ifinput == 'Y' || ifinput == 'y' )) {
        return 0;
    }

    // 获取用户输入并赋值给字符串

  	cout << "请输入想发送的消息内容：";
  	cin >> inputString;
  	//getline(cin,inputString);

  	// 在屏幕上打印输入的字符串
  	cout << "您输入的内容是：" << inputString << endl;

  	// 将输入的字符串复制到剪切板
  	if (OpenClipboard(NULL)) {
   	 	EmptyClipboard();
    	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, inputString.size() + 1);
    if (hMem) {
      	char* pMem = (char*)GlobalLock(hMem);
      	if (pMem) {
        	strcpy(pMem, inputString.c_str());
        	GlobalUnlock(hMem);
        	SetClipboardData(CF_TEXT, hMem);
      }
      else {
        	GlobalFree(hMem);
      }
    }
    CloseClipboard();
    return 0;
  }

  // 获取剪切板内容并打印
    if (OpenClipboard(NULL)) {
    	HANDLE hData = GetClipboardData(CF_TEXT);
        if (hData) {
      	    char* pMem = (char*)GlobalLock(hData);
      	if (pMem) {
        	cout << "剪切板当前的内容是：" << pMem << endl;
        GlobalUnlock(hData);
      }
    }
    CloseClipboard();
  }

  return 0;
}

int wait(){
	int seconds;

  	// 获取用户输入的秒数
  	cout << "请输入你需要用来准备的秒数：";
  	cin >> seconds;

  	// 将秒数转换为字符串
  	stringstream ss;
  	ss << seconds;
  	string timeStr = ss.str();

  	// 拼接字符串
  	string command = "timeout /t " + timeStr;
	
  	// 使用 system() 执行命令
  	system(command.c_str());
} 

int getmouse1(){
	// 获取屏幕分辨率
  	GetWindowRect(GetDesktopWindow(), &desktop);
  	int screenWidth = desktop.right - desktop.left;
  	int screenHeight = desktop.bottom - desktop.top;

    // 获取鼠标位置并打印 
  	GetCursorPos(&cursorPos1);
  	cout << "\n鼠标当前位置: (" << cursorPos1.x << ", " << cursorPos1.y << ")" << endl;

  	// 获取要点击的点的位置
  	//cout << "请输入要点击的点的 X 坐标 (0 到 " << screenWidth << "): ";
  	//cin >> x1;
  	//x1 = cursorPos1.x ;
  	//cout << "请输入要点击的点的 Y 坐标 (0 到 " << screenHeight << "): ";
  	//cin >> y1;
  	//y1 = cursorPos1.y ;
	
	cout << "\n请不要移动鼠标或操作键盘。" << endl;
	//cout << "\n目标的点击位置: (" << x1 << ", " << y1 << ")" << endl;
    cout << "\n目标的点击位置: (" << cursorPos1.x << ", " << cursorPos1.y << ")" << endl;
    return 0;
}

int getmouse2() {
    // 获取屏幕分辨率
    GetWindowRect(GetDesktopWindow(), &desktop);
    int screenWidth = desktop.right - desktop.left;
    int screenHeight = desktop.bottom - desktop.top;

    // 获取鼠标位置并打印 
    GetCursorPos(&cursorPos2);
    cout << "\n鼠标当前位置: (" << cursorPos2.x << ", " << cursorPos2.y << ")" << endl;

    // 获取要点击的点的位置
    //cout << "请输入要点击的点的 X 坐标 (0 到 " << screenWidth << "): ";
    //cin >> x2;
    //x2 = cursorPos2.x ;
    //cout << "请输入要点击的点的 Y 坐标 (0 到 " << screenHeight << "): ";
    //cin >> y2;
    //y2 = cursorPos2.y ;

    cout << "\n请不要移动鼠标或操作键盘。" << endl;
    //cout << "\n目标的点击位置: (" << x1 << ", " << y1 << ")" << endl;
    cout << "\n目标的点击位置: (" << cursorPos2.x << ", " << cursorPos2.y << ")" << endl;
    return 0;
}

bool judge() {
    char ifstop;
    cout << "请再次确认坐标是否正确，剪切板中想发送的消息是否正确！" << endl;
    cout << "确认的话，请输入 N 或 n 或 1: ";
    cin >> ifstop;
    if (!(ifstop == 'N' || ifstop == 'n' || ifstop == '1')) {
        cout << "我们从头开始，重新来！";
        Sleep(3000);
        return 1;
    }
    return 0;
}

int clickandctrlv() {
    // 将鼠标移动到目标点
    //SetCursorPos(x1, y1);
    SetCursorPos(cursorPos1.x, cursorPos1.y);
    Sleep(sleeptime);
    // 模拟左键点击
    //mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, x1, y1, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, cursorPos1.x, cursorPos1.y, 0, 0);
    cout << "\t 左键点击 操作成功！" << endl;

    Sleep(sleeptime);
    // 模拟 Ctrl+V
    keybd_event(VK_CONTROL, 0, 0, 0); // 按下 Ctrl 键
    keybd_event(0x56, 0, 0, 0);  // 按下 V 键
    keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0); // 释放 V 键
    keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); // 释放 Ctrl 键
    cout << "\t Ctrl+v 操作成功！" << endl;

    Sleep(sleeptime);

    return 0;
}

int main() {
    cout << "请支持作者 Midairlogn ：https://github.com/midairlogn" << endl << endl;
	copymessage();
	//控制输入的次数
	int sendtimes;
	cout << "\n请输入你想发送消息的次数:"; 
	cin >> sendtimes; 
    cout << "\n请输入你想发送消息的方式: \n1.\tCtrl+Enter\n2.\tEnter\n3.\t鼠标点击发送键\n如果输入其他默认方式1 : ";
    cin >> method;
    if (!(method == 1 || method == 2 || method == 3)) {
        method = 1;
    }

    cout << "\n请将此窗口移动到一边，不要遮挡目标窗口！\n并将鼠标移动至消息发送框！" << endl << endl;
    Sleep(1000);
	wait();
	cout << "\n请不要移动鼠标。\n1秒后获取鼠标位置！" << endl << endl;
  	Sleep(1000); 

    getmouse1();
	if( judge() ){
		return 0;
	}
	cout << "\n请不要移动鼠标或操作键盘，直到程序运行完成！" << endl  << endl;
	Sleep(1000); 
	
	for(int i=1;i<=sendtimes;i++){
        switch ( method ) {
        case 1:
            clickandctrlv();
            // 模拟Ctrl+Enter
            keybd_event(VK_CONTROL, 0, 0, 0); // 按下 Ctrl 键
            keybd_event(VK_RETURN, 0, 0, 0);  // 按下回车键
            keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0); // 释放回车键
            keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); // 释放 Ctrl 键
            cout << "\t Ctrl+Enter 操作成功！" << endl;
            break;
        case 2:
            clickandctrlv();
            // 模拟Enter
            keybd_event(VK_RETURN, 0, 0, 0);  // 按下回车键
            keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0); // 释放回车键
            cout << "\t Enter 操作成功！" << endl;
            break;
        case 3:
        	if( i == 1 ){
                cout << "\n请将此窗口移动到一边，不要遮挡目标窗口！\n并将鼠标移动至消息发送键处！" << endl << endl;
                Sleep(1000);
        		wait();
				cout << "\n请不要移动鼠标。\n1秒后获取鼠标位置！" << endl << endl;
  				Sleep(1000); 

    			getmouse2();
				if( judge() ){
					return 0;
				}
				cout << "\n请不要移动鼠标或操作键盘，直到程序运行完成！" << endl  << endl;
			}
            clickandctrlv();
            // 模拟鼠标左键点击
            // 将鼠标移动到目标点
            //SetCursorPos(x2, y2);
            SetCursorPos(cursorPos2.x, cursorPos2.y);
            Sleep(sleeptime);
            // 模拟左键点击
            //mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, x2, y2, 0, 0);
            mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, cursorPos2.x, cursorPos2.y, 0, 0);
            cout << "\t 左键点击 操作成功！" << endl;
            break;
        }

		cout << "第" << i  << "轮消息已发送"  << endl << endl; 
        Sleep(sleeptime);
	}
	
 	system("pause");
  	return 0;
}






