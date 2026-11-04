// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// ?drawLine@W3DDisplay@@UAEXMMMMMK@Z @0x000448CF 89B: BFME1's W3DDisplay::drawLine
// (x1, y1, x2, y2, width, color) at 0x006E9B90 has the same shape (clear the
// Render2D flag, Add_Line, ret 0x18); the two-color drawLine below likewise
// matches BFME1 0x006E9C00 (ClipLine2D then Add_Line).
// Render2D line wrapper reusing the target-proven W3DDisplay +0x168
// Render2D view (same as W3DDisplay::setWidth): clears the +0x48 byte in the
// Render2D member, then forwards two Vector2 temps plus width/color to the
// pinned Add_Line 0x00042A4D. Push order (color, width via fld/fstp dummy,
// two Vector2 temps) and movss temps prove the (x1,y1,x2,y2,width,color)
// shape; ret 0x18 proves six stack args. Address-derived name; offsets are
// target facts, Render2D +0x48 flag label descriptive. No header edits.
typedef unsigned long uint32;

#include "../../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../../Libraries/Include/Lib/IRegion2D.h"
bool ClipLine2D(ICoord2D *start,ICoord2D *end,ICoord2D *returnStart,ICoord2D *returnEnd,IRegion2D *region);

#include "../../../../../reference/shims/wwmath/Vector2.h"

#include "../../../../Libraries/Source/WWVegas/WW3D2/Render2DClass.h"

#include "../../../../GameEngine/Include/GameClient/Display.h"

class W3DDisplay : public Display
{
public:
	virtual void drawLine(float x1, float y1, float x2, float y2, float width, uint32 color);
	virtual void drawLine(float x1, float y1, float endX, float endY, float width, uint32 color0, uint32 color1);
private:
	char m_pad144[0x168 - 0x144];
	Render2DClass *m_render2D;
	IRegion2D m_clipRegion; // native +0x16C
	bool m_isClippedEnabled; // native +0x17C
};

void W3DDisplay::drawLine(float x1, float y1, float x2, float y2, float width, uint32 color)
{
	Render2DClass *rdClear = m_render2D;
	rdClear->m_flag48 = 0;
	Render2DClass *rd = m_render2D;
	rd->Add_Line(Vector2(x1, y1), Vector2(x2, y2), width, color);
}

// Native00044928..00044A1A RET1C: same measured receiver and +0x168
// renderer as the preceding 89-byte wrapper, but optionally clips through
// rowed ClipLine2D00025F406 and forwards two endpoint colours. Semantic lead
// is BFME1/ZH W3DDisplay::drawLine (two colours) plus drawOpenRect's clipping
// pattern, at BFME1 ba7ddda7e8. Target coordinates are floats, unlike the
// donor's integer overload; BFME1's ledger now rows this float overload as
// ?drawLine@W3DDisplay@@UAEXMMMMMKK@Z (0x006E9C00, matched).
void W3DDisplay::drawLine(float x1, float y1, float endX, float endY, float width, uint32 color0, uint32 color1)
{
    m_render2D->m_flag48 = 0;
    if (m_isClippedEnabled) {
        ICoord2D start,end,returnStart,returnEnd;
        start.x=(int)x1; start.y=(int)y1;
        end.x=(int)endX; end.y=(int)endY;
        if (ClipLine2D(&start,&end,&returnStart,&returnEnd,&m_clipRegion))
            m_render2D->Add_Line(Vector2((float)returnStart.x,(float)returnStart.y),
                                Vector2((float)returnEnd.x,(float)returnEnd.y),
                                width,color0,color1);
    } else {
        m_render2D->Add_Line(Vector2(x1,y1),Vector2(endX,endY),width,color0,color1);
    }
}
