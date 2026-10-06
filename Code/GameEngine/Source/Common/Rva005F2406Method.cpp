// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva005F2406@Rva005F2406@@QAEXH@Z @0x005F2406 51B insert int into set at +0x10 then broadcast
// If set<int>::insert 0x000BC15D reports new key, forEach 0x005F224E over list at +0
// with forwarder 0x001FF3A9 and this plus the key. Evidence: callees rowed, caller 0x005E4E12.
#include <set>

class Rva005F224EListener
{
public:
	virtual void notify(void *, int);
};

class Rva005F224EList
{
public:
	void forEach(void (Rva005F224EListener::*notify)(void *, int), void *arg, int value);
private:
	Rva005F224EListener **m_begin;
	Rva005F224EListener **m_end;
	Rva005F224EListener **m_capacity;
	unsigned int m_index;
};

class Rva001FF3A9
{
public:
	virtual void rva001FF3A9();
};

class Rva005F2406
{
public:
	void rva005F2406(int val);
private:
	Rva005F224EList m_list00;
	_STL::set<int> m_set10;
};

void Rva005F2406::rva005F2406(int val)
{
	if (m_set10.insert(val).second)
		m_list00.forEach((void (Rva005F224EListener::*)(void *, int))&Rva001FF3A9::rva001FF3A9, this, val);
}
