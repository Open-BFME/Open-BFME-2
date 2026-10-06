// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva002786D9@Drawable@@QAEXPAVXfer@@@Z, retail 0x002786D9, 400 bytes.
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

class Module
{
public:
	const ModuleData *getModuleData() const { return m_moduleData; }
	NameKeyType getModuleTagNameKey() const { return getModuleData()->getModuleTagNameKey(); }
private:
	void *m_vtable;
	const ModuleData *m_moduleData;
};

class NameKeyGenerator
{
public:
	const AsciiString &keyToName(NameKeyType key);
	NameKeyType nameToKey(const AsciiString &name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Xfer
{
public:
	Xfer();
	void Version1();
	virtual void slot00();
	virtual void slot01();
	virtual bool IsStoring() const;
	virtual void slot03();
	virtual void slot04();
	virtual int beginBlock(const char *name);
	virtual void endBlock();
	virtual void skipBlock(const char *name);
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(void *version);
	virtual void slot11();
	virtual void xferSnapshot(Module *module);
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slotExtra();
	virtual void xferAsciiString(AsciiString *value);
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void xferUnsignedShort(UnsignedShort *value);
};

class Drawable
{
public:
	void rva002786D9(Xfer *xfer);
private:
	unsigned char m_opaque[0x14C];
	Module **m_modules[3];
};

void Drawable::rva002786D9(Xfer *xfer)
{
	xfer->Version1();
	xfer->IsStoring();
	UnsignedShort moduleTypes = 3;
	xfer->xferUnsignedShort(&moduleTypes);
	AsciiString moduleIdentifier;
	for (UnsignedShort curModuleType = 0; curModuleType < moduleTypes; ++curModuleType) {
		Module **m;
		UnsignedShort moduleCount = 0;
		for (m = m_modules[curModuleType]; m && *m; ++m)
			++moduleCount;
		xfer->xferUnsignedShort(&moduleCount);
		if (xfer->IsStoring()) {
			for (m = m_modules[curModuleType]; m && *m; ++m) {
				moduleIdentifier = TheNameKeyGenerator->keyToName((*m)->getModuleTagNameKey());
				xfer->xferAsciiString(&moduleIdentifier);
				xfer->beginBlock("DrawableModule");
				xfer->xferSnapshot(*m);
				xfer->endBlock();
			}
		} else {
			for (UnsignedShort j = 0; j < moduleCount; ++j) {
				xfer->xferAsciiString(&moduleIdentifier);
				NameKeyType moduleIdentifierKey = TheNameKeyGenerator->nameToKey(moduleIdentifier);
				Module *module = 0;
				for (Module **mm = m_modules[curModuleType]; mm && *mm; ++mm) {
					if (moduleIdentifierKey == (*mm)->getModuleTagNameKey()) {
						module = *mm;
						break;
					}
				}
				if (module == 0) {
					xfer->skipBlock("DrawableModule");
				} else {
					xfer->beginBlock("DrawableModule");
					xfer->xferSnapshot(module);
					xfer->endBlock();
				}
			}
		}
	}
}
