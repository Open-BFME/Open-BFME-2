// cl: /DNDEBUG /MD
// ??0Rva0037E270@@QAE@XZ @0x0037E352 135B
// Default ctor over Rva0037E270: zeros plus ones plus clear80 0x001EAE6F plus
// Rva004E04FD ctor plus float global 1.0f plus AsciiString null.
// Neighbours in Rva0037E270Lookup.cpp share /O1 /DNDEBUG /MD; /arch:SSE for
// retail xorps plus movss float zero and global float moves.
class AsciiString
{
	char *m_text;
public:
	AsciiString &operator=(const AsciiString &other);
};
#include <new>
class Rva001EAE6FHelper
{
	char m_data[0x80];
public:
	Rva001EAE6FHelper *clear80() throw();
};
class Rva004E04FD
{
public:
	Rva004E04FD() throw();
};
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class Rva0037E270 {
    int m_00;
    int m_04;
    float m_08;
    int m_0C;
    int m_10;
    Rva001EAE6FHelper m_14;
    int m_94;
    int m_98;
    int m_9C;
    bool m_A0;
    bool m_A1;
    int m_A4;
    int m_A8;
    int m_AC;
    char m_B0_raw[0x18];
    int m_C8;
    float m_CC;
    int m_D0;
    AsciiString m_str;
public:
    Rva0037E270();
};
Rva0037E270::Rva0037E270()
{
	m_00 = 0;
	m_04 = 0;
	m_08 = 0.0f;
	m_0C = 1;
	m_10 = 1;
	m_14.clear80();
	m_98 = -1;
	m_94 = 0;
	m_9C = 0;
	m_A0 = 0;
	m_A1 = 0;
	m_A4 = 0;
	m_A8 = 0;
	m_AC = 0;
	Rva004E04FD *pB0 = (Rva004E04FD *)m_B0_raw;
	__assume(pB0 != 0);
	new (pB0) Rva004E04FD();
	float fCC = 1.0f;
	m_C8 = 0;
	m_CC = fCC;
	_ReadWriteBarrier();
	m_D0 = 0;
	*(int *)&m_str = 0;
}
