// ?rva00477305@Rva00477305Owner@@QAEXPAVObject@@@Z
// partial score=0.93 date=2026-10-08
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Retail 0x00477305, 96 bytes, thiscall with one Object argument (ret 4).
// Gated by the sub-object at +0x11D; when the argument has weapon-set flag 0x14
// it sets that flag and the 0x40000 status bit once, then calls the virtual
// slot 0x48 on this and the interface at +0x20 with (argument, false).
// Callees are rowed or pinned; class names are address-derived.
enum WeaponSetType { WEAPONSET_RETAIL_14 = 0x14 };
class Object;

class Object
{
public:
	bool rva0029091E(unsigned int flag) const;
	void setWeaponSetFlag(WeaponSetType set);
	void rva0028AE6D();
	char m_pad[0x128];
	unsigned int m_flags128;	// +0x128
};

class Rva0047A040Base9E0
{
public:
	bool rva00588D24(void *owner, Object *obj);
};

class Rva0046781F
{
public:
	void rva0046781F(Object *obj, bool flag);
};

class Rva00477305Owner
{
public:
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
	void rva00477305(Object *src);
};

void Rva00477305Owner::rva00477305(Object *src)
{
	char *self = (char *)this;
	if (!((Rva0047A040Base9E0 *)(self + 0x11D))->rva00588D24(this, src))
		return;
	if (src->rva0029091E(0x14))
	{
		src->setWeaponSetFlag(WEAPONSET_RETAIL_14);
		if (!(src->m_flags128 & 0x40000))
		{
			src->m_flags128 |= 0x40000;
			src->rva0028AE6D();
		}
	}
	this->slot18();
	((Rva0046781F *)(self + 0x20))->rva0046781F(src, false);
}
