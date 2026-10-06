// cl: /MD
// ?Rva000F5D1BGet@@YA?AVAssetReference@@H@Z @0x000F5D1B 32B; array-indexed AssetReference getter over 0x00DE1F8C.
// Retail: push ebp / mov ebp esp / push ecx / mov eax [ebp+c] / mov ecx [ebp+8] / and [ebp-4] 0 / lea eax [eax*4+0xde1f8c] / push eax / call 0x424BB copy ctor / mov eax [ebp+8] / leave / ret.
// Target facts: hidden-pointer return; source is global array at VA 0x00DE1F8C element size 4; callee rowed 0x000424BB; caller 0x000F5D9C passes index 0 and hidden at [ebp-0x10].
// Callers: 0x000F5D9C in 0x000F5D3B; callees: ??0AssetReference@@QAE@ABV0@@Z.
// Not established: owning TU/class and global identities; names are address-derived.
class CountedAsset
{
public:
	void Release_Ref();
};

class AssetReference
{
public:
	AssetReference(const AssetReference &other);
	~AssetReference();
private:
	CountedAsset *m_object;
};

extern AssetReference g_Va00DE1F8C[];

AssetReference Rva000F5D1BGet(int index)
{
	return g_Va00DE1F8C[index];
}
