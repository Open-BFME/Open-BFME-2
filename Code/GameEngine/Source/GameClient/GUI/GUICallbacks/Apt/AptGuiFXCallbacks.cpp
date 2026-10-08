// cl: /O1 /Ob1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
//
// BFME2's GuiFX screen Apt callback "AptGuiFX::OnInitialized", a static
// callback bound by that name through the holder 0x0023E8D8 by the
// screen's registration 0x00380B0C; that binding is its only reference.
// The class is named for the string's prefix.

// The GuiFX movie's ready flag (0x00E022E0, beside the "GuiFX.apt" name at
// 0x00E022E8).
extern bool g_Va00E022E0;

class AptGuiFX
{
public:
	static void OnInitialized(const char *unused);
};

// Retail 0x003808E8, 8 bytes: "AptGuiFX::OnInitialized" marks the GuiFX
// movie ready.
void AptGuiFX::OnInitialized(const char *unused)
{
	g_Va00E022E0 = true;
}

// Reference lead: Open-BFME-1 9cbfb551fe20dae985f91f2319d8997287b6a705,
// game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptGuiFX.cpp.
// WB F65460 names ShowToolTip in AptGuiFX.cpp:131..144. Retail boundary
// 0x3808F0..0x380A5D and the HideToolTip/tooltip-position siblings establish
// the movie, display-string globals and this body. Existing address-derived
// free-function spelling is retained; original qualification is unasserted.
// Target evidence establishes manager slots3C/38, display slots4/18/1C/
// 20/24/28/3C, font-height field10, and width/height output globals. These
// declarations describe only the observed virtual call ABI, not full layouts.
// The target uses FontLibrary instead of WB's GlobalLanguage wrapper. Its
// recovered getFont consumes a bool in the low byte of a DWORD stack argument.
// Native caller forwards the style DWORD verbatim; the member-pointer union
// projects that proven stack ABI without a second name/pin or boolean coercion.
// UnicodeString uses the canonical BFME2 header. Formatting and movie-call
// semantics come from the clean BFME1 donor, with BFME2 dimensions and slots.
// The donor's compiler barrier retains the native final receiver-load order;
// it emits no machine instructions. All365 retail bytes are independently gated.
#include "ascii_string.h"
#include "unicode_string.h"
class GameFont;
class FontLibrary { public: GameFont *getFont(const AsciiString *,float,bool); };
extern FontLibrary *TheFontLibrary;
class DisplayString {
public:
 virtual void slot00();
 virtual void setText(UnicodeString text);
 virtual void slot08(); virtual void slot0C(); virtual void slot10(); virtual void slot14();
 virtual void setFont(GameFont *);
 virtual GameFont *getFont();
 virtual void slot20(int);
 virtual void slot24(int);
 virtual void slot28(unsigned int,int);
 virtual void slot2C(); virtual void slot30(); virtual void slot34(); virtual void slot38();
 virtual void getDimensions(int *,int *);
};
class DisplayStringManager {
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
 virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
 virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
 virtual void slot30(); virtual void slot34(); virtual DisplayString *newDisplayString();
};
extern DisplayStringManager *TheDisplayStringManager;
extern DisplayString *TheTooltipString;
extern int TooltipStringWidth,TooltipStringHeight;
class GuiFXDimensions {
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
 virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
 virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
 virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual float *getDimensions();
};
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
extern void *TheRva00222A8BOwner;
class Rva00222A8BTarget {
public: int invoke(void *,const char *,int,const char *,void *,void *,void *,void *);
};
void Rva003807B7Hide();
extern "C" __declspec(dllimport) int __cdecl _snprintf(char *,unsigned int,const char *,...);
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
void Rva003808F0Show(void *text,AsciiString *face,int size,int style,int color)
{
 if(TheTooltipString) Rva003807B7Hide();
 float *dimensions=reinterpret_cast<GuiFXDimensions *>(g_bfmeAptWindowManager)->getDimensions();
 float minScale=dimensions[0]<dimensions[1]?dimensions[0]:dimensions[1];
 union {GameFont *(FontLibrary::*typed)(const AsciiString *,float,bool); GameFont *(FontLibrary::*word)(const AsciiString *,float,int);} get;
 get.typed=&FontLibrary::getFont;
 GameFont *font=(TheFontLibrary->*get.word)(face,size*minScale,style);
 if(!font) return;
 DisplayString *display=TheDisplayStringManager->newDisplayString();
 TheTooltipString=display;
 display->setFont(font);
 TheTooltipString->setText(*reinterpret_cast<UnicodeString *>(text));
 TheTooltipString->slot28(color,0);
 TheTooltipString->slot24(1);
 TheTooltipString->slot20(255);
 TheTooltipString->getDimensions(&TooltipStringWidth,&TooltipStringHeight);
 GameFont *actualFont=TheTooltipString->getFont();
 int height=(*((int *)actualFont+4)+1)/3;
 char xText[16],yText[16];
 _snprintf(xText,16,"%g",((float)(TooltipStringWidth+height)/dimensions[0])*0.5f);
 _snprintf(yText,16,"%g",(float)(TooltipStringHeight+height)/dimensions[1]);
 char *xTextArg=xText;
 char *yTextArg=yText;
 _ReadWriteBarrier();
 reinterpret_cast<Rva00222A8BTarget *>(g_bfmeAptWindowManager)->invoke(TheRva00222A8BOwner,"ShowToolTip",2,xTextArg,yTextArg,0,0,0);
}


