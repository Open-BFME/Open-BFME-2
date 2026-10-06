// cl: /DNDEBUG /MD
// stlport
//
// ?rva00462F75@OpenContain@@UAEXPAVObject@@@Z, retail 0x00462F75 62 bytes.
// OpenContain slot 13 (offset 0x34) of vtable 0x008435E8 and 13 sibling
// Contain vtables; called by SiegeEngineContain and HordeSiegeEngineContain
// slot 13 overrides. Iterates list<int> at +0x54 comparing node data at +8
// to rider pointer value, erases match via rowed list<int>::erase 0x00438539
// and decrements count at +0x58. Same list/count pattern as
// SiegeEngineContainRiders.cpp (+0x11C/+0x120) using list<int> storing rider
// as int.
#include <list>

class Object;

class OpenContain
{
public:
	virtual void s00() = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void s09() = 0;
	virtual void s10() = 0;
	virtual void s11() = 0;
	virtual void s12() = 0;
	virtual void rva00462F75(Object *rider);
private:
	unsigned char m_pad04[0x54 - 4];
	_STL::list<int> m_list54;
	int m_count58;
};

void OpenContain::rva00462F75(Object *rider)
{
	_STL::list<int>::iterator end = m_list54.end();
	for (_STL::list<int>::iterator it = m_list54.begin(); it != end;)
	{
		if (*it == (int)rider)
		{
			it = m_list54.erase(it);
			--m_count58;
		}
		else
		{
			++it;
		}
	}
}
