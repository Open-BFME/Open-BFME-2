// cl: /MD
// ?Rva0041BB49Check@@YG_NPAVObject@@PBUCoord3D@@HH@Z @0x0041BB49 62B
// Free function at 0x0041BB49 (62B): Object guard then shroud status != 2.
// Evidence: rowed callees ?rva0028BD5D@Object@@QBEPAXH@Z and ?getControllingPlayer@Object@@QBEPAVPlayer@@XZ and ?getShroudStatusForPlayer@PartitionManager@@QBE?AW4CellShroudStatus@@HPBUCoord3D@@@Z with extern TheShroudManager; caller 0x0029CBE3 pushes 0/[ebp+16?]/[ebp+8]/eax for 4 args ret 0x10; like neighbours Rva0041BB26 and Rva0041BB87.
struct Coord3D
{
	int x;
	int y;
};
enum CellShroudStatus
{
	VISIBLE = 0,
	FOGBANK = 1,
	SHROUDED = 2
};
class Player
{
public:
	char m_pad[0x54];
	int m_playerIndex;
};
class PartitionManager
{
public:
	CellShroudStatus getShroudStatusForPlayer(int playerIndex, const Coord3D *pos) const;
};
class Object
{
public:
	void *rva0028BD5D(int i) const;
	Player *getControllingPlayer() const;
};
extern PartitionManager *TheShroudManager;
bool __stdcall Rva0041BB49Check(Object *obj, const Coord3D *pos, int idx, int unused)
{
	if (obj->rva0028BD5D(idx) != 0)
	{
		Player *p = obj->getControllingPlayer();
		int playerIndex = p->m_playerIndex;
		CellShroudStatus st = TheShroudManager->getShroudStatusForPlayer(playerIndex, pos);
		return st != SHROUDED;
	}
	return false;
}
