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
//��������Ϣ�����̲����ļ��������Ϣ�������4��������ʹ��50-100������λ�����룩
int sleeptime = 50;
int method = 1;
char ifinput;
string inputString;

int copymessage(){
    cout << "��ѡ���Ƿ�Ҫ�ڴ˴�����������Ϣ���ݣ�\n1.\t����1��Y��y����Ҫ����֧�ֱ�������ļ��ȣ�\n2.\t�����������ݴ���Ҫ�����Ѿ�����Ϣ���Ƶ����а壩 �� ";
    cin >> ifinput;
    if (!( ifinput == '1' || ifinput == 'Y' || ifinput == 'y' )) {
        return 0;
    }

    // ��ȡ�û����벢��ֵ���ַ���

  	cout << "�������뷢�͵���Ϣ���ݣ�";
  	cin >> inputString;
  	//getline(cin,inputString);

  	// ����Ļ�ϴ�ӡ������ַ���
  	cout << "������������ǣ�" << inputString << endl;

  	// ��������ַ������Ƶ����а�
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

  // ��ȡ���а����ݲ���ӡ
    if (OpenClipboard(NULL)) {
    	HANDLE hData = GetClipboardData(CF_TEXT);
        if (hData) {
      	    char* pMem = (char*)GlobalLock(hData);
      	if (pMem) {
        	cout << "���а嵱ǰ�������ǣ�" << pMem << endl;
        GlobalUnlock(hData);
      }
    }
    CloseClipboard();
  }

  return 0;
}

int wait(){
	int seconds;

  	// ��ȡ�û����������
  	cout << "����������Ҫ����׼����������";
  	cin >> seconds;

  	// ������ת��Ϊ�ַ���
  	stringstream ss;
  	ss << seconds;
  	string timeStr = ss.str();

  	// ƴ���ַ���
  	string command = "timeout /t " + timeStr;
	
  	// ʹ�� system() ִ������
  	system(command.c_str());
} 

int getmouse1(){
	// ��ȡ��Ļ�ֱ���
  	GetWindowRect(GetDesktopWindow(), &desktop);
  	int screenWidth = desktop.right - desktop.left;
  	int screenHeight = desktop.bottom - desktop.top;

    // ��ȡ���λ�ò���ӡ 
  	GetCursorPos(&cursorPos1);
  	cout << "\n��굱ǰλ��: (" << cursorPos1.x << ", " << cursorPos1.y << ")" << endl;

  	// ��ȡҪ����ĵ��λ��
  	//cout << "������Ҫ����ĵ�� X ���� (0 �� " << screenWidth << "): ";
  	//cin >> x1;
  	//x1 = cursorPos1.x ;
  	//cout << "������Ҫ����ĵ�� Y ���� (0 �� " << screenHeight << "): ";
  	//cin >> y1;
  	//y1 = cursorPos1.y ;
	
	cout << "\n�벻Ҫ�ƶ�����������̡�" << endl;
	//cout << "\nĿ��ĵ��λ��: (" << x1 << ", " << y1 << ")" << endl;
    cout << "\nĿ��ĵ��λ��: (" << cursorPos1.x << ", " << cursorPos1.y << ")" << endl;
    return 0;
}

int getmouse2() {
    // ��ȡ��Ļ�ֱ���
    GetWindowRect(GetDesktopWindow(), &desktop);
    int screenWidth = desktop.right - desktop.left;
    int screenHeight = desktop.bottom - desktop.top;

    // ��ȡ���λ�ò���ӡ 
    GetCursorPos(&cursorPos2);
    cout << "\n��굱ǰλ��: (" << cursorPos2.x << ", " << cursorPos2.y << ")" << endl;

    // ��ȡҪ����ĵ��λ��
    //cout << "������Ҫ����ĵ�� X ���� (0 �� " << screenWidth << "): ";
    //cin >> x2;
    //x2 = cursorPos2.x ;
    //cout << "������Ҫ����ĵ�� Y ���� (0 �� " << screenHeight << "): ";
    //cin >> y2;
    //y2 = cursorPos2.y ;

    cout << "\n�벻Ҫ�ƶ�����������̡�" << endl;
    //cout << "\nĿ��ĵ��λ��: (" << x1 << ", " << y1 << ")" << endl;
    cout << "\nĿ��ĵ��λ��: (" << cursorPos2.x << ", " << cursorPos2.y << ")" << endl;
    return 0;
}

bool judge() {
    char ifstop;
    cout << "���ٴ�ȷ�������Ƿ���ȷ�����а����뷢�͵���Ϣ�Ƿ���ȷ��" << endl;
    cout << "ȷ�ϵĻ��������� N �� n �� 1: ";
    cin >> ifstop;
    if (!(ifstop == 'N' || ifstop == 'n' || ifstop == '1')) {
        cout << "���Ǵ�ͷ��ʼ����������";
        Sleep(3000);
        return 1;
    }
    return 0;
}

int clickandctrlv() {
    // ������ƶ���Ŀ���
    //SetCursorPos(x1, y1);
    SetCursorPos(cursorPos1.x, cursorPos1.y);
    Sleep(sleeptime);
    // ģ��������
    //mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, x1, y1, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, cursorPos1.x, cursorPos1.y, 0, 0);
    cout << "\t ������ �����ɹ���" << endl;

    Sleep(sleeptime);
    // ģ�� Ctrl+V
    keybd_event(VK_CONTROL, 0, 0, 0); // ���� Ctrl ��
    keybd_event(0x56, 0, 0, 0);  // ���� V ��
    keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0); // �ͷ� V ��
    keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); // �ͷ� Ctrl ��
    cout << "\t Ctrl+v �����ɹ���" << endl;

    Sleep(sleeptime);

    return 0;
}

int main() {
    cout << "��֧������ Midairlogn ��https://github.com/midairlogn" << endl << endl;
	copymessage();
	//��������Ĵ���
	int sendtimes;
	cout << "\n���������뷢����Ϣ�Ĵ���:"; 
	cin >> sendtimes; 
    cout << "\n���������뷢����Ϣ�ķ�ʽ: \n1.\tCtrl+Enter\n2.\tEnter\n3.\t��������ͼ�\n�����������Ĭ�Ϸ�ʽ1 : ";
    cin >> method;
    if (!(method == 1 || method == 2 || method == 3)) {
        method = 1;
    }

    cout << "\n�뽫�˴����ƶ���һ�ߣ���Ҫ�ڵ�Ŀ�괰�ڣ�\n��������ƶ�����Ϣ���Ϳ�" << endl << endl;
    Sleep(1000);
	wait();
	cout << "\n�벻Ҫ�ƶ���ꡣ\n1����ȡ���λ�ã�" << endl << endl;
  	Sleep(1000); 

    getmouse1();
	if( judge() ){
		return 0;
	}
	cout << "\n�벻Ҫ�ƶ�����������̣�ֱ������������ɣ�" << endl  << endl;
	Sleep(1000); 
	
	for(int i=1;i<=sendtimes;i++){
        switch ( method ) {
        case 1:
            clickandctrlv();
            // ģ��Ctrl+Enter
            keybd_event(VK_CONTROL, 0, 0, 0); // ���� Ctrl ��
            keybd_event(VK_RETURN, 0, 0, 0);  // ���»س���
            keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0); // �ͷŻس���
            keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); // �ͷ� Ctrl ��
            cout << "\t Ctrl+Enter �����ɹ���" << endl;
            break;
        case 2:
            clickandctrlv();
            // ģ��Enter
            keybd_event(VK_RETURN, 0, 0, 0);  // ���»س���
            keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0); // �ͷŻس���
            cout << "\t Enter �����ɹ���" << endl;
            break;
        case 3:
        	if( i == 1 ){
                cout << "\n�뽫�˴����ƶ���һ�ߣ���Ҫ�ڵ�Ŀ�괰�ڣ�\n��������ƶ�����Ϣ���ͼ�����" << endl << endl;
                Sleep(1000);
        		wait();
				cout << "\n�벻Ҫ�ƶ���ꡣ\n1����ȡ���λ�ã�" << endl << endl;
  				Sleep(1000); 

    			getmouse2();
				if( judge() ){
					return 0;
				}
				cout << "\n�벻Ҫ�ƶ�����������̣�ֱ������������ɣ�" << endl  << endl;
			}
            clickandctrlv();
            // ģ�����������
            // ������ƶ���Ŀ���
            //SetCursorPos(x2, y2);
            SetCursorPos(cursorPos2.x, cursorPos2.y);
            Sleep(sleeptime);
            // ģ��������
            //mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, x2, y2, 0, 0);
            mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, cursorPos2.x, cursorPos2.y, 0, 0);
            cout << "\t ������ �����ɹ���" << endl;
            break;
        }

		cout << "��" << i  << "����Ϣ�ѷ���"  << endl << endl; 
        Sleep(sleeptime);
	}
	
 	system("pause");
  	return 0;
}






