// Donor874e38488 game/GameEngine/Source/GameLogic/Map/TerrainLogicBuildBeacons.cpp
// supplies waypoint-path traversal and list ownership. Target diagnostic BFB230
// independently names buildBeacons; retail283E9C..283FAA fixes list+64 slot84
// and three-zero debug stream. Native waypoints share0C/1C/20/4C/60 accesses.
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
#include <stdlib.h>
namespace _STL {void __cdecl free(void *) throw(...);}
#define free _STL::free
#include <list>
#undef free

typedef bool Bool;
typedef float Real;
typedef int Int;

#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef _STL::list<Coord3D> Coord3DList;

// Target outer nodes own a coordinate list: clear283002 calls its5B
// destructor200667 and copy construction in282843 calls coordinate-list copy2820DD.
typedef Coord3DList BeaconPath00283E9C;

// Layout shared with the matched TerrainLogic::newMap: the location is at
// +0x0c and the all-waypoints link at +0x1c.  The remaining reads keep
// offset-derived names; no witness names them.
class Waypoint
{
public:
	Waypoint *getNext(void) const
	{
		return m_next;
	}

	Waypoint *getPtr20(void) const
	{
		return m_ptr_20;
	}

	Int getDword4C(void) const
	{
		return m_dword_4c;
	}

	Int getDword60(void) const
	{
		return m_dword_60;
	}

	unsigned char m_unreconstructed_00[0x0c];
	Coord3D m_location;
	unsigned char m_unreconstructed_18[4];
	Waypoint *m_next;
	Waypoint *m_ptr_20;
	unsigned char m_unreconstructed_24[0x28];
	Int m_dword_4c;
	unsigned char m_unreconstructed_50[0x10];
	Int m_dword_60;
};

class BfmeAwakenLog
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual BfmeAwakenLog *slot38(const char *text);
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C(int report);
};

class Debug
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual BfmeAwakenLog *slot6C(int first, int second, int third);
};

extern Debug *theDebug;
#define TheDebug theDebug
extern void _bfme_debugRecordCallsite(int kind);
extern bool bfmeRva000387C0(void);

class TerrainLogic
{
public:
	virtual void tlSlot00(void) = 0;
	virtual void tlSlot04(void) = 0;
	virtual void tlSlot08(void) = 0;
	virtual void tlSlot0C(void) = 0;
	virtual void tlSlot10(void) = 0;
	virtual void tlSlot14(void) = 0;
	virtual void tlSlot18(void) = 0;
	virtual void tlSlot1C(void) = 0;
	virtual void tlSlot20(void) = 0;
	virtual void tlSlot24(void) = 0;
	virtual void tlSlot28(void) = 0;
	virtual void tlSlot2C(void) = 0;
	virtual void tlSlot30(void) = 0;
	virtual void tlSlot34(void) = 0;
	virtual void tlSlot38(void) = 0;
	virtual void tlSlot3C(void) = 0;
	virtual void tlSlot40(void) = 0;
	virtual void tlSlot44(void) = 0;
	virtual void tlSlot48(void) = 0;
	virtual void tlSlot4C(void) = 0;
	virtual void tlSlot50(void) = 0;
	virtual void tlSlot54(void) = 0;
	virtual void tlSlot58(void) = 0;
	virtual void tlSlot5C(void) = 0;
	virtual void tlSlot60(void) = 0;
	virtual void tlSlot64(void) = 0;
	virtual void tlSlot68(void) = 0;
	virtual void tlSlot6C(void) = 0;
	virtual void tlSlot70(void) = 0;
	virtual void tlSlot74(void) = 0;
	virtual void tlSlot78(void) = 0;
	virtual void tlSlot7C(void) = 0;
	virtual void tlSlot80(void) = 0;
	virtual Waypoint *tlSlot84(void) = 0;

private:
	unsigned char m_unreconstructed_04[0x60];
	_STL::list<BeaconPath00283E9C> m_beaconPaths;

protected:
	void buildBeacons(void);
};

void TerrainLogic::buildBeacons(void)
{
	m_beaconPaths.clear();

	for (Waypoint *start = tlSlot84(); start != 0; start = start->getNext())
	{
		if (start->getDword60() != 5)
			continue;

		BeaconPath00283E9C path;

		for (Waypoint *way = start;;)
		{
			Coord3D point;
			point.x = way->m_location.x;
			point.y = way->m_location.y;
			point.z = way->m_location.z;
			path.push_front(point);

			Int links = way->getDword4C();
			if (links == 0)
				break;

			if (links != 1)
			{
				if (bfmeRva000387C0())
				{
					_bfme_debugRecordCallsite(1);
					TheDebug->slot60();
					TheDebug->slot6C(0, 0, 0)->slot38(
						"TerrainLogic::buildBeacons - A beacon waypoint path has more than one link. Not allowed.")->slot4C(2);
				}

				path.clear();
				break;
			}

			way = way->getPtr20();
			if (way == start)
				break;
			if (way == 0)
				break;
		}

		if (!path.empty())
			m_beaconPaths.push_front(path);
	}
}
