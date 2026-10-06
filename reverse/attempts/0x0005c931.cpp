// ?rva0005C931@MilesAudioManager@@QAEXPAXPAURva0005C931Pos@@@Z
// partial score=0.9896 date=2026-10-06
// ?rva0005C931@MilesAudioManager@@QAEXPAXPAURva0005C931Pos@@@Z
// partial score=0.95 date=2026-10-06
// cl: /O1 /Oy- /Oi- /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /arch:SSE2
// ?rva0005C931@MilesAudioManager@@QAEXPAXPAX@Z @0x0005C931 210B.
// 3D-sample filter voice setup: pinned rva00052662 yields the HSAMPLE saved
// for both AIL calls, the event pointer is kept as &pa->m_event (mov+add,
// re-deref'd after each call), the 5BA08 info layouts drive the rowed
// rva000581FA notify (begin/end via ebx scratch, this in edi so no spill),
// then a flag-plus-float select (pinned float-returning rva0002DA153 versus
// settings +0xB8, info +0x98 versus int-converted settings +0x74, scaled by
// literal 2.0f) feeds AIL_set_3D_sample_distances, AIL_set_3D_position takes
// pos with negated z, and pinned rva0005BB52 tail-calls with (ref, pos).
// Address-derived name; identities unproven.
typedef float Real;
typedef void *HSAMPLE;

extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_sample_distances(
	HSAMPLE sample, Real a, Real b);
extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_position(
	HSAMPLE sample, Real x, Real y, Real z);

struct Rva0005BA08List
{
	void *m_begin;
	void *m_end;
	bool empty() const { return m_begin == m_end; }
};

struct Rva0005C931AudioInfo
{
	char m_pad00[0x48];
	unsigned char m_flags48;
	char m_pad49[0x94 - 0x49];
	Real m_dist94;
	Real m_vol98;
	char m_pad9C[0xB8 - 0x9C];
	Rva0005BA08List m_list;
};

struct Rva0005BA08InfoRef
{
	Rva0005C931AudioInfo *m_info;
};

struct Rva0005C931Event
{
	char m_pad00[8];
	Rva0005BA08InfoRef m_info;
	char m_pad0C[0x30 - 0x0c];
	int m_value30;
};

struct Rva0005C931PlayingAudio
{
	char m_pad00[0x1c];
	Rva0005C931Event *m_event;
};

struct Rva0005C931Settings
{
	char m_pad00[0x74];
	int m_int74;
	char m_pad78[0xB8 - 0x78];
	Real m_fltB8;
};

struct Rva0005C931Pos
{
	Real m_x;
	Real m_y;
	Real m_z;
};

float rva0002DA153();

class MilesAudioManager
{
public:
	void rva0005C931(void *ref, Rva0005C931Pos *pos);
	HSAMPLE rva00052662(void *ref);
	void rva000581FA(const Rva0005BA08InfoRef &info, int value);
	void rva0005BB52(void *a, Rva0005C931Pos *b);
private:
	char m_pad00[0x10];
	Rva0005C931Settings *volatile m_settings10;
};

void MilesAudioManager::rva0005C931(void *ref, Rva0005C931Pos *pos)
{
	HSAMPLE sample = rva00052662(ref);
	Rva0005C931Event **pev = &((Rva0005C931PlayingAudio *)*(void **)ref)->m_event;
	Rva0005C931Event *event = *pev;
	Rva0005BA08InfoRef *inforef = &event->m_info;
	Rva0005BA08List *lst = &inforef->m_info->m_list;
	if (!lst->empty())
		rva000581FA(*inforef, event->m_value30);
	event = *pev;
	Rva0005C931Event *ev2 = *pev;
	Rva0005C931AudioInfo *info2 = ev2->m_info.m_info;
	Real f;
	if ((info2->m_flags48 & 8) == 0 && !(rva0002DA153() > m_settings10->m_fltB8))
		f = (*pev)->m_info.m_info->m_vol98;
	else
		f = (Real)m_settings10->m_int74;
	f *= 2.0f;
	AIL_set_3D_sample_distances(sample, (*pev)->m_info.m_info->m_dist94, f);
	AIL_set_3D_position(sample, pos->m_x, pos->m_y, -pos->m_z);
	rva0005BB52(ref, pos);
}
