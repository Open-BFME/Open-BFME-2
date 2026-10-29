// cl: /MD /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7
// stlport46
// ??_GRva00204686@@QAEPAXI@Z @0x00204AF6 28B
// Scalar deleting dtor: calls rowed ??1Rva00204686@@QAE@XZ at 0x00204686 then
// rowed operator delete at 0x0002FD60. Non-virtual public dtor (no vtable).
#include "ascii_string.h"
#include <utility>
typedef _STL::pair<AsciiString,AsciiString> ScriptStringKey;
typedef _STL::pair<const ScriptStringKey,AsciiString> ScriptStringValue;
template <> ScriptStringValue::~pair();
typedef ScriptStringValue Rva00204686;
void famgenDelete(Rva00204686 *p) { delete p; }
