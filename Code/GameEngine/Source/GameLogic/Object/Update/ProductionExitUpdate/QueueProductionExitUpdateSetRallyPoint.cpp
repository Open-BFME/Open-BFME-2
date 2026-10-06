// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX- /Ob1
//
// Ported from Open-BFME-1 GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/QueueProductionExitUpdateSetRallyPoint.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?setRallyPoint@QueueProductionExitUpdate@@UAEXPBUCoord3D@@@Z 0x004A051B (44B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
// QueueProductionExitUpdate::setRallyPoint at 0x002D0CA0.
struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;
Object *bfmeQueryRallyOverride(Object *obj, const Coord3D *pos);

class QueueProductionExitUpdate
{
public:
	virtual void setRallyPoint(const Coord3D *pos);

private:
	unsigned char m_pad[4];
	Coord3D m_rallyPoint;
	bool m_rallyPointExists;
};

void QueueProductionExitUpdate::setRallyPoint(const Coord3D *pos)
{
	Object *obj = *reinterpret_cast<Object **>(
		reinterpret_cast<char *>(this) - 0x18);
	Object *overrideHost = bfmeQueryRallyOverride(obj, pos);
	if (overrideHost)
		m_rallyPoint = *reinterpret_cast<const Coord3D *>(
			reinterpret_cast<const char *>(overrideHost) + 0x38);
	else
		m_rallyPoint = *pos;
	m_rallyPointExists = true;
}
