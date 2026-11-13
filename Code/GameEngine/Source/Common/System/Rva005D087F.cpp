// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// ??BRva005D087F@@QAE?AVUnicodeString@@XZ, retail 0x005D087F, 98 bytes.
// Wide materializer twin of Rva0002CB02Operator (98B Ascii): length via rowed
// Rva005D0507, buffer via shared getBufferForRead, payloads via rowed
// Rva005D061E, return copy with releaseBuffer via tmp dtor. Evidence: callees
// rowed 0x005D0507 0x000370A0 0x005D061E 0x00037050 0x00036E70; caller 0x005D09FA.
// Honest address name; owner unproven.
// Native unwind-map references and the complete exact parent EH graph
// establish the naturally emitted return-object cleanup at 0x007A1B98.
// Its 25-byte extent excludes the interior return label.
#include "unicode_string.h"

#include "../../../Include/Common/Rva005D0507.h"

class Rva005D061E
{
public:
	int copyToBuffer(unsigned short *dst);
};

class Rva005D087F
{
public:
	operator UnicodeString();
};

Rva005D087F::operator UnicodeString()
{
	UnicodeString tmp;
	int len = ((Rva005D0507 *)this)->rva005D0507();
	unsigned short *buf = ((StringBase<unsigned short> *)&tmp)->getBufferForRead(len);
	((Rva005D061E *)this)->copyToBuffer(buf);
	return tmp;
}
