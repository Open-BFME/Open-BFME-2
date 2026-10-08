#pragma once

enum CellShroudStatus;
class Object;
struct Coord3D;
struct FindPositionOptions;
class Rva000421C8;
class Rva00628770Impl;
enum CellShroudStatus;

// The native query result has one pointer-sized word, a copy constructor and
// a destructor (0x0004AA28). Its Object iterator step is rowed at 0x00045623.
struct BfmeWideResult
{
	void *m_value;
	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &that);
	~BfmeWideResult();
	Object *next() throw();	// nothrow: no unwind state spans a query loop (0x003A2DBB)
	void rva00626630(Object *obj, float distance);	// 0x00626630
};

// ThePartitionManager's native query wrappers at 0x006255D0/0x00625610
// forward through +0x10 to implementation 0x00628770. This is an accessed
// prefix and call view; the complete manager extent is not reconstructed.
class PartitionManager
{
	char m_pad[0x10];
	Rva00628770Impl *m_impl;
public:
	static bool findPositionAround(const Coord3D*,const FindPositionOptions*,Coord3D*);
	// Existing native shroud facade; +0x10 forwarder at RVA007397F0.
	CellShroudStatus getShroudStatusForPlayer(int playerIndex, const Coord3D *pos) const;
	// Original name unknown: the four-argument range query uses no filters.
	BfmeWideResult rva006255D0(const Coord3D *pos, float radius, int distType, int order);
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius,
		int distType, Rva000421C8 *filters, int order);
	Object *getClosestObject(const Coord3D *pos, float maxDist, int dc,
		Rva000421C8 *filters);	// 0x00625360
	// TheShroudManager's this-adjusting forwarder through +0x10.
	CellShroudStatus getShroudStatusForPlayer(int playerIndex, const Coord3D *pos) const;	// 0x007397F0
};
