// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ??1Rva005211D1@@QAE@XZ retail 0x005211D1 53B
// Evidence: unlock lane; two inlined releaseBuffer calls for members at +0/+4; caller 0x00521206 constructs member at +0x27c then calls this; callees rowed releaseBuffer 0x00036410; no vptr store so non-virtual public dtor.
#include "ascii_string.h"
class Rva005211D1
{
public:
	~Rva005211D1();
private:
	AsciiString m_a;
	AsciiString m_b;
};
Rva005211D1::~Rva005211D1()
{
}
