// ?Capture_Bone@HTreeClass@@QAEXH@Z
// cl: /G7 /arch:SSE /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?Capture_Bone@HTreeClass@@QAEXH@Z, retail 0x00166980 (229 bytes).
//
// BFME2 rewrote Zero Hour's per-pivot IsCaptured flag as a sorted vector of
// 36-byte captured-bone records at +0x1C (Begin/End/Capacity), the same
// member HTreeClassFree.cpp clears and HTreeClassReleaseBone.cpp erases from.
// Target loop first tests equality, overwriting a matching identity record,
// then greater-than, inserting before it and resetting the scan to begin.
// After that scan, it appends only when the iterator equals the current end.
// BFME 1 874e38488 Zero Hour htree.cpp supplies the bone-capture purpose;
// target bytes and already-matched Control_Bone/Release_Bone supply this
// target-specific sorted-vector representation, not the donor flag layout.
// The record is Index, identity quaternion (0,0,0,1), zero translation, and a
// false world-space flag, matching the Control_Bone record model. The vector
// helpers keep the recovered Elem36 stand-in identity so the call sites mangle
// to the rowed STLport 36-byte vector bodies.
#include <memory>

class Quaternion
{
public:
	float X, Y, Z, W;
	Quaternion() {}
	Quaternion(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w) {}
	Quaternion &operator=(const Quaternion &q)
	{
		X = q.X; Y = q.Y; Z = q.Z; W = q.W;
		return *this;
	}
};

class Vector3
{
public:
	float X, Y, Z;
	Vector3() {}
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	Vector3 &operator=(const Vector3 &v)
	{
		X = v.X; Y = v.Y; Z = v.Z;
		return *this;
	}
};

struct Elem36
{
	int Index;
	Quaternion Rotation;
	Vector3 Translation;
	bool WorldSpace;

	Elem36() {}
	Elem36(const Elem36 &other)
		: Index(other.Index), Rotation(other.Rotation),
		  Translation(other.Translation), WorldSpace(other.WorldSpace)
	{
	}
	Elem36 &operator=(const Elem36 &other)
	{
		Index = other.Index;
		Rotation = other.Rotation;
		Translation = other.Translation;
		WorldSpace = other.WorldSpace;
		return *this;
	}
};

// The existing target placement-copy provider is address-derived; call its
// real row spelling directly instead of adding a second external alias.
void gen001610F0(Elem36 *, const Elem36 *);
namespace _STL {
template<> inline void _Construct<Elem36, Elem36>(Elem36 *p, const Elem36 &v)
{ gen001610F0(p, &v); }
}
#include <vector>
namespace _STL {
template<> Elem36 *vector<Elem36>::insert(Elem36 *, const Elem36 &);
template<> void vector<Elem36>::_M_insert_overflow(Elem36 *, const Elem36 &, const __false_type &, unsigned int, bool);
// STLport's normal append algorithm, with an uninitialized empty dispatch
// tag: retail does not zero the tag byte, and the tag carries no value.
// Scoped here to preserve the independently verified shared providers.
template<> inline void vector<Elem36>::push_back(const Elem36 &v) {
 if(this->_M_finish != this->_M_end_of_storage._M_data) {
  _Construct(this->_M_finish,v);
  ++this->_M_finish;
 } else {
  __false_type tag;
  _M_insert_overflow(this->_M_finish,v,tag,1UL,true);
 }
}
}
typedef _STL::vector<Elem36, _STL::allocator<Elem36> > Elem36Vector;

class HTreeClass
{
public:
	void Capture_Bone(int boneindex);

private:
	char Name[16];
	int NumPivots;			// +0x10
	void *Pivot;			// +0x14
	float ScaleFactor;		// +0x18
	Elem36Vector m_bones;	// +0x1C
};

// ?Capture_Bone@HTreeClass@@QAEXH@Z
void HTreeClass::Capture_Bone(int boneindex)
{
	Elem36 bone;
	bone.Index = boneindex;
	bone.WorldSpace = false;
	bone.Rotation = Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
	bone.Translation = Vector3(0.0f, 0.0f, 0.0f);

	Elem36 *it = m_bones.begin();
	Elem36 *end = m_bones.end();
 while (it != end) {
  if(it->Index == boneindex) {
   it->Index=boneindex;
   it->Rotation=Quaternion(0.0f,0.0f,0.0f,1.0f);
   it->Translation=Vector3(0.0f,0.0f,0.0f);
   it->WorldSpace=false;
   break;
  }
  if(it->Index > boneindex) {
   m_bones.insert(it, bone);
   it = m_bones.begin();
   break;
  }
  ++it;
 }
 if(it == m_bones.end()) m_bones.push_back(bone);
}
