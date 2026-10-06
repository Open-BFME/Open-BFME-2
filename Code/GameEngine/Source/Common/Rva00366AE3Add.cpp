// cl: /MD
// PathfindLayer::AddWallConnectCell 0x00366AE3 77B (WorldBuilder name,
// pathfinder_layer.cpp lines 278..287: up to two raised-wall connect cells) via ICoord2D slots at +0x18/+0x20
// Evidence: retail compares incoming ICoord2D against two stored slots then fills first with x==-1; callees ??8ICoord2D@@QBE_NABUICoord2DBase@@@Z rowed in icoord.cpp; callers in FUN_0092ed74
struct ICoord2DBase
{
	int x;
	int y;
};

struct ICoord2D : public ICoord2DBase
{
	bool operator==(const ICoord2DBase &that) const;
};

class PathfindLayer
{
public:
	char m_lead[0x18];
	ICoord2D m_a;
	ICoord2D m_b;
	void AddWallConnectCell(const ICoord2D *p);
};

void PathfindLayer::AddWallConnectCell(const ICoord2D *p)
{
	if (*p == m_a)
		return;
	if (*p == m_b)
		return;
	if (m_a.x == -1) {
		m_a = *p;
		return;
	}
	if (m_b.x == -1) {
		m_b = *p;
	}
}
