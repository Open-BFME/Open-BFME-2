// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?findTemplate@ParticleSystemManager@@QBEPAVParticleSystemTemplate@@ABVAsciiString@@@Z
// retail 0x001F90DA (43B). Zero Hour ParticleSys.cpp:
//   ParticleSystemTemplate *sysTemplate = NULL;
//   TemplateMap::const_iterator find(m_templateMap.find(name));
//   if (find != m_templateMap.end()) sysTemplate = (*find).second;
//   return sysTemplate;
// The template map sits at +0x88 and is the Rva00056F61 bucket table whose
// iterator find (0x0041534B) is rowed; retail tests the iterator's node
// rather than comparing with end(), as the rowed sibling lookups
// (Rva0021311FGet.cpp) do. Evidence: symbols.csv pin (INI::
// parseParticleSystemTemplate's call at 0x003395BB); 8 units call it.
#include "ascii_string.h"

class Rva00056F61;
struct Rva0041534BIter
{
	void *m_node;
	Rva00056F61 *m_table;
};
class Rva00056F61
{
public:
	Rva0041534BIter rva0041534B(const AsciiString *key);
};

class ParticleSystemTemplate;

class ParticleSystemManager
{
public:
	ParticleSystemTemplate *findTemplate(const AsciiString &name) const;

private:
	char m_pad[0x88];
	Rva00056F61 m_templateMap;	// +0x88
};

ParticleSystemTemplate *ParticleSystemManager::findTemplate(const AsciiString &name) const
{
	ParticleSystemTemplate *sysTemplate = 0;
	Rva0041534BIter find = const_cast<Rva00056F61 &>(m_templateMap).rva0041534B(&name);
	if (find.m_node != 0)
		sysTemplate = *(ParticleSystemTemplate **)((char *)find.m_node + 8);
	return sysTemplate;
}
