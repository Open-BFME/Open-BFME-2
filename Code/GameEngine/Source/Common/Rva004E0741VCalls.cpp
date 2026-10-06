// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva004E0741@Rva004E0741@@QBEXXZ @0x004E0741 15B + ?rva004E0750@Rva004E0750@@QBEXXZ @0x004E0750 15B
// Conditional void virtual tail-calls: if dword at +0x2c == 0 return void else
// tail-jump to virtual slot 1 (0741, offset 4) / slot 2 (0750, offset 8) of the
// object at +0x2c. Retail is cmp [ecx+0x2c],0 / je ret / mov ecx,[ecx+0x2c] /
// mov eax,[ecx] / jmp [eax+4|8] / ret (15B). /O1 selects cmp-mem plus reload
// (defaults give mov+test plus mov ecx,eax).
// Evidence: unlock lane twins sharing +0x2c check; callers at 0x005CE631
// 0x005CF0C2 (0741) and 0x005CE110 0x005CE578 (0750); void return (no eax use).
class Rva004E0741Target
{
public:
	virtual void v0();
	virtual void v1();
};

class Rva004E0741
{
public:
	void rva004E0741() const;
	char m_pad[0x2c];
	Rva004E0741Target *m_ptr;
};
void Rva004E0741::rva004E0741() const
{
	if (m_ptr == 0)
		return;
	m_ptr->v1();
}

class Rva004E0750Target
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
};

class Rva004E0750
{
public:
	void rva004E0750() const;
	char m_pad[0x2c];
	Rva004E0750Target *m_ptr;
};
void Rva004E0750::rva004E0750() const
{
	if (m_ptr == 0)
		return;
	m_ptr->v2();
}
