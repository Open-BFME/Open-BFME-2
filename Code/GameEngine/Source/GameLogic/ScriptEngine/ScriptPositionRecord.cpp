// cl: /O1 /G7 /arch:SSE  /Ireference/shims/bfmelist /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /MD /EHsc
// stlport
// Native 0035818E..00358211: CRC-keyed records in ScriptEngine+0x1A498.
// ScriptPositionRecord is a structural name: retail compares the first word
// and copies three coordinates at +4. The default constructor initializes
// the key only; the empty destructor and visible STL erase preserve the
// native outgoing iterator argument lifetime and stack-home store.
#include "ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include <list>
unsigned long Rva003ECA13Get(const AsciiString &);
struct ScriptPositionRecord {
 ScriptPositionRecord();
 ~ScriptPositionRecord() {}
 unsigned long key;
 Coord3D position;
};

// Native folded six-byte key initializer; called at 0x003581CA.
ScriptPositionRecord::ScriptPositionRecord() : key(0) {}
