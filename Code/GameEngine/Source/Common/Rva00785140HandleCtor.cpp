// cl: /DNDEBUG /MD
// ??0Rva00785140Handle@@QAE@ABVAssetReference@@@Z @0x000A9EB2 27B handle-from-AssetReference ctor: vtable 0x00BC940C at [this] then AssetReference copy at +4 via ??0AssetReference@@QAE@ABV0@@Z rowed; caller 0x000AB193
class AssetReference
{
public:
	AssetReference(const AssetReference &);
	AssetReference();
	~AssetReference();
	unsigned pointer; // +0x00
};
// Native new-expression carries no delete-on-throw state for this 27B
// pointer-copy constructor; carry that observed caller contract.
class Rva00785140Handle
{
public:
	__declspec(nothrow) Rva00785140Handle(const AssetReference &);
	virtual ~Rva00785140Handle();
private:
	AssetReference ref; // +0x04
};
Rva00785140Handle::Rva00785140Handle(const AssetReference &that) : ref(that)
{
}

