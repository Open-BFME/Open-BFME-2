// cl: /O1 /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc
//
// ?rva002332B2@Rva002332B2@@QAEXH@Z,
// retail 0x002332B2 (73 bytes). Chain after wide StringBase vector dtor.
// Cleanup: hide window at +0x3050 via rowed winHide, notify window manager
// slot 0x104, free wide-string array at +0x3044 via rowed ??_E with flags 3,
// then null +0x3044 and +0x3040. Single int arg unused (ret 4).
// Evidence: calls rowed ?winHide@GameWindow@@QAEH_N@Z and
// ??_E?$StringBase@G@@AAEPAXI@Z; global 0x00DFEF1C is TheWindowManager.
typedef unsigned short wchar_t;
void operator delete[](void *p);

class GameWindow
{
public:
	int winHide(bool hide);
};

class GameWindowManager
{
public:
	virtual void dummy00(); virtual void dummy01(); virtual void dummy02(); virtual void dummy03();
	virtual void dummy04(); virtual void dummy05(); virtual void dummy06(); virtual void dummy07();
	virtual void dummy08(); virtual void dummy09(); virtual void dummy10(); virtual void dummy11();
	virtual void dummy12(); virtual void dummy13(); virtual void dummy14(); virtual void dummy15();
	virtual void dummy16(); virtual void dummy17(); virtual void dummy18(); virtual void dummy19();
	virtual void dummy20(); virtual void dummy21(); virtual void dummy22(); virtual void dummy23();
	virtual void dummy24(); virtual void dummy25(); virtual void dummy26(); virtual void dummy27();
	virtual void dummy28(); virtual void dummy29(); virtual void dummy30(); virtual void dummy31();
	virtual void dummy32(); virtual void dummy33(); virtual void dummy34(); virtual void dummy35();
	virtual void dummy36(); virtual void dummy37(); virtual void dummy38(); virtual void dummy39();
	virtual void dummy40(); virtual void dummy41(); virtual void dummy42(); virtual void dummy43();
	virtual void dummy44(); virtual void dummy45(); virtual void dummy46(); virtual void dummy47();
	virtual void dummy48(); virtual void dummy49(); virtual void dummy50(); virtual void dummy51();
	virtual void dummy52(); virtual void dummy53(); virtual void dummy54(); virtual void dummy55();
	virtual void dummy56(); virtual void dummy57(); virtual void dummy58(); virtual void dummy59();
	virtual void dummy60(); virtual void dummy61(); virtual void dummy62(); virtual void dummy63();
	virtual void dummy64();
	virtual void slot65(GameWindow *w);
};
extern GameWindowManager *TheWindowManager;


template <typename T>
class StringBase
{
public:
	friend class Rva002332B2;
private:
	~StringBase();
	T *m_data;
};

class Rva002332B2
{
public:
	void rva002332B2(int unused);

private:
	char m_pad0[0x3040];
	int m_3040;
	void *m_3044;
	char m_pad3048[0x3050 - 0x3048];
	GameWindow *m_window;
};

void Rva002332B2::rva002332B2(int unused)
{
	(void)unused;
	if (m_window)
	{
		m_window->winHide(true);
		TheWindowManager->slot65(m_window);
	}
	StringBase<wchar_t> *arr = (StringBase<wchar_t> *)m_3044;
	if (arr)
	{
		delete[] arr;
		m_3044 = 0;
	}
	m_3040 = 0;
}
