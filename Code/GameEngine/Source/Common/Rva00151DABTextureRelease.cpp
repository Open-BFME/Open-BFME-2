// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??1Rva00151DAB@@QAE@XZ @0x00151DAB 13B.
// 8-byte holder with TextureBaseClass* at +4; dtor releases it via rowed
// Release_Ref 0x0061ED10 when non-null. Callers 0x00151EB1 deleting dtor
// plus vector Destroy loop 0x0015209B over 8-byte elements plus list free
// 0x00170B19 member at +0x10. No vptr stores so non-virtual QAE.
class TextureBaseClass
{
public:
	void Release_Ref();
};

class Rva00151DAB
{
public:
	~Rva00151DAB();
private:
	int m_a;
	TextureBaseClass *m_tex;
};

Rva00151DAB::~Rva00151DAB()
{
	if (m_tex)
		m_tex->Release_Ref();
}
