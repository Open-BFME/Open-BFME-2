// cl: /DNDEBUG /MD
// ??0Rva00785140Handle@@QAE@ABVAssetReference@@@Z @0x000A9EB2 27B handle-from-AssetReference ctor: vtable 0x00BC940C at [this] then AssetReference copy at +4 via ??0AssetReference@@QAE@ABV0@@Z rowed; caller 0x000AB193
class AssetReference
{
public:
    AssetReference(const AssetReference &that);
};
extern const void *const g_00BC940C[];
class Rva00785140Handle
{
public:
    Rva00785140Handle(const AssetReference &that);
private:
    const void *m_vptr;
    AssetReference m_ref;
};
Rva00785140Handle::Rva00785140Handle(const AssetReference &that) : m_vptr(g_00BC940C), m_ref(that)
{
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_00BC940C@@3QBQBXB=??_7Rva00785140Handle@@6B@")
