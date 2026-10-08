// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// W3DShadowGeometry constructor and virtual key accessor.
// BFME 1 donor ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f supplies Get_Key
// semantics; retail constructor establishes AsciiString at complete this+0x10.
// Native F1EC2..F1ED3 is a full 17-byte accessor with two terminal returns.

#define MAX_SHADOW_CASTER_MESHES 160

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
#pragma optimize("t", on)
class RefCountClass
{
public:
	RefCountClass(void) : NumRefs(1) {}
	void Add_Ref(void) { NumRefs++; }
	int Num_Refs(void) { return NumRefs; }
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
	HashableClass(void) : NextHash(0) {}
	virtual ~HashableClass(void) {}
	virtual const char *Get_Key(void) = 0;

private:
	HashableClass *NextHash;
};
#pragma optimize("", on)

struct AsciiStringData;

// BFME drift: the geometry name is a StringBase-derived string object at +0x10,
// not Zero Hour's inline char[2*W3D_NAME_LEN].
#include "ascii_string.h"

class W3DShadowGeometryMesh
{
public:
	W3DShadowGeometryMesh(void);
	~W3DShadowGeometryMesh(void);

private:
	int m_opaque[13];
};

class W3DShadowGeometry : public RefCountClass, public HashableClass
{
public:
	W3DShadowGeometry(void);
	~W3DShadowGeometry(void) {}

	// Secondary HashableClass vftable 0x00BCEFF4 slot 1 points to F1EC2.
	// MSVC receives this as the Hashable subobject: m_namebuf is then +8.
	virtual const char *Get_Key(void) { return m_namebuf.str(); }

private:
	AsciiString m_namebuf;
	W3DShadowGeometryMesh m_meshList[MAX_SHADOW_CASTER_MESHES];
	Int m_meshCount;
	Int m_numTotalsVerts;
};

// ??0W3DShadowGeometry@@QAE@XZ
W3DShadowGeometry::W3DShadowGeometry(void)
{
	m_numTotalsVerts = 0;
	m_meshCount = 0;
}
