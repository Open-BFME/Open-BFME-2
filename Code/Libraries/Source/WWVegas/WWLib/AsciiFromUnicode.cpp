// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Reference: BFME1 ascii/unicode string construction/translation family.
// Explicit BFME2 export ??0AsciiString@@QAE@ABVUnicodeString@@@Z identifies
// RVA38250 (91 bytes). Its exported wide translate38170 distinguishes it
// from the masked-identical reverse conversion6CB6D0; no duplicate range.
typedef unsigned short Wide;
#include "unicode_string.h"
class AsciiString:public StringBase<char> {
public:
    AsciiString(const UnicodeString&);
    void translate(const Wide*);
};
AsciiString::AsciiString(const UnicodeString& text) {
    translate(text.str());
}
