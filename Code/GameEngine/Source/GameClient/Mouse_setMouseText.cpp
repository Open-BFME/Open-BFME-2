// cl: /FIzh_ascii.h /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2_ascii_common /Ireference/open-bfme-1/reference/shims/ini /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/shims/sweep
// stlport

#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"
#define __SUBSYSTEMINTERFACE_H_
class SubsystemInterfaceList;
#include "PreRTS.h"
#include "../../../../reference/shims/bfme2_mouse/GameClient/Mouse.h"
// ?setMouseText@Mouse@@QAEXVUnicodeString@@PBU_MouseSixteen@@1@Z, retail 0x001EEBD5, 118 bytes.
// Zero Hour's and BFME1's Mouse::setMouseText (BFME1 0x005A5950, same
// signature; the text goes to the cursor display string, then the optional
// colour and drop colour are copied). Evidence: Mouse neighbours
// (same /O1 area, +0x4Fxx offsets near rva001EEA6D); by-value wide-string temp
// via rowed private StringBase<G> copyctor plus rowed releaseBuffer EH
// cleanup (GadgetStaticText/MouseRva001EEC4B friend pattern); virtual slot 1
// on +0x4FA8; guarded 16-byte copies into +0x4FAC/+0x4FBC.
class Mouse;
#include "unicode_string.h"
struct MouseFontThunk {
    virtual void slot0();
    virtual void setText(UnicodeString text);
};
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
void Mouse::setMouseText(UnicodeString text, const RGBAColorInt *lhs, const RGBAColorInt *rhs)
{
    if (m_cursorTextDisplayString) {
        _ReadWriteBarrier();
        reinterpret_cast<MouseFontThunk *>(m_cursorTextDisplayString)->setText(text);
        if (lhs)
            m_cursorTextColor = *lhs;
        if (rhs)
            m_cursorTextDropColor = *rhs;
    }
}
