// ?setCursorDirection@W3DMouse@@AAEXW4MouseCursor@Mouse@@@Z
// Verified native245B; canonical coordinate layout and ordered8B snapshot.
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
//
// ?setCursorDirection@W3DMouse@@AAEXW4MouseCursor@Mouse@@@Z, retail 0x0009910E, 245 bytes.
// Zero Hour's W3DMouse::setCursorDirection. It sits between W3DMouse::init's
// slot (0x00099109) and initPolygonAssets (0x0009921F), reads the cursor's
// numDirections from m_cursorInfo (+0x0C, stride 0x54, field +0x50), asks
// TheInGameUI whether it is scrolling (slot 42, +0xA8) and for the scroll
// amount (slot 46, +0xB8), and stores the frame in Win32Mouse's
// m_directionFrame at +0x601C, the field Win32Mouse::setCursor 0x00041A83
// indexes cursorResources with. m_currentCursor is +0x4FA4 as in
// Mouse::setCursor 0x001EEFD2.

// math.h's x86 plain-inline float wrappers would emit a TU-local _atan2f
// COMDAT that loses to the retail home copy (Rva000422A0 owns _atan2f).
// Rename it away so this TU's out-of-line call binds the home copy.
#define atan2f bfmeMathUnusedAtan2f
#include <math.h>
#undef atan2f

extern "C" float __cdecl atan2f( float y, float x );

typedef int Int;
typedef float Real;
typedef bool Bool;

#define M_PI 3.14159265358979323846

#include "../../../../Libraries/Include/Lib/Coord2D.h"

static __forceinline void copyScroll(Coord2D &out,const Coord2D &in) {
    *reinterpret_cast<unsigned __int64 *>(&out)=*reinterpret_cast<const volatile unsigned __int64 *>(&in);
}
class InGameUI
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41();
	virtual Bool isScrolling( void );					// slot 42 (+0xA8)
	virtual void slot43(); virtual void slot44(); virtual void slot45();
	virtual Coord2D getScrollAmount( void );			// slot 46 (+0xB8)
};
extern InGameUI *TheInGameUI;

struct CursorInfo
{
	char m_pad[0x50];
	Int numDirections;
};

class Mouse
{
public:
	enum MouseCursor
	{
		NONE = 0
	};

protected:
	void *m_vtable;
	char m_pad004[0x0C - 4];
	CursorInfo m_cursorInfo[0x38];
	char m_pad126C[0x4FA4 - 0x126C];
	MouseCursor m_currentCursor;
	char m_pad4FA8[0x601C - 0x4FA8];
};

class Win32Mouse : public Mouse
{
protected:
	Int m_directionFrame;
};

class W3DMouse : public Win32Mouse
{
private:
	void setCursorDirection( MouseCursor cursor );
};

//-------------------------------------------------------------------------------------------------
/** Pick the predrawn frame of a directional cursor that best matches the scroll direction */
//-------------------------------------------------------------------------------------------------
void W3DMouse::setCursorDirection(MouseCursor cursor)
{
	Coord2D offset;
	//Check if we have a directional cursor that needs different images for each direction on screen
	if (m_cursorInfo[cursor].numDirections > 1 && TheInGameUI && TheInGameUI->isScrolling())
	{
		copyScroll(offset, TheInGameUI->getScrollAmount());
		if (offset.x || offset.y)
		{
			offset.normalize();
			Real theta = atan2f(offset.y, offset.x);
			theta = fmod(theta+M_PI*2,M_PI*2);
			Int numDirections=m_cursorInfo[m_currentCursor].numDirections;
			//Figure out which of our predrawn cursor orientations best matches the
			//actual cursor direction.  Frame 0 is assumed to point right and continue
			//clockwise.
			m_directionFrame=(Int)(theta/(2.0f*M_PI/(Real)numDirections)+0.5f);
			if (m_directionFrame >= numDirections)
				m_directionFrame = 0;
		}
		else
		{
			m_directionFrame=0;
		}
	}
	else
		m_directionFrame=0;
}
