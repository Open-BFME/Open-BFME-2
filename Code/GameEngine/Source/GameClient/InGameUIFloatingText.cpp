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
// the default timeout is the logic frame rate BfmeClientFramesPerSecond / 3 and a configured
// timeout at +0x8A4 is scaled by BfmeClientFramesPerMillisecond in floating point. The list at
// +0x8A0 takes the record through the folded four-byte push_front 0x00392076.
#include <list>
#include "unicode_string.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"
#include "../Common/GameLogicObjectLookupView.h"

typedef int Color;

#include "../../Include/GameClient/DisplayString.h"

#include "../../Include/GameClient/DisplayStringManager.h"

extern DisplayStringManager *TheDisplayStringManager;

class ClientFrameSubsystem;
extern class GameClient *TheGameClient;

#include "../../Include/GameClient/GameClientClass.h"

extern GameLogic *TheGameLogic;
extern int BfmeClientFramesPerSecond;
extern float BfmeClientFramesPerMillisecond;

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

#include "../../Include/GameClient/InGameUI.h"

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

// ?addFloatingText@InGameUI@@UAEXABVUnicodeString@@PBUCoord3D@@H@Z
void InGameUI::addFloatingText( const UnicodeString &text, const Coord3D *pos, Color color )
{
	if( TheGameLogic->getDrawIconUI() )
	{
		FloatingTextData *newFTD = new FloatingTextData;
		newFTD->m_frameCount = 0;
		newFTD->m_color = color;
		newFTD->m_pos3D.x = pos->x;
		newFTD->m_pos3D.z = pos->z;
		newFTD->m_pos3D.y = pos->y;
		newFTD->m_text = text;
		newFTD->m_dString->setText( text );

		if( m_floatingTextTimeOut <= 0 )
			newFTD->m_frameTimeOut = TheGameClient->getFrame() + BfmeClientFramesPerSecond / 3;
		else
			newFTD->m_frameTimeOut = TheGameClient->getFrame() + BfmeClientFramesPerMillisecond * m_floatingTextTimeOut;

		m_floatingTextList.push_front( newFTD );
	}
}
