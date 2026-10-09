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
// set 0x000366F0). Map iteration uses the shared rts::hash<AsciiString>
// begin 0x00427195 and increment 0x00411084 (named here through the
// Rva00409FFA instantiation like ControlBarReloadNotice.cpp). Other callees:
// getTextureFilename 0x0000261E and StringBase isEmpty 0x00001E2F
// removeLastChar 0x00036C50 releaseBuffer 0x00036410. WorldBuilder twin
// 0x00B176C0 (vtable evidence).

#include "ascii_string.h"
#include <hash_map>

// Retail schedules no unwind state around the temporary filename that only
// isEmpty touches, as for a non-throwing callee (ScriptEngineExecuteScript.cpp
// declares the same specialisation).
template <> bool StringBase<char>::isEmpty() const throw();

namespace rts
{
template <class T> struct hash
{
	unsigned int operator()(T value) const;
};
}

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

// The map's values are template pointers; the shared iterator bodies are
// named through the existing Rva00409FFA instantiation.
class Rva00409FFA;
typedef _STL::hash_map<AsciiString, Rva00409FFA *, rts::hash<AsciiString>,
	_STL::equal_to<AsciiString> > ParticleTemplateMap;

// BFME1 ba7ddda7 supplies the parent-search algorithm. Target findTemplate
// proves map +88; the native comparison reads SlaveSystemName at template +68.
// This view asserts only the observed prefix, not a complete class size.
class ParticleSystemTemplate
{
public:
	char m_prefix[0x68];
	AsciiString m_slaveSystemName;
};

class ParticleSystemManager
{
public:
	virtual void rva001F9F66();
	ParticleSystemTemplate *findParentTemplate(const AsciiString &name, int parentNum) const;
private:
	char m_pad04[0x88 - 0x04];
	ParticleTemplateMap m_templateMap; // +0x88
};

void ParticleSystemManager::rva001F9F66()
{
	for (ParticleTemplateMap::iterator it = m_templateMap.begin(); it != m_templateMap.end(); ++it)
	{
		FXParticleSystem::ParticleSystemTemplate *tmpl = (FXParticleSystem::ParticleSystemTemplate *)(*it).second;
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
// the already established ICF providers 427195/411084, as rva001F9F66 does.
ParticleSystemTemplate *ParticleSystemManager::findParentTemplate(const AsciiString &name, int parentNum) const
{
	if (((const StringBase<char> *)&name)->isEmpty())
		return 0;
	ParticleTemplateMap &templates = const_cast<ParticleTemplateMap &>(m_templateMap);
	ParticleTemplateMap::iterator begin(templates.begin()), end(templates.end());
	for (; begin != end; ++begin)
	{
		ParticleSystemTemplate *tmpl = (ParticleSystemTemplate *)(*begin).second;
		if (name.compare(tmpl->m_slaveSystemName) == 0 && !parentNum--)
			return tmpl;
	}
	return 0;
}
