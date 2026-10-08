// ?SetTabCount@BattlePromptPlayerTabsMovieClip@StrategicHUD@@QAEXI@Z
// partial score=0.92 date=2026-10-08
// ?rva005FEA02@Rva005FE750@@QAEXI@Z
// partial score=0.92 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /G7 /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??1Rva005FE750@@UAE@XZ @0x005FE750 87B via vtable plus StringBase plus Rva members plus wide vector
// Evidence: prev 0x005FE589 and next 0x005FE835 same vector family same flags; callees rowed vector 0x005FE4A3 Rva 0x005242D7 Rva 0x0052413E releaseBuffer 0x00036410; vtable 0x0087A3F4.

#include <vector>

#include "ascii_string.h"
#include "unicode_string.h"

struct BfmeContainerRecord005FDEC7
{
	unsigned int word0;
	unsigned int word1;
	UnicodeString text;
};

namespace _STL { template<> void vector<BfmeContainerRecord005FDEC7>::reserve(unsigned int); }

class Rva0052413E
{
public:
	~Rva0052413E();
private:
	char m_pad[12];
};

class Rva005242D7
{
public:
	~Rva005242D7();
private:
	char m_pad[12];
};

class Image;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

int __cdecl Rva0052519DFire(void *a1, void *a2, const char *a3, const char *a4, int *a5);

__forceinline const char *GetStr005FEA02(const AsciiString &s)
{
	char *t = *(char **)(void *)&s;
	return t ? t + 8 : "";
}

class Rva005FE974Vector
{
public:
	void rva005FE9E0(unsigned count);
};

namespace StrategicHUD { class BattlePromptPlayerTabsMovieClip; }
class StrategicHUD::BattlePromptPlayerTabsMovieClip
{
public:
	virtual ~BattlePromptPlayerTabsMovieClip();
	void SetTabCount(unsigned newCount);
private:
	int m_04;
	AsciiString m_08;
	Rva0052413E m_0C;
	Rva005242D7 m_18;
	int m_24;
	_STL::vector<BfmeContainerRecord005FDEC7, _STL::allocator<BfmeContainerRecord005FDEC7> > m_28;
};


// ?rva005FEA02@Rva005FE750@@QAEXI@Z present-unmatched
void StrategicHUD::BattlePromptPlayerTabsMovieClip::SetTabCount(unsigned newCount)
{
	if (newCount == m_28.size())
		return;
	m_28.reserve(newCount);
	const char *mid = GetStr005FEA02(this->m_08);
	Rva0052519DFire(g_bfmeAptWindowManager, (void *)this->m_04, mid, "SetTabCount", (int *)&newCount);
	((Rva005FE974Vector *)&m_28)->rva005FE9E0(newCount);
}
