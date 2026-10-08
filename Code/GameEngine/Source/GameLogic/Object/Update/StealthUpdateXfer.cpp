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
// Xfer declaration and template round-trip idiom verbatim from
// SpawnBehaviorXfer.cpp (xferVersion slot 0x28, IsLoading slot 0x4,
// IsLightCRC slot 0x10, xferAsciiString 0x6c, xferUnsignedInt 0x78,
// xferInt 0x7c, xferBool 0x90).

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
	unsigned short m_pad;
};

struct XferException
{
	char *text;
	int tag;
};

#include "ascii_string.h"

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08();
	virtual void slot09();

	virtual Xfer &xferVersion(XferVersion *version);

	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;

	virtual Xfer &xferAsciiString(AsciiString &value);

	virtual void slot28() = 0;
	virtual void slot29() = 0;

	virtual Xfer &xferUnsignedInt(UnsignedInt &value);
	virtual Xfer &xferInt(int &value);

	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;

	virtual Xfer &xferBool(bool &value);
};

extern "C" XferException *__cdecl bfmeFormatText(
	XferException *result, int tag, const char *format, ...);
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
extern int g_rva008ffd18ThrowInfo;

class Thing;
class ModuleData;
class Object;
class ThingTemplate;

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};

extern class ThingFactory *TheThingFactory;

class ThingTemplate
{
public:
	unsigned char m_pad[0x64];
	AsciiString m_name;
};

class UpdateModule
{
public:
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

private:
	unsigned char m_pad[0x1C];
};

class StealthUpdate : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_stealthAllowedFrame; // +0x20
	unsigned int m_detectionExpiresFrame; // +0x24
	unsigned int m_framesGranted; // +0x28, version >= 2 (donor's version>=2 member)
	int m_2c; // +0x2C, version >= 3 (BFME2-new)
	bool m_enabled; // +0x30
	bool m_31; // +0x31 (BFME2-new)
	bool m_32; // +0x32 (BFME2-new)
	bool m_33; // +0x33 (BFME2-new)
	bool m_34; // +0x34 (BFME2-new)
	unsigned char m_pad35[3];
	int m_disguiseAsPlayerIndex; // +0x38
	const ThingTemplate *m_disguiseAsTemplate; // +0x3C
	unsigned int m_disguiseTransitionFrames; // +0x40
	bool m_disguiseHalfpointReached; // +0x44
	bool m_transitioningToDisguise; // +0x45
	bool m_disguised; // +0x46
	unsigned char m_pad47[1];
	unsigned char m_pad48[0x100]; // +0x48..+0x147 (upgrade masks etc, not xfer'd)
	bool m_148; // +0x148, version >= 4 (BFME2-new)
};

void StealthUpdate::xfer(Xfer *xfer)
{
	XferException error;
	UpdateModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 4;
	xfer->xferVersion(&version);
	xfer->xferUnsignedInt(m_stealthAllowedFrame);
	xfer->xferUnsignedInt(m_detectionExpiresFrame);
	if (version.m_currentVersion >= 2)
		xfer->xferUnsignedInt(m_framesGranted);
	xfer->xferBool(m_enabled);
	xfer->xferInt(m_disguiseAsPlayerIndex);
	AsciiString tmp = m_disguiseAsTemplate ? m_disguiseAsTemplate->m_name : AsciiString::TheEmptyString;
	xfer->xferAsciiString(tmp);
	if (xfer->IsLoading()) {
		m_disguiseAsTemplate = NULL;
		if (!tmp.isEmpty()) {
			m_disguiseAsTemplate = (const ThingTemplate *)((Rva002D06CA *)TheThingFactory)->rva002D06CA(&tmp);
			if (m_disguiseAsTemplate == NULL) {
				bfmeFormatText(&error, 5, 0);
				_CxxThrowException(&error, (const _s__ThrowInfo *)&g_rva008ffd18ThrowInfo); __assume(0);
			}
		}
	}
	xfer->xferUnsignedInt(m_disguiseTransitionFrames);
	xfer->xferBool(m_disguiseHalfpointReached);
	xfer->xferBool(m_transitioningToDisguise);
	xfer->xferBool(m_disguised);
	xfer->xferBool(m_34);
	xfer->xferBool(m_32);
	xfer->xferBool(m_33);
	xfer->xferBool(m_31);
	if (version.m_currentVersion >= 3)
		xfer->xferInt(m_2c);
	if (version.m_currentVersion >= 4)
		xfer->xferBool(m_148);
}
// ?g_rva008ffd18ThrowInfo@@3HA: the global at VA 0xcffd18 is ?g_guardTargetTypeThrowInfo@@3HA.
#pragma comment(linker, "/alternatename:?g_rva008ffd18ThrowInfo@@3HA=?g_guardTargetTypeThrowInfo@@3HA")
