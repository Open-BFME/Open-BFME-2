// cl: /DNDEBUG /MD /Ob2 /EHsc
//
// MeshMatDescClass::Get_Color_Array, retail 0x00D1FBD (105 bytes). BFME1
// header-inline shape (reference/.../meshmatdesclayout/meshmatdesc.h in this
// tree): create-gated allocation of a ShareBufferClass<unsigned> over
// VertexCount, then the Array (+0x0C) or 0. Retail keeps it out of line
// (dx8renderer Define_FVF calls it cross-TU at 0x144286/0x14429E). Retail
// touches ColorArray at this+0x50 -- four bytes past the shared shim's
// +0x4C -- so this TU uses a TU-local layout view anchored at the two
// retail-touched members (VertexCount +0x04, ColorArray +0x50) instead of
// editing the shared header. The allocator (??2 at 0x2FDA0) resolves via
// its pin and the ShareBuffer<unsigned> ctor via its matched row; the
// "MeshMatDescClass::ColorArray" literal is verified against 0x7CE358.
// Like its ctor dependency, this unit builds at /O1 for the ebp-frame
// __EH_prolog prologue.

class RefCountClass
{
public:
	RefCountClass() : m_refs(1) {}
	RefCountClass(const RefCountClass &) : m_refs(1) {}
	virtual void Delete_This();

protected:
	virtual ~RefCountClass() {}

private:
	int m_refs;
};

template <class T>
class ShareBufferClass : public RefCountClass
{
public:
	ShareBufferClass(int count, const char *msg, int alignment = 0);
	T *Get_Array() { return m_array; }

protected:
	T *m_rawBuffer; // +0x08
	T *m_array; // +0x0C
	int m_count; // +0x10
	int m_alignment; // +0x14
};

class MeshMatDescClass
{
public:
	unsigned *Get_Color_Array(int index, bool create);

private:
	int m_passCount; // +0x00
	int m_vertexCount; // +0x04
	// +0x08..+0x4F hold the UV/UV-source tables in the shared header; retail
	// anchors ColorArray at +0x50 here, so the middle stays unmapped.
	unsigned char m_unmapped[0x48];
	ShareBufferClass<unsigned> *m_colorArray[2]; // +0x50
};

inline unsigned *MeshMatDescClass::Get_Color_Array(int index, bool create)
{
	if (create && !m_colorArray[index]) {
		m_colorArray[index] = new ShareBufferClass<unsigned>(m_vertexCount, "MeshMatDescClass::ColorArray");
	}
	if (m_colorArray[index]) {
		return m_colorArray[index]->Get_Array();
	}
	return 0;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. Taking each one's
// address keeps this unit's copy for its row; these pointers are not retail
// data.
unsigned * (MeshMatDescClass::*_bfmeInlineAnchor_MeshMatDescClassGetColorArray_0)(int index, bool create) = &MeshMatDescClass::Get_Color_Array;
