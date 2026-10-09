// cl: /O2 /G6 /arch:SSE /DNDEBUG
//
// ?rva006C1AA0@Rva006C1F60@@QAEPAUSlot64@@I@Z @ 0x006C1AA0..0x006C1B48 (168B)
// Array-slot duplicator for the lock-guarded pool (class Rva006C1F60): under
// the AddRef/Release guard on the +0x4e4 lock (rows 0x00030DD0 0x00030DF0)
// copies the template fields of slot 0 into slot `index` (stride 64 from
// +0x570) and returns &slot[index].
//
// Target facts: the fields copied are +0x570..+0x57c +0x580/+0x584 and
// +0x5a0/+0x5a4 of each slot; the +0x580/+0x584 pair is copied through one
// base ((index+22)<<6 + this) with ebx while every other field goes through
// index<<6 + this -- the shape of an 8-byte struct assignment and the only
// change from the 0.9 bank. Region flags (0x00684BB0..0x0073EE20) are /O2
// /arch:SSE /G6. Caller 0x0004826C. Field meanings are unknown; names are
// structural.
struct Rva00030DD0Lock;
int Rva00030DD0AddRef(Rva00030DD0Lock *lock);
int Rva00030DF0Release(Rva00030DD0Lock *lock);

struct Slot64Pair
{
	int a;
	int b;
};

struct Slot64
{
	int f0;
	int f1;
	int f2;
	int f3;
	Slot64Pair pair;	// +0x10 copied as one struct
	unsigned char pad18[0x30 - 0x18];
	int f12;		// +0x30
	int f13;		// +0x34
	unsigned char pad38[0x40 - 0x38];
};

class Rva006C1F60
{
public:
	Slot64 *rva006C1AA0(unsigned int index);
private:
	unsigned char m_pad0[0x4e4];
	Rva00030DD0Lock *m_lock;	// +0x4e4
	unsigned char m_pad1[0x570 - 0x4e8];
	Slot64 m_slots[16];		// +0x570
};

Slot64 *Rva006C1F60::rva006C1AA0(unsigned int index)
{
	Rva00030DD0Lock *lock = m_lock;
	if (lock != 0)
		Rva00030DD0AddRef(lock);
	if (index != 0) {
		m_slots[index].f0 = m_slots[0].f0;
		m_slots[index].f1 = m_slots[0].f1;
		m_slots[index].f2 = m_slots[0].f2;
		m_slots[index].f3 = m_slots[0].f3;
		m_slots[index].pair = m_slots[0].pair;
		m_slots[index].f12 = m_slots[0].f12;
		m_slots[index].f13 = m_slots[0].f13;
	}
	Slot64 *ret = &m_slots[index];
	if (lock != 0)
		Rva00030DF0Release(lock);
	return ret;
}
