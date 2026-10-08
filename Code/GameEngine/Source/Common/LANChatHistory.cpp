// Target Ghidra00381618..0038169D (133B), called by005AFC40.
// Existing BFME2 history writer00381C82 defines two12B STLport vectors of
// BfmeStringRecord005DDD40 (UnicodeString+color). Record copy005DDD40 and
// GadgetListBoxReset/AddEntryText establish history/listbox semantics independently.
// ZH LanLobbyMenu.cpp provides the reference UI chat/listbox relationship.
// Original helper name unknown; retain address identity. Bind vector by reference
// to preserve native ESI base+EDI iteration; all by-value UnicodeString cleanup verified.
// cl: /O1 /Oy- /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
#include "unicode_string.h"
#include <vector>
class GameWindow;
struct BfmeStringRecord005DDD40 {UnicodeString text;unsigned word;BfmeStringRecord005DDD40(const BfmeStringRecord005DDD40&);};
extern _STL::vector<BfmeStringRecord005DDD40> g_00E022F8[2];
void GadgetListBoxReset(GameWindow*);
int GadgetListBoxAddEntryText(GameWindow*,UnicodeString,int,int,int,bool);
void Rva00381618(GameWindow*window,unsigned kind) {
 if(window&&kind<2) {
  GadgetListBoxReset(window);
  _STL::vector<BfmeStringRecord005DDD40>&history=g_00E022F8[kind];
  for(BfmeStringRecord005DDD40*it=history.begin();it!=history.end();++it) {
   BfmeStringRecord005DDD40 entry(*it);
   GadgetListBoxAddEntryText(window,entry.text,entry.word,-1,-1,true);
  }
 }
}
