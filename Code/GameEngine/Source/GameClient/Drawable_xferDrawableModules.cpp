// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?xferDrawableModules@Drawable@@QAEXPAVXfer@@@Z, retail 0x002786D9, 400 bytes.
// Drawable xferDrawableModules: version via rowed Version1 0x000053EE then
// IsStoring then UShort count at +0x14C array (3 types) then per-module
// keyToName/nameToKey via TheNameKeyGenerator plus DrawableModule
// begin/end/skip via Xfer slots 0x14/0x18/0x1C plus snapshot via 0x30
// plus AsciiString via 0x6C plus UShort via 0x80. Evidence: same +0x14C
// walk as landed Drawable_rva00278689 0x00278689 and Drawable_rva002724FD
// 0x002724FD; string literal DrawableModule; callers 0x0027A729 0x0027AFD8
// in FUN_0067a219; donor BFME1 DrawableXferDrawableModules.
#include "ascii_string.h"

typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class ModuleData
{
public:
	NameKeyType getModuleTagNameKey() const { return m_moduleTagNameKey; }
private:
	void *m_vtable;
	NameKeyType m_moduleTagNameKey;
};

#include "../../Include/Common/Module.h"

// Access to the existing +4 data pointer; no additional state or helper body.
class Rva002786D9ModuleDataAccess : public Module
{
public:
    using Module::getModuleData;
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
	NameKeyType nameToKey(const AsciiString &name);
	const AsciiString &keyToName(NameKeyType key);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
struct RealRange;
struct RGBColor;
struct RGBAColorReal;
struct RGBAColorInt;
#include "../../Include/Common/BfmeXfer.h"

class Drawable
{
public:
	void xferDrawableModules(Xfer *xfer);
private:
	unsigned char m_opaque[0x14C];
	Module **m_modules[3];
};

void Drawable::xferDrawableModules(Xfer *xfer)
{
	xfer->Version1();
	xfer->IsStoring();
	UnsignedShort moduleTypes = 3;
	*xfer == moduleTypes;
	AsciiString moduleIdentifier;
	for (UnsignedShort curModuleType = 0; curModuleType < moduleTypes; ++curModuleType) {
		Module **m;
		UnsignedShort moduleCount = 0;
		for (m = m_modules[curModuleType]; m && *m; ++m)
			++moduleCount;
		*xfer == moduleCount;
		if (xfer->IsStoring()) {
			for (m = m_modules[curModuleType]; m && *m; ++m) {
				moduleIdentifier = TheNameKeyGenerator->keyToName(((Rva002786D9ModuleDataAccess *)(*m))->getModuleData()->getModuleTagNameKey());
				*xfer == moduleIdentifier;
				xfer->BeginBlock("DrawableModule");
				*xfer == *(Snapshot *)(*m);
				xfer->EndBlock();
			}
		} else {
			for (UnsignedShort j = 0; j < moduleCount; ++j) {
				*xfer == moduleIdentifier;
				NameKeyType moduleIdentifierKey = TheNameKeyGenerator->nameToKey(moduleIdentifier);
				Module *module = 0;
				for (Module **mm = m_modules[curModuleType]; mm && *mm; ++mm) {
					if (moduleIdentifierKey == ((Rva002786D9ModuleDataAccess *)(*mm))->getModuleData()->getModuleTagNameKey()) {
						module = *mm;
						break;
					}
				}
				if (module == 0) {
					xfer->SkipBlock("DrawableModule");
				} else {
					xfer->BeginBlock("DrawableModule");
					*xfer == *(Snapshot *)module;
					xfer->EndBlock();
				}
			}
		}
	}
}
