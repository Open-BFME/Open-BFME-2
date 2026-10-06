// cl: /MD
//
// ?rva005FED59@Rva005FED59@@QBEXXZ @0x005FED59 8B
// Tail-jmp to rowed ?validate@?$StringBase@G@@ABEXXZ at 0x000B3FD0
// via member at +8. Evidence: add ecx-8 plus jmp, 3 callers,
// prev/next neighbours, honest address name.
template <typename T> class StringBase
{
	friend class Rva005FED59;
	friend class Rva005E218F;
	void validate() const;
};

class Rva005FED59
{
public:
	void rva005FED59() const;
private:
	char m_pad00[8];
};

void Rva005FED59::rva005FED59() const
{
	((StringBase<unsigned short> *)((char *)this + 8))->validate();
}

// ?rva005E218F@Rva005E218F@@UAEXXZ @ 0x005E218F (14B).
// Vtable slot 3 of 0x00877B2C; ref table slot 0x00877B38.
// Validates wide string at +0 via rowed validate 0x000B3FD0 then sets +0x2C.
class Rva005E218F
{
public:
	virtual void d00() {}
	virtual void d01() {}
	virtual void d02() {}
	virtual void rva005E218F();
private:
	char m_pad04[0x28];
	unsigned char m_2C;
};

void Rva005E218F::rva005E218F()
{
	((StringBase<unsigned short> *)this)->validate();
	m_2C = 1;
}
