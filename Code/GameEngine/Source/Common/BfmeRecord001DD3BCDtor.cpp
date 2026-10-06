// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// ??1BfmeRecord001DD3BC@@QAE@XZ @0x001DD1FF 57B dtor releases +4 ref then AsciiString +0 with EH.
// Evidence: unlock lane EH prolog shape via rowed Release_Ref 0x00050ED3 and releaseBuffer 0x00036410; next-row copy ctor proves BfmeRecord001DD3BC layout; 28B ??_G caller at 0x001DD38E.
class OpaqueRefCounted
{
public:
	void Release_Ref();
};
#include "ascii_string.h"
class Rva0036CA00Str
{
public:
	~Rva0036CA00Str()
	{
		if (m_item != 0)
			((OpaqueRefCounted *)m_item)->Release_Ref();
	}
private:
	void *m_item;
};
class BfmeRecord001DD3BC
{
public:
	~BfmeRecord001DD3BC();
private:
	AsciiString m_a0;
	Rva0036CA00Str m_a4;
};
BfmeRecord001DD3BC::~BfmeRecord001DD3BC()
{
}
