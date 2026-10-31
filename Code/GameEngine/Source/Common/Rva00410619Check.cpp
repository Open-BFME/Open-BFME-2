// cl: /MD
// ?process@Rva0045F0A0@@QAEXPAURva0045F0A0Input@@@Z, retail 0x00410619 111B:
// the per-entry body of the window enable functor that
// Rva00462710ModeCheckForEach.cpp's for_each<..., Rva0045F0A0> (0x004113F4)
// calls (formerly rowed as ?rva00410619@Rva00410619@@..., same bytes).
// Syncs GameWindow enabled bit with bool at +0 when AsciiString at +4 matches
// arg AsciiString at +0x10 via strncmp IAT. Evidence: strncmp FF15,
// winGetStatus row 0x30F45F mov eax [ecx+8], winEnable row 0x313BEC,
// empty string 0xBBAC1C, caller 0x411413, prev 0x4105A8 next 0x410688.

#include <string.h>


struct AsciiHeader
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	char data[1];
};

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

class GameWindow
{
public:
	unsigned int winGetStatus();
	int winEnable(bool enable);
};

struct Rva0045F0A0Input
{
	char m_00[0x10];
	AsciiString m_10;
	GameWindow *m_14;
};

class Rva0045F0A0
{
public:
	void process(Rva0045F0A0Input *input);
private:
	bool m_flag;
	char m_pad[3];
	AsciiString m_name;
};

void Rva0045F0A0::process(Rva0045F0A0Input *input)
{
	AsciiHeader *asciiHeader = *(AsciiHeader **)&m_name;
	unsigned int len;
	if (asciiHeader != 0)
		len = asciiHeader->length;
	else
		len = 0;
	AsciiHeader *prefixHeader = *(AsciiHeader * volatile *)&m_name;
	const char *prefix;
	if (prefixHeader != 0)
		prefix = prefixHeader->data;
	else
		prefix = (char *)"";
	const char *text = input->m_10.str();
	if (strncmp(text, prefix, len) != 0)
		return;
	GameWindow *win = input->m_14;
	if (win == 0)
		return;
	if (((win->winGetStatus() >> 3) & 1) != (unsigned int)m_flag)
		win->winEnable(m_flag);
}
