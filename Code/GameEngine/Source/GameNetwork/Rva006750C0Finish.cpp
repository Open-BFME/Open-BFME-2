// cl: /O2 /GX- /GS
// ?handle@Rva008091C0Owner@@QAEXPAVBfmeC994@@HPAD@Z @ 0x006750C0 361B via Fesl handler leaf
// Evidence: callers Rva0080A280FeslHandler Rva0080A3C0FeslDispatcher, pins d_008091c0 handle
//
// Recovered from the banked 0.995 attempt.  Two layout facts were corrected
// against retail bytes: the entry stride is 8 (`lea eax,[eax+ebx*8]`, so
// m_name at +0 with a 4-byte tail pad) and FeslState::m_array sits at +0x2A8
// (the attempt carried a stray int at +0x2A8 that pushed the count to +0x2AC
// and the owner to +0x2DC; retail loads owner from +0x2D8).
// The closing lever is register allocation only: passing owner->slot04(n)
// inline as the bfmeGoCIC argument, with no `void *v` temporary, leaves the
// loop induction variable in EBX and the array base in EDI so the allocator
// saves EBX and spills the base exactly as retail does.
#include <string.h>

extern "C" int sprintf(char *buffer, const char *format, ...);

extern char g_00C63E7C[];
extern char g_00CE3648[];
extern char g_00CE3664[];
extern char g_00CE3618[];

class Rva007E86B0Base
{
public:
	Rva007E86B0Base();
	virtual ~Rva007E86B0Base();
	int m_field04;
};

class BfmeC994 : public Rva007E86B0Base
{
public:
	BfmeC994(char *buffer, int capacity);
	int m_field08;
	int m_field0c;
	char m_pad10[0x0c];
	int m_category;
	int m_field20;
	char m_pad24[0x0c];
	char m_tail30;
};

class BfmeThingCIB
{
public:
	void bfmeGoCIB(void *one, void *two);
};

class BfmeThingCIC
{
public:
	void bfmeGoCIC(void *one, void *two);
};

class Rva00657650LeaGetter
{
public:
	void *get() const;
};

class Rva00802040Owner
{
public:
	virtual ~Rva00802040Owner() {}
	virtual void *slot04(char *name);
	void rva00801ae0(int *outMatches, int *outOther);
};

struct FeslEntry
{
	char *m_name;
	char m_pad04[4];
};

struct FeslArray
{
	FeslEntry *m_ptr;
	int m_count;
	__forceinline FeslEntry *at(int index)
	{
		if (index >= m_count)
			return 0;
		return m_ptr + index;
	}
};

struct FeslState
{
	char m_pad00[0x0c];
	Rva00657650LeaGetter *m_getter;
	char m_pad10[0x18];
	void *m_28;
	void *m_2c;
	char m_pad30[0x278];
	FeslArray m_array;
	char m_pad2b0[0x28];
	Rva00802040Owner *m_owner;
};

class Rva008091C0Owner
{
public:
	void handle(BfmeC994 *message, int gid, char *name);
	char m_pad00[8];
	FeslState *m_state;
	char m_pad0c[0x4c];
	char *m_field58;
	char m_pad5c[0x118];
	int m_174;
};

void Rva008091C0Owner::handle(BfmeC994 *message, int gid, char *name)
{
	Rva00802040Owner *owner = m_state->m_owner;
	reinterpret_cast<BfmeThingCIB *>(message)->bfmeGoCIB("LID", (void *)-2);
	reinterpret_cast<BfmeThingCIB *>(message)->bfmeGoCIB("GID", (void *)gid);
	void *got = m_state->m_getter->get();
	reinterpret_cast<BfmeThingCIC *>(message)->bfmeGoCIC(g_00C63E7C, got);
	reinterpret_cast<BfmeThingCIC *>(message)->bfmeGoCIC(g_00CE3648, m_field58 + 0x0c);
	reinterpret_cast<BfmeThingCIB *>(message)->bfmeGoCIB("MP", *(void **)(m_field58 + 4));
	reinterpret_cast<BfmeThingCIC *>(message)->bfmeGoCIC(g_00CE3664, name);
	void *sel = m_state->m_2c != 0 ? m_state->m_2c : m_state->m_28;
	reinterpret_cast<BfmeThingCIB *>(message)->bfmeGoCIB(g_00CE3618, sel);
	reinterpret_cast<BfmeThingCIC *>(message)->bfmeGoCIC("HN", &m_174);
	int matches;
	int other;
	owner->rva00801ae0(&matches, &other);
	reinterpret_cast<BfmeThingCIB *>(message)->bfmeGoCIB("AP", (void *)matches);
	reinterpret_cast<BfmeThingCIB *>(message)->bfmeGoCIB("JP", (void *)other);
	FeslArray *arr = &m_state->m_array;
	int count = arr->m_count;
	for (int i = 0; i < count; ++i)
	{
		char *n = arr->at(i)->m_name;
		char buf[0x40];
		sprintf(buf, "B-%.60s", n);
		reinterpret_cast<BfmeThingCIC *>(message)->bfmeGoCIC(buf, owner->slot04(n));
	}
}
