// ?rva0032A587@SidesList@@QAE_NHHPAVBuildListInfo@@H@Z
// partial score=0.8974358974 date=2026-10-08
// ?rva0032A587@SidesList@@QAE_NHHPAVBuildListInfo@@H@Z
// cl: /O1 /arch:SSE /G7 /Oy- /MD
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// stlport
// ?swap@SidesList@@QAEXPAV1@@Z @0x0032B690 279B unlock caller 0x0032F449
// Evidence: prev/next swap TUs name SidesList swap; retail swaps counts SidesInfo arrays teamrecs extra vectors cleared byte then notifier posts both ways via rowed swaps and pin ??_9@$BBI@AE.
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
#include <algorithm>
#include <vector>

class BuildListInfo
{
public:
 BuildListInfo &operator=(const BuildListInfo &);
private:
 void *m_vtable;
 unsigned char m_body[0x7C];
};

struct BfmeE12
{
	float x;
	float y;
	float z;
};

class ScriptList
{
public:
	void swap(ScriptList *other);
	char m_body[0x4C];
};

class SidesInfo
{
public:
	void swap(SidesInfo *other);

private:
public:
	char m_head[8];
	ScriptList m_scripts; // +8, 0x4C-byte by-value list
	char m_tail[0x60 - 8 - 0x4C];
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
	std::vector<BuildListInfo> m_v1;
	std::vector<BuildListInfo> m_v2;
};

class SidesList
{
public:
	void swap(SidesList *other);
	bool rva0032A587(int key, int index, BuildListInfo *out, int mode);
	void rva0032B7E3(SidesList *other);

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

// Native 0x0032B7E3..0x0032B831, RET4. SidesList identity and the
// side/script offsets follow the rowed swap above and SidesInfo::swap.
// The callback is the already-rowed MSVC virtual-slot-5 thunk; the
// notifier consumes its four-byte member-pointer representation.
class Rva0032B7E3Listener
{
public:
 virtual void slot00();
 virtual void slot04();
 virtual void slot08();
 virtual void slot0C();
 virtual void slot10();
 virtual void slot14(SidesList *, SidesList *);
};

void SidesList::rva0032B7E3(SidesList *other)
{
 for (int i=0; i<m_numSides; ++i)
  m_sides[i].m_scripts.swap(&other->m_sides[i].m_scripts);
 union {
  void (Rva0032B7E3Listener::*member)(SidesList *, SidesList *);
  void (*callback)();
 } notify;
 notify.member=&Rva0032B7E3Listener::slot14;
 m_notifier.post(notify.callback,this,(int)other);
 other->m_notifier.post(notify.callback,other,(int)this);
}

bool SidesList::rva0032A587(int key, int index, BuildListInfo *out, int mode)
{
 if (mode != 0 && mode != 1) return false;
 for (int i = 0; i < 20; ++i)
 {
  if (m_extra[i].m_x != key) continue;
  std::vector<BuildListInfo> *list;
  if (mode == 0) list = &m_extra[i].m_v1;
  else if (mode == 1) list = &m_extra[i].m_v2;
  else return true;
  if (index >= (int)list->size()) return false;
  _ReadWriteBarrier();
  *out = (*list)[index];
  return true;
 }
 return false;
}
