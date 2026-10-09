// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// W3DView virtual (primary vftable VA 0x00BC7568 stored by the ctor at
// 0x0008B805) that restores the camera saved around an object-follow mode:
//
// ?rva00087642@W3DView@@QAEXXZ retail 0x00087642..0x0008780A (456B), vftable
// slot 119 (+0x1DC): restores the saved camera. When slot +0x1CC is set it
// clears the followed id (slots +0x1D4 / +0x1D8) and puts back the eight
// saved camera values (position z angle pitch zoom +0x23E8 target height and
// the +0x70 +0xAC +0xB0 values) from the file statics at VA 0x00DE2024..
// 0x00DE2067; the position comes from +0x2484/+0x2488 when +0x2493 is set.
// The ground height under the camera (TheTerrainLogic slot +0x18; 10 without
// terrain logic; clamped to 700) is stored in the +0x2408 height setter;
// then the follow flag +0x2449 is cleared and the mouse is reset (TheMouse
// 0x001EDE9C / _bfme_setEngineVisibility 0x001EE5BE and byte +0x5009).
// The follow toggle 0x0008ADEA (vftable slot 116 +0x1D0) saves these
// statics and calls this body through slot +0x1DC when follow mode is turned
// off; it lives in W3DViewRotateCamera.cpp beside the register-convention
// normAngle it calls.
//
// The statics are read and written only by those two bodies and by
// 0x0008780A; their original names are unknown so they are address-named.
// Retail's file statics are internal so cl moves their loads across the
// stores to this; the named temporaries below reproduce that order with
// extern declarations.
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef float Real;
typedef int Int;
typedef bool Bool;

extern float g_Va00DE2024;
extern float g_Va00DE2028;
extern float g_Va00DE202C;
extern float g_Va00DE2030;
extern float g_Va00DE2034;
extern float g_Va00DE2038;
extern float g_Va00DE203C;
extern Coord3D g_Va00DE2050;
extern Coord3D g_Va00DE205C;

class TerrainLogic
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal);	// +0x18
};

extern TerrainLogic *TheTerrainLogic;

class Mouse
{
public:
	void rva001EDE9C();
	void _bfme_setEngineVisibility(bool visible);
private:
	char m_pad0000[0x5009];
public:
	Bool m_5009;
};

extern Mouse *TheMouse;

#define W3DVIEW_SLOT(n) virtual void slot##n();

class W3DView
{
public:
	W3DVIEW_SLOT(0)   W3DVIEW_SLOT(1)   W3DVIEW_SLOT(2)   W3DVIEW_SLOT(3)
	W3DVIEW_SLOT(4)   W3DVIEW_SLOT(5)   W3DVIEW_SLOT(6)   W3DVIEW_SLOT(7)
	W3DVIEW_SLOT(8)   W3DVIEW_SLOT(9)   W3DVIEW_SLOT(10)  W3DVIEW_SLOT(11)
	W3DVIEW_SLOT(12)  W3DVIEW_SLOT(13)  W3DVIEW_SLOT(14)  W3DVIEW_SLOT(15)
	W3DVIEW_SLOT(16)  W3DVIEW_SLOT(17)  W3DVIEW_SLOT(18)  W3DVIEW_SLOT(19)
	W3DVIEW_SLOT(20)
	virtual void lookAt(const Coord3D *pos);			// +0x54
	W3DVIEW_SLOT(22)  W3DVIEW_SLOT(23)
	W3DVIEW_SLOT(24)  W3DVIEW_SLOT(25)  W3DVIEW_SLOT(26)  W3DVIEW_SLOT(27)
	W3DVIEW_SLOT(28)  W3DVIEW_SLOT(29)  W3DVIEW_SLOT(30)  W3DVIEW_SLOT(31)
	W3DVIEW_SLOT(32)  W3DVIEW_SLOT(33)  W3DVIEW_SLOT(34)  W3DVIEW_SLOT(35)
	W3DVIEW_SLOT(36)  W3DVIEW_SLOT(37)  W3DVIEW_SLOT(38)  W3DVIEW_SLOT(39)
	W3DVIEW_SLOT(40)  W3DVIEW_SLOT(41)  W3DVIEW_SLOT(42)  W3DVIEW_SLOT(43)
	W3DVIEW_SLOT(44)  W3DVIEW_SLOT(45)  W3DVIEW_SLOT(46)  W3DVIEW_SLOT(47)
	W3DVIEW_SLOT(48)  W3DVIEW_SLOT(49)  W3DVIEW_SLOT(50)  W3DVIEW_SLOT(51)
	W3DVIEW_SLOT(52)  W3DVIEW_SLOT(53)  W3DVIEW_SLOT(54)  W3DVIEW_SLOT(55)
	W3DVIEW_SLOT(56)  W3DVIEW_SLOT(57)  W3DVIEW_SLOT(58)  W3DVIEW_SLOT(59)
	W3DVIEW_SLOT(60)
	virtual void zoomCamera(Real finalZoom, Real milliseconds, Bool flag, Real easeIn);	// +0xF4
	W3DVIEW_SLOT(62)  W3DVIEW_SLOT(63)
	W3DVIEW_SLOT(64)  W3DVIEW_SLOT(65)  W3DVIEW_SLOT(66)  W3DVIEW_SLOT(67)
	W3DVIEW_SLOT(68)  W3DVIEW_SLOT(69)  W3DVIEW_SLOT(70)  W3DVIEW_SLOT(71)
	W3DVIEW_SLOT(72)  W3DVIEW_SLOT(73)  W3DVIEW_SLOT(74)  W3DVIEW_SLOT(75)
	W3DVIEW_SLOT(76)  W3DVIEW_SLOT(77)  W3DVIEW_SLOT(78)  W3DVIEW_SLOT(79)
	W3DVIEW_SLOT(80)  W3DVIEW_SLOT(81)  W3DVIEW_SLOT(82)  W3DVIEW_SLOT(83)
	W3DVIEW_SLOT(84)  W3DVIEW_SLOT(85)  W3DVIEW_SLOT(86)  W3DVIEW_SLOT(87)
	W3DVIEW_SLOT(88)  W3DVIEW_SLOT(89)  W3DVIEW_SLOT(90)  W3DVIEW_SLOT(91)
	W3DVIEW_SLOT(92)  W3DVIEW_SLOT(93)  W3DVIEW_SLOT(94)  W3DVIEW_SLOT(95)
	W3DVIEW_SLOT(96)  W3DVIEW_SLOT(97)  W3DVIEW_SLOT(98)  W3DVIEW_SLOT(99)
	W3DVIEW_SLOT(100) W3DVIEW_SLOT(101) W3DVIEW_SLOT(102) W3DVIEW_SLOT(103)
	W3DVIEW_SLOT(104) W3DVIEW_SLOT(105) W3DVIEW_SLOT(106) W3DVIEW_SLOT(107)
	W3DVIEW_SLOT(108) W3DVIEW_SLOT(109) W3DVIEW_SLOT(110) W3DVIEW_SLOT(111)
	W3DVIEW_SLOT(112) W3DVIEW_SLOT(113) W3DVIEW_SLOT(114)
	virtual Bool isFollowing();				// +0x1CC
	W3DVIEW_SLOT(116)
	virtual Int getFollowedID();				// +0x1D4
	virtual void setFollowedID(Int id);			// +0x1D8
	virtual void stopFollowing();				// +0x1DC
	W3DVIEW_SLOT(120)
	virtual void slot121Reset();				// +0x1E4
	virtual Bool slot122Test();				// +0x1E8
	W3DVIEW_SLOT(123)
	W3DVIEW_SLOT(124) W3DVIEW_SLOT(125) W3DVIEW_SLOT(126) W3DVIEW_SLOT(127)
	W3DVIEW_SLOT(128) W3DVIEW_SLOT(129) W3DVIEW_SLOT(130) W3DVIEW_SLOT(131)
	virtual void setPitchLimits(Real low, Real high);	// +0x210
	W3DVIEW_SLOT(133) W3DVIEW_SLOT(134) W3DVIEW_SLOT(135)
	W3DVIEW_SLOT(136) W3DVIEW_SLOT(137) W3DVIEW_SLOT(138) W3DVIEW_SLOT(139)
	W3DVIEW_SLOT(140) W3DVIEW_SLOT(141) W3DVIEW_SLOT(142) W3DVIEW_SLOT(143)
	W3DVIEW_SLOT(144) W3DVIEW_SLOT(145) W3DVIEW_SLOT(146) W3DVIEW_SLOT(147)
	W3DVIEW_SLOT(148) W3DVIEW_SLOT(149) W3DVIEW_SLOT(150) W3DVIEW_SLOT(151)
	W3DVIEW_SLOT(152) W3DVIEW_SLOT(153) W3DVIEW_SLOT(154) W3DVIEW_SLOT(155)
	W3DVIEW_SLOT(156) W3DVIEW_SLOT(157) W3DVIEW_SLOT(158) W3DVIEW_SLOT(159)
	W3DVIEW_SLOT(160) W3DVIEW_SLOT(161)
	virtual void slot162Set(Int value);			// +0x288
	virtual Bool slot163Test();				// +0x28C
	virtual void slot164Set(Int value);			// +0x290

	void rva00087642();

private:
	char m_pad0004[0x0C - 0x04];
	Coord3D m_pos;				// +0x0C
	char m_pad0018[0x28 - 0x18];
	Real m_28;				// +0x28
	Int m_2c;				// +0x2C
	char m_pad0030[0x3C - 0x30];
	Real m_angle;				// +0x3C
	Real m_40;				// +0x40
	char m_pad0044[0x4C - 0x44];
	Int m_4c;				// +0x4C
	Real m_50;				// +0x50
	char m_pad0054[0x6C - 0x54];
	Real m_6c;				// +0x6C
	Real m_70;				// +0x70
	char m_pad0074[0xAC - 0x74];
	Real m_ac;				// +0xAC
	Real m_b0;				// +0xB0
	char m_pad00b4[0x23E8 - 0xB4];
	Coord3D m_23e8;				// +0x23E8
	char m_pad23f4[0x2408 - 0x23F4];
	Real m_cameraHeight;			// +0x2408
	char m_pad240c[0x241C - 0x240C];
	Bool m_cameraHeightValid;		// +0x241C
	char m_pad241d[0x2449 - 0x241D];
	Bool m_following;			// +0x2449
	char m_pad244a[0x2484 - 0x244A];
	Real m_2484;				// +0x2484
	Real m_2488;				// +0x2488
	char m_pad248c[0x2493 - 0x248C];
	Bool m_2493;				// +0x2493
};

#undef W3DVIEW_SLOT

#define W3DVIEW_MAX_CAMERA_HEIGHT 700.0f

void W3DView::rva00087642()
{
	isFollowing();
	if (!isFollowing())
		return;
	getFollowedID();
	setFollowedID(0);
	m_6c = g_Va00DE203C;
	if (m_2493) {
		Coord3D pos;
		pos.x = m_2484;
		pos.y = m_2488;
		pos.z = 0.0f;
		m_pos = pos;
	}
	m_pos.z = g_Va00DE2050.z;
	m_angle = g_Va00DE2038;
	Real pitch = g_Va00DE2034;
	m_40 = pitch;
	m_50 = pitch;
	Real saved28 = g_Va00DE2030;
	m_23e8 = g_Va00DE205C;
	m_28 = saved28;
	m_70 = g_Va00DE202C;
	m_ac = g_Va00DE2028;
	Real savedB0 = g_Va00DE2024;
	m_2c = m_4c;
	m_b0 = savedB0;

	Real height;
	if (TheTerrainLogic) {
		height = TheTerrainLogic->getGroundHeight(m_pos.x, m_pos.y, 0);
		if (height > W3DVIEW_MAX_CAMERA_HEIGHT)
			height = W3DVIEW_MAX_CAMERA_HEIGHT;
	} else {
		height = 10.0f;
	}
	if (height != m_cameraHeight) {
		m_cameraHeight = height;
		m_cameraHeightValid = false;
	}
	m_following = false;
	TheMouse->rva001EDE9C();
	if (slot122Test())
		slot121Reset();
	slot164Set(0);
	if (slot163Test())
		slot162Set(0);
	TheMouse->_bfme_setEngineVisibility(true);
	TheMouse->m_5009 = false;
}
