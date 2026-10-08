// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
//
// InGameUI's floating text: the FloatingTextData record and
// InGameUI::addFloatingText (vftable 0x7FD410 slot 104).
// Donor: ZH GameEngine/Source/GameClient/InGameUI.cpp (FloatingTextData ctor,
// addFloatingText), same control flow.
// Target evidence for the layout: addFloatingText (0x002A0D19, ret 0xC) news
// 0x24 bytes (0x0002FDA0) and runs the ctor 0x0029D352 under unwind state 0,
// then writes the frame count at +0x20, the color at +4, the position at
// +0x10/+0x14/+0x18 (x, z, y order as in ZH), assigns the text at +8 (wide
// set 0x00037150) and passes a by-value copy (0x00037050) to slot 1 of the
// display string at +0xC. The ctor stores vftable 0x7FD1C0 (also stored by the
// rowed dtor 0x0029D3B0), clears the record, releases the text (0x00036E70)
// and takes the display string from TheDisplayStringManager slot 14.
// BFME 2 differences from ZH: the gate is TheGameLogic's byte at +0x9A
// (getDrawIconUI) but the frame comes from TheGameClient (slot 31, unsigned);
// the default timeout is the logic frame rate g_009BA4E8 / 3 and a configured
// timeout at +0x8A4 is scaled by g_00DBA500 in floating point. The list at
// +0x8A0 takes the record through the folded four-byte push_front 0x00392076.
#include <list>
#include "unicode_string.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"
#include "../Common/GameLogicObjectLookupView.h"

typedef int Color;

class DisplayString
{
public:
	virtual ~DisplayString();
	virtual void setText( UnicodeString text );	// slot 1
};

class DisplayStringManager
{
public:
#define SLOT(N) virtual void slot##N();
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13)
#undef SLOT
	virtual DisplayString *newDisplayString();	// slot 14
	virtual void freeDisplayString( DisplayString *string );	// slot 15
};

extern DisplayStringManager *TheDisplayStringManager;

class ClientFrameSubsystem;
extern class GameClient *TheGameClient;

class GameClient
{
public:
#define SLOT(N) virtual void slot##N();
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
	SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30)
#undef SLOT
	virtual unsigned int getFrame();	// slot 31
};

extern GameLogic *TheGameLogic;
extern int g_009BA4E8;
extern float g_00DBA500;

class FloatingTextData
{
public:
	FloatingTextData();
	virtual ~FloatingTextData();
	Color m_color;							// +0x04
	UnicodeString m_text;					// +0x08
	DisplayString *m_dString;				// +0x0C
	Coord3D m_pos3D;						// +0x10
	int m_frameTimeOut;						// +0x1C
	int m_frameCount;						// +0x20
};

typedef _STL::list<FloatingTextData *> FloatingTextList;

// ZH's Coord3D::zero(). Plain assignments let the scheduler hoist the int
// stores ahead of the unwind-state store; the inline call keeps retail's order.
inline void zeroCoord( Coord3D &c ) { c.x = 0.0f; c.y = 0.0f; c.z = 0.0f; }

class InGameUI
{
public:
	virtual ~InGameUI();
#define SLOT(N) virtual void slot##N();
	SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07) SLOT(08)
	SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16)
	SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24)
	SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31) SLOT(32)
	SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39) SLOT(40)
	SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47) SLOT(48)
	SLOT(49) SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54) SLOT(55) SLOT(56)
	SLOT(57) SLOT(58) SLOT(59) SLOT(60) SLOT(61) SLOT(62) SLOT(63) SLOT(64)
	SLOT(65) SLOT(66) SLOT(67) SLOT(68) SLOT(69) SLOT(70) SLOT(71) SLOT(72)
	SLOT(73) SLOT(74) SLOT(75) SLOT(76) SLOT(77) SLOT(78) SLOT(79) SLOT(80)
	SLOT(81) SLOT(82) SLOT(83) SLOT(84) SLOT(85) SLOT(86) SLOT(87) SLOT(88)
	SLOT(89) SLOT(90) SLOT(91) SLOT(92) SLOT(93) SLOT(94) SLOT(95) SLOT(96)
	SLOT(97) SLOT(98) SLOT(99) SLOT(100) SLOT(101) SLOT(102) SLOT(103)
#undef SLOT
	virtual void addFloatingText( const UnicodeString &text, const Coord3D *pos, Color color );	// slot 104

protected:
	char m_opaque004[0x8A0 - 0x4];
	FloatingTextList m_floatingTextList;	// +0x8A0
	float m_floatingTextTimeOut;			// +0x8A4
};

// ??0FloatingTextData@@QAE@XZ
FloatingTextData::FloatingTextData()
{
	m_color = 0;
	m_frameCount = 0;
	m_frameTimeOut = 0;
	zeroCoord( m_pos3D );
	m_text.clear();
	m_dString = TheDisplayStringManager->newDisplayString();
}
