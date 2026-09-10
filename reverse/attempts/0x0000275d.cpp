// ?d_0000275d@@YAXXZ
// partial score=0.85 date=2026-09-09
// cl: /O1
//
// Retail RVA 0x0000275D, 395 bytes. initializeAppWindows from Generals
// WinMain.cpp, reconciled to BFME 2:
//   - hInstance arrives in EDI from the same-TU caller
//   - two stack args: nCmdShow, runWindowed
//   - Debug slot-0xB0 notify via bfmeNotifyDebugWindowed before RegisterClass
//   - LoadImageA("lotrbfme.ico") instead of LoadIcon
//   - RegisterClassW / CreateWindowExW with the class name at 0x00DA5F10
 //   - window title from a UnicodeString-returning helper at 0x0023484D
 //   - centered position only when the X/Y sentinels still hold -1000000
//   - branchless window style: 0x90080008 fullscreen, 0x90C80000 windowed
//   - explicit releaseBuffer (no C++ EH frame around the title temporary)

typedef void *HANDLE;
typedef void *HINSTANCE;
typedef void *HWND;
typedef void *HICON;
typedef void *HCURSOR;
typedef void *HBRUSH;
typedef void *HMENU;
typedef void *HGDIOBJ;
typedef unsigned long DWORD;
typedef long LONG;
typedef int BOOL;
typedef unsigned int UINT;
typedef long LRESULT;
typedef unsigned int WPARAM;
typedef long LPARAM;

typedef LRESULT (__stdcall *WNDPROC)(HWND, UINT, WPARAM, LPARAM);

typedef struct tagRECT
{
	LONG left;
	LONG top;
	LONG right;
	LONG bottom;
} RECT;

typedef struct tagWNDCLASSW
{
	UINT style;
	WNDPROC lpfnWndProc;
	int cbClsExtra;
	int cbWndExtra;
	HINSTANCE hInstance;
	HICON hIcon;
	HCURSOR hCursor;
	HBRUSH hbrBackground;
	const unsigned short *lpszMenuName;
	const unsigned short *lpszClassName;
} WNDCLASSW;

#define CS_VREDRAW 0x0001
#define CS_HREDRAW 0x0002
#define CS_DBLCLKS 0x0008
#define IMAGE_ICON 1
#define LR_LOADFROMFILE 0x0010
#define LR_DEFAULTSIZE 0x0040
#define BLACK_BRUSH 4
#define SM_CXSCREEN 0
#define SM_CYSCREEN 1
#define SWP_NOSIZE 0x0001
#define SWP_NOMOVE 0x0002
#define HWND_TOP ((HWND)0)
#define HWND_TOPMOST ((HWND)-1)
#define DEFAULT_XRESOLUTION 800
#define DEFAULT_YRESOLUTION 600
#define WINDOW_POS_SENTINEL (-1000000)

extern "C" {
__declspec(dllimport) HANDLE __stdcall LoadImageA(HINSTANCE, const char *, UINT, int, int, UINT);
__declspec(dllimport) HGDIOBJ __stdcall GetStockObject(int);
__declspec(dllimport) UINT __stdcall RegisterClassW(const WNDCLASSW *);
__declspec(dllimport) BOOL __stdcall AdjustWindowRect(RECT *, DWORD, BOOL);
__declspec(dllimport) int __stdcall GetSystemMetrics(int);
__declspec(dllimport) HWND __stdcall CreateWindowExW(DWORD, const unsigned short *, const unsigned short *, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, void *);
__declspec(dllimport) BOOL __stdcall SetWindowPos(HWND, HWND, int, int, int, int, UINT);
__declspec(dllimport) HWND __stdcall SetFocus(HWND);
__declspec(dllimport) BOOL __stdcall SetForegroundWindow(HWND);
__declspec(dllimport) BOOL __stdcall ShowWindow(HWND, int);
__declspec(dllimport) BOOL __stdcall UpdateWindow(HWND);
}

LRESULT __stdcall WndProc(HWND, UINT, WPARAM, LPARAM);
void bfmeNotifyDebugWindowed(unsigned runWindowed);

template <typename T>
class StringBase
{
	friend class UnicodeString;

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	void releaseBuffer();
	Header *m_data;
};

class UnicodeString
{
public:
	const unsigned short *str() const
	{
		static const unsigned short empty[1] = {0};
		return m_data.m_data ? m_data.m_data->data : empty;
	}

	void release()
	{
		m_data.releaseBuffer();
	}

private:
	StringBase<unsigned short> m_data;
};

UnicodeString bfmeGetMainWindowTitle();

const unsigned short *g_windowClassName;
int g_windowPosX;
int g_windowPosY;

HINSTANCE ApplicationHInstance;
HWND ApplicationHWnd;
bool gInitializing;
bool gDoPaint;

static bool initializeAppWindows(HINSTANCE hInstance, int nCmdShow, bool runWindowed)
{
	WNDCLASSW wndClass;
	RECT rect;
	UnicodeString title;
	DWORD windowStyle;

	bfmeNotifyDebugWindowed(*(unsigned *)&runWindowed);

	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = (HICON)LoadImageA(hInstance, "lotrbfme.ico", IMAGE_ICON, 0, 0,
		LR_LOADFROMFILE | LR_DEFAULTSIZE);
	wndClass.hCursor = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszMenuName = 0;
	wndClass.lpszClassName = g_windowClassName;
	RegisterClassW(&wndClass);

	unsigned char rw = *(unsigned char *)&runWindowed;
	windowStyle = 0x90080008 + ((0 - (int)rw) & 0x00BFFFF8);

	rect.left = 0;
	rect.top = 0;
	rect.right = DEFAULT_XRESOLUTION;
	rect.bottom = DEFAULT_YRESOLUTION;
	AdjustWindowRect(&rect, windowStyle, 0);

	gInitializing = true;

	if (g_windowPosX == WINDOW_POS_SENTINEL)
		g_windowPosX = (GetSystemMetrics(SM_CXSCREEN) / 2) - 400;
	if (g_windowPosY == WINDOW_POS_SENTINEL)
		g_windowPosY = (GetSystemMetrics(SM_CYSCREEN) / 2) - 332;

	title = bfmeGetMainWindowTitle();
	HWND hWnd = CreateWindowExW(
		0,
		g_windowClassName,
		title.str(),
		windowStyle,
		g_windowPosX,
		g_windowPosY,
		rect.right - rect.left,
		rect.bottom - rect.top,
		0,
		0,
		hInstance,
		0);
	title.release();

	if (!runWindowed)
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	else
		SetWindowPos(hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

	SetFocus(hWnd);
	SetForegroundWindow(hWnd);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	ApplicationHInstance = hInstance;
	ApplicationHWnd = hWnd;
	gInitializing = false;
	if (!runWindowed)
		gDoPaint = false;

	return true;
}

bool bfmeCallInitializeAppWindows(HINSTANCE hInstance, int nCmdShow, bool runWindowed)
{
	return initializeAppWindows(hInstance, nCmdShow, runWindowed);
}
