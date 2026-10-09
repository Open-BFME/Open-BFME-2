// cl: /DNDEBUG /MD /EHsc
//
// ?Rva0012CA49Run@@YAXXZ, retail 0x0012CA49, 122 bytes.
// Enumerate the FXSH (0x46585348) shader resources and invoke vtable slot 11
// on each live one. Evidence: bfmeBeginResourceEnumeration tag constant,
// BfmeResetShaderRef assign row 0x0015142A, TextureBaseClass::Release_Ref row
// 0x0061ED10, AssetReference current-asset row 0x009EBDC0. The only caller,
// 0x0012D265 in 0x0012CFA0, makes the call with no ECX setup (the registers
// are whatever the preceding cdecl cleanup left), so this is a free cdecl
// function rather than the earlier address-named __thiscall method.

void Rva0012CA49Run();

class TextureBaseClass
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void Delete_This();
	virtual void v24();
	virtual void v28();
	virtual void v2c();
	void Release_Ref();
};

struct BfmeResetAnyRef
{
	TextureBaseClass *pointer;
};

struct BfmeResetShaderRef
{
	TextureBaseClass *pointer;
	BfmeResetShaderRef() : pointer(0) {}
	~BfmeResetShaderRef() { if (pointer) pointer->Release_Ref(); }
	BfmeResetShaderRef &operator=(const BfmeResetAnyRef &rhs);
};

class AssetReference : public BfmeResetAnyRef
{
public:
	~AssetReference() { if (pointer) pointer->Release_Ref(); }
};

void __cdecl bfmeBeginResourceEnumeration(unsigned tag);
AssetReference __cdecl Rva009EBDC0();

void Rva0012CA49Run()
{
	bfmeBeginResourceEnumeration(0x46585348);
	BfmeResetShaderRef shader;
	for (;;) {
		if ((shader = Rva009EBDC0()).pointer != 0) {
			if (shader.pointer != 0)
				shader.pointer->v2c();
		} else {
			break;
		}
	}
}
