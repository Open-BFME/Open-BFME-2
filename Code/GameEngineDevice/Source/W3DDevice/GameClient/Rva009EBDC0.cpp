// Retail 0x009EBDC0: return the registry's current counted asset.
// The dump's generated name is replaced by the recovered return-by-value ABI.

#include "../../../Include/W3DDevice/GameClient/CountedAsset.h"

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

#include "../../../Include/W3DDevice/GameClient/AssetRegistry.h"

extern class Q1Receiver0134FAAC *TheQ1Receiver;

AssetReference Rva009EBDC0()
{
	return ((AssetRegistry *)TheQ1Receiver)
		? ((AssetRegistry *)TheQ1Receiver)->Get_Current_Asset()
		: AssetReference();
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeNextResource@@YA?AUBfmeResetAnyRef@@XZ=?Rva009EBDC0@@YA?AVAssetReference@@XZ")
