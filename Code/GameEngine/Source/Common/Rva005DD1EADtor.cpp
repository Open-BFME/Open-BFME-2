// cl: /DNDEBUG /MD /EHs

// ??1Rva005DD1EA@@UAE@XZ, RVA 0x005DD1EA, 65B. Chain lane: virtual dtor
// storing vtable 0x008769B0, freeing the pointer at +0x20 via rowed _free
// 0x00030830, then calling the rowed base dtor ??1Rva005DE9E3@@UAE@XZ at
// 0x005DE9E3 with this. Base sits at +0 (16B: vector plus int); pad to +0x20.
// Callers at 0x005B7FD7/0x005C1A73/0x005DD5ED; landing unblocks 0x005DD5ED
// (its ??_G), 0x005C1A36 and 0x005B7FA4. Flags copy the prev neighbour
// V3PolyCopyCtors.cpp.
class Rva005DE9E3
{
public:
	virtual ~Rva005DE9E3();
private:
	char m_base_pad[0x0C];
};

class Rva005DD1EA : public Rva005DE9E3
{
public:
	virtual ~Rva005DD1EA();
private:
	char m_pad10[0x10];
	void *m_20;
};

extern "C" void free(void *);

Rva005DD1EA::~Rva005DD1EA()
{
	if (m_20)
		free(m_20);
}
