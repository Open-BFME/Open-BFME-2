// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ??0Rva00238B90@@QAE@XZ @0x00238AC7 201B.
// Ctor storing vtable 0x007ED654 then six StringBase members from literals
// ("Sounds" "Music" "Streams" "AmbientStreams" "wav" plus TheEmptyString copy)
// via rowed 0x00037BA0/0x000365F0, ints at +0x44/+0x48/+0x4C via g_Va00DBA4E4,
// seventh string at +0x50 via g_00BBD3EC, and two float[5] at +0x1C/+0x30 via
// 1.0f. Layout matches Rva00238B90Dtor.cpp; vtable and callees rowed.
// Evidence: unlock lane vtable store plus seven constructions; caller 0x0004159B.
#include "ascii_string.h"

extern int g_Va00DBA4E4;
class Rva00238B90
{
public:
	Rva00238B90();
	virtual ~Rva00238B90();
private:
	AsciiString m_04;
	AsciiString m_08;
	AsciiString m_0C;
	AsciiString m_10;
	AsciiString m_14;
	AsciiString m_18;
	float m_1C[5];
	float m_30[5];
	int m_44;
	int m_48;
	int m_4C;
	AsciiString m_50;
};
Rva00238B90::Rva00238B90() : m_04("Sounds"), m_08("Music"), m_0C("Streams"), m_10("AmbientStreams"), m_14("wav"), m_18(AsciiString::TheEmptyString), m_44(0), m_48(5), m_4C(g_Va00DBA4E4 * 5), m_50(".")
{
	float v = 1.0f;
	for (int i = 0; i < 5; ++i)
	{
		m_1C[i] = v;
		m_30[i] = v;
	}
}
