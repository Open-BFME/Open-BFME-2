// cl: /DNDEBUG /MD /GX- /O2 /Ob2
// Readable out-of-line body of ?Release_Ref@TextureBaseClass@@QAEXXZ
// (retail 0x0061ED10, 36 bytes). Verbatim port of the Open-BFME-1
// TextureBaseReleaseRefThunk: WORD refcount at +4 with flag bits, virtual
// Delete_This at slot 8 when the count hits zero with 0x1000000 set.
// Shared by all texture-handle releases image-wide (477 retail callers),
// including the MeshMatDesc TextureArray init loops.

class TextureBaseClass
{
public:
	void Release_Ref();
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void Delete_This();

private:
	unsigned int m_refBits;
};

// ?Release_Ref@TextureBaseClass@@QAEXXZ
void TextureBaseClass::Release_Ref()
{
	if ((m_refBits & 0xffff) == 0)
		return;
	*reinterpret_cast<unsigned short *>(&m_refBits) =
		static_cast<unsigned short>(*reinterpret_cast<unsigned short *>(&m_refBits) - 1);
	if ((m_refBits & 0xffff) != 0)
		return;
	if ((m_refBits & 0x1000000) == 0)
		return;
	Delete_This();
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?Release_Ref@BfmeResetResource@@QAEXXZ=?Release_Ref@TextureBaseClass@@QAEXXZ")
#pragma comment(linker, "/alternatename:?Release_Ref@BFME2TextureResource@@QAEXXZ=?Release_Ref@TextureBaseClass@@QAEXXZ")
#pragma comment(linker, "/alternatename:?Release_Ref@CountedAsset@@QAEXXZ=?Release_Ref@TextureBaseClass@@QAEXXZ")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
