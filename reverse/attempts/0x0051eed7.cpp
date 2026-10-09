// ?RenderGraph@AptTimeLine@@QAEXABUPair0051E31A@@0HPBD@Z
// partial score=0.78 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?RenderGraph@AptTimeLine@@QAEXABUPair0051E31A@@0HPBD@Z
// retail 0x0051EED7..0x0051F6D7 (2048 bytes).
// The time line (post-game graph) screen's "AptTimeLine::RenderGraph" Apt
// callback: the registration at 0x0051FE1F binds this address under that
// string (0x0086724C) as a member pointer. WorldBuilder twin 0x013DC050
// (AptTimeLine.cpp) gives the shape: read the Apt "_graphMode" parameter
// through the pinned 0x004128F0 (default FinalScore) and pick the series
// mode; walk every player's series (vtables 0x00867268 / 0x00867270 by the
// screen's game type at +0x284) for the longest series and the largest value;
// round the value scale to a power of ten (rowed 0x0051E458); lay out the
// graph (rowed 0x0051E31A); draw each player's line twice (glow and line
// through 0x0051E511 with the focus weight at +0x2B8 as alpha) and its
// markers (0x0051E664 with the side image at +0x298 and the event images at
// +0x2A8 / +0x2AC); refresh the eleven Y axis labels when the scale changed
// (+0x2B0) and the eleven X axis labels (frame numbers or GameText time
// formats) when the length changed (+0x2B4). Retail 1.06 replaces the
// WorldBuilder scale loop by the digit count of the formatted maximum.
#include <vector>
#include <algorithm>

#include "ascii_string.h"
#include "unicode_string.h"

struct Pair0051E31A
{
	int word;
	volatile float scalar;
};

class Image;

// One player's row of the time line (0x50 bytes).
struct AptTimeLinePlayer
{
	unsigned char m_pad00[0x8];
	int m_color;              // +0x08
	AsciiString m_faction;    // +0x0C
	int m_side;               // +0x10
	unsigned char m_pad14[0x2C - 0x14];
	_STL::vector<int> m_eventsA; // +0x2C
	_STL::vector<int> m_eventsB; // +0x38
	unsigned char m_pad44[0x50 - 0x44];
};

class __declspec(novtable) TimelineSeries
{
public:
	virtual int count() = 0;
	virtual float value(int index) = 0;

	AptTimeLinePlayer *m_player; // +0x04
	int m_mode;                  // +0x08
};

// Vtable 0x00867268 (slots 0x0051E72C / 0x0051E96B).
class Rva00867268Series : public TimelineSeries
{
public:
	Rva00867268Series(int mode)
	{
		m_player = 0;
		m_mode = mode;
	}
	virtual int count();
	virtual float value(int index);
};

// Vtable 0x00867270 (slots 0x0051E754 / 0x0051E9D2).
class Rva00867270Series : public Rva00867268Series
{
public:
	Rva00867270Series(int mode) : Rva00867268Series(mode)
	{
	}
	virtual int count();
	virtual float value(int index);
};

class Rva0051E354
{
public:
	void rva0051E664(TimelineSeries *series, int index, Image *image);
	void rva0051E511(TimelineSeries *series, float a, float b, unsigned long color);

	float x, y, width, height;
	int frames;
	float maximum;
};

class Rva0051E31A
{
public:
	void writeFields(const Pair0051E31A &a, const Pair0051E31A &b, int word, float scalar);
};

class GameTextInterface
{
public:
#define V(n) virtual void v##n();
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09) V(0A) V(0B) V(0C) V(0D) V(0E)
#undef V
	virtual UnicodeString fetch(const char *label, bool *exists = 0); // +0x3C
};

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &name, const UnicodeString &text, bool flag);
};

struct WideStringView
{
	struct Header
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
		unsigned short data[1];
	};
	__forceinline unsigned short charAt(int index) const { return m_data ? m_data->data[index] : 0; }
	Header *m_data;
};

bool __cdecl Rva004128F0GetParam(const char *params, const char *key, AsciiString &value);
float Rva0051E458PowFloat(int base, int exp);

extern GameTextInterface *TheGameText;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
extern int g_Va00DBA4E4;

class AptTimeLine
{
public:
	void RenderGraph(const Pair0051E31A &position, const Pair0051E31A &size, int unused, const char *params);

private:
	unsigned char m_pad000[0x284];
	int m_gameType;                     // +0x284
	_STL::vector<AptTimeLinePlayer> m_players; // +0x288
	unsigned char m_pad294[0x298 - 0x294];
	Image *m_sideImages[4];             // +0x298
	Image *m_eventImageA;               // +0x2A8
	Image *m_eventImageB;               // +0x2AC
	float m_lastMaximum;                // +0x2B0
	int m_lastFrames;                   // +0x2B4
	float *m_focus;                     // +0x2B8, the focus weights' vector storage
};

void AptTimeLine::RenderGraph(const Pair0051E31A &position, const Pair0051E31A &size, int unused, const char *params)
{
	AsciiString graphMode;
	if (!Rva004128F0GetParam(params, "_graphMode", graphMode))
		graphMode = "FinalScore";

	int mode = 4;
	if (graphMode.compare("Units") == 0)
		mode = 0;
	else if (graphMode.compare("Structures") == 0)
		mode = 1;
	else if (graphMode.compare("Resources") == 0)
		mode = 2;
	else if (graphMode.compare("Territories") == 0)
		mode = 3;
	else if (graphMode.compare("FinalScore") == 0)
		mode = 4;

	Rva00867268Series seriesA(mode);
	Rva00867270Series seriesB(mode);
	TimelineSeries *series;
	if (m_gameType == 6 || m_gameType == 7)
		series = &seriesB;
	else
		series = &seriesA;

	int maxFrames = 0;
	float maximum = -3.402823466e+38f;
	_STL::vector<AptTimeLinePlayer>::iterator player;
	for (player = m_players.begin(); player != m_players.end(); ++player)
	{
		series->m_player = player;
		int count = series->count();
		maxFrames = _STL::max(maxFrames, count);
		for (int i = 0; i < series->count(); ++i)
		{
			float value = series->value(i);
			maximum = _STL::max(maximum, value);
		}
	}

	int top = (int)maximum;
	AsciiString digits;
	digits.format("%d", top);
	int places = digits.getLength() - 2;
	if (places < 1)
		places = 1;
	int scale = (int)Rva0051E458PowFloat(10, places);
	int step = (top / scale + 1) * scale / 10;
	if (step == 0)
		step = 1;
	maximum = (float)(step * 10);

	Rva0051E354 graph;
	((Rva0051E31A *)&graph)->writeFields(position, size, maxFrames, maximum);

	for (player = m_players.begin(); player != m_players.end(); ++player)
	{
		unsigned int color = player->m_color & 0xFFFFFF;
		series->m_player = player;
		graph.rva0051E511(series, 1.0f, 3.0f, ((int)(m_focus[player - m_players.begin()] * 0.5f * 255.5)) << 24 | color);
		graph.rva0051E511(series, 1.0f, 1.0f, ((int)(m_focus[player - m_players.begin()] * 255.5)) << 24 | color);
	}

	for (player = m_players.begin(); player != m_players.end(); ++player)
	{
		series->m_player = player;
		int last = series->count() - 1;
		if (last >= 0)
			graph.rva0051E664(series, last, (player->m_side == 4 || player->m_side == 3) ? 0 : m_sideImages[player->m_side]);
		_STL::vector<int>::iterator it;
		for (it = player->m_eventsA.begin(); it != player->m_eventsA.end(); ++it)
			graph.rva0051E664(series, *it, m_eventImageA);
		for (it = player->m_eventsB.begin(); it != player->m_eventsB.end(); ++it)
			graph.rva0051E664(series, *it, m_eventImageB);
	}

	if (m_lastMaximum != maximum)
	{
		int label = 0;
		for (int i = 0; i < 11; ++i, label += step)
		{
			AsciiString name;
			name.format("Timeline:YAxis:%d", i);
			UnicodeString text;
			text.format(L"%d", label);
			g_bfmeAptWindowManager->bfmeSetText(name, text, false);
		}
		m_lastMaximum = maximum;
	}

	if (m_lastFrames != maxFrames)
	{
		for (int i = 0; i < 11; ++i)
		{
			UnicodeString text;
			if (m_gameType == 6 || m_gameType == 7)
			{
				text.format(L"%d", _STL::min(i * maxFrames / 10 + 1, maxFrames));
				g_bfmeAptWindowManager->bfmeSetText(AsciiString("Timeline:XAxisDescription"), UnicodeString(L" "), false);
			}
			else
			{
				int frame = (int)((maxFrames + 0.5f) * i * 0.1f);
				int totalSeconds = maxFrames / g_Va00DBA4E4;
				int seconds = frame / g_Va00DBA4E4;
				UnicodeString format;
				if (totalSeconds < 3600)
				{
					format = TheGameText->fetch("APT:TimeMinuteSecond");
					AsciiString name("Timeline:XAxisDescription");
					g_bfmeAptWindowManager->bfmeSetText(name, TheGameText->fetch("APT:TimeDescriptionMinuteSecond"), false);
				}
				else if (totalSeconds < 86400)
				{
					format = TheGameText->fetch("APT:TimeHoursMinute");
					AsciiString name("Timeline:XAxisDescription");
					g_bfmeAptWindowManager->bfmeSetText(name, TheGameText->fetch("APT:TimeDescriptionHoursMinute"), false);
				}
				else
				{
					format = TheGameText->fetch("APT:TimeDaysHoursMinute");
					AsciiString name("Timeline:XAxisDescription");
					g_bfmeAptWindowManager->bfmeSetText(name, TheGameText->fetch("APT:TimeDescriptionDaysHoursMinute"), false);
				}

				UnicodeString piece;
				for (int j = 0; j < format.getLength(); ++j)
				{
					const WideStringView &view = *(const WideStringView *)&format;
					if (view.charAt(j) == 's')
					{
						piece.format(L"%02d", seconds % 60);
						text += piece;
					}
					else if (view.charAt(j) == 'm')
					{
						piece.format(L"%02d", seconds / 60 % 60);
						text += piece;
					}
					else if (view.charAt(j) == 'h')
					{
						piece.format(L"%02d", seconds / 60 / 60 % 24);
						text += piece;
					}
					else if (view.charAt(j) == 'd')
					{
						piece.format(L"%d", seconds / 60 / 60 / 24);
						text += piece;
					}
					else
					{
						unsigned short ch = view.charAt(j);
						text.concat(&ch, 1);
					}
				}
			}

			AsciiString name;
			name.format("Timeline:XAxis:%d", i);
			g_bfmeAptWindowManager->bfmeSetText(name, text, false);
			if (i == 10)
				g_bfmeAptWindowManager->bfmeSetText(AsciiString("Timeline:TotalTime"), text, false);
		}
		m_lastFrames = maxFrames;
	}
}
