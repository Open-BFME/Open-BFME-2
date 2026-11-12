// cl: /Ireference/shims/bfme2_ascii /EHsc
#define _DLL
#include <string.h>

// Retail 0x0060C0A0 288B vtable slot 25 (offset 0x64) of 0x007BB910 (class of
// ??1Xfer@@UAE@XZ). Xfer::operator==(PooledString&) via astr tag 0x61737472,
// strlen 0x629170, AsciiString temp with getBufferForRead 0x36640 and
// releaseBuffer 0x36410, PooledString::operator=(AsciiString) 0x60BE7F.
// Evidence: slot order Ascii 27 / Unicode 26 / Pooled 25 (reverse overload
// order); callers: PooledString assign caller at 0x60C19C; donor:
// XferAsciiStringTransfer.cpp logic with PooledString strlen/getLength.

#include "../../../../Libraries/Include/Lib/Coord3DBase.h"

#include "../../../../Libraries/Include/Lib/ICoord3D.h"

#include "../../../../Libraries/Include/Lib/Coord2D.h"

#include "../../../../Libraries/Include/Lib/ICoord2D.h"

#include "../../../../Libraries/Include/Lib/Region3D.h"

struct IRegion3D
{
    ICoord3D lo;
    ICoord3D hi;
};

#include "../../../../Libraries/Include/Lib/Region2D.h"

#include "../../../../Libraries/Include/Lib/IRegion2D.h"

struct RealRange
{
    float lo;
    float hi;
};

#include "../../../../Libraries/Include/Lib/RGBColor.h"

struct RGBAColorReal
{
    float red;
    float green;
    float blue;
    float alpha;
};

#include "../../../Include/Common/RGBAColorInt.h"

class Xfer;

#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;

#include "ascii_string.h"


#include "unicode_string.h"

struct PooledStringEntry
{
    void *m_unknown0;
    PooledStringEntry *m_noCase;
    char m_text[1];
};

class PooledString
{
public:
    PooledString &operator=(const AsciiString &that);
    const char *str() const { return m_entry->m_text; }

    PooledStringEntry *m_entry;
};

#include "../../../Include/Common/BfmeXfer.h"

Xfer &Xfer::operator==(PooledString &ps)
{
    if (IsStoring())
    {
        int length = (int)strlen(ps.m_entry->m_text);
        if (length >= 255)
        {
            unsigned char marker = 255;
            XferData(0x61737472, &marker, 1);
            XferData(0, &length, 4);
        }
        else
        {
            XferData(0x61737472, &length, 1);
        }
        XferData(0, (void *)ps.str(), length);
    }
    else
    {
        AsciiString temp;
        int length = 0;
        XferData(0x61737472, &length, 1);
        if (length == 255)
        {
            XferData(0, &length, 4);
        }
        if (length != 0)
        {
            XferData(0, ((StringBase<char> *)&temp)->getBufferForRead(length), length);
            ((StringBase<char> *)&temp)->getBufferForRead(length)[length] = 0;
        }
        else
        {
            temp.clear();
        }
        ps = temp;
    }
    return *this;
}
