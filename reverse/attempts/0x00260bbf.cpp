// ?rva00260BBF@SubTitleWindow@@QAEXABV?$StringBase@G@@I@Z
// partial score=0.9386475126 date=2026-10-10
// ?rva00260BBF@SubTitleWindow@@QAEXABV?$StringBase@G@@I@Z
// partial score=0.9386475126363394 date=2026-10-10
// ?rva00260BBF@SubTitleWindow@@QAEXABV?$StringBase@G@@I@Z
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /DNDEBUG /MD /EHsc /arch:SSE /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
// Native260BBF..260DCF RET8 and WBDA5180 callgraph prove same subtitle6C receiver.
// Retail reconstructed word scan/measurement/record lifetimes; original method spelling unknown.
#include "unicode_string.h"
#include <vector>
#include <algorithm>

struct Rva00260B88Element{int a[2];};
class Rva0025FB9B{public:void rva0025FB9B();};
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
extern BfmeItemKA **g_bfmeBegKA, **g_bfmeEndKA;


struct Rva00260826 : _STL::_Vector_base<BfmeStringRecord005DDD40,_STL::allocator<BfmeStringRecord005DDD40> > {
 __forceinline Rva00260826():_STL::_Vector_base<BfmeStringRecord005DDD40,_STL::allocator<BfmeStringRecord005DDD40> >(_STL::allocator<BfmeStringRecord005DDD40>()){}
 ~Rva00260826();
};

class SubTitleWindow
{
public:
 ~SubTitleWindow();
 void rva00260BBF(const StringBase<unsigned short>&, unsigned);
	SubTitleWindow(GameFont *font, float f2, float f3, int i4, int count, int i6, int i7);
private:
	DisplayString *m_00;
	GameFont *m_04;
	Rva00260826 m_vec;
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
	int w;
	int h;
	{
		m_34[0]->setText(UnicodeString((const unsigned short*)L" "));
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

SubTitleWindow::~SubTitleWindow() {
 if(TheDisplayStringManager) {
  for(int i=0;i<m_24;++i)
   TheDisplayStringManager->freeDisplayString(m_34[i]);
  if(m_00)
   TheDisplayStringManager->freeDisplayString(m_00);
 }
 m_00=0;
 delete[] m_34;
 SubTitleWindow *self=this;
 SubTitleWindow **found=_STL::find((SubTitleWindow**)g_bfmeBegKA,(SubTitleWindow**)g_bfmeEndKA,self);
 if(found!=(SubTitleWindow**)g_bfmeEndKA)
  ((_STL::vector<void*>*)&g_bfmeBegKA)->erase((void**)found);
}


__forceinline bool SubtitleSeparator(unsigned short c){return c==0x20||c==0x95;}
void SubTitleWindow::rva00260BBF(const StringBase<unsigned short>&text,unsigned color){
 int available=(int)(m_64-m_5c);
 const unsigned short*p=text.str();
 while(*p){
  const unsigned short*start=p;
  while(*start&&SubtitleSeparator(*start))++start;
  p=start;
  const unsigned short*lastBreak=start;
  if(!*p)continue;
  do{
   unsigned short c=*p;
   while(c&&SubtitleSeparator(c)){++p;c=*p;}
   while(*p&&!SubtitleSeparator(*p)&&*p!='\n')++p;
   UnicodeString measured(start,(int)(p-start));
   m_00->setText(measured);
   int w,h;
   m_00->getSize(&w,&h);
   if(w<=available){lastBreak=p;if(*p&&*p!='\n')continue;}
   if(lastBreak==start)lastBreak=p;
   {
   UnicodeString line((const UnicodeString&)text,(int)(start-text.str()),(int)(lastBreak-start));
   BfmeStringRecord005DDD40 value={line,color};
   ((_STL::vector<Rva00260B88Element>*)&m_vec)->push_back(*(const Rva00260B88Element*)&value);
   }
   if(*p=='\n')++p;
   if(SubtitleSeparator(*lastBreak))p=lastBreak;
   break;
  }while(*p);
 }
 {
 UnicodeString blank;
 BfmeStringRecord005DDD40 value={blank,color};
 ((_STL::vector<Rva00260B88Element>*)&m_vec)->push_back(*(const Rva00260B88Element*)&value);
 }
 ((Rva0025FB9B*)this)->rva0025FB9B();
}
