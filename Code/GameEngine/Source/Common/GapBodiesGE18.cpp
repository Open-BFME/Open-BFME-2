// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc /Ireference/shims/bfme2_ascii
// Small GameEngine bodies from .text gaps no Ghidra function covers
// (eighteenth batch; see GapBodiesGE01.cpp). Retail bytes establish every
// shape; owning classes are not recovered, so each keeps an address-derived
// name and a view of only the members it touches. Callees and globals use the
// ledger's existing spellings.
#include "ascii_string.h"

// --- 0x001EB3D1 (100B): mark +0xC2; while enabled (+0xC0) count the first
// pass (+0x0C, latched by +0xC3) and hand the map path of that record's
// +0x04 name to the game state's rowed 0x001EB298 setter.
struct BfmeAssignRecord36;

struct Rva001EB3D1Record
{
	int m_00;
	AsciiString m_name;										// +0x04
};

class Rva001EB3A6
{
public:
	BfmeAssignRecord36 *rva001EB3A6(int i);					// 0x001EB3A6
};

class Rva001EB298
{
public:
	void rva001EB298(AsciiString s);						// 0x001EB298
};

AsciiString Rva001EB2CCGetMapPath(const char *name);		// 0x001EB2CC

class GameState;
extern GameState *TheGameState;

class Rva001EB3D1
{
public:
	void rva001EB3D1();
private:
	int m_00;
	Rva001EB3A6 *m_records;									// +0x04
	int m_08;
	int m_count;											// +0x0C
	char m_pad10[0xC0 - 0x10];
	bool m_enabled;											// +0xC0
	bool m_C1;
	bool m_marked;											// +0xC2
	bool m_counted;											// +0xC3
};

void Rva001EB3D1::rva001EB3D1()
{
	m_marked = true;
	if (m_enabled && !m_counted)
	{
		++m_count;
		m_counted = true;
	}
	if (m_enabled)
	{
		Rva001EB3D1Record *record = (Rva001EB3D1Record *)m_records->rva001EB3A6(m_count);
		if (record)
			((Rva001EB298 *)TheGameState)->rva001EB298(Rva001EB2CCGetMapPath(record->m_name.str()));
	}
}

// --- 0x0020461E (104B): the profiling report stub: zero times and the
// "Script Engine Profiling disabled." message (Zero Hour's
// ScriptEngine::getStats shape; the owner is not proven here).
class Rva0020461E
{
public:
	virtual AsciiString getStats(float *curTime, float *curFrameTime, float *totalTime);
};

AsciiString Rva0020461E::getStats(float *curTime, float *curFrameTime, float *totalTime)
{
	*curTime = 0.0f;
	*curFrameTime = 0.0f;
	*totalTime = 0.0f;
	AsciiString msg("Script Engine Profiling disabled.");
	return msg;
}
