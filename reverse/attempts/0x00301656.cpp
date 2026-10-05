// ?positionAdditionalImages@@YAXPAVMapMetaData@@PAVGameWindow@@_N@Z
// partial score=0.75 date=2026-10-05
// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Reference: GeneralsMD SkirmishGameOptionsMenu.cpp positionAdditionalImages.
// Target evidence: 00301656..00301883. Extent +8, position lists +48/+4C.
// Prefix view only: other MapMetaData fields and its full size remain unknown.
#include <list>
typedef bool Bool;
typedef int Int;
typedef float Real;
struct ICoord2D { int x,y; };
struct Coord3D {float x,y,z;};
struct Region3D { Coord3D lo,hi; Region3D(const Region3D&); ~Region3D() {} };
typedef _STL::list<Coord3D> Coord3DList;
class MapMetaData {
public:
 char unknown00[8]; Region3D m_extent;
 char unknown20[0x48-0x20];
 Coord3DList m_supplyPositions,m_techPositions;
};
class GameWindow {
public: bool winIsHidden(); int winGetSize(int*,int*); int winGetScreenPosition(int*,int*);
};
class TechAndSupplyImages {
public: _STL::list<ICoord2D> m_techPosList,m_supplyPosList;
};
extern TechAndSupplyImages TheSupplyAndTechImageLocations;
void findDrawPositions(int,int,int,int,Region3D,ICoord2D*,ICoord2D*);
enum {SUPPLY_TECH_SIZE=15};
void positionAdditionalImages( MapMetaData *mmd, GameWindow *mapWindow, Bool force)

{
	TheSupplyAndTechImageLocations.m_supplyPosList.clear();
	TheSupplyAndTechImageLocations.m_techPosList.clear();

	if( !mmd || !mapWindow || mapWindow->winIsHidden())
		return;
	static MapMetaData *prevMMD = NULL;
	if(force)
		prevMMD = NULL;
	// we already populated the supply and tech image locations.
	if(mmd == prevMMD)
		return;
	ICoord2D winMapSize, winMapPos;
	mapWindow->winGetSize(&winMapSize.x, &winMapSize.y);
	mapWindow->winGetScreenPosition(&winMapPos.x, &winMapPos.y);

	//SUPPLY_TECH_SIZE
	ICoord2D ul, lr;
	findDrawPositions(0,0, winMapSize.x, winMapSize.y,mmd->m_extent, &ul, &lr);
	Int smallWidth = lr.x - ul.x;
	Int smallHeight= lr.y - ul.y;

	Coord3DList::iterator it = mmd->m_supplyPositions.begin();
		// loop through and make sure we're not on top of anyone else
	while( it != mmd->m_supplyPositions.end())
	{

		ICoord2D markerPos;

		// When we actually draw the map, save off it's screen position and use that instead of the map window's position/size
		Real position;
		position = (it->x - mmd->m_extent.lo.x) / (mmd->m_extent.hi.x - mmd->m_extent.lo.x);
		markerPos.x = (position * smallWidth) - SUPPLY_TECH_SIZE /2 + ul.x;// + winMapPos.x;

		position = (it->y - mmd->m_extent.lo.y) / (mmd->m_extent.hi.y - mmd->m_extent.lo.y);
		markerPos.y = ((1- position) * smallHeight) - SUPPLY_TECH_SIZE /2 + ul.y;// + winMapPos.y;
		TheSupplyAndTechImageLocations.m_supplyPosList.push_front(markerPos);
		it++;
	}

	it = mmd->m_techPositions.begin();
		// loop through and make sure we're not on top of anyone else
	while( it != mmd->m_techPositions.end())
	{

		ICoord2D markerPos;
		// When we actually draw the map, save off it's screen position and use that instead of the map window's position/size
		Real position;
		position = (it->x - mmd->m_extent.lo.x) / (mmd->m_extent.hi.x - mmd->m_extent.lo.x);
		markerPos.x = (position * smallWidth) - SUPPLY_TECH_SIZE /2 + ul.x;// + winMapPos.x;

		position = (it->y - mmd->m_extent.lo.y) / (mmd->m_extent.hi.y - mmd->m_extent.lo.y);
		markerPos.y = ((1- position) * smallHeight) - SUPPLY_TECH_SIZE /2 + ul.y;// + winMapPos.y;
		TheSupplyAndTechImageLocations.m_techPosList.push_front(markerPos);
		it++;
	}


	//TheSupplyAndTechImageLocations
}
