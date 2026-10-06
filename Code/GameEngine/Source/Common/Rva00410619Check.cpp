// cl: /MD
// ?rva00410619@Rva00410619@@QAEXPAURva00410619Arg@@@Z, retail 0x00410619 111B.
// Syncs GameWindow enabled bit with bool at +0 when AsciiString at +4 matches
// arg AsciiString at +0x10 via strncmp IAT. Evidence: strncmp FF15,
// winGetStatus row 0x30F45F mov eax [ecx+8], winEnable row 0x313BEC,
// empty string 0xBBAC1C, caller 0x411413, prev 0x4105A8 next 0x410688.

extern "C" __declspec(dllimport) int __cdecl strncmp(const char *s1, const char *s2, unsigned int n);


struct AsciiHeader
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	char data[1];
};

struct AsciiString
{
	AsciiHeader *m_data;
};

class GameWindow
{
public:
	unsigned int winGetStatus();
	int winEnable(bool enable);
};

struct Rva00410619Arg
{
	char m_00[0x10];
	AsciiString m_10;
	GameWindow *m_14;
};

class Rva00410619
{
public:
	void rva00410619(Rva00410619Arg *arg);
private:
	bool m_flag;
	char m_pad[3];
	AsciiString m_name;
};

void Rva00410619::rva00410619(Rva00410619Arg *arg)
{
	AsciiHeader *p1 = m_name.m_data;
	unsigned int len;
	if (p1 != 0)
		len = p1->length;
	else
		len = 0;
	AsciiHeader *p2 = *(AsciiHeader * volatile *)&m_name.m_data;
	const char *b;
	if (p2 != 0)
		b = p2->data;
	else
		b = (char *)"";
	const char *a;
	if (arg->m_10.m_data != 0)
		a = arg->m_10.m_data->data;
	else
		a = (char *)"";
	if (strncmp(a, b, len) != 0)
		return;
	GameWindow *win = arg->m_14;
	if (win == 0)
		return;
	if (((win->winGetStatus() >> 3) & 1) != (unsigned int)m_flag)
		win->winEnable(m_flag);
}
