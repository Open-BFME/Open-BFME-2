// ?Rva003E4EA5Get@@YG_NPAVParameter@@@Z
// cl: /O1
// @0x003E4EA5 48B leaf single-param terrain-tactical check via TheTerrainLogic
// slot 0x88 plus TheTacticalView slot 0x6C. Evidence: caller 0x003EBDBF;
// prev 0x003E4BFA evaluateSkirmishPlayerHasBeenAttackedByPlayer; next
// 0x003E514F Rva003E514FCheck.
class Parameter;
class TerrainLogic
{
public:
	virtual void _d00(), _d01(), _d02(), _d03(), _d04(), _d05(), _d06();
	virtual void _d07(), _d08(), _d09(), _d10(), _d11(), _d12(), _d13();
	virtual void _d14(), _d15(), _d16(), _d17(), _d18(), _d19(), _d20();
	virtual void _d21(), _d22(), _d23(), _d24(), _d25(), _d26(), _d27();
	virtual void _d28(), _d29(), _d30(), _d31(), _d32(), _d33();
	virtual void *slot88(void *arg);
};
extern TerrainLogic *TheTerrainLogic;
class TacticalView
{
public:
	virtual void _e00(), _e01(), _e02(), _e03(), _e04(), _e05(), _e06();
	virtual void _e07(), _e08(), _e09(), _e10(), _e11(), _e12(), _e13();
	virtual void _e14(), _e15(), _e16(), _e17(), _e18(), _e19(), _e20();
	virtual void _e21(), _e22(), _e23(), _e24(), _e25(), _e26();
	virtual bool slot6C(int arg);
};
extern TacticalView *TheTacticalView;

bool __stdcall Rva003E4EA5Get(Parameter *p)
{
	void *cell = TheTerrainLogic->slot88((void *)((char *)p + 0x10));
	if (cell) {
		int val = *(int *)((char *)cell + 4);
		return TheTacticalView->slot6C(val);
	}
	return false;
}
