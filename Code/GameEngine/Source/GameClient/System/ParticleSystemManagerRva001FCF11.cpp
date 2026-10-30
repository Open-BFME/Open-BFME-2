// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_MALLOC
// stlport
// ?rva001FCF11@ParticleSystemManager@@QAEXABVAsciiString@@PAVParticleSystemTemplate@FXParticleSystem@@@Z
// retail 0x001FCF11..0x001FD016 (261 bytes, EH, thiscall ret 8).
//
// Registers a particle-system template under a name (WB B16EC0's name-keyed
// template replacement/insert; BFME1 ParticleSys::newTemplate is the
// semantic guide; the vtable slot 0x00204316 calls it with a copied
// template). The template takes the name; when the name is already in the
// template map (+0x88, the bucket table whose find 0x0041534B is rowed) the
// stored template is destroyed in place and copy-constructed (rowed
// 0x001FCE6B) from the new one, which is then deleted; otherwise the pair
// is inserted (make_pair 0x0032ACCF, converting pair ctor 0x00466EA7, insert
// 0x001F93A3) and the template is deleted when the insert finds a duplicate.
// Both deletes are ::delete (vslot 0 with flag 0, then operator delete).
//
// Codegen: the find is defined here (never inlined; the row's own body).
// Seeing that it only writes its result lets cl give the converting pair
// temporary the iterator's slot ([ebp-0x14]) and keep retail's 0x1C frame.
#include "ascii_string.h"
#include <utility>
#include <new>

namespace FXParticleSystem
{
class ParticleSystemTemplate
{
public:
	ParticleSystemTemplate(const ParticleSystemTemplate &that);	// rowed 0x001FCE6B
	virtual ~ParticleSystemTemplate();

	char m_pad04[0x9C - 4];
	AsciiString m_name;	// +0x9C
	char m_tail[0x34];
};
}

struct Rva0041534BNode
{
	Rva0041534BNode *m_next;
	AsciiString m_name;
	FXParticleSystem::ParticleSystemTemplate *m_value;
};
class Rva00056F61;
struct Rva0041534BIter
{
	Rva0041534BNode *m_node;
	Rva00056F61 *m_table;
	Rva0041534BIter(Rva0041534BNode *n, Rva00056F61 *t) : m_node(n), m_table(t) {}
};
class Rva00056F61
{
public:
	void *rva00056F61(const AsciiString *key);
	__declspec(nothrow) __declspec(noinline) Rva0041534BIter rva0041534B(const AsciiString *key)
	{
		return Rva0041534BIter((Rva0041534BNode *)rva00056F61(key), this);
	}
};

struct InsertRet001F8F2A
{
	void *m_node;
	void *m_owner;
	unsigned char m_found;
};

typedef _STL::pair<const AsciiString, FXParticleSystem::ParticleSystemTemplate *> TemplateMapEntry;

class Rva000427195
{
public:
	InsertRet001F8F2A insertWithGrow(const void *key);
	InsertRet001F8F2A insert(const TemplateMapEntry &entry) { return insertWithGrow(&entry); }
};

class ParticleSystemManager
{
public:
	void rva001FCF11(const AsciiString &name, FXParticleSystem::ParticleSystemTemplate *system);

private:
	char m_pad[0x88];
	Rva00056F61 m_templateMap;	// +0x88
};

void ParticleSystemManager::rva001FCF11(const AsciiString &name, FXParticleSystem::ParticleSystemTemplate *system)
{
	if (system->m_name != name)
		system->m_name = name;
	Rva0041534BIter it = m_templateMap.rva0041534B(&name);
	if (it.m_node != 0)
	{
		it.m_node->m_value->~ParticleSystemTemplate();
		FXParticleSystem::ParticleSystemTemplate *slot = it.m_node->m_value;
		new (slot) FXParticleSystem::ParticleSystemTemplate(*system);
		::delete system;
		return;
	}
	if (!((Rva000427195 *)&m_templateMap)->insert(_STL::make_pair(name, system)).m_found)
		::delete system;
}
