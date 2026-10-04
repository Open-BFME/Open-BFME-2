// cl: /arch:SSE /G7 /DNDEBUG /MD /EHsc
//
// ?_Invalidate_Textures@WW3D@@SAXXZ retail 0x001171B0, 199 bytes.
//
// BFME2 version of WW3D::_Invalidate_Textures (the ZH HashTemplateIterator
// body is present-unmatched in ww3d.cpp). Retail instead takes the DX8 device
// lock (0x0011F520 / 0x00120F50), selects the 'TEX' asset stream through
// bfmeBeginResourceEnumeration 0x0061F110, and loops on the counted
// AssetReference returned by 0x0061F310, invalidating each texture through
// vtable slot +0x30. Shape follows the BFME1 reconstruction
// reference/open-bfme-1/game/.../WW3D__Invalidate_TexturesMethodThunk.cpp,
// which stores the same AssetReference loop; only the lock is added.

class TextureClass
{
public:
	void Add_Ref()
	{
		++*(unsigned short *)((char *)this + 4);
	}

	void Release_Ref();

	virtual void VTableSlot00();
	virtual void VTableSlot01();
	virtual void VTableSlot02();
	virtual void VTableSlot03();
	virtual void VTableSlot04();
	virtual void VTableSlot05();
	virtual void VTableSlot06();
	virtual void VTableSlot07();
	virtual void VTableSlot08();
	virtual void VTableSlot09();
	virtual void VTableSlot10();
	virtual void VTableSlot11();
	virtual void Invalidate();
};

class DummyPtrType;

class AssetReference
{
public:
	AssetReference() : m_object(0) {}

	AssetReference(const AssetReference &that) : m_object(that.m_object)
	{
		if (m_object)
			m_object->Add_Ref();
	}

	~AssetReference()
	{
		if (m_object)
			m_object->Release_Ref();
	}

	AssetReference &operator=(const AssetReference &that)
	{
		if (that.m_object)
			that.m_object->Add_Ref();
		if (m_object)
			m_object->Release_Ref();
		m_object = that.m_object;
		return *this;
	}

	operator const DummyPtrType *() const
	{
		return (DummyPtrType *)m_object;
	}

	TextureClass *operator->() const
	{
		return m_object;
	}

	TextureClass *m_object;
};

void bfmeBeginResourceEnumeration(unsigned asset_type);
AssetReference Rva009EBDC0();

extern void BFME_DX8_Thread_Lock();
extern bool BFME_DX8_Thread_Assert();

class BFMEDX8DeviceLock {
public:
	BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
	~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};

class __declspec(novtable) WW3D
{
public:
	static void _Invalidate_Textures();
};

inline void WW3D::_Invalidate_Textures()
{
	BFMEDX8DeviceLock lock;
	bfmeBeginResourceEnumeration('TEX');
	AssetReference texture;
	bool has_texture;
	for (;;) {
		has_texture = (texture = Rva009EBDC0()) != 0;
		if (has_texture && texture)
			texture->Invalidate();
		if (!has_texture)
			break;
	}
}

#pragma inline_depth(0)
// ?_bfmeRva001171B0Anchor present-unmatched
void _bfmeRva001171B0Anchor() { WW3D::_Invalidate_Textures(); }
#pragma inline_depth()

// Other units call this body (pinned at its address) under the spelling(s)
// below, with the same calling convention and stack arguments; bind them.
#pragma comment(linker, "/alternatename:?Rva001171B0@@YAXXZ=?_Invalidate_Textures@WW3D@@SAXXZ")
#pragma comment(linker, "/alternatename:?rva001171B0Notify@@YAXXZ=?_Invalidate_Textures@WW3D@@SAXXZ")
