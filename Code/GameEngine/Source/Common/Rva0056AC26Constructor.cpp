// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /MD /EHsc
//
// ??1Rva0056AC26@@UAE@XZ, retail 0x0056AC26 (84B): destructor of the opaque
// base several BFME 2 registry entries derive from (Rva0056AC26Derived.cpp,
// Rva0056B218Dtor.cpp, ...). Layout from this body: two polymorphic bases,
// the first (vftable 0x00BC6F20) with a word at +4 and the second (vftable
// 0x00C37298) at +8, a UnicodeString at +0xC and the owning registry at
// +0x10. Retail stores this class's vftables (0x00C6D058 / 0x00C6D01C), asks
// the owner to forget it (0x003F88A7, pinned), releases the string, and the
// inline base destructors restore their vftables. Names stay address-derived.

#include "unicode_string.h"

class Rva0056AC26;

class Rva0056AC26Owner
{
public:
	UnicodeString rva003F855D();
 void rva003F88A7(Rva0056AC26 *entry);
};

class Rva0056AC26Base1
{
public:
	// ?Rva0056AC26Base1::Rva0056AC26Base1 present-unmatched
 Rva0056AC26Base1():m_04(0){}
 virtual ~Rva0056AC26Base1() {}

private:
	int m_04;
};

class Rva0056AC26Base2
{
public:
	virtual ~Rva0056AC26Base2() {}
};

class Rva0056AC26 : public Rva0056AC26Base1, public Rva0056AC26Base2
{
public:
	Rva0056AC26(Rva0056AC26Owner *owner);
 virtual ~Rva0056AC26();

private:
	UnicodeString m_text;        // +0x0C
	Rva0056AC26Owner *m_owner;   // +0x10
};


Rva0056AC26::Rva0056AC26(Rva0056AC26Owner *owner):m_text(owner->rva003F855D()),m_owner(owner){}

// Native56AD80..56ADD5 is85B (next28B is a deleting destructor).
// Existing84B destructor proves MI0/8, UnicodeStringC and owner10; native
// construction selects the same class vftables C6D058/C6D01C. Hidden getter
// 3F855D initializes the owned string directly, not an explicit raw output.
// Original registry-entry and getter names are unknown; view follows target.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva002B2702 { public: void rva002B2702(void*,void*,int); };
class Rva0056AC82:public Rva0056AC26 {
public:virtual ~Rva0056AC82();
 Rva0056AC82(Rva0056AC26Owner *,void *,void *);
};
Rva0056AC82::Rva0056AC82(Rva0056AC26Owner *owner,void *second,void *third):Rva0056AC26(owner){
 reinterpret_cast<Rva002B2702 *>(TheLivingWorldLogic)->rva002B2702(second,third,1);
}

// Native scalar destructor56AEAA (already rowed as Rva0056AC82) identifies
// constructor56AE5C via first slot C6D0A8; secondary C6D06C points its
// this-8 adjustment. Existing constructor bank named the entry address
// instead; real source now shares the already recovered destructor owner.
// TheLivingWorldLogic is independently named by the data ledger at9FEF10.
