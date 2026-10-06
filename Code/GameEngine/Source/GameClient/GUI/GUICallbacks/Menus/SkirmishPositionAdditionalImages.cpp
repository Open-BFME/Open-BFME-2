// cl: /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /D_CRTIMP= /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Oy /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus
// stlport
// BFME 1 donor game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/
// SkirmishPositionAdditionalImages.cpp at 6583b3c1ff21db4a561285717028fdafc780b7db.
// Recompiled /O1 /arch:SSE /G5: unique 557-byte BFME 2 placement at 0x00301656.
// Target independently confirms extent +8; source position lists +0x48/+0x4C;
// both output lists; window queries; Region3D copy; findDrawPositions and the
// two coordinate loops. The donor supplies the semantic names. The historical
// 536-byte partial used a different Region3D declaration and local lifetimes.

#define _STLP_NO_EXCEPTIONS 1

typedef int Int;
typedef bool Bool;
typedef float Real;

struct Coord3DBase
{
	float x, y, z;
};

class Coord3D : public Coord3DBase
{
public:
	Coord3D();
	Coord3D(const Coord3D &that);
	~Coord3D();
};

struct Region3D
{
	Region3D();
	Region3D(const Region3D &that);
	~Region3D();

	Coord3D lo, hi;
};

struct ICoord2D
{
	Int x, y;
};

#include <list>

// Retail keeps creation of this 16-byte node out of line. This follows the
// already-matched SpecialPowerTimerList.cpp repair. The emitted clear (39B),
// push-front (28B), insert (37B), node creation (34B) and copy (23B) all match
// their shared retail providers; each REL32 callee was checked recursively.
namespace _STL {
template <> __declspec(noinline) _List_node<ICoord2D> *
list<ICoord2D, allocator<ICoord2D> >::_M_create_node(const ICoord2D &);
template <> __declspec(noinline) _List_node<ICoord2D> *
list<ICoord2D, allocator<ICoord2D> >::_M_create_node(const ICoord2D &value)
{
    _Node *node = this->_M_node.allocate(1);
    _Construct(&node->_M_data, value);
    return node;
}
}

typedef std::list<ICoord2D> ICoord2DList;
typedef std::list<Coord3D> Coord3DList;

class TechAndSupplyImages
{
public:
	ICoord2DList m_techPosList;
	ICoord2DList m_supplyPosList;
};

extern TechAndSupplyImages TheSupplyAndTechImageLocations;

class GameWindow
{
public:
	Bool winIsHidden(void);
	Int winGetSize(Int *width, Int *height);
	Int winGetScreenPosition(Int *x, Int *y);
};

class MapMetaData
{
	public:
	char m_beforeExtent[8];
	Region3D m_extent;
	char m_betweenExtentAndLists[0x28];
	Coord3DList m_supplyPositions;
	Coord3DList m_techPositions;
};

void findDrawPositions(Int startX, Int startY, Int width, Int height,
	Region3D extent, ICoord2D *ul, ICoord2D *lr);

enum { SUPPLY_TECH_SIZE = 15 };

void positionAdditionalImages(MapMetaData *mmd, GameWindow *mapWindow, Bool force)
{
	TheSupplyAndTechImageLocations.m_supplyPosList.clear();
	TheSupplyAndTechImageLocations.m_techPosList.clear();

	if( !mmd || !mapWindow || mapWindow->winIsHidden())
		return;
	static MapMetaData *prevMMD = NULL;
	if(force)
		prevMMD = NULL;
	if(mmd == prevMMD)
		return;
	ICoord2D winMapSize, winMapPos;
	mapWindow->winGetSize(&winMapSize.x, &winMapSize.y);
	mapWindow->winGetScreenPosition(&winMapPos.x, &winMapPos.y);

	ICoord2D ul;
	Int smallWidth, smallHeight;
	{
		ICoord2D lr;
		findDrawPositions(0,0, winMapSize.x, winMapSize.y,mmd->m_extent, &ul, &lr);
		smallWidth = lr.x - ul.x;
		smallHeight= lr.y - ul.y;
	}

	Coord3DList::iterator it = mmd->m_supplyPositions.begin();
	Int ulX = ul.x;
	Int ulY = ul.y;
	while( it._M_node != mmd->m_supplyPositions.end()._M_node)
	{
		ICoord2D markerPos;
		Real position;
		position = (it->x - mmd->m_extent.lo.x) / (mmd->m_extent.hi.x - mmd->m_extent.lo.x);
		markerPos.x = (position * smallWidth) - SUPPLY_TECH_SIZE /2 + ulX;
		position = (it->y - mmd->m_extent.lo.y) / (mmd->m_extent.hi.y - mmd->m_extent.lo.y);
		markerPos.y = ((1- position) * smallHeight) - SUPPLY_TECH_SIZE /2 + ulY;
		TheSupplyAndTechImageLocations.m_supplyPosList.push_front(markerPos);
		it++;
	}

	it = mmd->m_techPositions.begin();
	ulX = ul.x;
	ulY = ul.y;
	while( it._M_node != mmd->m_techPositions.end()._M_node)
	{
		ICoord2D markerPos;
		Real position;
		position = (it->x - mmd->m_extent.lo.x) / (mmd->m_extent.hi.x - mmd->m_extent.lo.x);
		markerPos.x = (position * smallWidth) - SUPPLY_TECH_SIZE /2 + ulX;
		position = (it->y - mmd->m_extent.lo.y) / (mmd->m_extent.hi.y - mmd->m_extent.lo.y);
		markerPos.y = ((1- position) * smallHeight) - SUPPLY_TECH_SIZE /2 + ulY;
		TheSupplyAndTechImageLocations.m_techPosList.push_front(markerPos);
		it++;
	}
}
