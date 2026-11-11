// cl: /O1 /DNDEBUG /MD /EHsc
// ??1Rva005D2111@@UAE@XZ retail 0x005D2111 87B virtual dtor stores derived vtables then cond erase via 0x002B7250 then base 0x005CCDDD. Evidence: deleting-dtor caller 0x005D2168 vtable 0x00C75790#0 rowed erase callee pinned base.
class CreateAHeroData;
#include "../../Include/Common/Rva002B7250.h"
struct Holder005D2111
{
	int m00;
	int m04;
	Rva002B7250 m08;
};
class Rva005CCDDD
{
public:
	virtual ~Rva005CCDDD();
protected:
	int m04;
	int m08;
};
#include "../../Include/Common/LivingWorldBattleListener.h"
class Rva005D2111 : public Rva005CCDDD, public LivingWorldBattleListener
{
public:
	virtual ~Rva005D2111();
private:
	// Native holder stays at+14; the unread word+10 is not assigned to
	// the shared four-byte observer by the destructor evidence.
	int m_opaque10;
	Holder005D2111 *m_holder;
};
Rva005D2111::~Rva005D2111()
{
	if (m_holder)
		m_holder->m08.rva002B7250((CreateAHeroData *)(LivingWorldBattleListener *)this);
}
