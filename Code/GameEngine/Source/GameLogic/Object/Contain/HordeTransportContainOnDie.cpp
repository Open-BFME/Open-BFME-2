// cl: /DNDEBUG /MD
//
// Target evidence: 0x00477003 installs vtable 0x00C45D2C at the
// HordeTransportContain +0x28 subobject; its first entry is 0x00477B69.
// The target reads module data through this-0x24 and the owner through
// this-0x28, then optionally calls the helper at this+0xF5. The address-only
// callee 0x0047778B is reached directly from the target's REL32 call.
//
// Identity inference: the BFME1 OpenContain hierarchy places DieModuleInterface
// after CollideModuleInterface, consistent with the target's +0x28 vtable and
// one-pointer ABI. That supports the onDie name; the +0x82 module-data flag and
// helper meaning remain unnamed target fields. Donor source is a layout/slot
// lead, not proof of BFME2 field semantics.
class DamageInfo;

class Rva00462785
{
public:
	int rva00462785();
};

class Rva00588E44
{
public:
	void rva00588E44(void *argument);
};

class Rva0047778B
{
public:
	void rva0047778B();
};

class HordeTransportContain
{
public:
	virtual void onDie(const DamageInfo *damageInfo);
};

void HordeTransportContain::onDie(const DamageInfo *damageInfo)
{
	const unsigned char *moduleData =
		*(const unsigned char **)((char *)this - 0x24);
	if (moduleData[0x82] != 0) {
		((Rva0047778B *)((char *)this - 0x28))->rva0047778B();
	} else {
		Rva00462785 *owner = (Rva00462785 *)((char *)this - 0x28);
		if ((unsigned char)owner->rva00462785() != 0)
			((Rva00588E44 *)((char *)this + 0xF5))->rva00588E44(owner);
	}
}
