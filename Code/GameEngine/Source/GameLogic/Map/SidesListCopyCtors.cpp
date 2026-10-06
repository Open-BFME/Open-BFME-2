// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /Ireference/shims/bfmealloc
// stlport
//
// Target-side copy layout for SidesList. The donor SidesList.h establishes the
// SubsystemInterface/Snapshot bases; retail 0x0032EF3E then proves the BFME2
// offsets: notifier subobject +0x10, list/maps +0x20/+0x24/+0x30, counts and
// SidesInfo arrays +0x3C/+0x40/+0x7C0/+0x7C4, TeamsInfoRec +0xF44/+0xF60,
// cleared byte +0xF7C, and the 20 28-byte records at +0xF80. The latter's
// two vector assignments call the rowed 128-byte vector operator= at 0x32C0E3.
// The donor class identity is supported by the base, matching SidesList method
// call sites, the two target vtables and the target member offsets. Extra-field
// semantics beyond the vector control blocks remain address-derived.

#include <algorithm>
#include <vector>
#include "Common/Snapshot.h"

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual bool loadIniFilesFromLegend();
	virtual void reset() = 0;
	virtual void update() = 0;
	virtual void draw();
	SubsystemInterface(const SubsystemInterface &that);

private:
	bool m_flag;
	char m_pad05[3];
	char m_name[4];
};

#pragma comment(linker, "/alternatename:??1SubsystemInterface@@UAE@XZ=??1GameEngineDeletingBase@@UAE@XZ")

class Rva00330757Member
{
public:
	Rva00330757Member();
	~Rva00330757Member();

private:
	char m_body[0x10];
};

#pragma comment(linker, "/alternatename:??1Rva00330757Member@@QAE@XZ=??1BasicStringCharDtor_dup@@QAE@XZ")

class SidesListNotifier : public Rva00330757Member
{
public:
	__forceinline SidesListNotifier() : Rva00330757Member() {}
	__forceinline SidesListNotifier(const SidesListNotifier &) : Rva00330757Member() {}
	__forceinline ~SidesListNotifier() {}
};

namespace _STL
{
template <class T, class Alloc> class _List_base
{
public:
	_List_base(const Alloc &alloc);
	~_List_base();

private:
	void *m_node;
};
}

class SidesListListField : public _STL::_List_base<int, _STL::allocator<int> >
{
public:
	__forceinline SidesListListField()
		: _STL::_List_base<int, _STL::allocator<int> >(_STL::allocator<int>()) {}
	~SidesListListField();
};

#pragma comment(linker, "/alternatename:??1SidesListListField@@QAE@XZ=??1Rva00207F08Dtor@@QAE@XZ")

class Rva0032D3D3Map
{
public:
	Rva0032D3D3Map();
	~Rva0032D3D3Map();

private:
	char m_body[0x0C];
};

class Rva0032EAA1Map
{
public:
	Rva0032EAA1Map();
	~Rva0032EAA1Map();

private:
	char m_body[0x0C];
};

#pragma comment(linker, "/alternatename:??0Rva0032D3D3Map@@QAE@XZ=??0?$map@W4NameKeyType@@VModuleTemplate@ModuleFactory@@U?$less@W4NameKeyType@@@_STL@@V?$allocator@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@5@@_STL@@QAE@XZ")
#pragma comment(linker, "/alternatename:??0Rva0032EAA1Map@@QAE@XZ=??0?$map@W4NameKeyType@@VModuleTemplate@ModuleFactory@@U?$less@W4NameKeyType@@@_STL@@V?$allocator@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@5@@_STL@@QAE@XZ")
#pragma comment(linker, "/alternatename:??1Rva0032D3D3Map@@QAE@XZ=??1Rva0032D3D3@@QAE@XZ")
#pragma comment(linker, "/alternatename:??1Rva0032EAA1Map@@QAE@XZ=??1Rva0032EAA1@@QAE@XZ")

class SidesInfo
{
public:
	SidesInfo();
	SidesInfo(const SidesInfo &that);
	~SidesInfo();
	SidesInfo &operator=(const SidesInfo &that);

private:
	char m_body[0x60];
};

class TeamsInfoRec
{
public:
	TeamsInfoRec();
	TeamsInfoRec(const TeamsInfoRec &that);
	~TeamsInfoRec();
	void clear();

private:
	char m_body[0x1C];
};

#pragma comment(linker, "/alternatename:??0TeamsInfoRec@@QAE@XZ=??0Rva0019A1D0Owner@@QAE@XZ")
#pragma comment(linker, "/alternatename:??0TeamsInfoRec@@QAE@ABV0@@Z=??0BfmeTmpACH@@QAE@PAX@Z")
#pragma comment(linker, "/alternatename:??1TeamsInfoRec@@QAE@XZ=??1BfmeTmpACH@@QAE@XZ")

struct Rva0032C0E3Element
{
	char m_body[0x80];
};

class Rva0032C19D
{
public:
	Rva0032C19D();
	~Rva0032C19D();
	Rva0032C19D &operator=(const Rva0032C19D &that);

private:
	int m_value;
	std::vector<Rva0032C0E3Element> m_first;
	std::vector<Rva0032C0E3Element> m_second;
};

#pragma comment(linker, "/alternatename:??1Rva0032C19D@@QAE@XZ=??1Rva001976F0@@QAE@XZ")

class SidesList : public SubsystemInterface, public Snapshot, public SidesListNotifier
{
public:
	SidesList(const SidesList &that);
	virtual ~SidesList();
	virtual void init();
	virtual void reset();
	virtual void update();
	virtual void draw();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();

private:
	SidesListListField m_list;				// +0x20
	Rva0032D3D3Map m_map1;					// +0x24
	Rva0032EAA1Map m_map2;					// +0x30
	int m_numSides;							// +0x3C
	SidesInfo m_sides[20];					// +0x40
	int m_numSkirmishSides;					// +0x7C0
	SidesInfo m_skirmishSides[20];			// +0x7C4
	TeamsInfoRec m_teamrec;				// +0xF44
	TeamsInfoRec m_skirmishTeamrec;		// +0xF60
	bool m_cleared;							// +0xF7C
	char m_pad[3];
	Rva0032C19D m_extra[20];				// +0xF80
};

Rva0032C19D::Rva0032C19D()
{
}

Rva0032C19D &Rva0032C19D::operator=(const Rva0032C19D &that)
{
	m_value = that.m_value;
	m_first = that.m_first;
	m_second = that.m_second;
	return *this;
}

// ?SidesList::SidesList present-unmatched
SidesList::SidesList(const SidesList &that)
	: SubsystemInterface(that),
	  Snapshot(that),
	  SidesListNotifier(that),
	  m_list(),
	  m_map1(),
	  m_map2(),
	  m_numSides(that.m_numSides),
	  m_numSkirmishSides(that.m_numSkirmishSides),
	  m_teamrec(that.m_teamrec),
	  m_skirmishTeamrec(that.m_skirmishTeamrec),
	  m_cleared(that.m_cleared)
{
	std::copy(that.m_sides, that.m_sides + m_numSides, m_sides);
	std::copy(that.m_skirmishSides, that.m_skirmishSides + m_numSkirmishSides, m_skirmishSides);
	for (int i = 0; i < 20; ++i)
		m_extra[i] = that.m_extra[i];
}
