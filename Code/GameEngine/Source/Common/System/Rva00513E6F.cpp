// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
#include "unicode_string.h"
// ?rva00513E6F@Rva00513E6F@@QAE?AVUnicodeString@@XZ @0x00513E6F 98B
// Chain lane: calls 0x00513E4A just landed; length via rowed 0x00513E03 then
// wide getBufferForRead then rowed fill 0x00513E4A then wide copy ctor
// 0x00037050 then releaseBuffer; EH frame ret 4. Prev 0x00513E4A in
// Rva00513D8F.cpp; caller 0x00513F70 unclaimed 415B. Layout matches 24B
// Rva00513E03/Rva00513E4A views at offset 0; wide materializer twin of narrow
// Rva005E36EA in Rva005E36EAMat.cpp and operator UnicodeString in
// WinMainPairUnicode.cpp.
struct Rva00513E03
{
	int length() const;
};
class Rva00513E4A
{
public:
	int rva00513E4A(unsigned short *dst);
};
class Rva00513E6F
{
public:
	UnicodeString rva00513E6F();
};
UnicodeString Rva00513E6F::rva00513E6F()
{
	UnicodeString tmp;
	((Rva00513E4A *)this)->rva00513E4A(tmp.getBufferForRead(((const Rva00513E03 *)this)->length()));
	return tmp;
}
