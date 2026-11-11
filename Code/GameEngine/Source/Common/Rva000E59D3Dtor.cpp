// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// ??1Rva000E59D3@@UAE@XZ retail 0x000E59D3 82B
// Own vptr BCE9E0; under EH state 2 the rowed ?rva000E473F@W3DFloorBuffer@@QAEXXZ
// 0x000E473F runs on this object; then member dtors -- the STLport list base
// at +0x18 (rowed ??1?$_List_base@HV?$allocator@H@_STL@@@_STL@@QAE@XZ
// 0x004EC395) and the texture handle at +0x14 (rowed
// ?Release_Ref@TextureClass@@QAEXXZ 0x0061ED10); the base's inline dtor
// restores BBB554. Names address-derived.

#include <list>

// Retail calls the out-of-line list-base destructor at RVA 0x004EC395.
template <> _STL::_List_base<int, _STL::allocator<int> >::~_List_base();

class TextureClass
{
public:
	void Release_Ref();
};

class Rva000E59D3TextureHandle
{
public:
	~Rva000E59D3TextureHandle()
	{
		if (m_texture)
			m_texture->Release_Ref();
	}

	TextureClass *m_texture;
};

#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/W3DFloorBuffer.h"

class Rva000E59D3Base
{
public:
	virtual ~Rva000E59D3Base() {}
};

class Rva000E59D3 : public Rva000E59D3Base
{
public:
	virtual ~Rva000E59D3();

private:
	char m_pad04[0x14 - 4];
	Rva000E59D3TextureHandle m_texture; // +0x14
	_STL::list<int> m_list; // +0x18
};

Rva000E59D3::~Rva000E59D3()
{
	reinterpret_cast<W3DFloorBuffer *>(this)->rva000E473F();
}
