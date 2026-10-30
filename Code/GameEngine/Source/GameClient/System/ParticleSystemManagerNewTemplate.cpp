// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?newTemplate@ParticleSystemManager@@QAEPAVParticleSystemTemplate@@ABVAsciiString@@@Z
// retail 0x001FC25A (217B). Zero Hour ParticleSystemManager::newTemplate: find an
// existing template of that name, otherwise build one and insert it into the
// template map (+0x88); a failed insert deletes the new template again.
// make_pair and the const-key pair ctor are the rowed AsciiString/int
// instantiations at 0x0032ACCF and 0x00466EA7; the map insert is the rowed
// 0x001F93A3.
//
// Codegen: retail passes the make_pair result (EAX) straight into the const-key
// pair copy and keeps that temporary alive until after the insert. The
// make_pair call sits in the argument list of a forceinline helper that holds
// the pair copy and the insert; a named reference to the temporary makes cl
// rematerialise the address with an extra lea instead.
#include "ascii_string.h"

class Rva00056F61;
class ParticleSystemTemplate;
class BfmeParticleSystemHandle;

class ParticleSystemManager
{
public:
	virtual void rva001F9F66();
	ParticleSystemTemplate *findTemplate(const AsciiString &name) const;
	ParticleSystemTemplate *newTemplate(const AsciiString &name);
	BfmeParticleSystemHandle createParticleSystem(const ParticleSystemTemplate*,bool);

private:
	char m_pad[0x84];
	char m_templateMap[0x14];	// +0x88 (Rva00056F61 bucket table; address only here)
};

namespace FXParticleSystem {
class ParticleSystemTemplate {
public:
	ParticleSystemTemplate(const AsciiString &name);
	virtual FXParticleSystem::ParticleSystemTemplate *rva001FC25ADelete(int flags);
	AsciiString getName() const;
	char m_rest[0xD4 - 4];
};
}

namespace _STL {
template <class _T1, class _T2>
struct pair {
	_T1 first;
	_T2 second;
	pair();
	pair(const _T1 &a, const _T2 &b);
	template <class _U1, class _U2>
	pair(const pair<_U1, _U2> &other);
};
template <class _T1, class _T2>
pair<_T1, _T2> make_pair(const _T1 &a, const _T2 &b);
}

struct InsertRet001F8F2A
{
	void *m_node;
	void *m_owner;
	unsigned char m_found;
};

class Rva000411084;
struct VideoPair;
class Rva000427195
{
public:
	void *first(Rva000411084 *iter);
	void rva003A37DC(VideoPair p);
	InsertRet001F8F2A insertWithGrow(const void *key);
};

#include <new>


static __forceinline bool InsertPairHelper(Rva000427195 *m, const _STL::pair<AsciiString, int> &made)
{
	_STL::pair<const AsciiString, int> stored(made);
	InsertRet001F8F2A inserted = m->insertWithGrow(&stored);
	return inserted.m_found == 0;
}
ParticleSystemTemplate *ParticleSystemManager::newTemplate(const AsciiString &name)
{
	ParticleSystemTemplate *sysTemplate = findTemplate(name);
	if (sysTemplate == 0)
	{
		sysTemplate = (ParticleSystemTemplate *)new FXParticleSystem::ParticleSystemTemplate(name);
		bool failed;
		{
			int second = (int)sysTemplate;
			failed = InsertPairHelper((Rva000427195 *)&m_templateMap, _STL::make_pair(name, second));
		}
		if (failed)
		{
			FXParticleSystem::ParticleSystemTemplate *fx =
				(FXParticleSystem::ParticleSystemTemplate *)sysTemplate;
			operator delete(fx ? fx->rva001FC25ADelete(0) : 0);
			sysTemplate = 0;
		}
	}
	return sysTemplate;
}
