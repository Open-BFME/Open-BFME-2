// cl: /Ireference/shims/bfme2_ascii /MD
//
// ??0Rva005DAAB6@@QAE@XZ 45B @0x005DAA71: ctor for Rva005DAAB6 over base
// Rva0055B0CC ctor at 0x0055B048, then installs vtable 0x008765A8, zeroes
// byte at +0x2C and four floats at +0x30/+0x34/+0x38/+0x3C via SSE.
// Evidence: base call plus vptr store plus mov byte [esi+2c],0 plus xorps
// plus 4x movss, sole caller at 0x00597D9B. Layout (base members plus
// derived m_2C/m_30/m_3C) verbatim from landed sibling
// Code/GameEngine/Source/Common/Rva005DAAB6Slot15.cpp; dtor row
// ??1Rva005DAAB6@@UAE@XZ at 0x005DAAB6 proves the class.

#include "ascii_string.h"

enum ObjectID
{
	INVALID_ID = 0
};

class Rva0055B0CC
{
public:
	Rva0055B0CC();
	virtual ~Rva0055B0CC();
private:
	float m_04;
	ObjectID m_08;
	AsciiString m_0C;
	unsigned int m_10;
	int m_pad14;
	float m_18;
	int m_pad1C;
	bool m_20;
	bool m_21;
	ObjectID m_24;
	bool m_28;
};

class Rva005DAAB6 : public Rva0055B0CC
{
public:
	Rva005DAAB6();
	virtual ~Rva005DAAB6();
private:
	bool m_2C;
	struct Coord3D
	{
		float x;
		float y;
		float z;
	};
	Coord3D m_30;
	float m_3C;
};

Rva005DAAB6::Rva005DAAB6()
	: m_2C(false)
{
	m_30.x = 0.0f;
	m_30.y = 0.0f;
	m_30.z = 0.0f;
	m_3C = 0.0f;
}
