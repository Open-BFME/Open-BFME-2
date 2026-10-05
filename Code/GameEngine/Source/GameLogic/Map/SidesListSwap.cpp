// cl: /O1
// stlport
// ?swap@SidesList@@QAEXPAV1@@Z @0x0032B690 279B unlock caller 0x0032F449
// Evidence: prev/next swap TUs name SidesList swap; retail swaps counts SidesInfo arrays teamrecs extra vectors cleared byte then notifier posts both ways via rowed swaps and pin ??_9@$BBI@AE.
#include <algorithm>
#include <vector>

struct BfmeE12
{
	float x;
	float y;
	float z;
};

class SidesInfo
{
public:
	void swap(SidesInfo *other);

private:
	char m_body[0x60];
};

class TeamsInfoRec
{
public:
	void swap(TeamsInfoRec *other);

private:
	char m_body[0x1C];
};

class SidesListNotifier
{
public:
	void post(void (*callback)(), void *owner, int index);
};

void Rva005CB274();

// Retail pushes the vcall thunk at 0x005CB274 (rowed ??_9@$BBI@AE, slot +0x18).
// Bind the honest free-function spelling callers use to that row so the push links.
#pragma comment(linker, "/alternatename:?Rva005CB274@@YAXXZ=??_9@$BBI@AE")

struct SidesListExtra
{
	int m_x;
	std::vector<BfmeE12> m_v1;
	std::vector<BfmeE12> m_v2;
};

class SidesList
{
public:
	void swap(SidesList *other);

private:
	char m_head[0x10];
	SidesListNotifier m_notifier;          // +0x10
	char m_pad[0x3C - 0x11];
	int m_numSides;                        // +0x3C
	SidesInfo m_sides[20];                 // +0x40
	int m_numSkirmishSides;                // +0x7C0
	SidesInfo m_skirmishSides[20];         // +0x7C4
	TeamsInfoRec m_teamrec;                // +0xF44
	TeamsInfoRec m_skirmishTeamrec;        // +0xF60
	bool m_cleared;                        // +0xF7C
	char m_pad2[0xF80 - 0xF7D];
	SidesListExtra m_extra[20];            // +0xF80
};

void SidesList::swap(SidesList *other)
{
	int i;
	std::swap(m_numSides, other->m_numSides);
	for (i = 0; i < 20; i++)
		m_sides[i].swap(&other->m_sides[i]);
	std::swap(m_numSkirmishSides, other->m_numSkirmishSides);
	for (i = 0; i < 20; i++)
		m_skirmishSides[i].swap(&other->m_skirmishSides[i]);
	m_teamrec.swap(&other->m_teamrec);
	m_skirmishTeamrec.swap(&other->m_skirmishTeamrec);
	for (i = 0; i < 20; i++) {
		std::swap(m_extra[i].m_x, other->m_extra[i].m_x);
		m_extra[i].m_v1.swap(other->m_extra[i].m_v1);
		m_extra[i].m_v2.swap(other->m_extra[i].m_v2);
	}
	std::swap(m_cleared, other->m_cleared);
	m_notifier.post(Rva005CB274, this, (int)other);
	other->m_notifier.post(Rva005CB274, other, (int)this);
}
