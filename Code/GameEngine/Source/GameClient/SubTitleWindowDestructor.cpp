// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/inputs/vendor/stlport
// Native260A3C..260AD6 /154B; WB DA4FD0 names SubTitleWindow destructor.
// Constructor260865 and display caller47F79 independently prove a nonvirtual
// 0x6C receiver, main text0, font4, owning records8, count24, lines34.
// Existing member destructor260826 owns the12B record-vector cleanup.
// Registry begin/end use the canonical bfmeGoKA globals at DFEA44/48; native
// search/erase and iterator260805 attest the subtitle registry relationship.
// STLport pointer search is instantiated for this window type. Its27B dispatch
// and103B unrolled search reproduce the existing owners including relocations;
// these are actual template bodies and add no unique retail bytes.
// /EHsc permits the same-type search key to share the EH receiver stack word.
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
 char remainingFields[0x6C-0x38];
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
 SubTitleWindow *self=this;
 SubTitleWindow **found=_STL::find((SubTitleWindow**)g_bfmeBegKA,(SubTitleWindow**)g_bfmeEndKA,self);
 if(found!=(SubTitleWindow**)g_bfmeEndKA)
  ((_STL::vector<void*>*)&g_bfmeBegKA)->erase((void**)found);
}

