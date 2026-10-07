// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// MeshMatDescClass::Get_Single_Texture, meshmatdesc.cpp's out-of-line /O2 body.
// ZH defines it just ahead of Reset and Init_Alternate; retail places it at
// 0x15A180, immediately before Init_Alternate (0x15A1B0). Callers are
// MeshModelClass::Get_Single_Texture (0x149540, through CurMatDesc at +0x94)
// and the descriptor's pass-0 state store (0x15D5B0). BFME2 returns an owning
// RefCountPtr; its count is a WORD at +4 and it releases through
// TextureClass::Release_Ref at 0x61ED10. The header inline Peek_Single_Texture
// is the /O1 twin at 0xD2026.
class TextureBaseClass
{
public:
    void Release_Ref();
protected:
    void *VTable;
    unsigned short NumRefs;
};

class TextureClass : public TextureBaseClass
{
public:
    void Add_Ref() { ++NumRefs; }
};

template <class T> class RefCountPtr
{
public:
    RefCountPtr(const RefCountPtr &that) : Referent(that.Referent) {
        if (Referent)
            Referent->Add_Ref();
    }
    ~RefCountPtr() { if (Referent) Referent->Release_Ref(); }
private:
    T *Referent;
};

class MeshMatDescClass
{
    char unknown0[0x78];
    RefCountPtr<TextureClass> Texture[4][2];
public:
    RefCountPtr<TextureClass> Get_Single_Texture(int pass, int stage) const;
};

RefCountPtr<TextureClass> MeshMatDescClass::Get_Single_Texture(int pass, int stage) const
{
    return Texture[pass][stage];
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeGetAUZA@BfmeSubAUZA@@QBE?AUBfmeHandleUZA@@HH@Z=?Get_Single_Texture@MeshMatDescClass@@QBE?AV?$RefCountPtr@VTextureClass@@@@HH@Z")
