// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x009EBEC0: return a counted AssetRegistry lookup by value.

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
	AssetReference &operator=( const AssetReference &that )
	{
		CountedAsset *object = that.m_object;
		if ( object )
		{
			++*(unsigned short *)((char *)object + 4);
		}
		if ( m_object )
		{
			m_object->Release_Ref();
		}
		m_object = object;
		return *this;
	}

private:
	CountedAsset *m_object;
};

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
