// cl: /O1 /DNDEBUG /MD /EHsc
// By-value texture-handle getters the terrain FX texture callbacks call
// (0x000E28C3 calls 0x000E2983 on TheTerrainRenderObject, VA 0x00DE1EAC, and
// tests the returned handle before Peek_D3D_Base_Texture). Each copies one
// member handle into the hidden return slot, bumping the 16-bit reference
// count at +4 that the rowed TextureClass::Release_Ref (0x0061ED10) drops.
// Target facts: thiscall, ret 4, hidden return pointer, member offsets below.
// The handle template and method names are inferred/address-derived.
//
// ?rva000E234E@BaseHeightMapRenderObjClass@@QAE?AV?$RefCountPtr@VTextureClass@@@@XZ @0x000E234E 31B (+0x3828)
// ?rva000E2983@BaseHeightMapRenderObjClass@@QAE?AV?$RefCountPtr@VTextureClass@@@@XZ @0x000E2983 31B (+0x3838)
// ?rva000E2A62@BaseHeightMapRenderObjClass@@QAE?AV?$RefCountPtr@VTextureClass@@@@XZ @0x000E2A62 31B (+0x3844)
// ?rva000E2BCF@BaseHeightMapRenderObjClass@@QAE?AV?$RefCountPtr@VTextureClass@@@@XZ @0x000E2BCF 31B (+0x381C)
// ?rva000E28A7@Rva000E28A7@@QAE?AV?$RefCountPtr@VTextureClass@@@@XZ               @0x000E28A7 28B (+0x1C)

class TextureClass
{
public:
	__forceinline void Add_Ref() { ++m_refCount; }
	void Release_Ref();

private:
	void *m_vtable;
	unsigned short m_refCount;
};

template <class T> class RefCountPtr
{
public:
	__forceinline RefCountPtr(const RefCountPtr &that) : m_ptr(that.m_ptr)
	{
		if (m_ptr)
			m_ptr->Add_Ref();
	}
	~RefCountPtr()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

private:
	T *m_ptr;
};

class BaseHeightMapRenderObjClass
{
public:
	RefCountPtr<TextureClass> rva000E234E();
	RefCountPtr<TextureClass> rva000E2983();
	RefCountPtr<TextureClass> rva000E2A62();
	RefCountPtr<TextureClass> rva000E2BCF();

private:
	char m_pad0000[0x381c];
	RefCountPtr<TextureClass> m_381c;
	char m_pad3820[0x3828 - 0x3820];
	RefCountPtr<TextureClass> m_3828;
	char m_pad382c[0x3838 - 0x382c];
	RefCountPtr<TextureClass> m_3838;
	char m_pad383c[0x3844 - 0x383c];
	RefCountPtr<TextureClass> m_3844;
};

RefCountPtr<TextureClass> BaseHeightMapRenderObjClass::rva000E234E()
{
	return m_3828;
}

RefCountPtr<TextureClass> BaseHeightMapRenderObjClass::rva000E2983()
{
	return m_3838;
}

RefCountPtr<TextureClass> BaseHeightMapRenderObjClass::rva000E2A62()
{
	return m_3844;
}

RefCountPtr<TextureClass> BaseHeightMapRenderObjClass::rva000E2BCF()
{
	return m_381c;
}

class Rva000E28A7
{
public:
	RefCountPtr<TextureClass> rva000E28A7();

private:
	char m_pad00[0x1c];
	RefCountPtr<TextureClass> m_1c;
};

RefCountPtr<TextureClass> Rva000E28A7::rva000E28A7()
{
	return m_1c;
}
