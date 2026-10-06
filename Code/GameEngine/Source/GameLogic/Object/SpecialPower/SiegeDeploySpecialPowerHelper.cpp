// cl: /DNDEBUG /MD /EHsc
// ?rva004C573C@SiegeDeploySpecialPower@@QAEXXZ @0x004C573C 21B: SiegeDeploy helper that fetches the DynamicPortalBehaviour module for m_object via the rowed 0x004608E0 finder and tail-calls the pinned ?bfmeCallEBC@BfmeOwnerEBC@@QAEXXZ on the result when non-null. push [ecx+8] proves BehaviorModule m_object at +8. Callers at 0x004C57F8 0x004C5C4C 0x004C5E99 all SiegeDeploy bodies. Recipe ObjectFindModule plus WallUpgrade static prelude.

class Module
{
};

class Object
{
};

class BfmeOwnerEBC
{
public:
	void bfmeCallEBC();
};

class DynamicPortalBehaviour
{
public:
	static Module *rva004608E0(Object *obj);
};

class BehaviorModule
{
public:
	virtual void anchor();
	unsigned int m_04;
	Object *m_object;
};

class SiegeDeploySpecialPower : public BehaviorModule
{
public:
	void rva004C573C();
};

void SiegeDeploySpecialPower::rva004C573C()
{
	Module *found = DynamicPortalBehaviour::rva004608E0(m_object);
	if (found)
	{
		((BfmeOwnerEBC *)found)->bfmeCallEBC();
	}
}
