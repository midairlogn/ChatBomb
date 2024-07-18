#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

POINT cursorPos;
int x;
int y;
RECT desktop;
//��������Ϣ�����̲����ļ��������Ϣ�������4��������ʹ��100������λ�����룩
int sleeptime = 100;

int copymessage(){
	// ��ȡ�û����벢��ֵ���ַ���
  	string inputString;
  	cout << "�������뷢�͵���Ϣ���ݣ�";
  	getline(cin, inputString);

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
	
	cout << "�뽫�˴����ƶ���һ�ߣ���Ҫ�ڵ�Ŀ�괰�ڣ�" << endl << endl; 
	Sleep(1000); 
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

bool getmouse(){
	// ��ȡ��Ļ�ֱ���
  	GetWindowRect(GetDesktopWindow(), &desktop);
  	int screenWidth = desktop.right - desktop.left;
  	int screenHeight = desktop.bottom - desktop.top;

    // ��ȡ���λ�ò���ӡ 
  	GetCursorPos(&cursorPos);
  	cout << "\n��굱ǰλ��: (" << cursorPos.x << ", " << cursorPos.y << ")" << endl;

  	// ��ȡҪ����ĵ��λ��
  	//cout << "������Ҫ����ĵ�� X ���� (0 �� " << screenWidth << "): ";
  	//cin >> x;
  	x = cursorPos.x ;
  	//cout << "������Ҫ����ĵ�� Y ���� (0 �� " << screenHeight << "): ";
  	//cin >> y;
  	y = cursorPos.y ;
	
	cout << "\n�벻Ҫ�ƶ�����������̡�" << endl;
	cout << "\nĿ��ĵ��λ��: (" << cursorPos.x << ", " << cursorPos.y << ")" << endl;
	
	char ifstop;
	cout << "���ٴ�ȷ�������Ƿ���ȷ�����а����뷢�͵���Ϣ�Ƿ���ȷ��" <<endl;
	cout << "ȷ�ϵĻ��������� N �� n �� 1: ";
	cin >> ifstop ;
	if ( !( ifstop == 'N' || ifstop == 'n' || ifstop == '1' ) ){
		cout << "���Ǵ�ͷ��ʼ����������";
		Sleep(3000);
		return 1 ; 
	}
	return 0 ;
}

int main() {
    cout << "��������Midairlogn�����Ͷ��ĳɹ���" << endl << endl;
	copymessage();
	//��������Ĵ���
	int sendtimes;
	cout << "\n���������뷢����Ϣ�Ĵ���:"; 
	cin >> sendtimes; 
	
	wait();
	cout << "\n�벻Ҫ�ƶ���ꡣ\n1����ȡ���λ�ã�" << endl << endl;
  	Sleep(1000); 
    
	if( getmouse()){
		return 0;
	}
	cout << "\n�벻Ҫ�ƶ�����������̣�ֱ������������ɣ�" << endl  << endl;
	Sleep(1000); 
	
	for(int i=1;i<=sendtimes;i++){
		// ������ƶ���Ŀ���
  		SetCursorPos(x, y);
  		Sleep(sleeptime);
  		// ģ��������
  		mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, x, y, 0, 0);
  		cout <<"\t ������ �����ɹ���" << endl; 

        Sleep(sleeptime);
        // ģ�� Ctrl+V
  		keybd_event(VK_CONTROL, 0, 0, 0); // ���� Ctrl ��
  		keybd_event(0x56, 0, 0, 0);  // ���� V ��
  		keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0); // �ͷ� V ��
  		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); // �ͷ� Ctrl ��
  		cout <<"\t Ctrl+v �����ɹ���" << endl; 
	
		Sleep(sleeptime);
  		// ģ��Ctrl+Enter
  		keybd_event(VK_CONTROL, 0, 0, 0); // ���� Ctrl ��
  		keybd_event(VK_RETURN, 0, 0, 0);  // ���»س���
  		keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0); // �ͷŻس���
  		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); // �ͷ� Ctrl ��
  		cout <<"\t Ctrl+Enter �����ɹ���" << endl; 
		cout << "��" << i  << "����Ϣ�ѷ���"  << endl << endl; 
        Sleep(sleeptime);
	}
	
 	system("pause");
  	return 0;
}






