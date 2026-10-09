// ??0SubTitleWindow@@QAE@PAVGameFont@@MMHHHH@Z
// partial score=0.9659198556774068 date=2026-10-09
// ??0SubTitleWindow@@QAE@PAVGameFont@@MMHHHH@Z
// partial score=0.9659198557 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ??0SubTitleWindow@@QAE@PAVGameFont@@MMHHHH@Z @0x00260865 471B ctor with DisplayString arrays and layout floats via TheDisplayStringManager slot 0x38 and global vector push. Evidence: callers 0x00047F79 0x00051353 new 0x6c then forward font and floats, dtor 0x00260A3C frees array and manager slots, Rva0029B816Ctor pattern for newDisplayString plus temp UnicodeString.
#include "unicode_string.h"
#include <vector>

class GameFont;
class ModuleData;

struct BfmeStringRecord005DDD40 { UnicodeString text; unsigned word; };

class DisplayString
{
public:
	virtual void s00();
	virtual void setText(UnicodeString s);
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void setFont(GameFont *font);
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void getSize(int *w, int *h);
};

class DisplayStringManager
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual DisplayString *newDisplayString();
	virtual void freeDisplayString(DisplayString *s);
};

extern DisplayStringManager *TheDisplayStringManager;


class BfmeItemKA;
extern BfmeItemKA **g_bfmeBegKA;

class SubTitleWindow
{
public:
	SubTitleWindow(GameFont *font, float f2, float f3, int i4, int count, int i6, int i7);
private:
	DisplayString *m_00;
	GameFont *m_04;
	_STL::vector<BfmeStringRecord005DDD40, _STL::allocator<BfmeStringRecord005DDD40> > m_vec;
	int m_14;
	int m_18;
	int m_1c;
	int m_20;
	int m_24;
	int m_28;
	int m_2c;
	int m_30;
	DisplayString **m_34;
	DisplayString **m_38;
	int m_3c;
	int m_40;
	float m_44;
	float m_48;
	float m_4c;
	float m_50;
	float m_54;
	float m_58;
	float m_5c;
	float m_60;
	float m_64;
	float m_68;
};


SubTitleWindow::SubTitleWindow(GameFont *font, float f2, float f3, int i4, int count, int i6, int i7)
	: m_00(0)
	, m_04(font)
	, m_vec()
	, m_14(4)
	, m_18(i6)
	, m_1c(0)
	, m_20(i4)
	, m_24(count)
	, m_28(0)
	, m_2c(i7)
	, m_30(0)
	, m_34(0)
	, m_38(0)
	, m_3c(0)
	, m_40(0)
	, m_44(0.0f)
	, m_48(0.0f)
	, m_4c(0.0f)
	, m_50(0.0f)
	, m_54(0.0f)
	, m_58(0.0f)
	, m_5c(0.0f)
	, m_60(0.0f)
	, m_64(0.0f)
	, m_68(0.0f)
{
	m_34 = new DisplayString *[count];
	m_38 = new DisplayString *[m_24];
	for (int i = 0; i < m_24; ++i) {
		m_34[i] = TheDisplayStringManager->newDisplayString();
		m_34[i]->setFont(m_04);
	}
	{
		m_34[0]->setText(UnicodeString((const unsigned short*)L" "));
		int w;
		int h;
		m_34[0]->getSize(&w, &h);
		m_30=h;
        m_48=(float)h*(1.0f/15.0f);
        m_4c=f2;
        m_50=f3-(float)((m_24-1)*h);
        m_54=(float)m_20+f2;
        m_58=f3;
        m_5c=(float)(h>>1)+f2;
        m_60=(float)(h>>1)+m_50;
        m_64=(float)m_20-(float)h+m_5c;
        m_68=(float)((m_24-2)*h)+m_60;
	}
	((_STL::vector<const ModuleData *>*)&g_bfmeBegKA)->push_back((const ModuleData *)this);
	DisplayString *cur = TheDisplayStringManager->newDisplayString();
	m_00 = cur;
	cur->setFont(font);
}
