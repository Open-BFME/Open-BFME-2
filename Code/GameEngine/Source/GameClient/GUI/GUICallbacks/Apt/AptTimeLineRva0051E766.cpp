// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva0051E766@Rva0051E766@@QAEXHPAD_N@Z, retail 0x0051E766 (354 bytes,
// RET 0xC), beside the AptTimeLine.cpp rows: write one game-setup value
// into the caller's buffer as text. Unless only probing, the buffer starts
// as "0". Value 0 names the game type from the mode at +0x284
// ("OtherSingle", "OtherOnlineLan", "WOTRSingle", "WOTROnlineLan"); 1 is
// 0 when TheWritableGlobalData's +0x9D4 has either low bit, else whether
// the mode is 3 or 4; 2 counts the 80-byte records at +0x288; 3 counts the
// global ScienceType vector at VA 0x00E04920; 4 is the flag at +0x294; and
// 5 is 1 for a War of the Ring mode without that flag whose first record's
// +0x10 is 0 or 1. Values 0..2 are skipped when probing. Field meanings and
// names are not established.
#include <vector>

#include <string.h>
#include <stdio.h>

enum ScienceType { SCIENCE_INVALID = -1 };
// The vector at 0x00E04920 is owned as g_Va00E04920 (Rva007B6880Thunks.cpp).
extern unsigned int g_Va00E04920;
#define g_00E04920 (*(_STL::vector<ScienceType> *)&g_Va00E04920)

class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct Rva0051E766GlobalView
{
	char m_pad000[0x9D4];
	unsigned char m_9D4;
};

struct Rva0051E766Record
{
	char m_pad00[0x10];
	int m_10;
	char m_pad14[0x50 - 0x14];
};

class Rva0051E766
{
public:
	void rva0051E766(int which, char *buffer, bool probing);
	char m_pad00[0x284];
private:
	int m_mode; // +0x284 +0x284
	_STL::vector<Rva0051E766Record> m_records; // +0x288 +0x288
	bool m_294; // +0x294
	char m_pad295[0x3];
};

void Rva0051E766::rva0051E766(int which, char *buffer, bool probing)
{
	if (!probing)
	{
		buffer[0] = '0';
		buffer[1] = 0;
	}
	if (which == 0)
	{
		if (probing)
			return;
		int mode = m_mode;
		if (mode == 2 || mode == 1 || mode == 8)
			strcpy(buffer, "OtherSingle");
		else if (mode == 3 || mode == 4 || mode == 5)
			strcpy(buffer, "OtherOnlineLan");
		else if (mode == 6)
			strcpy(buffer, "WOTRSingle");
		else if (mode == 7)
			strcpy(buffer, "WOTROnlineLan");
	}
	else if (which == 1)
	{
		if (probing)
			return;
		if (((Rva0051E766GlobalView *)TheWritableGlobalData)->m_9D4 & 3)
			strcpy(buffer, "0");
		else
			sprintf(buffer, "%d", (m_mode == 3 || m_mode == 4) ? 1 : 0);
	}
	else if (which == 2)
	{
		if (probing)
			return;
		sprintf(buffer, "%d", m_records.size());
	}
	else if (which == 3)
	{
		sprintf(buffer, "%d", g_00E04920.size());
	}
	else if (which == 4)
	{
		strcpy(buffer, m_294 ? "1" : "0");
	}
	else if (which == 5)
	{
		int mode = m_mode;
		strcpy(buffer, ((mode == 7 || mode == 6) && !m_294 && !m_records.empty()
			&& (m_records.front().m_10 == 0 || m_records.front().m_10 == 1)) ? "1" : "0");
	}
}
