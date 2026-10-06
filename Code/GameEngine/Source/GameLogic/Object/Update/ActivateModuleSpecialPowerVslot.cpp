// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva004CDEED@ActivateModuleSpecialPower@@UAEXXZ, retail 0x004CDEED, 19 bytes.
// Vslot 17 offset 0x44 of vtable 0x0085FC88 owned by ??0ActivateModuleSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z.
// Calls SpecialAbilityUpdate slot-17 body at 0x0045108D then same-class int method at 0x004CDDBA with 0.
class SpecialAbilityUpdate
{
public:
	virtual void rva0045108D();
};

class Rva004CDF00 : public SpecialAbilityUpdate
{
public:
	void rva004CDDBA(int a);
};

class ActivateModuleSpecialPower : public Rva004CDF00
{
public:
	virtual void rva004CDEED();
};

void ActivateModuleSpecialPower::rva004CDEED()
{
	SpecialAbilityUpdate::rva0045108D();
	Rva004CDF00::rva004CDDBA(0);
}
