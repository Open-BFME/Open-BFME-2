// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii
// stlport
//
// ?rva001F9F66@ParticleSystemManager@@UAEXXZ, retail 0x001F9F66 (229 bytes).
// Slot 23 of the FXParticleSystemManager vtable 0x007E18B8 (its slot 2 name
// getter 0x0004CE28 returns "FXParticleSystemManager"; slots 18 and 20-22
// are __purecall) and inherited unchanged by the derived vtable 0x007C4C70.
// Walks the AsciiString-keyed template map at +0x88 (the map findTemplate
// 0x001F90DA reads): every template whose particle type (+0x0C) is 1 and
// whose texture filename is not empty has the filename stripped of its last
// four characters and looked up in TheMappedImageCollection
// (findImageByName 0x002D92F6). A found image gives the template its UV
// rectangle (image +0x14 through the rowed setUV 0x00001278) and its
// texture filename (template +0x10 set from image +0x08 through StringBase
// set 0x000366F0). Map iteration uses the established cursor
// begin 0x00427195 and increment 0x00411084 providers. Other callees:
// getTextureFilename 0x0000261E and StringBase isEmpty 0x00001E2F
// removeLastChar 0x00036C50 releaseBuffer 0x00036410. WorldBuilder twin
// 0x00B176C0 (vtable evidence).

#include "ascii_string.h"


// Retail schedules no unwind state around the temporary filename that only
// isEmpty touches, as for a non-throwing callee (ScriptEngineExecuteScript.cpp
// declares the same specialisation).
template <> bool StringBase<char>::isEmpty() const throw();

struct Region2D
{
	float x_min;
	float y_min;
	float x_max;
	float y_max;
};

namespace FXParticleSystem
{
class ParticleSystemTemplate
{
public:
	int getParticleType() const { return m_particleType; }
	AsciiString getTextureFilename() const;
	void setUV(const Region2D *region);
	void setTextureFilenameInline(const AsciiString &name) { m_textureFilename = name; }
private:
	char m_pad00[0x0C];
	int m_particleType; // +0x0C
	AsciiString m_textureFilename; // +0x10
};
}

class Image
{
public:
	const AsciiString &getFilename() const { return m_filename; }
	const Region2D *getUV() const { return &m_UVCoords; }
private:
	char m_pad00[0x08];
	AsciiString m_filename; // +0x08
	char m_pad0C[0x14 - 0x0C];
	Region2D m_UVCoords; // +0x14
};

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern ImageCollection *TheMappedImageCollection;

// The map's values are template pointers; its cursor operations are
// accessed through established cursor-provider names, without emitting a
// competing STL iterator definition.
class Rva000411084
{
public:
	void *next();
	void *m_current;
	void *m_owner;
};
struct VideoPair
{
	struct { void *first; void *second; } s;
	VideoPair(void *a,void *b) { s.first=a;s.second=b; }
	VideoPair(const VideoPair &p) { s.first=p.s.first;s.second=p.s.second; }
};
inline VideoPair makePair(void *const &x,void *const &y) { return VideoPair(x,y); }
struct Rva0041534BIter { void *m_node; void *m_table; };
class Rva00056F61 { public: Rva0041534BIter rva0041534B(const AsciiString *); };
class Rva001F58D4 { public: void rva001F58D4(); };
class BFMERetailAsciiString;
class Rva000427195
{
public:
	void *first(Rva000411084 *iter);
	void rva003A37DC(VideoPair p);
};

// BFME1 ba7ddda7 supplies the parent-search algorithm. Target findTemplate
// proves map +88; the native comparison reads SlaveSystemName at template +68.
// The removal body independently proves its virtual destruction slot.
// This view asserts only the observed prefix, not a complete class size.
class ParticleSystemTemplate
{
public:
	virtual void *deleteInstance(int flags);
	char m_prefix[0x68 - 4];
	AsciiString m_slaveSystemName;
};

class ParticleSystemManager
{
public:
	virtual void rva001F9F66();
	void bfmeStopCW(const BFMERetailAsciiString &name);
	ParticleSystemTemplate *findParentTemplate(const AsciiString &name, int parentNum) const;
private:
	char m_pad04[0x88 - 0x04];
	char m_templateMap[0x14]; // +0x88; observed bucket table prefix
};

void ParticleSystemManager::rva001F9F66()
{
	Rva000411084 it;
	((Rva000427195 *)m_templateMap)->first(&it);
	for (; it.m_current; it.next())
	{
		FXParticleSystem::ParticleSystemTemplate *tmpl = *(FXParticleSystem::ParticleSystemTemplate **)((char *)it.m_current + 8);
		if (tmpl->getParticleType() == 1 && !((const StringBase<char> *)&tmpl->getTextureFilename())->isEmpty())
		{
			AsciiString name = tmpl->getTextureFilename();
			for (int i = 0; i < 4; ++i)
				name.removeLastChar();
			const Image *image = TheMappedImageCollection->findImageByName(name);
			if (image)
			{
				tmpl->setUV(image->getUV());
				tmpl->setTextureFilenameInline(image->getFilename());
			}
		}
	}
}

// Native 0x001F9F08..0x001F9F66, ret8 at 1F9F5F. Lookup compares the
// requested name against each template's slave name, selecting the numbered
// parent. The map is traversed without modifying it; a nonconst cursor names
// the established cursor providers 427195/411084, as rva001F9F66 does.
ParticleSystemTemplate *ParticleSystemManager::findParentTemplate(const AsciiString &name, int parentNum) const
{
	if (((const StringBase<char> *)&name)->isEmpty())
		return 0;
	Rva000411084 begin;
	((Rva000427195 *)m_templateMap)->first(&begin);
	for (; begin.m_current; begin.next())
	{
		ParticleSystemTemplate *tmpl = *(ParticleSystemTemplate **)((char *)begin.m_current + 8);
		if (name.compare(tmpl->m_slaveSystemName) == 0 && !parentNum--)
			return tmpl;
	}
	return 0;
}

// BFME1 ba7ddda7 ParticleSys.cpp supplies stop-CW behavior. Target caller
// 204C49 and native 1F9EAF..1F9F08 establish the template-map removal path:
// find41534B, reset1F58D4, virtual destruction without freeing (slot0, flag0),
// then operator delete2FD60 and the rowed by-value cursor erase3A37DC.
// VideoPair follows that provider's nontrivial two-word copy contract; the
// reference builder preserves the cursor words while constructing its value.
void ParticleSystemManager::bfmeStopCW(const BFMERetailAsciiString &name)
{
	Rva0041534BIter find = ((Rva00056F61 *)m_templateMap)->rva0041534B((const AsciiString *)&name);
	void *node = find.m_node;
	if (node == 0)
		return;
	((Rva001F58D4 *)this)->rva001F58D4();
	ParticleSystemTemplate *tmpl = *(ParticleSystemTemplate **)((char *)node + 8);
	::operator delete(tmpl ? tmpl->deleteInstance(0) : 0);
	((Rva000427195 *)m_templateMap)->rva003A37DC(makePair(node,find.m_table));
}
