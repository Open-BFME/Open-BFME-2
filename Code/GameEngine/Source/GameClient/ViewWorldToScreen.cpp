// cl: /O2 /G6 /MD /D_CRTIMP= /DNDEBUG
//
// View::worldToScreen, retail 0x00050F29 (24 bytes, ret 8).
// Donor: ZH GameEngine/Include/GameClient/View.h, where it is inline:
//   return worldToScreenTriReturn( w, s ) == WTS_INSIDE_FRUSTUM;
// Target evidence: the body calls slot 88 (+0x160) of the receiver with both
// arguments and returns result == 0 (neg/sbb/inc). Slot 88 of W3DView's
// primary vftable 0x00BC7568 is 0x0008619F, the rowed
// W3DView::worldToScreenTriReturn. Earlier slots are opaque in this view.
struct Coord3D;
struct ICoord2D;

class View
{
public:
	enum WorldToScreenReturn
	{
		WTS_INSIDE_FRUSTUM = 0,
		WTS_OUTSIDE_FRUSTUM,
		WTS_INVALID,
		WTS_COUNT
	};

#define SLOT(N) virtual void slot##N();
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
	SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31)
	SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
	SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47)
	SLOT(48) SLOT(49) SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54) SLOT(55)
	SLOT(56) SLOT(57) SLOT(58) SLOT(59) SLOT(60) SLOT(61) SLOT(62) SLOT(63)
	SLOT(64) SLOT(65) SLOT(66) SLOT(67) SLOT(68) SLOT(69) SLOT(70) SLOT(71)
	SLOT(72) SLOT(73) SLOT(74) SLOT(75) SLOT(76) SLOT(77) SLOT(78) SLOT(79)
	SLOT(80) SLOT(81) SLOT(82) SLOT(83) SLOT(84) SLOT(85) SLOT(86) SLOT(87)
#undef SLOT
	virtual WorldToScreenReturn worldToScreenTriReturn( const Coord3D *w, ICoord2D *s );	// slot 88

	bool worldToScreen( const Coord3D *w, ICoord2D *s );
};

// ?worldToScreen@View@@QAE_NPBUCoord3D@@PAUICoord2D@@@Z
bool View::worldToScreen( const Coord3D *w, ICoord2D *s )
{
	return worldToScreenTriReturn( w, s ) == WTS_INSIDE_FRUSTUM;
}
