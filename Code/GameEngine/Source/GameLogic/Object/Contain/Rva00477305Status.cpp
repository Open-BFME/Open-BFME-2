// ?rva00477305@Rva00477305Owner@@QAEXPAVObject@@@Z
// ?rva00477305@Rva00477305Owner@@QAEXPAVObject@@@Z @0x00477305 96B
// Evidence: Native477305..477365 complete RET4 and neighbours identify HordeContain family; gate receiver+11D callee588D24; status word Object+128 test/or40000 precedes28AE6D notifier. Inline bit-array methods preserve direct memory operands; layout span is target-measured; original status index name unproven. All REL32 providers already landed.
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Retail 0x00477305, 96 bytes, thiscall with one Object argument (ret 4).
// Gated by the sub-object at +0x11D; when the argument has weapon-set flag 0x14
// it sets that flag and the 0x40000 status bit once, then calls the virtual
// slot 0x48 on this and the interface at +0x20 with (argument, false).
// Callees are rowed or pinned; class names are address-derived.
enum WeaponSetType { WEAPONSET_NONE = 0 };
class Bits {public: unsigned test(unsigned n)const{return words[n>>5]&(1u<<(n&31));} void set(unsigned n){words[n>>5]|=1u<<(n&31);} unsigned words[20];};
// Object prefix view: the status bit array starts at +0x10C (bit 242 is
// the word at +0x128).
struct Rva00477305ObjectView { char m_pad[0x10C]; Bits status; };

class Object
{
public:
	bool rva0029091E(unsigned int flag) const;
	void setWeaponSetFlag(WeaponSetType set);
	void rva0028AE6D();
	__forceinline Bits &statusBits() { return ((Rva00477305ObjectView *)this)->status; }
};

struct Coord3D;
class Rva00588E44Contain;
class Rva0047A040Base9E0
{
public:
	void *rva00588B8A(void *);
	void rva00588BA8(Object *obj, bool flag);
	Object *rva00588C4E(void *contain, const struct Coord3D *obj);
	void rva00588F61(void *contain, Object *owner, enum CommandSourceType obj);
	void rva00588D99(Object *obj);
	void rva00588E20(Object *object);
	Rva00588E44Contain *rva00588BF3(void *contain, Object *obj);
	bool rva00588D24(void *owner, Object *obj);
	void rva00588E44(void *argument);
};

class Rva0046781F
{
public:
	void rva0046781F(Object *obj, bool flag);
};

class Rva00477305Owner
{
public:
	void rva00477305(Object *obj);
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
};

void Rva00477305Owner::rva00477305(Object *src)
{
	char *self = (char *)this;
	if (!((Rva0047A040Base9E0 *)(self + 0x11D))->rva00588D24(this, src))
		return;
	if (src->rva0029091E(0x14))
	{
		src->setWeaponSetFlag((WeaponSetType)0x14);
		if (!(src->statusBits().test(242)))
		{
			src->statusBits().set(242);
			src->rva0028AE6D();
		}
	}
	this->slot18();
	((Rva0046781F *)(self + 0x20))->rva0046781F(src, false);
}
