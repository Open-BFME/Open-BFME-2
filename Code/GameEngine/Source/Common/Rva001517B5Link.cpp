// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva001517B5@Rva00151632@@QAEXXZ at 0x001517B5 (41B). Slot 7 of vtable
// 0x007D3A6C for the Rva00151632 class proven by ctor 0x001515CA plus dtor
// rows. Clears the +0x14 link via rowed 0x00151744 then frees its slot-0
// virtual result via rowed operator delete 0x0002FD60 and nulls the link.
// Called from nothing rowed. Layout mirrors Rva00151632Ctor TU.
class FXShaderAsset
{
public:
	class Impl;
};

class FXShaderAsset::Impl
{
public:
	virtual void *get(int x);
	void Unload();
};

class GenBase009EB7D0
{
public:
	GenBase009EB7D0();
	virtual ~GenBase009EB7D0();
};

class Rva00151632 : public GenBase009EB7D0
{
public:
	void rva001517B5();
	char m_pad04[0x10]; // +0x04..+0x13
	FXShaderAsset::Impl *m_link; // +0x14
};

void Rva00151632::rva001517B5()
{
	m_link->Unload();
	FXShaderAsset::Impl *link = m_link;
	void *p = link ? link->get(0) : 0;
	::operator delete(p);
	m_link = 0;
}
