// cl: /MD
//
// ?rva0007BB4B@Rva0007BB4B@@QAE?AVAssetReference@@XZ @ 0x0007BB4B (46B):
// by-value AssetReference getter selecting between the two refs at +0x14
// and +0x18. Retail copies into the hidden return buffer via the rowed
// copy ctor ??0AssetReference@@QAE@ABV0@@Z (0x000424BB), returning +0x18
// only when the flag byte at 0x009E1FFC is set and the +0x18 ref holds a
// counted object (its first dword, the pointer, is nonzero), else +0x14.
// Shape follows the proven sibling Rva000F5D1BGet (0x000F5D1B, same
// frame/slot/call/leave/ret sequence, // cl: /O1 /MD): two return sites
// tail-merge to one E8, and the EBP frame plus zeroed [ebp-4] slot are the
// compiler's by-value-return machinery, not a source local. Owner unproven
// (neighbours are the Rva0007BB16Record dtor rows), so the class carries
// the honest address name. m_object is public here only for layout access;
// the canonical AssetReference keeps it private
// (Code/GameEngineDevice/Source/W3DDevice/GameClient/Rva009EBDC0.cpp).

class AssetReference
{
public:
	AssetReference(const AssetReference &that);
	~AssetReference();

public:
	void *m_object;
};

extern unsigned char g_009E1FFC;
// g_009E1FFC: matched references place it at VA 0xde1ffc (zero-filled .bss).
unsigned char g_009E1FFC;

class Rva0007BB4B
{
public:
	AssetReference rva0007BB4B();

private:
	int m_pad00[5];
	AssetReference m_ref14;
	AssetReference m_ref18;
};

AssetReference Rva0007BB4B::rva0007BB4B()
{
	if (g_009E1FFC != 0 && m_ref18.m_object != 0)
		return m_ref18;
	return m_ref14;
}
