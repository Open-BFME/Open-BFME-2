// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib -ICode/Libraries/Source/WWVegas/WW3D2 -ICode/Libraries/Source/WWVegas/WWLib -ICode/Libraries/Source/WWVegas/WWMath -ICode/Libraries/Source/WWVegas/WWSaveLoad -ICode/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil -Ireference/shims/sweep
// W3DShadowGeometry constructor and virtual key accessor.
// BFME 1 donor ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f supplies Get_Key
// semantics; retail constructor establishes AsciiString at complete this+0x10.
// Native F1EC2..F1ED3 is a full 17-byte accessor with two terminal returns.

#define MAX_SHADOW_CASTER_MESHES 160

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class RefCountClass
{
public:
	__declspec(dllimport) __forceinline RefCountClass(void) : NumRefs(1) {}
	void Add_Ref(void) { NumRefs++; }
	int Num_Refs(void) { return NumRefs; }
	virtual void Delete_This(void);

protected:
	virtual ~RefCountClass(void) {}

private:
	int NumRefs;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/hash.h
#include "../../../../../Libraries/Source/WWVegas/WWLib/HashableClass.h"

struct AsciiStringData;

// BFME drift: the geometry name is a StringBase-derived string object at +0x10,
// not Zero Hour's inline char[2*W3D_NAME_LEN].
#include "ascii_string.h"

#include "../../../../Include/W3DDevice/GameClient/W3DShadowGeometryMesh.h"

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
