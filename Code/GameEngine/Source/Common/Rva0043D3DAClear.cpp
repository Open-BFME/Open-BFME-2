// cl: /O1 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
// ?rva0043D3DA@Rva0043D3DA@@QAEXH@Z @0x0043D3DA 68B
// Conditional clear of +0x288 sub-object and +0x27C void-ptr vector.
// Evidence: caller @0x0043D452; callee rowed ?rva0043D3A8@Rva0043D3A8@@QAEXXZ
// @0x0043D3A8 via outer+0x288 and rowed void-ptr erase @0x0031BD55 via
// outer+0x27C; globals 0x009FE78C+0x110 and 0x009FEDF0+0x16 gate the clear.
#include <vector>

enum ScienceType
{
	SCIENCE_INVALID = 0
};

class Rva0043D3A8
{
public:
	void rva0043D3A8();
	void rva0043D5CB(ScienceType science);

private:
	char m_unk0[8];
	_STL::vector<ScienceType> m_sciences;
	int m_unk14;
};

class ScienceStore
{
public:
	int getSciencePurchaseCost(ScienceType science) const;
};

extern ScienceStore *TheScienceStore;

extern int g_Va009FE78C;
extern int g_Va009FEDF0;

class Rva0043D3DA
{
public:
	void rva0043D3DA(int unused);

private:
	char m_pad0[0x27c];
	_STL::vector<void *> m_ptrs;
	Rva0043D3A8 m_sub;
	char m_pad1[2];
	bool m_flag;
};

void Rva0043D3DA::rva0043D3DA(int unused)
{
	(void)unused;
	if (*(int *)(g_Va009FE78C + 0x110) == 6) {
		if (*(unsigned char *)(g_Va009FEDF0 + 0x16) == 0)
			return;
	}
	if (m_flag)
		return;
	m_sub.rva0043D3A8();
	_STL::vector<void *> &slot = m_ptrs;
	slot.erase(slot.begin(), slot.end());
}
// ?rva0043D5CB@Rva0043D3A8@@QAEXW4ScienceType@@@Z @0x0043D5CB 42B
// Evidence: unlock lane, TheScienceStore getSciencePurchaseCost 0x001FF3DC, vector<ScienceType> push_back 0x002E01C6 at +8, add cost to +0x14, caller 0x0043D67A.
void Rva0043D3A8::rva0043D5CB(ScienceType science)
{
	int cost = TheScienceStore->getSciencePurchaseCost(science);
	m_sciences.push_back(science);
	m_unk14 += cost;
}
// ?g_Va009FEDF0@@3HA: the global at VA 0xdfedf0 is ?TheInGameUI@@3PAVInGameUI@@A.
#pragma comment(linker, "/alternatename:?g_Va009FEDF0@@3HA=?TheInGameUI@@3PAVInGameUI@@A")
// ?g_Va009FE78C@@3HA: the global at VA 0xdfe78c is ?TheGameLogic@@3PAVGameLogic@@A.
#pragma comment(linker, "/alternatename:?g_Va009FE78C@@3HA=?TheGameLogic@@3PAVGameLogic@@A")
