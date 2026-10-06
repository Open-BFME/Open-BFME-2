// cl: /DNDEBUG /MD
// ?rva004B5783@WeaponSetUpgradeSecondary@@QAEXXZ retail 0x004B5783 39B
// Slot 20 of vtable 0x00857F68 class Rva004B55C8; Object mask clear via data+0x118 then UpgradeModule remove then vslot 9 with 0.
// Evidence: vtable 0x00857F68 slot 20 plus sibling 0x004B5765 pattern plus rowed 0x00290AC1 0x004CE4A8 plus prev 0x004B5765 next 0x004B57AA.
class Rva0028C570;
class ModuleData;
class Object
{
public:
	void rva00290AC1(const Rva0028C570 &other);
};
class UpgradeModule
{
public:
	void rva004CE4A8();
};
class WeaponSetUpgradeSecondary
{
public:
	void rva004B5783();
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09(int x);
};

void WeaponSetUpgradeSecondary::rva004B5783()
{
	const ModuleData *data = *(const ModuleData * const *)((const char *)this - 0xC);
	Object *obj = *(Object * const *)((const char *)this - 0x8);
	const Rva0028C570 *bits = (const Rva0028C570 *)((const char *)data + 0x118);
	obj->rva00290AC1(*bits);
	((UpgradeModule *)((char *)this - 0x10))->rva004CE4A8();
	v09(0);
}
