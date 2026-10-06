// cl: /DNDEBUG /MD /Ob2 /EHsc
// ?Get_UV_Array_By_Index@MeshMatDescClass@@QAEPAVVector2@@H_N@Z @0x000D1F40 125B
// Create-gated UV buffer accessor with legacy Get_UV_Array fallback.
// Evidence: retail EH_prolog, new 0x1c plus UVBuffer ctor with
// "MeshMatDescClass::UV" and VertexCount+0x04, table+0x10, array+0x0C,
// rowed Get_UV_Array at 0x000D1F1A, callers 0x000D2057 0x000D239A 0x000DDF36
// 0x000E5521 0x0014436F 0x0018CE74; donor ZH meshmatdesc.h Get_UV_Array_By_Index.

class Vector2;

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

class UVBufferClass : public ShareBufferClass<Vector2>
{
public:
	UVBufferClass(int count, const char *msg);

private:
	unsigned int m_crc; // +0x18 (sizeof 0x1C)
};

class MeshMatDescClass
{
public:
	Vector2 *Get_UV_Array(int pass, int stage);
	Vector2 *Get_UV_Array_By_Index(int index, bool create);

private:
	int m_passCount; // +0x00
	int m_vertexCount; // +0x04
	int m_polyCount; // +0x08
	int m_unknown0C; // +0x0C
	UVBufferClass *m_uv[8]; // +0x10
};

inline Vector2 *MeshMatDescClass::Get_UV_Array_By_Index(int index, bool create)
{
	if (create && !m_uv[index])
		m_uv[index] = new UVBufferClass(m_vertexCount, "MeshMatDescClass::UV");
	if (!create && m_unknown0C != 0 && index < 2)
		return Get_UV_Array(0, index);
	if (m_uv[index])
		return m_uv[index]->Get_Array();
	return 0;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. Taking each one's
// address keeps this unit's copy for its row; these pointers are not retail
// data.
Vector2 * (MeshMatDescClass::*_bfmeInlineAnchor_MeshMatDescGetUVArrayByIndex_0)(int index, bool create) = &MeshMatDescClass::Get_UV_Array_By_Index;
