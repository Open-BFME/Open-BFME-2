// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib

#define MAX_SHADOW_CASTER_MESHES 160

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class RefCountClass
{
public:
	virtual void Delete_This(void);

protected:
	virtual ~RefCountClass(void) {}

private:
	int NumRefs;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/hash.h
class HashableClass
{
public:
	// Native EF9CF..EF9D6 restores BCEF94 between the verified base
	// constructor EF9C2 and scalar deleting destructor EF9D6.
	virtual ~HashableClass(void) {}
	virtual const char *Get_Key(void) = 0;

private:
	HashableClass *NextHash;
};

struct AsciiStringData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
#include "ascii_string.h"

class W3DShadowGeometryMesh
{
public:
	~W3DShadowGeometryMesh(void);

private:
	int m_opaque[13];
};

class W3DShadowGeometry : public RefCountClass, public HashableClass
{
public:
	~W3DShadowGeometry(void);
	virtual const char *Get_Key(void);

private:
	AsciiString m_namebuf;
	W3DShadowGeometryMesh m_meshList[MAX_SHADOW_CASTER_MESHES];
	Int m_meshCount;
	Int m_numTotalsVerts;
};

inline W3DShadowGeometry::~W3DShadowGeometry(void)
{
}

// ??1W3DShadowGeometry is a header inline elsewhere: another unit emits a
// select-any copy, so a strong definition here was a duplicate symbol in
// the linked build. This anchor only makes this unit emit its copy for the
// ledger row; it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitW3DShadowGeometryDtor@@YAXPAVW3DShadowGeometry@@@Z present-unmatched
void bfmeEmitW3DShadowGeometryDtor(W3DShadowGeometry *p)
{
	p->W3DShadowGeometry::~W3DShadowGeometry();
}
#pragma inline_depth()
