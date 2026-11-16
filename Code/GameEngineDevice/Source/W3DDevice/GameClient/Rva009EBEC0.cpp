// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x009EBEC0: return a counted AssetRegistry lookup by value.

#include "../../../Include/W3DDevice/GameClient/CountedAsset.h"

#include "../../../../GameEngine/Include/Common/AssetReference.h"

inline AssetReference::AssetReference( const AssetReference &that ) : field00( that.field00 )
{
	if ( field00 )
	{
		++*(unsigned short *)((char *)field00 + 4);
	}
}

inline AssetReference::~AssetReference()
{
	if ( field00 )
	{
		field00->Release_Ref();
	}
}

#include "../../../Include/W3DDevice/GameClient/AssetRegistry.h"

class AssetName
{
public:
	const char *Peek_Buffer() const
	{
		return m_data ? m_data + 8 : "";
	}

private:
	const char *m_data;
};

extern class Q1Receiver0134FAAC *TheQ1Receiver;

AssetReference Rva009EBEC0( const AssetName &name )
{
	return ((AssetRegistry *)TheQ1Receiver)
		? ((AssetRegistry *)TheQ1Receiver)->Find_Asset( name.Peek_Buffer() )
		: AssetReference();
}
