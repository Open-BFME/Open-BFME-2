// ??1SubTitleWindow@@QAE@XZ
// partial score=0.97 date=2026-10-08
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/inputs/vendor/stlport
// WB0xDA4FD0 SubTitleWindow::~SubTitleWindow; complete native154B at260A3C.
// Native fields and calls match this reconstruction, but VC7 allocates a second
// stack word: EH this is at EBP-14 instead of native EBP-10; total155 vs154B.
// Existing pin ??1Rva00260A3C@@UAE@XZ belongs to three incompatible private
// class views, including an MI COMDAT anchor. Those need provider/consumer
// reconciliation before replacing the legacy virtual-dtor identity.
// Rva00260826 member destructor63 at+8 and pointer-vector find20E873/erase1FF51F
// are existing owners. The CreateAHeroData cast reuses their verified ICF body,
// and does not assert a hero semantic identity for the subtitle registry.
#include <vector>
#include <algorithm>
class DisplayString {};
class DisplayStringManager;
extern DisplayStringManager *TheDisplayStringManager;
class SubtitleDisplayFreeView {
public:
 virtual void f0(); virtual void f1(); virtual void f2(); virtual void f3();
 virtual void f4(); virtual void f5(); virtual void f6(); virtual void f7();
 virtual void f8(); virtual void f9(); virtual void f10(); virtual void f11();
 virtual void f12(); virtual void f13(); virtual void f14();
 virtual void freeDisplayString(DisplayString*);
};
struct Rva00260826 {
 void *begin, *end, *capacity;
 ~Rva00260826();
};
class BfmeItemKA;
class CreateAHeroData;
extern BfmeItemKA **g_bfmeBegKA, **g_bfmeEndKA;
class SubTitleWindow {
public:
 ~SubTitleWindow();
private:
 DisplayString *mainText;
 void *font;
 Rva00260826 records;
 int state, field18, wait, field20, count, opacity, color, field30;
 DisplayString **lines;
};
SubTitleWindow::~SubTitleWindow() {
 if(TheDisplayStringManager) {
  for(int i=0;i<count;++i)
   ((SubtitleDisplayFreeView*)TheDisplayStringManager)->freeDisplayString(lines[i]);
  if(mainText)
   ((SubtitleDisplayFreeView*)TheDisplayStringManager)->freeDisplayString(mainText);
 }
 mainText=0;
 delete[] lines;
 CreateAHeroData *self=(CreateAHeroData*)this;
 CreateAHeroData **found=_STL::find((CreateAHeroData**)g_bfmeBegKA,(CreateAHeroData**)g_bfmeEndKA,self);
 if(found!=(CreateAHeroData**)g_bfmeEndKA)
  ((_STL::vector<void*>*)&g_bfmeBegKA)->erase((void**)found);
}

