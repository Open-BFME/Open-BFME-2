// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?rva005F2792@Rva005F2792@@QAEXXZ, retail 0x005F2792, 102 bytes.
// Key builder: formats "_level%u.%s_OnUnitIconSlotLoaded%d" from m_info->m_level,
// team name at m_info->m_holder+8 (else g_Rva0107301CEmptyString) and m_slot,
// then erases via rowed 0x00224455 through TheRva00222A8BTarget.
// Evidence: chain via 0x00224455; callers 0x005F27F8 0x005F2B22; format row
// 0x00038150; releaseBuffer row 0x00036410; precedent Rva005FF450Apt.
#include "ascii_string.h"


class Rva00224455
{
public:
	int rva00224455(const AsciiString *key);
};

class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;

struct Rva005F2792Name
{
	char m_pad[8];
	char m_name[1];
};

struct Rva005F2792Info
{
	char m_pad[8];
	unsigned int m_level;
	Rva005F2792Name *m_holder;
};

const char *__cdecl Rva00412845AfterLevel(const char *);
int __cdecl Rva004128BBGetLevel(const char *);
class Object;
class Rva00575674 { public: void rva00575674(Object *); };
class Rva005C31FB {
public:
    virtual ~Rva005C31FB();
    Rva005C31FB(int level, const AsciiString &name);
private:
    int m_level;
    AsciiString m_name;
    bool m_flag0C;
};
class Rva005F2792
{
public:
	void rva005F2792();
	void rva005F27F8(const char *path);
private:
	char m_pad[8];
	Rva005F2792Info *m_info;
	int m_slot;
	char m_pad10[0x10];
	Rva005C31FB *m_panel20;
};

void Rva005F2792::rva005F2792()
{
	AsciiString key;
	const char *mid = m_info->m_holder ? m_info->m_holder->m_name : "";
	key.format("_level%u.%s_OnUnitIconSlotLoaded%d", m_info->m_level, mid, m_slot);
	((Rva00224455 *)TheRva00222A8BTarget)->rva00224455(&key);
}

// Native 0x005F27F8..0x005F2897, RET4. The proven callback family supplies
// the temporary-string lifetime; the target uses its +0x20 owner, the rowed
// 16-byte panel constructor, then this unit's key-removal callback.
void Rva005F2792::rva005F27F8(const char *path)
{
    if (m_panel20 == 0) {
        ((Rva00575674 *)&m_panel20)->rva00575674((Object *)new Rva005C31FB(
            Rva004128BBGetLevel(path), AsciiString(Rva00412845AfterLevel(path))));
        rva005F2792();
    }
}
