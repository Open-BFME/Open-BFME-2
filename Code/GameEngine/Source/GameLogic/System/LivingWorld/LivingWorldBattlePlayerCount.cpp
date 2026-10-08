// cl: /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Native3F459A..3F45DF and WB104A920 establish a thiscall count over
// the side vector at18/1C: outer elements28B and inner elements48B,
// with the inner vector at side+4/+8. The existing LivingWorldBattle
// address-qualified pin is retained; WB does not recover the method name.
// These are accessed storage views, not recovered full application classes.
// Related BattlePlayer transfer3F5CA9 independently reaches offset2C,
// agreeing with the 48B stride; no unobserved field purpose is asserted.
// Real STLport vectors reproduce both outer size divisions and the inner
// count division, closing the previously blocked raw-pointer shape.
#include <vector>

struct BattlePlayerCountView
{
	char unknown00[48];
};
struct BattleSideCountView
{
	int unknown00;
	_STL::vector<BattlePlayerCountView> players;
	char unknown10[12];
};
class LivingWorldBattle
{
public:
	int rva003F459A();
	char unknown00[0x18];
	_STL::vector<BattleSideCountView> sides;
};

int LivingWorldBattle::rva003F459A()
{
	int count = 0;
	for (unsigned i = 0; i < sides.size(); ++i)
		count += sides[i].players.size();
	return count;
}
