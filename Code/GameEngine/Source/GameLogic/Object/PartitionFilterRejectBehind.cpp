// Donor: Open-BFME-1 1399ad37d42ea52a63829e417c46a1ba9ed2cd20,
// game/GameEngine/Source/GameLogic/Object/PartitionFilterRejectBehind_allow.cpp.
// Donor name describes a forward-direction rejection predicate. The original
// target class/method and virtual ownership remain unproven; this receiver
// view keeps an address-based identity and its observed thiscall RET4 ABI.
// Native facts: object pointer at receiver+8, transform basis at Object+8,
// normalized direction then positive dot against the position delta. The
// exact native delta callee 0x261988 is already rowed as Rva001E438B::rva00261988,
// whose own body passes other+0x38 to 0x1E438B and returns the three-float result.
// The receiver cast reuses that existing ABI and adds no alias pin.
// cl: -O1 -arch:SSE -G7 -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/Object -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug

#include "wwmath.h"
// Inline math views preserve the donor arithmetic and native 3x4 basis stride.
// The local receiver views do not claim the library classes or their ABI.
class Rva00261ABBVector { public:
 float X,Y,Z;
 __forceinline Rva00261ABBVector() {}
 __forceinline Rva00261ABBVector(float x,float y,float z) : X(x),Y(y),Z(z) {}
 __forceinline float Length2() const { return X*X + Y*Y + Z*Z; }
 __forceinline Rva00261ABBVector &operator*=(float k) { X=X*k;Y=Y*k;Z=Z*k;return *this; }
};
class Rva00261ABBMatrix { public:
 float row[3][4];
 __forceinline Rva00261ABBVector Get_X_Vector() const { return Rva00261ABBVector(row[0][0],row[1][0],row[2][0]); }
};

typedef bool Bool;
typedef float Real;



// Existing native object-position delta provider at RVA0x261988.
class Rva001E438B { public: float *rva00261988(float *, Rva001E438B *); };
// BFME stores this filter's object pointer at +0x08.
class Object
{
public:
	const Rva00261ABBMatrix *getTransformMatrix(void) const
	{
		return (const Rva00261ABBMatrix *)((const char *)this + 0x08);
	}
};

// The unmodeled eight-byte prefix preserves the observed object offset.
class Rva00261ABBFilter
{
public:
	Bool rva00261ABB(Object *other);

private:
	unsigned char m_unreconstructed_00[8];
	Object *m_obj;
};

// ?rva00261ABB@Rva00261ABBFilter@@QAE_NPAVObject@@@Z
Bool Rva00261ABBFilter::rva00261ABB(Object *other)
{
	Rva00261ABBVector dir = m_obj->getTransformMatrix()->Get_X_Vector();
	Real len2 = dir.Length2();
	if (len2 != 0.0f)
		dir *= WWMath::Inv_Sqrt(len2);

	Rva00261ABBVector v;
	reinterpret_cast<Rva001E438B *>(m_obj)->rva00261988(&v.X, reinterpret_cast<Rva001E438B *>(other));

	Real dot = dir.X * v.X + dir.Y * v.Y + dir.Z * v.Z;
	if (dot > 0.0f)
		return true;

	return false;
}
