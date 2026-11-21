// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ??0Rva0056B2DD@@QAE@PAVRva0056AC26Owner@@PAUParent0056B2DD@@H@Z, retail
// 0x0056B599..0x0056B613 (122 bytes, EH, ret 0xC). Constructor of the
// parent listener of Rva0056B2DDDtor.cpp (vtables 0x00C6D470, 0x00C6D434 at
// +8 and 0x00C6D420 at +0x14): the rowed base Rva0056AC26 gets the owner,
// the listener is registered with the list at +8 of the parent (rowed append
// 0x005A0B4C), the int is kept at +0x1C and, when TheLivingWorldManager has
// its notifier at +0x268, that is told the int (rowed 0x003EE91A). Class and
// parent names address-derived.
class Rva0056AC26Owner;
struct Rva002BA8F1Listener;

#include "../../Include/Common/Rva005A0B4CList.h"

struct Parent0056B2DD
{
	char pad[8];
	Rva005A0B4CList holder;
};

#include "../../Include/Common/Rva0056AC26.h"

#include "../../Include/Common/LivingWorldBattleListener.h"

class Rva0056B2DDB2 : public LivingWorldBattleListener
{
public:
	Rva0056B2DDB2() {}
};

#include "../../Include/Common/Rva003EE91A.h"
#include "../../Include/Common/Rva003EE966.h"
#include "../../Include/Common/Rva00318FA1MainOwner.h"

class Rva0021294A
{
public:
	char m_pad[0x268];
	Rva003EE91A *m_268;
};

class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;

class Rva0056B2DD : public Rva0056AC26, public Rva0056B2DDB2
{
public:
	Rva0056B2DD(Rva0056AC26Owner *owner, Parent0056B2DD *parent, int value);
	virtual ~Rva0056B2DD();
	// Rva0056AC26 slot 1 (retail table 0x00C6D470 slot 1): 0x0056AAF4.
	virtual bool ac26Slot1();
	// LivingWorldBattleListener at +0x14 (retail table 0x00C6D420) slot 4.
	virtual void slot4(int army);
	// Rva0056AC26Base2 at +8 (retail table 0x00C6D434) slots 1, 4 and 5.
	virtual bool slot1(Rva002B4BC9Arg *candidate);
	virtual bool slot4(LivingWorldArmy *army, Rva00318C32Ret *value);
	virtual bool slot5(int);
private:
	Parent0056B2DD *m_parent18;
	int m_x1C;
};

Rva0056B2DD::Rva0056B2DD(Rva0056AC26Owner *owner, Parent0056B2DD *parent, int value)
	: Rva0056AC26(owner), m_parent18(parent), m_x1C(value)
{
	m_parent18->holder.append((Rva002BA8F1Listener *)static_cast<Rva0056B2DDB2 *>(this));
	Rva003EE91A *notifier = ((Rva0021294A *)TheLivingWorldManager)->m_268;
	if (notifier)
		notifier->rva003EE91A(value);
}

// Slot 1 of retail table 0x00C6D470: whether the parent resolves to the int.
bool Rva0056B2DD::ac26Slot1()
{
	return ((Rva00318FA1MainOwner *)m_parent18)->rva00318FA1() == m_x1C;
}

// Slot 4 of retail table 0x00C6D420: tell the manager's notifier the int,
// through 0x003EE966 when the army resolves to it and 0x003EE91A otherwise.
void Rva0056B2DD::slot4(int army)
{
	Rva003EE91A *notifier = ((Rva0021294A *)TheLivingWorldManager)->m_268;
	if (notifier) {
		int value = m_x1C;
		if (((Rva00318FA1MainOwner *)army)->rva00318FA1() == value)
			((Rva003EE966 *)notifier)->rva003EE966(value);
		else
			notifier->rva003EE91A(value);
	}
}

// Slot 1 of retail table 0x00C6D434: whether the candidate is the parent.
bool Rva0056B2DD::slot1(Rva002B4BC9Arg *candidate)
{
	return m_parent18 == reinterpret_cast<Parent0056B2DD *>(candidate);
}

// Slot 4 of retail table 0x00C6D434: whether the pair is the parent and the int.
bool Rva0056B2DD::slot4(LivingWorldArmy *army, Rva00318C32Ret *value)
{
	return m_parent18 == (Parent0056B2DD *)army && m_x1C == (int)value;
}

// Slot 5 of retail table 0x00C6D434: the negation of slot 1 of the primary table.
bool Rva0056B2DD::slot5(int)
{
	return !ac26Slot1();
}
