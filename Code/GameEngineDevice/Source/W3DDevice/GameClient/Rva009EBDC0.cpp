// Retail 0x009EBDC0: return the registry's current counted asset.
// The dump's generated name is replaced by the recovered return-by-value ABI.

class CountedAsset
{
public:
	void Release_Ref();
};

class AssetReference
{
public:
	AssetReference() : m_object( 0 ) {}
	AssetReference( const AssetReference &that ) : m_object( that.m_object )
	{
		if ( m_object )
		{
			++*(unsigned short *)((char *)m_object + 4);
		}
	}
	~AssetReference()
	{
		if ( m_object )
		{
			m_object->Release_Ref();
		}
	}

private:
	CountedAsset *m_object;
};

class AssetRegistry
{
public:
	AssetReference Get_Current_Asset();
};

extern AssetRegistry *g_theAssetRegistry;

AssetReference Rva009EBDC0()
{
	return g_theAssetRegistry
		? g_theAssetRegistry->Get_Current_Asset()
		: AssetReference();
}

// ?g_theAssetRegistry@@3PAVAssetRegistry@@A: the global at this VA is ?TheQ1Receiver@@3PAVQ1Receiver0134FAAC@@A; this name is an alias for it.
#pragma comment(linker, "/alternatename:?g_theAssetRegistry@@3PAVAssetRegistry@@A=?TheQ1Receiver@@3PAVQ1Receiver0134FAAC@@A")
#pragma comment(linker, "/alternatename:?Rva00F4FAACRegistry@@3PAVRva009EEC60Registry@@A=?TheQ1Receiver@@3PAVQ1Receiver0134FAAC@@A")
// ?g_theAssetRegistry@@3PAVAssetRegistry@@A: the global at VA 0xe09c0c is ?TheQ1Receiver@@3PAVQ1Receiver0134FAAC@@A.
#pragma comment(linker, "/alternatename:?g_theAssetRegistry@@3PAVAssetRegistry@@A=?TheQ1Receiver@@3PAVQ1Receiver0134FAAC@@A")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeNextResource@@YA?AUBfmeResetAnyRef@@XZ=?Rva009EBDC0@@YA?AVAssetReference@@XZ")
