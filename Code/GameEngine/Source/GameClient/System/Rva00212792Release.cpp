// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
//
// ?rva00212792@Rva002141D1@@QAEXXZ, retail 0x00212792 (198 bytes). Release
// pass over the two entry vectors at +0x234 and +0x240 of the receiver that
// Rva00211494Loops.cpp names Rva002141D1: first the rowed per-entry pass
// rva002118C2 0x002118C2 on the same receiver; then each vector walked from
// the back. An entry whose target (+0x08) is set has the target's slot 16
// (+0x40) called; an entry of the first vector also passes its name
// (AsciiString +0x04) to the pinned rva002C004F 0x002C004F on the global
// 0x009FEF18; the entry is then destroyed through its virtual destructor and
// freed with the global operator delete 0x0002FD60 (::delete). Each vector
// is emptied through the rowed vector<void *>::erase 0x0031BD55. No call
// site or data reference in game.dat; WorldBuilder twin 0x00B61700
// (callgraph evidence) has the same two loops.

#include "ascii_string.h"

class Rva00212792Target
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15();
	virtual void slot16(); // +0x40
};

class Rva00212792Entry
{
public:
	virtual ~Rva00212792Entry();
	AsciiString m_name; // +0x04
	Rva00212792Target *m_target; // +0x08
};

class Rva002D3627Host
{
public:
	void rva002C004F(const char *name);
};

extern Rva002D3627Host *g_00DFEF18;

namespace _STL
{
template<class T> class allocator {};
template<class T, class A = allocator<T> > class vector
{
public:
	unsigned int size() const { return last - first; }
	T *begin() { return first; }
	T *end() { return last; }
	T &operator[](unsigned int n) { return *(begin() + n); }
	T *erase(T *a, T *b);
	void clear() { erase(begin(), end()); }
private:
	T *first, *last, *limit;
};
}

class Rva002141D1
{
public:
	void rva002118C2();
	void rva00212792();
private:
	char m_pad000[0x234];
	_STL::vector<void *> m_entries234; // +0x234
	_STL::vector<void *> m_entries240; // +0x240
};

void Rva002141D1::rva00212792()
{
	rva002118C2();
	int i;
	for (i = m_entries234.size() - 1; i >= 0; --i)
	{
		if (((Rva00212792Entry *)m_entries234[i])->m_target)
		{
			((Rva00212792Entry *)m_entries234[i])->m_target->slot16();
			g_00DFEF18->rva002C004F(((Rva00212792Entry *)m_entries234[i])->m_name.str());
			::delete (Rva00212792Entry *)m_entries234[i];
		}
	}
	m_entries234.clear();
	for (i = m_entries240.size() - 1; i >= 0; --i)
	{
		if (((Rva00212792Entry *)m_entries240[i])->m_target)
		{
			((Rva00212792Entry *)m_entries240[i])->m_target->slot16();
			::delete (Rva00212792Entry *)m_entries240[i];
		}
	}
	m_entries240.clear();
}
