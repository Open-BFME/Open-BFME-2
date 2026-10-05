// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// ?rva004638F1@OpenContain@@UAEXPAVObject@@@Z @0x004638F1 42B
// OpenContain slot-40 add-rider: push rider as int into +0x34 list<int>,
// bump +0x38, and bump +0x48 when rider template kind bit1 set.
// Evidence: vslot 78 of 0x00848AA0 SlaughterHordeContain; pin OpenContain;
// callers 0x0047C155 and HordeSiege override 0x0047D17E; neighbours
// Rva004DD206TwoTreeConstructor and HordeTransportContainRva00463A4D.
#include <list>

class ThingTemplate
{
public:
	char m_pad[0x10C];
};

class Object
{
public:
	void *m_vtable;
	ThingTemplate *m_template;
};

class OpenContain
{
public:
	virtual void rva004638F1(Object *rider);
private:
	char m_pad[0x30];
	_STL::list<int> m_list;
	int m_38;
	char m_pad2[0x48 - 0x3C];
	int m_48;
};

void OpenContain::rva004638F1(Object *rider)
{
	m_list.push_back((const int &)rider);
	++m_38;
	if (*(unsigned char *)((char *)rider->m_template + 0x10C) & 2)
		++m_48;
}
