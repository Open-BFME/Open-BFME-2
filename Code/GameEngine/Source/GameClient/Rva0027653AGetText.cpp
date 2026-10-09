// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
// Native 0x27653A..0x27656F; ControlBar caller 0x50DCDF.
// WinInstanceData getTooltipText is a semantic twin; receiver identity unknown.
// Target loads +0x344 twice and calls virtual slot +8 or copies TheEmptyString.
#include "unicode_string.h"
class Rva0027653ADisplayString {public:virtual ~Rva0027653ADisplayString();virtual void setText(UnicodeString);virtual UnicodeString getText();};
class Rva0027653A {public:UnicodeString rva0027653A();private:char pad[0x344];Rva0027653ADisplayString * volatile text;};
UnicodeString Rva0027653A::rva0027653A(){if(text)return text->getText();return UnicodeString::TheEmptyString;}
