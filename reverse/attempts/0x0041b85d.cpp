// ?Rva0041B85DCheck@@YA_NPAVObject@@0H@Z
// partial score=0.99 date=2026-10-06
// cl: /O1 /MD
// ?Rva0041B85DCheck@@YA_NPAVObject@@0H@Z @0x0041B85D 88B
// Free static helper at 0x0041B85D (88B): shroud/visibility gate used by canEnterObject callers.
// Evidence: rowed callees ?getControllingPlayer@Object@@QBEPAVPlayer@@XZ and ?getShroudStatusForPlayer@Object@@QBE?AW4CellShroudStatus@@H@Z; callers 0x0041B9D0 0x0041C385 pass (edi, esi, stack int); prev/next same flags.
enum CellShroudStatus
{
	CELLSHROUD_CLEAR = 0,
	CELLSHROUD_FOGGED = 1,
	CELLSHROUD_SHROUDED = 2,
	CELLSHROUD_COUNT = 3
};
class Player;
class Object;
class Player
{
public:
	char m_pad00[0x54];
	int m_playerIndex;
	int m_pad58;
	int m_val5c;
};
class Object
{
public:
	Player *getControllingPlayer() const;
	CellShroudStatus getShroudStatusForPlayer(int playerIndex) const;
public:
	char m_pad00[0x74];
	int m_id74;
};
static __declspec(noinline) bool Rva0041B85DCheck(Object *a, Object *b, int c);
static __declspec(noinline) bool Rva0041B85DCheck(Object *a, Object *b, int c)
{
	if (b) {
		int v = b->m_id74;
		if (v >= 0x5F5E0FC && v <= 0x5F5E0FF)
			return false;
	}
	if (!a || !b)
		return false;
	if (a->getControllingPlayer() == 0)
		return false;
	if (a->getControllingPlayer()->m_val5c != 0)
		return false;
	if (c == 1)
		return false;
	int idx = a->getControllingPlayer()->m_playerIndex;
	CellShroudStatus st = b->getShroudStatusForPlayer(idx);
	if (st >= CELLSHROUD_COUNT)
		return true;
	return false;
}
bool Rva0041B85DCaller(Object *a, Object *b, int c)
{
	return Rva0041B85DCheck(a, b, c);
}
