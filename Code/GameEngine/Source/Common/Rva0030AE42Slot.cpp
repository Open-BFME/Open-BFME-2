// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG
// ?rva0030AE42@Rva00985E4@@UAEXXZ @0x0030AE42 100B
// VSlot 14 of 0x0081CA04 (class Rva00985E4): assigns AsciiStrings at +0xC/+0x10
// from globals then 12B copies at +0x14/+0x20/+0x30/+0x3C plus byte +0x2C and
// float +0x48. Evidence: rowed do-nothing (no EH prolog? Actually pushes,
// AsciiString operator= pin-only, movsd string moves, movss needs SSE).
#include "ascii_string.h"

// Matched DIR32 witness places this one-pointer AsciiString at VA 0x00DFF4F8
// in the zero-filled .data tail; the next known object starts at 0x00DFF4FC.
AsciiString g_00DFF4F8;
// Matched DIR32 witness places this one-pointer AsciiString at VA 0x00DFF4FC
// in the zero-filled .data tail; g_00DFF500 begins immediately after it.
AsciiString g_00DFF4FC;

struct S12
{
	int a;
	int b;
	int c;
};

// g_00DFF500: matched references place it at VA 0xdff500 (zero-filled; a plain-data view).
S12 g_00DFF500;
// g_00DFF50C: matched references place it at VA 0xdff50c (zero-filled; a plain-data view).
S12 g_00DFF50C;
// g_00DFF51C: matched references place it at VA 0xdff51c (zero-filled; a plain-data view).
S12 g_00DFF51C;
// g_00DFF528: matched references place it at VA 0xdff528 (zero-filled; a plain-data view).
S12 g_00DFF528;
extern unsigned char g_00DFF518;
// g_00DFF518: matched references place it at VA 0xdff518 (zero-filled .bss).
unsigned char g_00DFF518;
extern float g_00DFF534;
// g_00DFF534: matched references place it at VA 0xdff534 (zero-filled .bss).
float g_00DFF534;

class Rva00985E4
{
public:
	virtual void rva0030AE42();
private:
	char m_pad[0x08];
	AsciiString m_0C;
	AsciiString m_10;
	S12 m_14;
	S12 m_20;
	unsigned char m_2C;
	char m_pad2D[0x30 - 0x2C - 1];
	S12 m_30;
	S12 m_3C;
	float m_48;
};

void Rva00985E4::rva0030AE42()
{
	m_0C = g_00DFF4F8;
	m_10 = g_00DFF4FC;
	m_14 = g_00DFF500;
	m_20 = g_00DFF50C;
	m_2C = g_00DFF518;
	m_30 = g_00DFF51C;
	m_3C = g_00DFF528;
	m_48 = g_00DFF534;
}
