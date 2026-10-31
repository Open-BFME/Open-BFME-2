// cl: /DNDEBUG /MD
//
// ?rva00278689@Drawable@@QAE_NABVAsciiString@@_N1@Z, retail 0x00278689, 80 bytes.
// Drawable find-DrawModule-by-tag via TheNameKeyGenerator, matching the +0x14C
// walk of landed Drawable_rva002724FD 0x002724FD. Evidence: same +0x14C array,
// same callers (lua CurDrawableShow/HideSubObject 0x00333424/0x003334EA,
// ObjectHideSubObjectPermanently 0x00334AF3, vector 0x004B4EC3/0x004B4F11);
// key compare is DrawModule+4 -> ModuleData+4 tag; found path calls DrawModule
// slots 0x48 then 0x40, returns bool.

#include "../../Include/GameClient/DrawableBFME2.h"
#include "DrawableFieldsView.h"
enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class AsciiString;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
	NameKeyType nameToKey(const AsciiString &name);
	const AsciiString &keyToName(NameKeyType key);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class ModuleData
{
public:
	NameKeyType getModuleTagNameKey() const { return m_moduleTagNameKey; }
private:
	void *m_vtable;
	NameKeyType m_moduleTagNameKey;
};


bool Drawable::rva00278689(const AsciiString &name, bool a2, bool a3)
{
	NameKeyType key = TheNameKeyGenerator->nameToKey(name);
	DrawModule **modules = *reinterpret_cast<DrawModule ***>((unsigned char *)this + 0x14C);
	for (DrawModule **dm = modules; *dm; ++dm) {
		DrawModule *drawModule = *dm;
		if (key == drawModule->m_moduleData->getModuleTagNameKey()) {
			drawModule->slot48(a3);
			drawModule->slot40(a2 == 0);
			return true;
		}
	}
	return false;
}
