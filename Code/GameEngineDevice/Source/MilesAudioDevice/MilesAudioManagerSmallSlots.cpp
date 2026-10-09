// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX-
//
// Small MilesAudioManager vtable slots (vtable VA 0x00BC55B0, which also holds
// stopAudio and the rows of MilesAudioManagerRva0005168C.cpp) that had no
// ledger owner. Byte fields +0x69E..+0x6A2 are the ones that sibling's setter
// stores under the same flag bits; the getter here reads them back.
//
// The two AIL preference updates and the AIL_serve slot are the BFME2 copies
// of Open-BFME-1's Rva006962A0PreferenceProduct.cpp bodies (donor source,
// same shape; BFME2 reads +0x84/+0x88 of the +0x10 settings object where BFME1
// read +0x48/+0x4C). The object at +0xBE8 is the one whose destructor is the
// opaque pin 0x00260A3C and whose scalar deleting dtor is 0x000453F5; its
// 0x00045837 query is called here for a bool result. Method names stay
// address derived: the bytes prove the hops, offsets and argument counts only.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

extern "C" __declspec(dllimport) int __stdcall AIL_get_preference(
	unsigned int preference);
extern "C" __declspec(dllimport) void __stdcall AIL_set_preference(
	unsigned int preference, int value);
extern "C" __declspec(dllimport) void __stdcall AIL_serve(void);

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *section);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *section);

class Rva00260A3C
{
public:
	virtual ~Rva00260A3C();
	Bool test() const;
};

struct Rva000517F1Settings
{
	char m_pad00[0x84];
	UnsignedInt m_84;
	UnsignedInt m_88;
};

struct Rva0005185EBlock
{
	char m_pad00[0x38];
	Int m_38;
	Int m_3c;
	Int m_40;
};

struct Rva00053281Lock
{
	char m_pad00[0x40];
	char m_section[0x18];	// +0x40, handed to Enter/LeaveCriticalSection
	Bool m_58;
};

struct Rva000527E2Event
{
	char m_pad00[8];
	Int m_8;
};

class AudioEventRTS;

class MilesAudioManager
{
public:
	unsigned int addOrResumeAudioEvent(AudioEventRTS *a, Int b, Int c, Int d, Int e);

	void rva000514BB();
	void rva000517F1();
	void rva0005181B();
	void rva00051840();
	void rva0005185E(Int *a, Int *b, Int *c);
	unsigned char rva0005164F(unsigned char flags);
	Bool rva000527E2(const Rva000527E2Event *event);
	Bool rva000531F6();
	void rva00053281();
	void rva0005329C();
	void rva0005DABB(Int a);
	void rva0005DAE6(Int a, Int b);
private:
	char m_pad00[0x10];
	Rva000517F1Settings *m_10;
	char m_pad14[0x69e - 0x14];
	unsigned char m_69E;
	unsigned char m_69F;
	unsigned char m_6A0;
	unsigned char m_6A1;
	unsigned char m_6A2;
	char m_pad6A3[0xb8c - 0x6a3];
	Rva0005185EBlock *m_b8c;
	Rva00053281Lock *m_b90;
	char m_padB94[0xbe8 - 0xb94];
	Rva00260A3C *m_be8;
};

// vtable 0x00BC55B0#100
void MilesAudioManager::rva000514BB()
{
	Rva00260A3C *obj = m_be8;
	if (obj)
	{
		obj->Rva00260A3C::~Rva00260A3C();
		operator delete(obj);
		m_be8 = 0;
	}
}

// vtable 0x00BC55B0#56
unsigned char MilesAudioManager::rva0005164F(unsigned char flags)
{
	if (flags & 1)
		return m_6A1;
	if (flags & 2)
		return m_69F;
	if (flags & 4)
		return m_6A0;
	if (flags & 0x10)
		return m_6A2;
	return m_69E;
}

// vtable 0x00BC55B0#69
void MilesAudioManager::rva000517F1()
{
	int pref = AIL_get_preference(0x22);
	AIL_set_preference(0x2A, m_10->m_88 / pref);
	AIL_serve();
}

// vtable 0x00BC55B0#70
void MilesAudioManager::rva0005181B()
{
	int pref = AIL_get_preference(0x22);
	AIL_set_preference(0x2A, m_10->m_84 / pref);
}

// vtable 0x00BC55B0#71
void MilesAudioManager::rva00051840()
{
	AIL_serve();
}

// vtable 0x00BC55B0#82
void MilesAudioManager::rva0005185E(Int *a, Int *b, Int *c)
{
	*a = m_b8c->m_38;
	*c = m_b8c->m_40;
	*b = m_b8c->m_3c;
}

// vtable 0x00BC55B0#31
Bool MilesAudioManager::rva000527E2(const Rva000527E2Event *event)
{
	if (!event)
		return false;
	return event->m_8 != 0;
}

// vtable 0x00BC55B0#99
Bool MilesAudioManager::rva000531F6()
{
	if (m_be8 && m_be8->test())
		return true;
	return false;
}

// vtable 0x00BC55B0#101
void MilesAudioManager::rva00053281()
{
	if (m_b90 && !m_b90->m_58)
		EnterCriticalSection(m_b90->m_section);
}

// vtable 0x00BC55B0#102
void MilesAudioManager::rva0005329C()
{
	if (m_b90 && !m_b90->m_58)
		LeaveCriticalSection(m_b90->m_section);
}

// Native5D734 returns an audio handle in EAX; WB786F40 identifies addOrResumeAudioEvent.
// These vtable wrappers discard the returned handle.
// vtable 0x00BC55B0#25
void MilesAudioManager::rva0005DABB(Int a)
{
	addOrResumeAudioEvent(reinterpret_cast<AudioEventRTS *>(a), 0, 1, 0, 1);
}

// vtable 0x00BC55B0#29
void MilesAudioManager::rva0005DAE6(Int a, Int b)
{
	addOrResumeAudioEvent(reinterpret_cast<AudioEventRTS *>(a), 1, b, 0, 1);
}
