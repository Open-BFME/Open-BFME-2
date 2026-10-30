// cl: /MD
//
// ?setupAllDuckingTargets@LargeGroupAudioSoundKeyPair@@QAEXXZ @0x0056956D 133B.
// Per-element resolve-and-arm: for each [m_begin,m_end) element stride 0x14,
// if its +0xC is null and the measured lookup call view (rowed 0x005686F5,
// free __stdcall body ignores ecx) finds a Rva00569543 record, dedup-push
// this (as ModuleData) via rowed 0x00569543, store the record at +0xC and
// clear +0x10. If +0x10 is clear, +0xC non-null, and both the record and this
// pass rowed LargeGroupAudioSoundKeyPair::rva00568920, fan the record plus the +0x8 float out
// the +0x2C slots via the verified HostClass005C815B::method_005C836F(int,float) at 0x005C836F and set +0x10.
// The resolve guard is goto-spelled: a null key jumps forward to the arm
// guard while a null lookup result jumps forward to the latch, an
// irreducible two-target flow no &&-chain reproduces (both its falses join).
// Native calls at 0x005695D6 and 0x0056897C target the same 44-byte
// vector worker; preserve the key word and float argument order. The
// pointer-valued record key is explicitly passed as its original 32-bit word.
// Honest address-derived names.
class ModuleData;

class Rva00569543
{
public:
	void rva00569543(const ModuleData *m);
};

class LargeGroupAudioSoundKeyPair;

class HostClass005C815B
{
public:
	void method_005C836F(int key, float value);
	void method_005C839B(int,int);
	void method_005C834A(int a, int b) throw();
	void method_005C815B();
};

struct Rva0056956DElem
{
	char m_pad[8];	// +0x0/+0x4 strings, unused here
	float m_f08;	// +0x8
	void *m_key;	// +0xC
	unsigned char m_active; // +0x10
	char m_pad2[3];
};

class LargeGroupAudioSoundKeyPair
{
public:
	bool rva00568920() const;	// 0x00568920
	void setupAllDuckingTargets();
private:
	char m_pad[0x14];
	Rva0056956DElem *m_begin;	// +0x14
	Rva0056956DElem *m_end;	// +0x18
	char m_pad2[0x10];
	HostClass005C815B *m_slots[4];	// +0x2C
};

// The rowed lookup reads only the two string words at element +0/+4, passes
// no receiver to its callees, and returns with RET 4. Retain the native ECX
// setup while binding its actual free-function name and element-prefix type.
struct Rva005686F5Elem;
void *__stdcall rva005686F5(const Rva005686F5Elem *);
union Rva0056956DLookupCall
{
 void *(__stdcall *target)(const Rva005686F5Elem *);
 void *(LargeGroupAudioSoundKeyPair::*member)(const Rva005686F5Elem *);
};
typedef char Rva0056956DLookupCallWidth[sizeof(Rva0056956DLookupCall)==4 ? 1 : -1];

void LargeGroupAudioSoundKeyPair::setupAllDuckingTargets()
{
	Rva0056956DLookupCall lookup;
	lookup.target = rva005686F5;
	for (Rva0056956DElem *e = m_begin; e != m_end; ++e) {
		if (e->m_key != 0)
			goto check_active;
		Rva00569543 *found = (Rva00569543 *)(this->*lookup.member)(reinterpret_cast<const Rva005686F5Elem *>(e));
		if (found == 0)
			goto next_elem;
		found->rva00569543((const ModuleData *)this);
		e->m_key = found;
		e->m_active = 0;
	check_active:
		if (e->m_active == 0 && e->m_key != 0
			&& ((const LargeGroupAudioSoundKeyPair *)e->m_key)->rva00568920()
			&& rva00568920()) {
			HostClass005C815B **slot = m_slots;
			int left = 4;
			do {
				if (*slot != 0)
					(*slot)->method_005C836F(reinterpret_cast<int>(e->m_key), e->m_f08);
				++slot;
			} while (--left != 0);
			e->m_active = 1;
		}
	next_elem:;
	}
}
