// cl: /MD /EHsc
// Powers table C72F3C slot 3 points to this member.
// Sets the holder's hero state, refreshes the grid and updates its Palantir buttons.
#include "../../../../GameEngine/Include/Common/Rva005B034ADwordSlot.h"
class Rva005B486DOwner
{
public:
	void rva005B4653();
};
struct Rva005B3676Owner;
class Rva005B414FBase
{
public:
	virtual ~Rva005B414FBase();
	virtual void rva000B3FD0_1();
	virtual void rva005B455D(bool);
	virtual void rva005B486D();
	virtual void rva000B3FD0_4();
	virtual int rva005748AD_5(int, int, int);
	virtual int rva005748AD_6(int, int, int);
	virtual void rva005B2B6D(const char *);
protected:
	Rva005B3676Owner *m_owner;
};
namespace AptCreateAHero
{
class Powers : public Rva005B414FBase
{
public:
	virtual ~Powers();
	virtual void rva005B455D(bool);
	virtual void rva005B486D();
	virtual void rva005B2B6D(const char *);
	void UpdatePalantirButtons();
};
}
void AptCreateAHero::Powers::rva005B486D()
{
	((Rva005B034ADwordSlot *)((char *)m_owner + 0x27c))->set(1);
	((Rva005B486DOwner *)this)->rva005B4653();
	UpdatePalantirButtons();
}
