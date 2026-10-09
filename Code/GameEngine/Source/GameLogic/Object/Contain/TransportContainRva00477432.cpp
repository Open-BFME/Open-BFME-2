// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva00477432@Rva00477432@@QAEXPAVObject@@H@Z, retail 0x00477432..0x0047748E
// (92 bytes, RET 8): slot 58 of TransportContain's contain-interface vtable
// (the B8 base), the transport twin of the rowed garrison handler 0x00479DCD.
// The outer contain starts 0x20 bytes before this interface. An object the
// +0xFD record knows (rowed 0x00588B8A) goes through the outer 0x004770DE
// and its entry is told through slots 74 and 4 (with 1); otherwise an object
// with status 0x26 goes to 0x00477365, any other to 0x004770DE (both recovered
// below). WorldBuilder's twin (0x0119FCF0) is unnamed.

enum ObjectStatusTypes
{
	OBJECT_STATUS_26 = 0x26
};

enum WeaponSetType { WEAPONSET_NONE = 0 };
class Drawable;

class Object
{
public:
	bool testStatus(ObjectStatusTypes status) const;
	void clearWeaponSetFlag(WeaponSetType wst);
	void rva0028AE6D();
	void rva0028DCC4();
	Drawable *getDrawable() const;
};

class Rva0047A040Base9E0
{
public:
	void *rva00588B8A(void *key);
	void rva00588E20(Object *object);
};

class Rva00477432Outer
{
public:
	void rva004770DE(Object *obj);
	void rva00477365(Object *obj);
};

class Rva00477432Entry
{
public:
#define V(n) virtual void pad##n();
	V(0)
#undef V
	virtual void slot1(); virtual void slot2(); virtual void slot3();
	virtual void slot4(int value);
#define V(n) virtual void pad##n();
	V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
	V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
	V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69)
	V(70) V(71) V(72) V(73)
#undef V
	virtual void slot74();
};

class Rva00477432
{
public:
	void rva00477432(Object *obj, int unused);
private:
	Rva00477432Outer *outer() { return reinterpret_cast<Rva00477432Outer *>(reinterpret_cast<char *>(this) - 0x20); }

	unsigned char m_pad00[0xFD];
	Rva0047A040Base9E0 m_recordFD;			// +0xFD
};

void Rva00477432::rva00477432(Object *obj, int /*unused*/)
{
	Rva00477432Entry *entry = static_cast<Rva00477432Entry *>(m_recordFD.rva00588B8A(obj));
	if (entry)
	{
		outer()->rva004770DE(obj);
		entry->slot74();
		entry->slot4(1);
	}
	else if (obj->testStatus(OBJECT_STATUS_26))
		outer()->rva00477365(obj);
	else
		outer()->rva004770DE(obj);
}

// WB119F950 and119FC10 correspond to complete native477365..4773D6 RET4
// and4770DE..47710B RET4. These are primary-object helpers called by the
// interface member above, not separately named virtual overrides. Preserve
// its existing address-derived owners and the +20/+11D subobjects.
// The parent removal at467AB8..467D8E is726B RET4, WB1159EA0 names
// TransportContain::onRemoving. Its consumed interface receiver stays neutral
// until the parent's class declaration is reconciled. No local vtable emits.
class Rva00463509
{
public:
    void rva00463509(Object *object, bool flag);
};

class Rva00467AB8
{
public:
    void rva00467AB8(Object *object);
};

class Rva00270260
{
public:
    bool rva00270260();
};

class Rva002716Holder
{
public:
    void rva00271601(unsigned char hidden);
};

struct TransportRemovalObjectFlags
{
    char m_unrecovered000[0x10C];
    unsigned m_conditions[19];
    char m_unrecovered158[0x2FC];
    bool m_flag454;
};

void Rva00477432Outer::rva00477365(Object *object)
{
    Rva00463509 *base = reinterpret_cast<Rva00463509 *>(
        reinterpret_cast<char *>(this) + 0x20);
    base->rva00463509(object, false);
    reinterpret_cast<Rva00467AB8 *>(base)->rva00467AB8(object);
    object->clearWeaponSetFlag((WeaponSetType)20);

    TransportRemovalObjectFlags *flags = reinterpret_cast<TransportRemovalObjectFlags *>(object);
    if (reinterpret_cast<const unsigned char *>(flags->m_conditions)[30] & 4)
    {
        flags->m_conditions[7] &= ~(1U << 18);
        object->rva0028AE6D();
    }
    if (!flags->m_flag454)
        object->rva0028DCC4();

    Drawable *drawable = object->getDrawable();
    if (drawable && reinterpret_cast<Rva00270260 *>(drawable)->rva00270260() == true)
        reinterpret_cast<Rva002716Holder *>(drawable)->rva00271601(0);
}

void Rva00477432Outer::rva004770DE(Object *object)
{
    reinterpret_cast<Rva00463509 *>(reinterpret_cast<char *>(this) + 0x20)
        ->rva00463509(object, false);
    object->clearWeaponSetFlag((WeaponSetType)20);
    reinterpret_cast<Rva0047A040Base9E0 *>(reinterpret_cast<char *>(this) + 0x11D)
        ->rva00588E20(object);
}
