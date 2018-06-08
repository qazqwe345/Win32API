#define UNICODE
#include<windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam){
  switch(message){
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
  }
  return DefWindowProc(hwnd,message,wparam,lparam);
}

int main(){
  WNDCLASS wndclass;
  ZeroMemory(&wndclass, sizeof(WNDCLASS));
  wndclass.style=CS_HREDRAW|CS_VREDRAW;
  wndclass.lpfnWndProc=WndProc;
  wndclass.hCursor=LoadCursor(NULL,IDC_ARROW);
  //wndclass.hbrBackground=(HBRUSH)(COLOR_BTNFACE+1);
  wndclass.hbrBackground=(HBRUSH)0;
  wndclass.lpszClassName=L"window";
  RegisterClass(&wndclass);
  
  while(1){
	  HWND window=CreateWindow(L"window",L"hello world!",
	    WS_EX_TOPMOST|WS_SYSMENU|WS_VISIBLE,CW_USEDEFAULT,CW_USEDEFAULT,
	    200,200,NULL,NULL,NULL,NULL);
	  ShowWindow(window, SW_NORMAL );
	  MSG msg;
	  SetWindowPos(window,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	  
	  HDC hDC;
	  PAINTSTRUCT ps;
	  RECT rt;

	  hDC = BeginPaint(window,&ps);
	  GetClientRect(window, &rt);
	  DrawText(hDC, TEXT("hello world!"), -1, &rt, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	  EndPaint(window, &ps);
	  
	  int ret;
	  for(;;){
	  	SetForegroundWindow(window);
	    ret=GetMessage(&msg,NULL,0,0);
	    if(ret<=0)
	      break;
	    DispatchMessage(&msg);
	    Sleep(5000);
	    HWND hwnd = FindWindow(NULL, L"hello world!");
		SendMessage(hwnd,WM_CLOSE,0,0);
	  }
}
	  return 0;
}
