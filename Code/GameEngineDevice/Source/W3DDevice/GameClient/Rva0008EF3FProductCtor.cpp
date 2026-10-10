// cl: /O1 /G7 /DNDEBUG /MD /Ireference/shims/moduledata
// ??0Rva0008EF3FProduct@@QAE@XZ retail 0x0008EF3F 66B.
//
// The 0xAC0-byte product of game client vtable 0x00BC4738 factory 0x0004C492
// (W3DGameClientFactories.cpp). Target facts: it calls the rowed
// ??0InGameUI@@QAE@XZ 0x002A61A9, stores its own vptrs 0x00BC7A88/+0x0C
// 0x00BC7A78/+0x10 0x00BC7A64 over InGameUI's three bases, clears two
// 25-pointer arrays at +0x9F0/+0xA54 in one loop and then +0xAB8/+0xABC; the
// object ends at 0xAC0, the factory's allocation size.
//
// Donor inference (Zero Hour W3DInGameUI.cpp, not asserted as the target
// name): this is W3DInGameUI::W3DInGameUI -- MAX_MOVE_HINTS is 25 and the
// fields are m_moveHintRenderObj/m_moveHintAnim then the building placement
// anchor and arrow. The class keeps the ledger's address-derived name.

#include "Common/Snapshot.h"

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init();
#define SLOT(N) virtual void slot##N();
	SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07) SLOT(08)
#undef SLOT
	virtual void reset();	// slot 9
	virtual void update();	// slot 10

private:
	char m_opaque04[0xC - 0x4];
};

class View;
class Drawable;
struct ICoord2D { int x, y; };

// The five-slot interface at +0x10 (InGameUICtor.cpp).
class InGameUIInterface10
{
public:
#define SLOT(N) virtual void slot##N() = 0;
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04)
#undef SLOT
};

class InGameUI : public SubsystemInterface, public Snapshot, public InGameUIInterface10
{
public:
	InGameUI();
	virtual ~InGameUI();
	virtual void init();
	virtual void reset();
	virtual void update();
#define SLOT(N) virtual void slot##N();
	SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18) SLOT(19)
	SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29)
	SLOT(30) SLOT(31) SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
	SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47) SLOT(48) SLOT(49)
	SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54) SLOT(55) SLOT(56) SLOT(57) SLOT(58) SLOT(59)
#undef SLOT
	virtual bool isPlacementAnchored(void);					// +0xF0
	virtual void getPlacementPoints(ICoord2D *start, ICoord2D *end);	// +0xF4

protected:
	char m_opaque14[0x544 - 0x14];
	Drawable **m_placeIcon;		// +0x544
	char m_opaque548[0x9F0 - 0x548];
};

class Rva0008EF3FProduct : public InGameUI
{
public:
	Rva0008EF3FProduct();
	virtual ~Rva0008EF3FProduct();
	virtual void init();
	virtual void reset();
	virtual void update();
	virtual void drawPlaceAngle(View *view);

private:
	enum { MAX_MOVE_HINTS = 25 };

	void *m_moveHintRenderObj[MAX_MOVE_HINTS];	// +0x9F0
	void *m_moveHintAnim[MAX_MOVE_HINTS];		// +0xA54
	class RenderObjClass *m_buildingPlacementAnchor;	// +0xAB8
	class RenderObjClass *m_buildingPlacementArrow;		// +0xABC
};

Rva0008EF3FProduct::Rva0008EF3FProduct()
{
	int i;

	for (i = 0; i < MAX_MOVE_HINTS; i++)
	{
		m_moveHintRenderObj[i] = 0;
		m_moveHintAnim[i] = 0;
	}

	m_buildingPlacementAnchor = 0;
	m_buildingPlacementArrow = 0;
}

// ?init@Rva0008EF3FProduct@@UAEXXZ @0x0008F0BB 5B: SubsystemInterface slot 1
// of the product's vtable 0x00BC7A88, extending nothing: a tail jump to the
// rowed InGameUI::init 0x0029E2DE (Zero Hour's W3DInGameUI::init has the same
// body; donor inference only).
void Rva0008EF3FProduct::init()
{
	InGameUI::init();
}

// ?update@Rva0008EF3FProduct@@UAEXXZ @0x0008F0C0 and
// ?reset@Rva0008EF3FProduct@@UAEXXZ @0x0008F0C5, 5B each: slots 10 and 9 of
// the same vtable, tail jumps to the rowed InGameUI::update 0x002A1582 and
// InGameUI::reset 0x002A5EE6 (Zero Hour's W3DInGameUI::update and ::reset
// only call the base; donor inference only).
void Rva0008EF3FProduct::update()
{
	InGameUI::update();
}

void Rva0008EF3FProduct::reset()
{
	InGameUI::reset();
}

// Zero Hour W3DInGameUI::drawPlaceAngle, retail 0x0008F179..0x0008F32C (435B,
// RET 4; vtable 0x00BC7A88 slot 123). BFME 2 builds both the anchor and the
// arrow from "W_Arrow" through the free Create_Render_Obj (0x00136175) and
// drops the sanity diagnostics; otherwise the donor algorithm: placement
// anchor or arrow by drag length (5.0), scene membership kept in step, and the
// shown one copies the first placement icon's transform.
#include "../../../../Libraries/Include/Lib/Coord3D.h"
class SceneClass;
class Matrix3D;
class RenderObjClass
{
public:
#define SLOT(N) virtual void slot##N();
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07) SLOT(08) SLOT(09)
	SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17)
#undef SLOT
	virtual SceneClass *Peek_Scene(void);		// +0x48
	virtual void slot19();
	virtual void slot20();
	virtual void Set_Transform(const Matrix3D &m);	// +0x54
};
RenderObjClass *Create_Render_Obj(const char *name);
class RTS3DScene
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void Add_Render_Object(RenderObjClass *obj);	// +0x08
	virtual void Remove_Render_Object(RenderObjClass *obj);	// +0x0C
};
class W3DDisplay { public: static RTS3DScene *m_3DScene; };
class Drawable { public: const Matrix3D *getTransformMatrix(void) const; };

void Rva0008EF3FProduct::drawPlaceAngle(View *view)
{
	//Create the anchor & arrow if not already created!
	if( !m_buildingPlacementAnchor )
	{
		m_buildingPlacementAnchor = Create_Render_Obj( "W_Arrow" );
		if( !m_buildingPlacementAnchor )
			return;
	}
	if( !m_buildingPlacementArrow )
	{
		m_buildingPlacementArrow = Create_Render_Obj( "W_Arrow" );
		if( !m_buildingPlacementArrow )
			return;
	}

	bool anchorInScene = m_buildingPlacementAnchor->Peek_Scene() != 0;
	bool arrowInScene = m_buildingPlacementArrow->Peek_Scene() != 0;

	// get out of here if this display isn't up anyway
	if( isPlacementAnchored() == false )
	{
		if( anchorInScene )
			W3DDisplay::m_3DScene->Remove_Render_Object( m_buildingPlacementAnchor );
		if( arrowInScene )
			W3DDisplay::m_3DScene->Remove_Render_Object( m_buildingPlacementArrow );
		return;
	}

	// get the anchor points
	ICoord2D start, end;
	getPlacementPoints( &start, &end );

	Coord3D vector;
	vector.x = end.x - start.x;
	vector.y = end.y - start.y;
	vector.z = 0.0f;
	float length = vector.length();

	bool showArrow = length >= 5.0f;

	if( showArrow )
	{
		if( anchorInScene )
			W3DDisplay::m_3DScene->Remove_Render_Object( m_buildingPlacementAnchor );
		if( !arrowInScene )
		{
			W3DDisplay::m_3DScene->Add_Render_Object( m_buildingPlacementArrow );
			arrowInScene = true;
		}
	}
	else
	{
		if( arrowInScene )
			W3DDisplay::m_3DScene->Remove_Render_Object( m_buildingPlacementArrow );
		if( !anchorInScene )
		{
			W3DDisplay::m_3DScene->Add_Render_Object( m_buildingPlacementAnchor );
			anchorInScene = true;
		}
	}

	//The proper way to orient the placement arrow is to copy the matrix from the m_placeIcon[0]!
	if( anchorInScene )
	{
		if ( m_placeIcon[ 0 ] )
			m_buildingPlacementAnchor->Set_Transform( *m_placeIcon[ 0 ]->getTransformMatrix() );
	}
	else if( arrowInScene )
	{
		if ( m_placeIcon[ 0 ] )
			m_buildingPlacementArrow->Set_Transform( *m_placeIcon[ 0 ]->getTransformMatrix() );
	}
}
