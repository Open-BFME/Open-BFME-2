// cl: /O1 /DNDEBUG /MD
// ?rva005757A5@Rva005757A5@@QAEXH@Z retail 0x005757A5 84B
// Ghidra gives an 84B body at 0x005757A5. It constructs the rowed local
// Rva005756B6 from this pointer, reads the dword at +4 of the opaque +0x18
// holder through the rowed 0x005ED28A getter (which adds 0x28), then uses the
// resulting address at +0x1C with the raw field at this+0x1C and its int
// argument in the existing 0x005CBB4A helper. These field meanings are not
// established. The helper's address-derived C++ owner name is reused only to
// emit the existing symbol; this call supplies the Rva005756B6 local.
class Rva0005CB9F3DwordImmSetter
{
public:
	void apply();
};
class Rva005756B6
{
public:
	Rva005756B6(int arg);
	__forceinline ~Rva005756B6()
	{
		((Rva0005CB9F3DwordImmSetter *)this)->apply();
	}
private:
	unsigned int m_layout[3];
};
class Rva00574815
{
public:
	void rva005CBB4A(int first, int second, int third);
};
class Rva005ED28AAddDwordField
{
public:
	int get() const;
};
struct Rva005757A5SlotView
{
	unsigned int m_00;
	Rva005ED28AAddDwordField *m_04;
};
struct Rva005757A5ResultView
{
	char m_00[0x1c];
	int m_1c;
};
class Rva005757A5
{
public:
	void rva005757A5(int arg);
private:
	char m_pad00[0x18];
	Rva005757A5SlotView *m_18;
	int m_1c;
};
void Rva005757A5::rva005757A5(int arg)
{
	Rva005756B6 local((int)this);
	Rva005757A5ResultView *result = (Rva005757A5ResultView *)m_18->m_04->get();
	((Rva00574815 *)&local)->rva005CBB4A(m_1c, arg, result->m_1c);
}
