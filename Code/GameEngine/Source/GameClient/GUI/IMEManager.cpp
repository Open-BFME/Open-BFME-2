// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfmealloc /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /EHsc
// stlport
//
// BFME2 IMEManager (retail block 0x00232D7B-0x00233E8B). Source carried from
// Zero Hour's GameClient/GUI/IMEManager.cpp
// (reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/
// Code/GameEngine/Source/GameClient/GUI/IMEManager.cpp); every body below is
// repaired against game.dat.
//
// Target facts (game.dat):
// - IMEManager vtable 0x00BE82B8, IMEManagerInterface vtable 0x00BE8238;
//   slots 0-13 are SubsystemInterface's, 14-31 Zero Hour's interface order
//   (attach +0x38, detatch +0x3C, enable +0x40, disable +0x44 are dispatched
//   through by init, attach and detatch).
// - The object is 0x3064 bytes (CreateIMEManagerInterface 0x002331BB). BFME2
//   adds a third 0x801-unit buffer at +0x2026 that updateCompositionString
//   clears; nothing else in this block names it.
// - The ANSI fallbacks of Zero Hour's composition and candidate readers are
//   gone; convertToUnicode (0x0023323B) survives without a caller here.
// - serviceIMEMessage handles WM_INPUTLANGCHANGEREQUEST through a BFME2 helper
//   (0x00233B31) that rotates the keyboard layout list and skips winabc.ime,
//   and WM_IME_SETCONTEXT forwards to DefWindowProc without
//   ISC_SHOWUICOMPOSITIONWINDOW.
// Structural inferences: names of BFME2-only members and the helper are ours.
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef char Char;
typedef unsigned short WideChar;

// string.h declares _strcmpi without dllimport because this TU builds with
// /D_CRTIMP=; rename that declaration away so the import declaration below is
// the only one the TU sees.
// STLport frees through a C++-linkage free; its decoration is what keeps the
// unwind state store retail has ahead of the keyboard-layout vector's free.
#define free bfmeUnusedCRTFree
#include <stdlib.h>
#undef free
void free(void *);
#define _strcmpi _stlport_hides_strcmpi
#include "subsystem_interface.h"
#include "unicode_string.h"
// Retail builds with STRICT handles: the keyboard-layout vector's members are
// instantiated over HKL__ *, not over the void * the sweep windows.h spells
// HKL with (vector<void *>'s own constructor is a different body, 0x00026AB0).
#define HKL SweepHKL
#define GetKeyboardLayout SweepGetKeyboardLayout
#include <windows.h>
#undef GetKeyboardLayout
#undef HKL
#include <string.h>
#include <vector>
#include <algorithm>
#undef _strcmpi

// msvcr71!_strcmpi through the IAT (retail slot 0x00BBA518).
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);

// What this unit needs from winuser.h and imm.h, which the sweep windows.h
// does not carry. The imm32 entry points are reached through the image's
// import thunks (0x0065560A-0x0065564C), so they are declared without
// dllimport; the user32 ones go through the IAT.
struct HKL__ { int unused; };
typedef HKL__ *HKL;
typedef void *HIMC;

#define WM_CHAR						0x0102
#define WM_INPUTLANGCHANGEREQUEST	0x0050
#define INPUTLANGCHANGE_BACKWARD	0x0004
#define WM_IME_STARTCOMPOSITION		0x010D
#define WM_IME_ENDCOMPOSITION		0x010E
#define WM_IME_COMPOSITION			0x010F
#define WM_IME_SETCONTEXT			0x0281
#define WM_IME_NOTIFY				0x0282
#define WM_IME_COMPOSITIONFULL		0x0284
#define WM_IME_SELECT				0x0285
#define WM_IME_CHAR					0x0286

#define GCS_COMPSTR					0x0008
#define GCS_CURSORPOS				0x0080
#define GCS_RESULTSTR				0x0800
#define NI_COMPOSITIONSTR			0x0015
#define CPS_CANCEL					0x0004
#define IGP_PROPERTY				0x00000004
#define IME_PROP_CANDLIST_START_FROM_1	0x00040000
#define IME_PROP_UNICODE			0x00080000
#define ISC_SHOWUICOMPOSITIONWINDOW	0x80000000
#define IME_CAND_UNKNOWN			0x0000
#define IME_CAND_READ				0x0002

#define IMN_CLOSESTATUSWINDOW		0x0001
#define IMN_OPENSTATUSWINDOW		0x0002
#define IMN_CHANGECANDIDATE			0x0003
#define IMN_CLOSECANDIDATE			0x0004
#define IMN_OPENCANDIDATE			0x0005
#define IMN_SETCONVERSIONMODE		0x0006
#define IMN_SETSENTENCEMODE			0x0007
#define IMN_SETOPENSTATUS			0x0008
#define IMN_SETCANDIDATEPOS			0x0009
#define IMN_SETCOMPOSITIONFONT		0x000A
#define IMN_SETCOMPOSITIONWINDOW	0x000B
#define IMN_SETSTATUSWINDOWPOS		0x000C
#define IMN_GUIDELINE				0x000D
#define IMN_PRIVATE					0x000E

typedef struct tagCANDIDATELIST
{
	DWORD dwSize;
	DWORD dwStyle;
	DWORD dwCount;
	DWORD dwSelection;
	DWORD dwPageStart;
	DWORD dwPageSize;
	DWORD dwOffset[1];
} CANDIDATELIST, *LPCANDIDATELIST;

extern "C" {
__declspec(dllimport) HKL WINAPI GetKeyboardLayout(DWORD);
__declspec(dllimport) BOOL WINAPI IsWindowUnicode(HWND);
__declspec(dllimport) LRESULT WINAPI DefWindowProcW(HWND, UINT, WPARAM, LPARAM);
__declspec(dllimport) int WINAPI GetKeyboardLayoutList(int, HKL *);

HIMC WINAPI ImmCreateContext(void);
BOOL WINAPI ImmDestroyContext(HIMC);
HIMC WINAPI ImmGetContext(HWND);
BOOL WINAPI ImmReleaseContext(HWND, HIMC);
HIMC WINAPI ImmAssociateContext(HWND, HIMC);
BOOL WINAPI ImmSetOpenStatus(HIMC, BOOL);
BOOL WINAPI ImmNotifyIME(HIMC, DWORD, DWORD, DWORD);
LONG WINAPI ImmGetCompositionStringW(HIMC, DWORD, LPVOID, DWORD);
DWORD WINAPI ImmGetProperty(HKL, DWORD);
DWORD WINAPI ImmGetCandidateListW(HIMC, DWORD, LPCANDIDATELIST, DWORD);
DWORD WINAPI ImmGetCandidateListCountW(HIMC, LPDWORD);
UINT WINAPI ImmGetIMEFileNameA(HKL, LPSTR, UINT);
}

class GameFont
{
public:
	char m_pad00[0x10];
	Int height;				// +0x10
};

class GameWindow
{
public:
	Int winSetPosition(Int x, Int y);
	Int winGetPosition(Int *x, Int *y);
	Int winGetCursorPosition(Int *x, Int *y);
	Int winGetScreenPosition(Int *x, Int *y);
	Int winSetSize(Int width, Int height);
	Int winGetSize(Int *width, Int *height);
	Int winHide(Bool hide);
	UnsignedInt winSetStatus(UnsignedInt status);
	UnsignedInt winGetStatus();
	GameFont *winGetFont();
	Int winBringToTop();
	void winSetUserData(void *userData);

	char m_pad000[0x1F4];
	Int m_1F4;				// cleared by openCandidateList after winBringToTop
};

enum NameKeyType { NAMEKEY_INVALID = 0 };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};

// Observed GameWindowManager slots only.
class GameWindowManager
{
public:
#define SLOT(N) virtual void slot##N();
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
	SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30)
	virtual GameWindow *winCreateFromScript(AsciiString filename, void *info, void *parent);	// +0x7C
	SLOT(32) SLOT(33) SLOT(34)
	virtual Int winDestroy(GameWindow *window);											// +0x8C
	SLOT(36) SLOT(37) SLOT(38) SLOT(39) SLOT(40) SLOT(41) SLOT(42) SLOT(43)
	SLOT(44) SLOT(45) SLOT(46) SLOT(47) SLOT(48) SLOT(49) SLOT(50) SLOT(51)
	SLOT(52) SLOT(53) SLOT(54) SLOT(55) SLOT(56) SLOT(57) SLOT(58)
	virtual Int winSendInputMsg(GameWindow *window, UnsignedInt msg, UnsignedInt mData1, UnsignedInt mData2);	// +0xEC
	virtual GameWindow *winGetWindowFromId(GameWindow *window, Int id);					// +0xF0
	SLOT(61) SLOT(62) SLOT(63)
	virtual Int winSetModal(GameWindow *window);											// +0x100
	virtual Int winUnsetModal(GameWindow *window);										// +0x104
#undef SLOT
};

// Observed Display slot only.
class Display
{
public:
#define SLOT(N) virtual void slot##N();
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
#undef SLOT
	virtual Int getWidth();																	// +0x40
};

extern GameWindowManager *TheWindowManager;
extern Display *TheDisplay;
extern NameKeyGenerator *TheNameKeyGenerator;
extern HWND ApplicationHWnd;

enum
{
	GWM_CHAR = 0x15,
	GWM_IME_CHAR = 0x19,
	KEY_BACKSPACE = 0x0E,
	KEY_STATE_DOWN = 0x02
};

class IMEManagerInterface : public SubsystemInterface
{
public:
	virtual ~IMEManagerInterface() {}

	virtual void attach(GameWindow *window) = 0;
	virtual void detatch(void) = 0;
	virtual void enable(void) = 0;
	virtual void disable(void) = 0;
	virtual Bool isEnabled(void) = 0;
	virtual Bool isAttachedTo(GameWindow *window) = 0;
	virtual GameWindow *getWindow(void) = 0;
	virtual Bool isComposing(void) = 0;
	virtual void getCompositionString(UnicodeString &string) = 0;
	virtual Int getCompositionCursorPosition(void) = 0;
	virtual Int getIndexBase(void) = 0;
	virtual Int getCandidateCount() = 0;
	virtual UnicodeString *getCandidate(Int index) = 0;
	virtual Int getSelectedCandidateIndex() = 0;
	virtual Int getCandidatePageSize() = 0;
	virtual Int getCandidatePageStart() = 0;
	virtual Bool serviceIMEMessage(void *windowsHandle, UnsignedInt message, Int wParam, Int lParam) = 0;
	virtual Int result(void) = 0;
};

class IMEManager : public IMEManagerInterface
{
public:
	IMEManager();
	~IMEManager();

	virtual void init(void);
	virtual void reset(void);
	virtual void update(void);

	virtual void attach(GameWindow *window);
	virtual void detatch(void);
	virtual void enable(void);
	virtual void disable(void);
	virtual Bool isEnabled(void);
	virtual Bool isAttachedTo(GameWindow *window);
	virtual GameWindow *getWindow(void);
	// Native vtable slots and constructor stores identify the getters owned here.
	virtual Bool isComposing(void);
	virtual void getCompositionString(UnicodeString &string);
	virtual Int getCompositionCursorPosition(void);
	virtual Int getIndexBase(void);
	virtual Int getCandidateCount();
	virtual UnicodeString *getCandidate(Int index);
	virtual Int getSelectedCandidateIndex();
	virtual Int getCandidatePageSize();
	virtual Int getCandidatePageStart();
	virtual Bool serviceIMEMessage(void *windowsHandle, UnsignedInt message, Int wParam, Int lParam);
	virtual Int result(void);

protected:
	enum
	{
		MAX_COMPSTRINGLEN = 2 * 1024
	};

	Int m_result;										// +0x0C
	GameWindow *m_window;								// +0x10
	HIMC m_context;										// +0x14
	HIMC m_oldContext;									// +0x18
	Int m_disabled;										// +0x1C
	Bool m_composing;									// +0x20
	WideChar m_compositionString[MAX_COMPSTRINGLEN + 1];	// +0x22
	WideChar m_resultsString[MAX_COMPSTRINGLEN + 1];		// +0x1024
	WideChar m_compositionString2[MAX_COMPSTRINGLEN + 1];	// +0x2026, BFME2 only
	Int m_compositionCursorPos;							// +0x3028
	Int m_compositionStringLength;						// +0x302C
	Int m_indexBase;									// +0x3030
	Int m_pageStart;									// +0x3034
	Int m_pageSize;										// +0x3038
	Int m_selectedIndex;								// +0x303C
	Int m_candidateCount;								// +0x3040
	UnicodeString *m_candidateString;					// +0x3044
	Bool m_unicodeIME;									// +0x3048
	Int m_compositionCharsDisplayed;					// +0x304C

	WideChar convertCharToWide(WPARAM mbchar, UINT codePage);
	void updateCompositionString(void);
	void getResultsString(void);
	void updateProperties(void);
	void openCandidateList(Int candidateFlags);
	void closeCandidateList(Int candidateFlags);
	void updateCandidateList(Int candidateFlags);
	void convertToUnicode(Char *mbcs, UnicodeString &unicode);
	void resizeCandidateWindow(Int pageSize);

	void openStatusWindow(void);
	void closeStatusWindow(void);

	GameWindow *m_candidateWindow;						// +0x3050
	GameWindow *m_statusWindow;							// +0x3054
	GameWindow *m_candidateTextArea;					// +0x3058
	GameWindow *m_candidateUpArrow;						// +0x305C
	GameWindow *m_candidateDownArrow;					// +0x3060
};

extern IMEManager *TheIMEManager;
Int IMECandidateWindowLineSpacing = 2;

IMEManager *CreateIMEManagerInterface(void)
{
	return new IMEManager;
}

// Retail IMEManager vftable 0x00BE82B8 slots 21/23/24/25/27/28/29 name
// these existing 4/7-byte bodies; fields agree with the constructor stores.
Bool IMEManager::isComposing(void) { return m_composing; }
Int IMEManager::getCompositionCursorPosition(void) { return m_compositionCursorPos; }
Int IMEManager::getIndexBase(void) { return m_indexBase; }
Int IMEManager::getCandidateCount(void) { return m_candidateCount; }
Int IMEManager::getSelectedCandidateIndex(void) { return m_selectedIndex; }
Int IMEManager::getCandidatePageSize(void) { return m_pageSize; }
Int IMEManager::getCandidatePageStart(void) { return m_pageStart; }

IMEManager::IMEManager()
{
	m_result = 0;
	m_window = NULL;
	m_context = NULL;
	m_oldContext = NULL;
	m_disabled = 0;
	m_composing = FALSE;
	m_compositionCursorPos = 0;
	m_compositionStringLength = 0;
	m_indexBase = 1;
	m_pageStart = 0;
	m_pageSize = 0;
	m_selectedIndex = 0;
	m_candidateCount = 0;
	m_candidateString = NULL;
	m_unicodeIME = FALSE;
	m_compositionCharsDisplayed = 0;
	m_candidateWindow = NULL;
	m_statusWindow = NULL;
	m_candidateTextArea = NULL;
	m_candidateUpArrow = NULL;
	m_candidateDownArrow = NULL;
	for (Int i = 0; i < MAX_COMPSTRINGLEN + 1; i++)
	{
		m_compositionString[i] = 0;
		m_resultsString[i] = 0;
	}
}

IMEManager::~IMEManager()
{
	if (m_candidateWindow)
	{
		TheWindowManager->winDestroy(m_candidateWindow);
	}

	if (m_statusWindow)
	{
		TheWindowManager->winDestroy(m_statusWindow);
	}

	if (m_candidateString)
	{
		delete[] m_candidateString;
	}

	IMEManager::detatch();
	ImmAssociateContext(ApplicationHWnd, m_oldContext);
	ImmReleaseContext(ApplicationHWnd, m_oldContext);

	if (m_context)
	{
		ImmDestroyContext(m_context);
	}
}

void IMEManager::init(void)
{
	m_context = ImmCreateContext();
	m_oldContext = ImmGetContext(ApplicationHWnd);
	m_disabled = 0;

	m_candidateWindow = TheWindowManager->winCreateFromScript(AsciiString("IMECandidateWindow.wnd"), NULL, NULL);
	m_candidateWindow->winSetStatus(0x20);

	if (m_candidateWindow)
	{
		m_candidateWindow->winHide(TRUE);

		NameKeyType id = TheNameKeyGenerator->nameToKey(AsciiString("IMECandidateWindow.wnd:TextArea"));
		m_candidateTextArea = TheWindowManager->winGetWindowFromId(m_candidateWindow, id);

		id = TheNameKeyGenerator->nameToKey(AsciiString("IMECandidateWindow.wnd:UpArrow"));
		m_candidateUpArrow = TheWindowManager->winGetWindowFromId(m_candidateWindow, id);

		id = TheNameKeyGenerator->nameToKey(AsciiString("IMECandidateWindow.wnd:DownArrow"));
		m_candidateDownArrow = TheWindowManager->winGetWindowFromId(m_candidateWindow, id);

		if (m_candidateTextArea == NULL)
		{
			TheWindowManager->winDestroy(m_candidateWindow);
			m_candidateWindow = NULL;
		}
	}

	m_statusWindow = TheWindowManager->winCreateFromScript(AsciiString("IMEStatusWindow.wnd"), NULL, NULL);

	if (m_statusWindow)
	{
		m_statusWindow->winHide(TRUE);
	}

	if (m_candidateWindow != NULL)
	{
		m_candidateWindow->winSetUserData(TheIMEManager);
		m_candidateTextArea->winSetUserData(TheIMEManager);
	}

	detatch();
	enable();
}

// ?IMEManager::reset present-unmatched
void IMEManager::reset(void)
{
}

// ?IMEManager::update present-unmatched
void IMEManager::update(void)
{
}

void IMEManager::attach(GameWindow *window)
{
	if (m_window != window)
	{
		detatch();

		if (window && (window->winGetStatus() & 0x02))
		{
			disable();
		}

		if (m_disabled == 0)
		{
			ImmSetOpenStatus(m_context, TRUE);
			ImmAssociateContext(ApplicationHWnd, m_context);
		}

		m_window = window;
	}
}

void IMEManager::detatch(void)
{
	if (m_context)
	{
		ImmNotifyIME(m_context, NI_COMPOSITIONSTR, CPS_CANCEL, 0);
		ImmSetOpenStatus(m_context, FALSE);
	}

	ImmAssociateContext(ApplicationHWnd, NULL);
	m_composing = FALSE;

	if (m_window && (m_window->winGetStatus() & 0x02))
	{
		enable();
	}

	m_window = NULL;
}

// BFME2's STLport takes resize's fill value by value (retail 0x000E6D39
// forwards the address of its own stack argument to _M_fill_insert), so the
// vector<HKL> nextKeyboardLayout uses is spelled out with the stock 4.5.3
// bodies around that one signature.
_STLP_BEGIN_NAMESPACE

template <>
class vector<HKL, allocator<HKL> > : public _Vector_base<HKL, allocator<HKL> >
{
public:
	typedef HKL *iterator;
	typedef size_t size_type;
	typedef allocator<HKL> allocator_type;

	explicit vector(size_type n)
		: _Vector_base<HKL, allocator<HKL> >(n, allocator_type())
	{
		_M_finish = uninitialized_fill_n(_M_start, n, HKL());
	}

	iterator begin() { return _M_start; }
	iterator end() { return _M_finish; }
	size_type size() const { return size_type(_M_finish - _M_start); }

	iterator erase(iterator first, iterator last)
	{
		HKL *i = __copy_ptrs(last, _M_finish, first, __true_type());
		_Destroy(i, _M_finish);
		_M_finish = i;
		return first;
	}

	void insert(iterator pos, size_type n, const HKL &x)
	{
		_M_fill_insert(pos, n, x);
	}

	void resize(size_type newSize, HKL x)
	{
		if (newSize < size())
			erase(begin() + newSize, end());
		else
			insert(end(), newSize - size(), x);
	}

	void _M_fill_insert(iterator position, size_type n, const HKL &x);

protected:
	void _M_insert_overflow(HKL *position, const HKL &x, const __true_type &, size_type fillLen, bool atEnd = false)
	{
		const size_type oldSize = size();
		const size_type &larger = oldSize < fillLen ? fillLen : oldSize;
		const size_type len = oldSize + larger;

		HKL *newStart = _M_end_of_storage.allocate(len);
		HKL *newFinish = (HKL *)__copy_trivial(_M_start, position, newStart);
		newFinish = fill_n(newFinish, fillLen, x);
		if (!atEnd)
			newFinish = (HKL *)__copy_trivial(position, _M_finish, newFinish);
		_M_clear();
		_M_set(newStart, newFinish, newStart + len);
	}

	void _M_clear()
	{
		_Destroy(_M_start, _M_finish);
		_M_end_of_storage.deallocate(_M_start, _M_end_of_storage._M_data - _M_start);
	}

	void _M_set(HKL *s, HKL *f, HKL *e)
	{
		_M_start = s;
		_M_finish = f;
		_M_end_of_storage._M_data = e;
	}
};

void vector<HKL, allocator<HKL> >::_M_fill_insert(iterator position, size_type n, const HKL &x)
{
	if (n != 0)
	{
		if (size_type(_M_end_of_storage._M_data - _M_finish) >= n)
		{
			HKL xCopy = x;
			const size_type elemsAfter = _M_finish - position;
			HKL *oldFinish = _M_finish;
			if (elemsAfter > n)
			{
				__uninitialized_copy(_M_finish - n, _M_finish, _M_finish, __true_type());
				_M_finish += n;
				__copy_backward_ptrs(position, oldFinish - n, oldFinish, __true_type());
				fill(position, position + n, xCopy);
			}
			else
			{
				uninitialized_fill_n(_M_finish, n - elemsAfter, xCopy);
				_M_finish += n - elemsAfter;
				__uninitialized_copy(position, oldFinish, _M_finish, __true_type());
				_M_finish += elemsAfter;
				fill(position, oldFinish, xCopy);
			}
		}
		else
		{
			_M_insert_overflow(position, x, __true_type(), n);
		}
	}
}

_STLP_END_NAMESPACE

// BFME2 only (0x00233B31): the next installed keyboard layout after current,
// walking the list backward when asked, skipping the winabc.ime layout.
static HKL nextKeyboardLayout(HKL current, Bool backward)
{
	HKL result = NULL;
	UINT count = GetKeyboardLayoutList(0, NULL);

	if (count != 0)
	{
		std::vector<HKL> layouts(count);
		layouts.resize(count, NULL);
		HKL *first = layouts.begin();
		GetKeyboardLayoutList(count, first);
		HKL *last = layouts.end();

		if (backward)
		{
			std::reverse(first, last);
		}

		HKL *it = std::find(first, last, current);

		if (it != last)
		{
			std::rotate(first, it, last);

			HKL *p;

			for (p = first; p != last; ++p)
			{
				char fileName[256];
				ImmGetIMEFileNameA(*p, fileName, 256);

				if (_strcmpi(fileName, "winabc.ime") != 0)
				{
					break;
				}
			}

			if (p != last)
			{
				result = *p;
			}
		}
	}

	return result;
}

Bool IMEManager::serviceIMEMessage(void *windowsHandle, UnsignedInt message, Int wParam, Int lParam)
{
	switch (message)
	{
		case WM_IME_CHAR:
		{
			WideChar wchar = convertCharToWide(wParam, CP_ACP);

			if (m_window && (wchar > 32 || wchar == VK_RETURN))
			{
				TheWindowManager->winSendInputMsg(m_window, GWM_IME_CHAR, (wParam & 0xffff), lParam);
				m_result = 0;
				return TRUE;
			}

			return FALSE;
		}

		case WM_CHAR:
		{
			WideChar wchar = (WideChar)(wParam & 0xffff);

			if (m_window && (wchar >= 32 || wchar == VK_RETURN))
			{
				TheWindowManager->winSendInputMsg(m_window, GWM_IME_CHAR, wchar, lParam);
				m_result = 0;
				return TRUE;
			}

			return FALSE;
		}

		case WM_IME_SELECT:
			return FALSE;

		case WM_IME_STARTCOMPOSITION:
			m_composing = TRUE;
			m_compositionCharsDisplayed = 0;
			updateCompositionString();
			m_result = 1;
			return TRUE;

		case WM_IME_ENDCOMPOSITION:
			updateCompositionString();
			m_compositionCharsDisplayed = 0;
			m_composing = FALSE;
			m_result = 1;
			return TRUE;

		case WM_IME_COMPOSITION:
		{
			if (lParam & GCS_RESULTSTR)
			{
				if (m_window)
				{
					m_composing = FALSE;

					while (m_compositionCharsDisplayed > 0)
					{
						TheWindowManager->winSendInputMsg(m_window, GWM_CHAR, KEY_BACKSPACE, KEY_STATE_DOWN);
						m_compositionCharsDisplayed--;
					}

					WideChar *ch = m_resultsString;
					getResultsString();

					while (*ch)
					{
						TheWindowManager->winSendInputMsg(m_window, GWM_IME_CHAR, *ch, 0);
						ch++;
					}

					m_composing = TRUE;
				}

				m_compositionCharsDisplayed = 0;
			}

			if (lParam & GCS_COMPSTR)
			{
				updateCompositionString();
			}

			m_result = 1;
			return TRUE;
		}

		case WM_IME_SETCONTEXT:
		{
			updateProperties();

			if (IsWindowUnicode((HWND)windowsHandle))
			{
				m_result = DefWindowProcW((HWND)windowsHandle, message, wParam, lParam & ~ISC_SHOWUICOMPOSITIONWINDOW);
			}
			else
			{
				m_result = DefWindowProcA((HWND)windowsHandle, message, wParam, lParam & ~ISC_SHOWUICOMPOSITIONWINDOW);
			}

			return TRUE;
		}

		case WM_IME_NOTIFY:
		{
			m_result = 1;

			switch (wParam)
			{
				case IMN_OPENCANDIDATE:
					openCandidateList(lParam);
					m_result = 1;
					return TRUE;

				case IMN_CLOSECANDIDATE:
					closeCandidateList(lParam);
					m_result = 1;
					return TRUE;

				case IMN_CHANGECANDIDATE:
					updateCandidateList(lParam);
					m_result = 1;
					return TRUE;

				case IMN_GUIDELINE:
					m_result = 1;
					return TRUE;

				case IMN_PRIVATE:
					if (lParam == 0x17)
					{
						return FALSE;
					}

					return TRUE;

				case IMN_CLOSESTATUSWINDOW:
					return TRUE;

				case IMN_OPENSTATUSWINDOW:
					return TRUE;

				case IMN_SETCONVERSIONMODE:
					return TRUE;

				case IMN_SETSENTENCEMODE:
					return TRUE;

				case IMN_SETOPENSTATUS:
					return TRUE;

				case IMN_SETCANDIDATEPOS:
					return TRUE;

				case IMN_SETCOMPOSITIONFONT:
					return TRUE;

				case IMN_SETCOMPOSITIONWINDOW:
					return TRUE;

				case IMN_SETSTATUSWINDOWPOS:
					return TRUE;

				default:
					m_result = 1;
					return TRUE;
			}
		}

		case WM_IME_COMPOSITIONFULL:
			m_result = 1;
			return TRUE;

		case WM_INPUTLANGCHANGEREQUEST:
		{
			HKL layout = nextKeyboardLayout((HKL)lParam, (wParam & INPUTLANGCHANGE_BACKWARD) != 0);

			if (layout == NULL)
			{
				return FALSE;
			}

			if (IsWindowUnicode((HWND)windowsHandle))
			{
				DefWindowProcW((HWND)windowsHandle, WM_INPUTLANGCHANGEREQUEST, wParam, (LPARAM)layout);
			}
			else
			{
				DefWindowProcA((HWND)windowsHandle, WM_INPUTLANGCHANGEREQUEST, wParam, (LPARAM)layout);
			}

			m_result = 0;
			return TRUE;
		}
	}

	return FALSE;
}

// ?IMEManager::result present-unmatched
Int IMEManager::result(void)
{
	return m_result;
}

void IMEManager::enable(void)
{
	m_disabled--;

	if (m_disabled <= 0)
	{
		m_disabled = 0;
		ImmAssociateContext(ApplicationHWnd, m_context);
	}
}

void IMEManager::disable(void)
{
	m_disabled++;
	ImmAssociateContext(ApplicationHWnd, NULL);
}

Bool IMEManager::isEnabled(void)
{
	return m_context != NULL && m_disabled == 0;
}

// ?IMEManager::isAttachedTo present-unmatched
Bool IMEManager::isAttachedTo(GameWindow *window)
{
	return m_window == window;
}

// ?IMEManager::getWindow present-unmatched
GameWindow *IMEManager::getWindow(void)
{
	return m_window;
}

WideChar IMEManager::convertCharToWide(WPARAM wParam, UINT codePage)
{
	char dcbsString[3];

	if (wParam & 0xff00)
	{
		dcbsString[0] = (wParam >> 8) & 0xff;
		dcbsString[1] = wParam & 0xff;
		dcbsString[2] = 0;
	}
	else
	{
		dcbsString[0] = wParam & 0xff;
		dcbsString[1] = 0;
	}

	WideChar uniString[2];

	if (MultiByteToWideChar(codePage, 0, dcbsString, strlen(dcbsString), uniString, 1) == 1)
	{
		return uniString[0];
	}

	return 0;
}

void IMEManager::getCompositionString(UnicodeString &string)
{
	string.set(m_compositionString);
}

void IMEManager::updateCompositionString(void)
{
	m_compositionCursorPos = 0;
	m_compositionString[0] = 0;
	m_compositionString2[0] = 0;
	m_compositionStringLength = 0;

	if (m_context)
	{
		LONG result = ImmGetCompositionStringW(m_context, GCS_COMPSTR, m_compositionString, MAX_COMPSTRINGLEN);

		if (result >= 0)
		{
			m_compositionStringLength = result / 2;
			m_compositionCursorPos = (ImmGetCompositionStringW(m_context, GCS_CURSORPOS, NULL, 0) & 0xffff);
		}
	}

	m_compositionString[m_compositionStringLength] = 0;
	m_compositionString[MAX_COMPSTRINGLEN] = 0;
}

void IMEManager::getResultsString(void)
{
	Int stringLen = 0;
	m_resultsString[0] = 0;

	if (m_context)
	{
		LONG result = ImmGetCompositionStringW(m_context, GCS_RESULTSTR, m_resultsString, MAX_COMPSTRINGLEN);

		if (result >= 0)
		{
			stringLen = result / 2;
		}
	}

	m_resultsString[stringLen] = 0;
	m_resultsString[MAX_COMPSTRINGLEN] = 0;
}

void IMEManager::convertToUnicode(Char *mbcs, UnicodeString &unicode)
{
	int size = MultiByteToWideChar(CP_ACP, 0, mbcs, strlen(mbcs), NULL, 0);

	unicode.clear();

	if (size <= 0)
	{
		return;
	}

	WideChar *buffer = new WideChar[size + 1];

	if (buffer)
	{
		size = MultiByteToWideChar(CP_ACP, 0, mbcs, strlen(mbcs), buffer, size);

		if (size <= 0)
		{
			unicode.clear();
		}
		else
		{
			buffer[size] = 0;
			unicode = buffer;
		}

		delete[] buffer;
	}
}

void IMEManager::openCandidateList(Int candidateFlags)
{
	if (m_candidateWindow == NULL)
	{
		return;
	}

	updateCandidateList(candidateFlags);
	resizeCandidateWindow(m_pageSize);

	m_candidateWindow->winHide(FALSE);
	m_candidateWindow->winBringToTop();
	m_candidateWindow->m_1F4 = 0;
	TheWindowManager->winSetModal(m_candidateWindow);

	Int wx, wy, wwidth, wheight, wcursorx, wcursory;
	Int cx, cy, cwidth, cheight;

	if (m_window)
	{
		m_window->winGetScreenPosition(&wx, &wy);
		m_window->winGetSize(&wwidth, &wheight);
		m_window->winGetCursorPosition(&wcursorx, &wcursory);
		m_window->winGetFont();
	}
	else
	{
		wx = wy = 0;
		wwidth = 10;
		wheight = 10;
		wcursorx = 0;
		wcursory = 0;
	}

	m_candidateWindow->winGetSize(&cwidth, &cheight);

	cx = TheDisplay->getWidth() - cwidth;
	cy = 0;

	updateProperties();

	m_candidateWindow->winSetPosition(cx, cy);
}

void IMEManager::closeCandidateList(Int candidateFlags)
{
	if (m_candidateWindow != NULL)
	{
		m_candidateWindow->winHide(TRUE);
		TheWindowManager->winUnsetModal(m_candidateWindow);
	}

	if (m_candidateString)
	{
		delete[] m_candidateString;
		m_candidateString = NULL;
	}

	m_candidateCount = 0;
}

void IMEManager::updateCandidateList(Int candidateFlags)
{
	if (m_candidateString)
	{
		delete[] m_candidateString;
		m_candidateString = NULL;
	}

	m_pageSize = 10;
	m_candidateCount = 0;
	m_pageStart = 0;
	m_selectedIndex = 0;

	if (m_candidateWindow == NULL || m_context == NULL || candidateFlags == 0)
	{
		return;
	}

	for (Int i = 0, candidate = 1; i < 32; i++, candidate = candidate << 1)
	{
		if (candidateFlags & candidate)
		{
			unsigned long listCount = 0;
			Int size = ImmGetCandidateListCountW(m_context, &listCount);

			Char *buffer = new Char[size];

			if (buffer == NULL)
			{
				return;
			}

			memset(buffer, 0, size);

			CANDIDATELIST *clist = (CANDIDATELIST *)buffer;
			Int bytesCopied = ImmGetCandidateListW(m_context, i, clist, size);

			if (bytesCopied != 0 && bytesCopied <= size && clist->dwStyle != IME_CAND_UNKNOWN && clist->dwStyle != IME_CAND_READ)
			{
				if ((clist->dwPageStart > clist->dwSelection) ||
					(clist->dwSelection >= clist->dwPageStart + clist->dwPageSize))
				{
					clist->dwPageStart = (clist->dwSelection / clist->dwPageSize) * clist->dwPageSize;
				}

				m_pageSize = clist->dwPageSize;
				m_candidateCount = clist->dwCount;
				m_pageStart = clist->dwPageStart;
				m_selectedIndex = clist->dwSelection;

				if (m_candidateUpArrow)
				{
					m_candidateUpArrow->winHide(m_pageStart == 0);
				}

				if (m_candidateDownArrow)
				{
					m_candidateDownArrow->winHide(m_candidateCount - m_pageStart <= m_pageSize);
				}

				if (m_candidateCount > 0)
				{
					m_candidateString = new UnicodeString[m_candidateCount];

					if (m_candidateString)
					{
						for (Int j = 0; j < m_candidateCount; j++)
						{
							Char *string = (Char *)((UnsignedInt)clist + (UnsignedInt)clist->dwOffset[j]);
							m_candidateString[j].set((WideChar *)string);
						}
					}
				}
			}

			delete[] buffer;
			return;
		}
	}
}

void IMEManager::updateProperties(void)
{
	HKL kb = GetKeyboardLayout(0);
	Int prop = ImmGetProperty(kb, IGP_PROPERTY);

	m_indexBase = prop & IME_PROP_CANDLIST_START_FROM_1 ? 1 : 0;
	m_unicodeIME = (prop & IME_PROP_UNICODE) != 0;
}

void IMEManager::resizeCandidateWindow(Int pageSize)
{
	if (m_candidateWindow == NULL)
	{
		return;
	}

	GameFont *font = m_candidateTextArea->winGetFont();

	if (font == NULL)
	{
		return;
	}

	Int newh = pageSize * (font->height + IMECandidateWindowLineSpacing);

	Int w, h;
	m_candidateTextArea->winGetSize(&w, &h);
	Int dif = newh - h;
	m_candidateTextArea->winSetSize(w, newh);

	m_candidateWindow->winGetSize(&w, &h);
	h += dif;
	m_candidateWindow->winSetSize(w, h);

	if (m_candidateDownArrow)
	{
		Int x, y;
		m_candidateDownArrow->winGetPosition(&x, &y);
		y += dif;
		m_candidateDownArrow->winSetPosition(x, y);
	}
}

UnicodeString *IMEManager::getCandidate(Int index)
{
	if (m_candidateString != NULL && index >= 0 && index < m_candidateCount)
	{
		return &m_candidateString[index];
	}

	static UnicodeString emptyString;
	return &emptyString;
}

void IMEManager::openStatusWindow(void)
{
	if (m_statusWindow)
	{
		m_statusWindow->winHide(FALSE);
	}
}

void IMEManager::closeStatusWindow(void)
{
	if (m_statusWindow)
	{
		m_statusWindow->winHide(TRUE);
	}
}
