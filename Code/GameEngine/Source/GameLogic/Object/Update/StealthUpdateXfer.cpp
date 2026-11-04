// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
//
// ?xfer@StealthUpdate@@MAEXPAVXfer@@@Z, retail 0x00374942, 422 bytes.
// Slot 3 (offset 0x0C) of vtable 0x00817F20 (class of ??1Rva00373CB1).
// Evidence: neighbours StealthUpdateUpgradeMasks.cpp (0x003748BD) and
// StealthUpdateLoadPost.cpp (0x00374AE8) share the class; ZH donor is
// StealthUpdate::xfer (xferVersion plus base plus uint/bool/int members plus
// AsciiString template round-trip through TheThingFactory with FormatText
// plus Throw). BFME2 bumps the version to (1,4): uint at +0x28 gated >=2 is
// m_framesGranted (donor's version>=2 member), int at +0x2C gated >=3 and
// bool at +0x148 gated >=4 are BFME2-new versioned fields; the four bools at
// +0x31..+0x34 are BFME2-new ungated members. Floats (pulse) are not xfer'd.
// Template round-trip idiom from SpawnBehaviorXfer.cpp. The canonical Xfer
// overloads retain Version slot 0x28, IsLoading slot 0x4, IsLightCRC slot
// 0x10, AsciiString 0x6c, unsigned int 0x78, int 0x7c and bool 0x90.

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
	unsigned short m_pad;
};

#include "../../../../Include/Common/XferException.h"

#include "ascii_string.h"

#include "UpdateXferTypes.h"
#include "../../../../Include/Common/BfmeXfer.h"


class Thing;
class ModuleData;
class Object;
class ThingTemplate;

#include "../../../../Include/Common/ThingFactory.h"

extern class ThingFactory *TheThingFactory;

#include "../../../../Include/Common/ThingTemplate.h"

#include "../../../../Include/GameLogic/Module/UpdateModule.h"

#include "../../../../Include/GameLogic/Module/StealthUpdate.h"

void StealthUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 4;
	*xfer == *reinterpret_cast<Xfer::Version *>(&version);
	*xfer == m_stealthAllowedFrame;
	*xfer == m_detectionExpiresFrame;
	if (version.m_currentVersion >= 2)
		*xfer == m_framesGranted;
	*xfer == m_enabled;
	*xfer == m_disguiseAsPlayerIndex;
	AsciiString tmp = m_disguiseAsTemplate ? m_disguiseAsTemplate->m_nameString : AsciiString::TheEmptyString;
	*xfer == tmp;
	if (xfer->IsLoading()) {
		m_disguiseAsTemplate = NULL;
		if (!tmp.isEmpty()) {
			m_disguiseAsTemplate = TheThingFactory->findTemplate(tmp);
			if (m_disguiseAsTemplate == NULL) {
				throw XferException(5, 0);
			}
		}
	}
	*xfer == m_disguiseTransitionFrames;
	*xfer == m_disguiseHalfpointReached;
	*xfer == m_transitioningToDisguise;
	*xfer == m_disguised;
	*xfer == m_field34;
	*xfer == m_field32;
	*xfer == m_field33;
	*xfer == m_field31;
	if (version.m_currentVersion >= 3)
		*xfer == m_field2C;
	if (version.m_currentVersion >= 4)
		*xfer == m_field148;
}
