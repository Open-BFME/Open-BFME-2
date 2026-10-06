// cl: /DNDEBUG /MD
//
// ?rva000B3271@Rva000B3271@@QAEXPBVRadiusDecalTemplate@@@Z, retail 0x000B3271, 81 bytes.
// Leaf via vtable slot 29 of W3D draws (Horde Quadruped Supply Truck Tank Sail).
// Copies RadiusDecalTemplate at +0x228 via rowed 0x330CDD then BIC flow via pin 0x290FC9
// then virtual at +0x84 with field pointer float and result pointer.

class RadiusDecalTemplate
{
public:
	void rva00330CDD(const RadiusDecalTemplate &other);
private:
	char m_pad[0x34];
};

class BfmeSubBIC
{
public:
	int bfmeAskBIC();
	char m_pad00[0x38];
	int m_field38;
	char m_pad3C[0x8];
	float m_float44;
};

class Rva000B3271Holder
{
public:
	char m_pad[0xFC];
	BfmeSubBIC *m_bic;
};

class Rva000B3271
{
public:
	virtual void v00() = 0;
	virtual void v01() = 0;
	virtual void v02() = 0;
	virtual void v03() = 0;
	virtual void v04() = 0;
	virtual void v05() = 0;
	virtual void v06() = 0;
	virtual void v07() = 0;
	virtual void v08() = 0;
	virtual void v09() = 0;
	virtual void v10() = 0;
	virtual void v11() = 0;
	virtual void v12() = 0;
	virtual void v13() = 0;
	virtual void v14() = 0;
	virtual void v15() = 0;
	virtual void v16() = 0;
	virtual void v17() = 0;
	virtual void v18() = 0;
	virtual void v19() = 0;
	virtual void v20() = 0;
	virtual void v21() = 0;
	virtual void v22() = 0;
	virtual void v23() = 0;
	virtual void v24() = 0;
	virtual void v25() = 0;
	virtual void v26() = 0;
	virtual void v27() = 0;
	virtual void v28() = 0;
	virtual void v29() = 0;
	virtual void v30() = 0;
	virtual void v31() = 0;
	virtual void v32() = 0;
	virtual void virt84(void *a, float b, int *c) = 0;
	void rva000B3271(const RadiusDecalTemplate *tmpl);
private:
	int m_pad4;
	Rva000B3271Holder *m_holder;
	char m_padC[0x21C];
	RadiusDecalTemplate m_decal;
};

void Rva000B3271::rva000B3271(const RadiusDecalTemplate *tmpl)
{
	if (tmpl) {
		m_decal.rva00330CDD(*tmpl);
		BfmeSubBIC *bic = m_holder->m_bic;
		if (bic) {
			int n = bic->bfmeAskBIC();
			virt84(&bic->m_field38, bic->m_float44, &n);
		}
	}
}
