// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD
// ??1Rva002217EA@@QAE@XZ @0x002217B1 57B
// Dtor of Rva002217EA: releases ref member at +4 via rowed Release_Ref plus
// wide string at +0 via releaseBuffer. Layout from rowed copy ctor 0x002217EA.
// Evidence: retail bytes and callers plus EH prolog shape.
#include "unicode_string.h"

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

class Rva0036CA00Str
{
	void *m_item;
public:
	__declspec(nothrow) Rva0036CA00Str(const Rva0036CA00Str &other);
	~Rva0036CA00Str() { if (m_item) ((OpaqueRefCounted *)m_item)->Release_Ref(); }
};

class Rva002217EA
{
public:
	~Rva002217EA();
private:
	UnicodeString m_00;
	Rva0036CA00Str m_04;
	int m_08;
	int m_0C;
	int m_10;
};

Rva002217EA::~Rva002217EA()
{
}
