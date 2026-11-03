// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport46
// ??_G?$pair@$$CBVAsciiString@@UTreeHintOpaque0043671B@@@_STL@@QAEPAXI@Z @0x004348AE 28B: deleting dtor calls rowed pair dtor 0x00434513 then operator delete 0x0002FD60 on flag; public QAE like AudioEventRTS precedent.
// ??_GTreeHintOpaque0043671B@@QAEPAXI@Z @0x002DDE27 28B: deleting dtor calls rowed TreeHintOpaque dtor 0x00229840 then operator delete; same shape.
#include <map>
#include "ascii_string.h"
#include "unicode_string.h"
#include "../../Include/GameClient/TreeHintOpaque0043671B.h"
typedef _STL::pair<const AsciiString, TreeHintOpaque0043671B> TreeHintPair0043671B;
void famgenDeletePair0043671B(TreeHintPair0043671B *p) { delete p; }
void famgenDeleteTreeHint0043671B(TreeHintOpaque0043671B *p) { delete p; }
