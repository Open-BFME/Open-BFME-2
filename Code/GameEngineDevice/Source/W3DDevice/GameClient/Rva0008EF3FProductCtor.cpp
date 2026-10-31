// cl: /DNDEBUG /MD /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /Ow
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
#include "../../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
class RenderObjClass;
class HAnimClass;

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
	// BFME's lasso selection: points in screen order, closed to the cursor.
	struct LassoPointNode
	{
		LassoPointNode *next;
		LassoPointNode *prev;
		ICoord2D point;
	};

	char m_opaque14[0x2C - 0x14];
	ICoord2D m_dragSelectRegionLo;	// +0x2C
	ICoord2D m_dragSelectRegionHi;	// +0x34
	char m_opaque3C[0x40 - 0x3C];
	// BFME 2's move hint record (0x14 bytes): Zero Hour's MoveHintStruct with
	// the source ID dropped and a byte that suppresses the hint (labels are
	// descriptive; the offsets are what 0x0008F48E reads).
	struct MoveHint
	{
		Coord3D pos;		// +0x00
		unsigned int frame;	// +0x0C
		bool suppressed;	// +0x10
	};
	MoveHint m_moveHint[25];	// +0x40
	char m_opaque234[0x544 - 0x234];
	Drawable **m_placeIcon;		// +0x544
	char m_opaque548[0x910 - 0x548];
	LassoPointNode *m_lassoPoints;	// +0x910, list sentinel
	char m_opaque914[0x924 - 0x914];
	bool m_lassoSelecting;		// +0x924
	char m_opaque925[0x9F0 - 0x925];
};

class Rva0008EF3FProduct : public InGameUI
{
public:
	Rva0008EF3FProduct();
	virtual ~Rva0008EF3FProduct();
	virtual void init();
	virtual void reset();
	virtual void update();
	virtual void drawSelectionRegion(void);
	virtual void drawMoveHints(View *view);
	virtual void drawPlaceAngle(View *view);

private:
	enum { MAX_MOVE_HINTS = 25 };

	RenderObjClass *m_moveHintRenderObj[MAX_MOVE_HINTS];	// +0x9F0
	HAnimClass *m_moveHintAnim[MAX_MOVE_HINTS];		// +0xA54
	class RenderObjClass *m_buildingPlacementAnchor;	// +0xAB8
	class RenderObjClass *m_buildingPlacementArrow;		// +0xABC
};


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
#define SLOT(N) virtual void slot##N();
	SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29)
	SLOT(30) SLOT(31) SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
	SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44)
#undef SLOT
	virtual void Set_Animation(HAnimClass *anim, float frame, int mode);	// +0xB4
#define SLOT(N) virtual void slot##N();
	SLOT(46) SLOT(47) SLOT(48) SLOT(49)
	SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54) SLOT(55) SLOT(56) SLOT(57) SLOT(58) SLOT(59)
	SLOT(60) SLOT(61) SLOT(62) SLOT(63) SLOT(64) SLOT(65) SLOT(66) SLOT(67) SLOT(68) SLOT(69)
	SLOT(70) SLOT(71) SLOT(72) SLOT(73) SLOT(74) SLOT(75) SLOT(76) SLOT(77) SLOT(78) SLOT(79)
	SLOT(80) SLOT(81) SLOT(82) SLOT(83) SLOT(84) SLOT(85) SLOT(86) SLOT(87) SLOT(88) SLOT(89)
	SLOT(90) SLOT(91) SLOT(92) SLOT(93) SLOT(94) SLOT(95) SLOT(96) SLOT(97) SLOT(98) SLOT(99)
#undef SLOT
	virtual int Is_Hidden(void);			// +0x190
	virtual void Set_Hidden(int hidden);		// +0x194
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
class W3DDisplay
{
public:
	static RTS3DScene *m_3DScene;
	void drawLine(float x1, float y1, float x2, float y2, float width, int color1, int color2);	// line
	void rva0008EEF0(float x, float y, float w, float h, float width, int color);	// open rect
};
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

// Zero Hour W3DInGameUI::drawSelectionRegion, retail 0x0008F395..0x0008F48E
// (249B; vtable 0x00BC7A88 slot 120). BFME 2 adds lasso selection: while
// +0x924 is set it draws the +0x910 point list as a polyline closed to the
// cursor (Mouse +0x4F0C); otherwise the donor's drag rectangle at +0x2C.
class Display;
extern Display *TheDisplay;
class Mouse;
extern Mouse *TheMouse;
struct InGameUIMouseView { char pad[0x4F0C]; ICoord2D position; };

void Rva0008EF3FProduct::drawSelectionRegion(void)
{
	float width = 2.0f;
	unsigned int color = 0xBBFFBB33;

	if( m_lassoSelecting )
	{
		LassoPointNode *it = m_lassoPoints->next;
		while( it != m_lassoPoints )
		{
			ICoord2D from = it->point;
			it = it->next;
			int toX, toY;
			if( it != m_lassoPoints )
			{
				toX = it->point.x;
				toY = it->point.y;
			}
			else
			{
				const ICoord2D &pos = reinterpret_cast<InGameUIMouseView *>(TheMouse)->position;
				toX = pos.x;
				toY = pos.y;
			}
			reinterpret_cast<W3DDisplay *>(TheDisplay)->drawLine( from.x, from.y, toX, toY,
				width, color, color );
		}
	}
	else
	{
		reinterpret_cast<W3DDisplay *>(TheDisplay)->rva0008EEF0( m_dragSelectRegionLo.x, m_dragSelectRegionLo.y,
			m_dragSelectRegionHi.x - m_dragSelectRegionLo.x,
			m_dragSelectRegionHi.y - m_dragSelectRegionLo.y,
			width, color );
	}
}

// Zero Hour W3DInGameUI::drawMoveHints, retail 0x0008F48E..0x0008F6E1 (595B,
// RET 4; vtable 0x00BC7A88 slot 121, between drawSelectionRegion and
// drawPlaceAngle). Target facts: TheGameClient's frame through its slot
// 0x7C (read twice: no hint shows during the first 40 frames), a per-hint
// suppress byte, the hint model from TheWritableGlobalData +0x10 through
// Create_Render_Obj and AnimationAsset::GetAnim("%s.%s"), a new hint hidden
// at once, TheTerrainLogic slots 0x48/0x4C (alignOnTerrain, a five-argument
// isUnderwater) and the 0x0027CEDE normal alignment for water. The rest is
// the donor algorithm.
#include "ascii_string.h"
class GameClient
{
public:
#define SLOT(N) virtual void slot##N();
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07) SLOT(08) SLOT(09)
	SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18) SLOT(19)
	SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29)
	SLOT(30)
#undef SLOT
	virtual unsigned int getFrame(void);		// +0x7C
};
extern GameClient *TheGameClient;
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct MoveHintGlobalDataView
{
	char m_opaque00[0x10];
	AsciiString m_moveHintName;	// +0x10
};
#define TheMoveHintData ((const MoveHintGlobalDataView *)TheWritableGlobalData)
class TerrainLogic
{
public:
#define SLOT(N) virtual void slot##N();
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07) SLOT(08) SLOT(09)
	SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17)
#undef SLOT
	virtual int alignOnTerrain(float angle, const Coord3D &pos, bool stickToGround, Matrix3D &mtx);	// +0x48
	virtual bool isUnderwater(float x, float y, float *waterZ, float *terrainZ, void *unknown);	// +0x4C
};
extern TerrainLogic *TheTerrainLogic;
class Matrix3D
{
public:
	float Row[3][4];
};
class HAnimClass
{
public:
	virtual void Delete_This(void);
	void Release_Ref(void)
	{
		NumRefs--;
		if (NumRefs == 0)
			Delete_This();
	}
private:
	int NumRefs;
};
class AnimationAsset
{
public:
	static HAnimClass *GetAnim(const char *name);
};
void alignToTerrain(float angle, const Coord3D &pos, const Coord3D &normal, Matrix3D &mtx);

void Rva0008EF3FProduct::drawMoveHints(View *view)
{
	int i;

	for (i = 0; i < MAX_MOVE_HINTS; i++)
	{
		// The hint's frame is read through both arms of an identical conditional: cl's
		// induction-variable pick counts the frame loads before the arms merge and then
		// bases the hint array walk on the frame field (retail's &frame = this+0x4C)
		// instead of pos.y, which a single read loses by the tie rule.
		int elapsed = (m_moveHint[i].suppressed) ? (TheGameClient->getFrame() - m_moveHint[i].frame) : (TheGameClient->getFrame() - m_moveHint[i].frame);
		if (TheGameClient->getFrame() <= 40)
			elapsed = 41;

		if (!m_moveHint[i].suppressed && elapsed <= 40)
		{
			// create render object if needed
			if (m_moveHintRenderObj[i] == 0)
			{
				RenderObjClass *hint = Create_Render_Obj(TheMoveHintData->m_moveHintName.str());

				AsciiString animName;
				animName.format("%s.%s", TheMoveHintData->m_moveHintName.str(), TheMoveHintData->m_moveHintName.str());
				HAnimClass *anim = AnimationAsset::GetAnim(animName.str());

				if (hint == 0)
					return;

				hint->Set_Hidden(1);
				m_moveHintRenderObj[i] = hint;

				if (m_moveHintAnim[i])
				{
					m_moveHintAnim[i]->Release_Ref();
					m_moveHintAnim[i] = 0;
				}
				m_moveHintAnim[i] = anim;
			}

			// show the render object if hidden
			if (m_moveHintRenderObj[i]->Is_Hidden() == 1)
			{
				m_moveHintRenderObj[i]->Set_Hidden(0);
				W3DDisplay::m_3DScene->Add_Render_Object(m_moveHintRenderObj[i]);
				if (m_moveHintAnim[i])
					m_moveHintRenderObj[i]->Set_Animation(m_moveHintAnim[i], 0, 2);
			}

			// move this hint render object to the position and align with terrain
			Matrix3D transform;
			const Coord3D &pos = m_moveHint[i].pos;
			int layer = TheTerrainLogic->alignOnTerrain(0, pos, true, transform);

			float waterZ;
			if (layer == 1 && TheTerrainLogic->isUnderwater(pos.x, pos.y, &waterZ, 0, 0))
			{
				Coord3D tmp;
				tmp.x = pos.x;
				tmp.y = pos.y;
				tmp.z = waterZ;
				Coord3D normal;
				normal.x = 0;
				normal.y = 0;
				normal.z = 1;
				alignToTerrain(0, tmp, normal, transform);
			}

			m_moveHintRenderObj[i]->Set_Transform(transform);
		}
		else
		{
			// hide hint marker
			if (m_moveHintRenderObj[i])
				if (m_moveHintRenderObj[i]->Is_Hidden() == 0)
				{
					m_moveHintRenderObj[i]->Set_Hidden(1);
					W3DDisplay::m_3DScene->Remove_Render_Object(m_moveHintRenderObj[i]);
				}
		}
	}
}
