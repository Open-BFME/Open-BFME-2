// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG
// ?rva0030AE42@Rva00985E4@@UAEXXZ @0x0030AE42 100B
// VSlot 14 of 0x0081CA04 (class Rva00985E4): assigns AsciiStrings at +0xC/+0x10
// from globals then 12B copies at +0x14/+0x20/+0x30/+0x3C plus byte +0x2C and
// float +0x48. Evidence: rowed do-nothing (no EH prolog? Actually pushes,
// AsciiString operator= pin-only, movsd string moves, movss needs SSE).
#include "ascii_string.h"

struct S12
{
	int a;
	int b;
	int c;
};

// The Fire settings this manager copies from (TheFireSettings, 0x00DFF4F8,
// defined in Rva007B6880Thunks.cpp). Members follow the retail field table
// at VA 0x00C08708 (INIBfmeSettingsParsers.cpp); ScorchIntensity is a Real.
class Rva0030ADED
{
public:
	AsciiString m_00;
	AsciiString m_04;
	S12 m_08;
	S12 m_14;
	unsigned char m_20;
	S12 m_24;
	S12 m_30;
	float m_3C;
};

extern Rva0030ADED TheFireSettings;

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
	m_0C = TheFireSettings.m_00;
	m_10 = TheFireSettings.m_04;
	m_14 = TheFireSettings.m_08;
	m_20 = TheFireSettings.m_14;
	m_2C = TheFireSettings.m_20;
	m_30 = TheFireSettings.m_24;
	m_3C = TheFireSettings.m_30;
	m_48 = TheFireSettings.m_3C;
}
