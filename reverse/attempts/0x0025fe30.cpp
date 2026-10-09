// ?rva0025FE30@BfmeItemKA@@AAEXMMMMHH@Z
// partial score=0.92 date=2026-10-09
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/inputs/vendor/stlport /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/shims/sweep
// ?getXFromAlignment@GameSubTitle@@SAHHHHMM@Z @0x0025FF8F 175B.
// WB 0x00DA61E0 names GameSubTitle::getXFromAlignment in GameSubTitles.cpp;
// the full retail boundary ends at 0x0026003E. Five stack arguments, caller
// cleanup, and no receiver use establish this utility's cdecl ABI. Original
// alignment enum spelling is unknown; retain its 32-bit integer representation.
// Donor: Open-BFME-1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f,
// game/GameEngineDevice/Source/VideoDevice/Bink/SubtitleEntryAlignment.cpp.
// The clean donor compiled under BFME2 /O1 /arch:SSE /G7 placed no bodies.
// Target adaptations: the owned theDebug pointer and the observed three-zero
// argument report factory at slot 0x6C. Math, cases, reference-returning minimum
// and diagnostic text are retained; all 175 bytes match under region flags.

#include <math.h>

typedef int Int;
typedef float Real;

class BfmeDebugReport
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual BfmeDebugReport *slot38(const char *text);
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C(Int value);
};

class BfmeDebugManager
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual BfmeDebugReport *slot6C(void *first, void *second, void *third);
};

class Debug;
extern Debug *theDebug;
extern void _bfme_debugRecordCallsite(Int kind);

static const Int &bfmeMin(const Int &first, const Int &second)
{
	return first < second ? first : second;
}

// ?getXFromAlignment@GameSubTitle@@SAHHHHMM@Z
typedef unsigned short WideChar;
typedef unsigned int UnsignedInt;
typedef int Int;



#include "unicode_string.h"
#include <string.h>
#pragma intrinsic(memset)

class GameFont;

class SubtitleEntry
{
public:
	SubtitleEntry(const UnicodeString &text, UnsignedInt color, Int style,
		Int alignment, Int line, Int startFrame, Int endFrame);
protected:
	virtual ~SubtitleEntry();

private:
	UnicodeString m_text;
	UnsignedInt m_color;
	Int m_style;
	Int m_alignment;
	Int m_line;
	Int m_startFrame;
	Int m_endFrame;
	bool m_displayed;
};

class DisplayString
{
public:
	virtual ~DisplayString();
	virtual void setText(UnicodeString text);
	virtual UnicodeString getText();
	virtual Int getTextLength();
	virtual void notifyTextChanged();
	virtual void reset();
	virtual void setFont(GameFont *font);
 virtual void s7();virtual void s8();virtual void s9();virtual void s10();
 virtual void colors(unsigned*);virtual void shadowColors(unsigned*);virtual void s13();
 virtual void position(Int,Int,Int,Int);
 virtual void s15();virtual void s16();virtual void s17();virtual void s18();virtual void s19();
 virtual void clip(Int*);
};

// The VA 0x00DFEAD8 singleton is DisplayStringManager *TheDisplayStringManager,
// reused through its existing owned symbol. This TU keeps its own view of
// the vtable and casts at the use.
class DisplayStringManager;

class SubtitleDisplayFactoryView
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual void f4();
	virtual void f5();
	virtual void f6();
	virtual void f7();
	virtual void f8();
	virtual void f9();
	virtual void f10();
	virtual void f11();
	virtual void f12();
	virtual void f13();
	virtual DisplayString *newDisplayString();
};

extern DisplayStringManager *TheDisplayStringManager;
static inline SubtitleDisplayFactoryView *theDisplayStringManagerView()
{
	return (SubtitleDisplayFactoryView *)TheDisplayStringManager;
}

extern "C" __declspec(dllimport) WideChar *__cdecl wcscpy(
	WideChar *destination, const WideChar *source);
extern "C" __declspec(dllimport) WideChar *__cdecl wcstok(
	WideChar *string, const WideChar *control);

class GameSubTitle : public SubtitleEntry
{
public:
	static Int getXFromAlignment(Int alignment, Int base, Int unused, Real low, Real high);
	virtual ~GameSubTitle();
	GameSubTitle(GameFont *font, const UnicodeString &text,
		UnsignedInt color, Int style, Int alignment, Int line,
		Int startFrame, Int endFrame);

private:
	DisplayString *m_displayStrings[3];
	Int m_displayStringCount;
	Int m_displayStringCapacity;
};


Int GameSubTitle::getXFromAlignment(Int alignment, Int base, Int unused, Real low, Real high)
{
	Int difference = (Int)fabs(high - low);

	switch (alignment)
	{
	case 1:
		return 0;
	case 0:
	{
		Int highInt = (Int)high;
		Int lowInt = (Int)low;
		const Int &minimum = bfmeMin(highInt, lowInt);
		return minimum + ((difference - base) >> 1);
	}
	case 2:
	{
		Int highInt = (Int)high;
		Int lowInt = (Int)low;
		const Int &minimum = bfmeMin(highInt, lowInt);
		return minimum - base + difference;
	}
	default:
		_bfme_debugRecordCallsite(1);
		reinterpret_cast<BfmeDebugManager *>(theDebug)->slot60();
		BfmeDebugReport *report = reinterpret_cast<BfmeDebugManager *>(theDebug)->slot6C(0, 0, 0);
		report = report->slot38("Invalid Subtitle alignment!");
		report->slot4C(1);
		return 0;
	}
}

// ??0GameSubTitle@@QAE@PAVGameFont@@ABVUnicodeString@@IHHHHH@Z @0x002603D1 233B.
// WB0x00DA5EF0 identifies the derived subtitle constructor; base at 0x00688550,
// members 0x24..0x34, DisplayString slots 0x18/0x04 and manager slot 0x38 are
// independently read from retail. Donor: Open-BFME-1 ba7ddda7,
// game/GameEngine/Source/GameClient/SubtitleEntryConstructor.cpp.
// Use the shared UnicodeString and owned manager global, protected base dtor,
// target slot 0x38, and actual newline delimiter. Target's three STOSD writes
// establish intrinsic memset for the pointer array; the donor's three scalar
// stores do not emit it. Full 233-byte constructor and prior alignment helper
// are verified together; no donor address is used as a target address.
GameSubTitle::GameSubTitle(GameFont *font,
	const UnicodeString &text, UnsignedInt color, Int style, Int alignment,
	Int line, Int startFrame, Int endFrame) :
	SubtitleEntry(text, color & 0x00FFFFFF, style, alignment, line, startFrame,
		endFrame),
	m_displayStrings(),
	m_displayStringCount(0),
	m_displayStringCapacity(0)
{
	memset(m_displayStrings, 0, sizeof(m_displayStrings));
	WideChar buffer[0x400];
	wcscpy(buffer, text.str());
	WideChar *token = wcstok(buffer, (const WideChar *)L"\n");
	while (token)
	{
		m_displayStrings[m_displayStringCount] =
			theDisplayStringManagerView()->newDisplayString();
		m_displayStrings[m_displayStringCount]->setFont(font);
		m_displayStrings[m_displayStringCount]->setText(UnicodeString(token));
		token = wcstok(0, (const WideChar *)L"\n");
		++m_displayStringCount;
	}
}

// ?rva002602DA@BfmeItemKA@@AAE_NXZ @0x002602DA 247B.
// WB 0x00DA5800 identifies SubTitleWindow::UpdateDraw in this source file.
// Retain the existing BfmeItemKA ABI view and private callee spelling used by
// BfmeConv902.cpp; this is the same receiver and native callee, not a new alias.
// Native bytes establish the five states, signed opacity/wait arithmetic,
// vector of eight-byte records at +8, count +24, display array +34, flag +3C.
// Record member meanings remain opaque. The real STLport size() expression and
// /GX preserve retail scheduling and the by-value empty UnicodeString lifetime.
// Complete native boundary 0x002602DA..0x002603D1, including the diagnostic.
#include <vector>
// STLport already included VC7.1 <new>; WWLib must use those placement forms.
#define _OPERATOR_NEW_DEFINED_
#include "wwmath.h"
struct SubtitleRecord { unsigned a,b; };
class BfmeItemKA {
private:
 bool rva002602DA();
 void rva0025FCE8(Int,Int,Int);
 void rva0025FBBC(unsigned*,unsigned,Int);
 void rva002606E6();
 void rva0025FE30(float,float,float,float,Int,Int);
 void *mainText, *font;
 _STL::vector<SubtitleRecord> records;
 int state, field18, wait, field20, count, opacity, color, field30;
 DisplayString **lines;
 unsigned *values;int displayed;
 float field40,baseline,field48,left,top,right,bottom,field5C,split60,field64,split68;
};
bool BfmeItemKA::rva002602DA() {
 bool draw=true;
 switch(state) {
 case 0:
  opacity+=18;
  if(opacity>=255) { opacity=255; state=3; }
  break;
 case 1:
 case 4:
  draw=false;
  break;
 case 2:
  opacity-=18;
  if(opacity<=0) {
   opacity=0; state=1; draw=false;
   for(int i=0;i<count;++i) lines[i]->setText(UnicodeString());
   displayed=0;
  }
  break;
 case 3:
  opacity=255;
  if(records.size()==0) {
   wait-=33;
   if(wait<=0) { wait=0; state=2; }
  }
  break;
 default:
  _bfme_debugRecordCallsite(1);
  ((BfmeDebugManager*)theDebug)->slot60();
  ((BfmeDebugManager*)theDebug)->slot6C(0,0,0)->slot38("Unrecognized SubTitleRenderState!")->slot4C(1);
  return false;
 }
 return draw;
}




// Native165B 25FBBC..25FC61: same receiver/mode/color helper called by draw328.
// Native accesses opacity28; three cases select the four corner alpha weights.
void BfmeItemKA::rva0025FBBC(unsigned *out,unsigned value,Int mode) {
 switch(mode) {
 case 2:
  for(Int i=0;i<4;++i) {
   out[i]=value&0x00ffffff;
   if(i<2)out[i]|=(opacity&~1)<<23;
   else out[i]|=(opacity&~7)<<21;
  }break;
 case 1:
  for(Int i=0;i<4;++i){out[i]=value&0x00ffffff;out[i]|=opacity<<24;}break;
 case 0:
  for(Int i=0;i<4;++i) {
   out[i]=value&0x00ffffff;
   if(i>=2)out[i]|=(opacity&~1)<<23;
   else out[i]|=(opacity&~7)<<21;
  }break;
 }
}
// BF1 f98983a7d Rva00435270SetRange.cpp clean guide. Target caller260787
// proves existing BfmeItemKA private ABI. Native adds split68/count24 start,
// iterated alpha masks and floor rounding; virtual offsets independently read.
void BfmeItemKA::rva0025FCE8(Int mode,Int from,Int to) {
 Int storage[4];storage[0]=(Int)left;storage[2]=(Int)right;storage[1]=from;storage[3]=to;
 float start=split68-(float)((count-1)*field30)+baseline;
 for(Int i=0;i<count;++i) {
  unsigned generated[4];unsigned masked[4]={0,0,0,0};
  Int index=(displayed+i)%count;
  rva0025FBBC(generated,values[index],mode);
  for(Int j=0;j<4;++j)masked[j]|=generated[j]&0xff000000;
  lines[index]->colors(generated);
  lines[(displayed+i)%count]->shadowColors(masked);
  lines[(displayed+i)%count]->clip(storage);
  Int product=field30*i;
  // Native FISTP obeys x87 rounding; VC7.1 rejects /QIfist with SSE.
  // Reuse the donor WWMath primitive; the draw algorithm remains C++.
  Int y=WWMath::Float_To_Long((float)floor((float)product+start+0.5f));
  lines[(displayed+i)%count]->position((Int)((float)(field30>>1)+(float)storage[0]),y,1,1);
 }
}

struct Rva002606AFElem;
class Rva002606AF {public:Rva002606AFElem *erase(Rva002606AFElem*);};
static __forceinline const float &subtitleMax(const float &a,const float &b){return a>b?a:b;}
// Target record first word is copied by StringBase<G> ctor37050; word4 is color.
// Canonical UnicodeString copy gives the same base lifetime without a private view.
void BfmeItemKA::rva002606E6() {
 if(baseline>0.0f || !records.empty()) {
  baseline-=field48;
  baseline=subtitleMax(0.0f,baseline);
  if(baseline==0.0f && !records.empty()) {
   lines[displayed%count]->setText(*(const UnicodeString*)records.begin());
   values[displayed%count]=records.begin()->b;
   ((Rva002606AF*)&records)->erase((Rva002606AFElem*)records.begin());
   ++displayed;baseline=(float)field30;
  }
 }
}
class Display;
extern Display *TheDisplay;
class Rva0004263F {public:void rva0004263F(float,float,float,float,Int);};
class W3DDisplay {public:void rva0008EEF0(float,float,float,float,float,Int);};
void BfmeItemKA::rva0025FE30(float x0,float y0,float x1,float y1,Int color,Int border) {
 float width=x1-x0;float height=y1-y0;
 Int alpha=(unsigned)color>>24;
 alpha=bfmeMin(alpha,opacity);
 Int fillColor=(color&0xffffff)|(alpha<<24);
 ((Rva0004263F*)TheDisplay)->rva0004263F(x0,y0,width,height,fillColor);
 alpha+=alpha;alpha=bfmeMin(alpha,opacity);
 float lineWidth=(float)border;
 width+=(float)(border+border);height+=(float)(border+border);
 x0-=lineWidth;y0-=lineWidth;
 ((W3DDisplay*)TheDisplay)->rva0008EEF0(x0+1.0f,y0+1.0f,width,height,lineWidth,alpha<<24);
 ((W3DDisplay*)TheDisplay)->rva0008EEF0(x0,y0,width,height,lineWidth,0x7f7f7f7f);
}
