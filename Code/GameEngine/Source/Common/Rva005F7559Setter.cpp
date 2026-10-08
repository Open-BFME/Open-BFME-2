// cl: /MD /EHsc
// ?rva005F7559@Rva005F6AB0@@QAEXH@Z retail 0x005F7559 85 bytes.
// Evidence: vslot 9 offset 0x24 of vtable 0x00879828 class Rva005F6AB0; cached index at +0x14 vs array at 0x00C78D64; owner at +0x1c with level at +4 and team at +8 with name at +8 plus empty fallback g_Rva0107301CEmptyString 0x007BAC1C; rowed Rva005252CDInvoke 0x005252CD with SetQueuedIconSlotState plus TheRva00222A8BTarget 0x009FE4CC; int at +0x20.
class Rva00222A8BTarget
{
public:
	int rva00222B19(void *level, const char *prefix, const char *name, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);
};

extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
extern const char *g_00C78D64[];

int __cdecl Rva005252CDInvoke(Rva00222A8BTarget *target, void *level, const char *prefix, const char *name, const int &a, const char *const &b);

struct Rva005F7559Team
{
	char m_pad00[8];
	char m_name[1];
};

struct Rva005F7559Owner
{
	char m_pad00[4];
	void *m_level04;
	Rva005F7559Team *m_team08;
};

class Rva005F6AB0
{
public:
	void rva005F7559(int index);
private:
	char m_pad00[0x14];
	int m_14;
	char m_pad18[4];
	Rva005F7559Owner *m_owner1C;
	int m_20;
};

void Rva005F6AB0::rva005F7559(int index)
{
	if (index == m_14)
		return;
	const char *icon = g_00C78D64[index];
	Rva005F7559Owner *owner = m_owner1C;
	const char *prefix = owner->m_team08 ? owner->m_team08->m_name : "";
	Rva005252CDInvoke((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), owner->m_level04, prefix, "SetQueuedIconSlotState", m_20, icon);
	m_14 = index;
}
