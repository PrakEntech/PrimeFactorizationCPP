#include <windows.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define GENERATE_BUTTON 4
LRESULT CALLBACK WinPro(HWND,UINT,WPARAM,LPARAM);

void AddMenus(HWND);
void AddControls(HWND);
HWND hIn,hOut;
HMENU hMenu;
std::string priFact(int q)
{
    std::string a="";
    int r=int(q/2);
    for (int i = 2; int(i <= r); i++)
        {
        int z=0;
        while(z==0)
        {
            if (q%i==0)
                {
                std::ostringstream str1;
                str1 << i;
                a+=str1.str()+',';
                q=int(q/i);
                }
            else{break;}
        }
        }
return a.substr(0,a.length()-1);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
    WNDCLASSW wc = {0};
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"myWindowClass";
    wc.lpfnWndProc = WinPro;
    if (!RegisterClassW(&wc)){return -1;}
    CreateWindowW(L"myWindowClass", L"Prime Factorization", WS_OVERLAPPEDWINDOW | WS_VISIBLE,100,100,350,160,NULL,NULL,NULL,NULL);
    MSG msg={0};
    while(GetMessage(&msg,NULL,NULL,NULL))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    //MessageBox(NULL,"Message","Title",MB_OK);
    return 0;
}
LRESULT CALLBACK WinPro(HWND hWnd,UINT msg,WPARAM wp,LPARAM lp)
{
    switch (msg)
    {
    case WM_COMMAND:
        switch(wp)
        {
        case GENERATE_BUTTON:{
            std::stringstream str;
            std::string q;
            char inp[10];
            GetWindowText(hIn,inp,10);
            str<<inp;
            int x;
            str>>x;
            q=priFact(x);
            char z[q.length()+1];
            strcpy(z, q.c_str());
            SetWindowText(hOut,z);
            break;}
        case FILE_MENU_EXIT:
            DestroyWindow(hWnd);
            break;
        case FILE_MENU_NEW:
            MessageBeep(MB_ICONINFORMATION);
            break;
        case FILE_MENU_OPEN:
            std::string linkChar;
            linkChar="https://www.youtube.com/c/PrakEnTech";
            ShellExecute(NULL, "open", linkChar.c_str(), NULL, NULL, SW_SHOWNORMAL);
            break;
        }
        break;
    case WM_CREATE:
        AddMenus(hWnd);
        AddControls(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        DefWindowProcW(hWnd,msg,wp,lp);
    }
}

void AddMenus(HWND hWnd)
{
    hMenu = CreateMenu();
    HMENU hFileMenu = CreateMenu();
    HMENU hFileMenuq = CreateMenu();
    AppendMenu(hFileMenu,MF_STRING,FILE_MENU_EXIT,"Exit");
    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)hFileMenu,"File");
    AppendMenu(hFileMenuq,MF_STRING,FILE_MENU_NEW,"Developed By - PrakEnTech");
    AppendMenu(hFileMenuq,MF_STRING,FILE_MENU_OPEN,"Dev's Web");
    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)hFileMenuq,"About");

    SetMenu(hWnd,hMenu);
}
void AddControls(HWND hWnd)
{
    CreateWindowW(L"Static", L"Number", WS_VISIBLE | WS_CHILD,10,10,59,30,hWnd,NULL,NULL,NULL);
    hIn = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,80,10,70,20,hWnd,NULL,NULL,NULL);
    CreateWindowW(L"Button",L"Calculate",WS_VISIBLE | WS_CHILD,260,10,70,18,hWnd,(HMENU)GENERATE_BUTTON,NULL,NULL);
    hOut = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,17,40,300,50,hWnd,NULL,NULL,NULL);
}
