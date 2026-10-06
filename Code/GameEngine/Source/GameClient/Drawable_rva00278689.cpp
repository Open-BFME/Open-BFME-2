// cl: /DNDEBUG /MD
//
// ?rva00278689@Drawable@@QAE_NABVAsciiString@@_N1@Z, retail 0x00278689, 80 bytes.
// Drawable find-DrawModule-by-tag via TheNameKeyGenerator, matching the +0x14C
// walk of landed Drawable_rva002724FD 0x002724FD. Evidence: same +0x14C array,
// same callers (lua CurDrawableShow/HideSubObject 0x00333424/0x003334EA,
// ObjectHideSubObjectPermanently 0x00334AF3, vector 0x004B4EC3/0x004B4F11);
// key compare is DrawModule+4 -> ModuleData+4 tag; found path calls DrawModule
// slots 0x48 then 0x40, returns bool.

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class AsciiString;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

struct ModuleData
{
	virtual void slot00() = 0;
	NameKeyType m_tagKey;
};

class DrawModule
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40(bool b) = 0;
	virtual void slot44() = 0;
	virtual void slot48(bool b) = 0;
	ModuleData *m_moduleData;
};

class Drawable
{
public:
	bool rva00278689(const AsciiString &name, bool a2, bool a3);
};

bool Drawable::rva00278689(const AsciiString &name, bool a2, bool a3)
{
	NameKeyType key = TheNameKeyGenerator->nameToKey(name);
	DrawModule **modules = *reinterpret_cast<DrawModule ***>((unsigned char *)this + 0x14C);
	for (DrawModule **dm = modules; *dm; ++dm) {
		DrawModule *m = *dm;
		if (key == m->m_moduleData->m_tagKey) {
			m->slot48(a3);
			m->slot40(a2 == 0);
			return true;
		}
	}
	return false;
}
