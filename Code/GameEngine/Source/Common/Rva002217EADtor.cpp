// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD
// ??1Rva002217EA@@QAE@XZ @0x002217B1 57B
// Dtor of Rva002217EA: releases ref member at +4 via rowed Release_Ref plus
// wide string at +0 via releaseBuffer. Layout from rowed copy ctor 0x002217EA.
// Evidence: retail bytes and callers plus EH prolog shape.
#include "unicode_string.h"

#include "../../../Libraries/Source/WWVegas/WWLib/OpaqueRefCounted.h"

#include "../../Include/Common/Rva0036CA00Str.h"
#include "../../Include/Common/Rva002390CBInlines.h"

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
