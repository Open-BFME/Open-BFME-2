// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/Rva002C7F30NestedVirtualDispatch.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?dispatch@Rva002C7F30Object@@QAEXH@Z 0x004A97D3 (27B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
class Rva002C7F30Nested
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6();
};

class Rva002C7F30Object
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14();
	virtual void v15( int value );

	void dispatch( int value );

	unsigned char m_padding[0xDC];
	Rva002C7F30Nested *m_nested;
};

void Rva002C7F30Object::dispatch( int value )
{
	v15( value );
	m_nested->v6();
}
