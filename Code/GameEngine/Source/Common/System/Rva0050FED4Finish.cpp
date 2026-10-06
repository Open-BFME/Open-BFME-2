// cl: /Ireference/shims/bfme2_ascii /EHsc
// ?rva0050FED4@Rva0050F0AB@@QAEHIPAVGameWindow@@I@Z retail 0x0050FED4 72B
// Window-message router: msg 0x400C (slider drag) forwards to m_78 via
// rva0050F420 when window matches; msg 0x4031/0x4032 (edit done) forwards to
// m_7c via rva0050F450; anything else or a mismatched window returns 0.
// Non-zero return means handled. Evidence: retail /O1 compares select
// 0x400C then 0x4031-0x4032 and share one return-1 tail, the switch layout;
// neighbours in Code/GameEngine/Source/Common/System/Rva0050F0AB.cpp.
typedef unsigned short wchar_t;

#include "unicode_string.h"

class GameWindow;

void GadgetTextEntrySetText(GameWindow *g, UnicodeString text);
UnicodeString __cdecl GadgetTextEntryGetText(GameWindow *g);
extern "C" __declspec(dllimport) int __cdecl _wtoi(const wchar_t *s);

class Rva0050F0AB
{
public:
	void rva0050F0AB();
	void rva0050F420(unsigned int val);
	void rva0050F290();
	void rva0050F450();
	int rva0050FED4(unsigned int msg, GameWindow *window, unsigned int val);
private:
	char m_pad00[0x68];
	unsigned int m_68;
	unsigned int m_6c;
	char m_pad70[0x78 - 0x70];
	GameWindow *m_78;
	GameWindow *m_7c;
};

int Rva0050F0AB::rva0050FED4(unsigned int msg, GameWindow *window, unsigned int val)
{
	switch (msg)
	{
	case 0x400C:
		if (window == m_78)
		{
			rva0050F420(val);
			return 1;
		}
		break;
	case 0x4031:
	case 0x4032:
		if (window == m_7c)
		{
			rva0050F450();
			return 1;
		}
		break;
	}
	return 0;
}
