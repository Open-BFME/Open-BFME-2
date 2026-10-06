// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0030BBC8@Rva0030BBC8@@QAEXM@Z @0x0030BBC8 29B
// Guarded float setter: store float at +0x5C and virtual slot 9 on change.
// Evidence: callers 0x0030C794 0x003293B6; prev 0x0030BBB4 int setter slot12 next 0x0030BBE5 slot11 same shape.
class Rva0030BBC8
{
public:
	void rva0030BBC8(float v);
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void notify();
private:
	char m_pad[0x58];
	float m_val;
};
void Rva0030BBC8::rva0030BBC8(float v)
{
	if (v == m_val)
		return;
	m_val = v;
	notify();
}
