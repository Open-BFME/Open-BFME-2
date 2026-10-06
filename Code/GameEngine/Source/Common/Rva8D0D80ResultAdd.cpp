// cl: /MD
//
// ?rva006FBB90@Rva8D0D80Result@@QAEXPAVRva8D0D80String@@PAVRva8D0D80Value@@@Z, retail 0x006FBB90, 8 bytes.
// Rva8D0D80Result::add forwarder over m_table at +8 tail-jumping to Rva8D0D80Table::add
// at 0x0070B410 (pin-only). Tail position return m_table.add gives add ecx 8 plus jmp at /O1.
// Evidence: 12 callers in FUN_00ade8e0; BFME1 donor Rva8D0D80BuildObject.cpp Result has Table at +8
// (base Value 8B: vptr plus m_flags); layout +8 proven by sibling 0x006FBBA0 using lea ecx esi+8
// for same Table::add call; pin Table::add via addIfAbsent 0x0070B4C0 call target.

class Rva8D0D80String;
class Rva8D0D80Value;

class Rva8D0D80Table
{
public:
	void add(Rva8D0D80String *name, Rva8D0D80Value *value);
};

class Rva8D0D80Value
{
public:
	virtual void addRef();
	virtual void release();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();

	unsigned m_flags;
};

class Rva8D0D80Result : public Rva8D0D80Value
{
public:
	void rva006FBB90(Rva8D0D80String *name, Rva8D0D80Value *value);

private:
	Rva8D0D80Table m_table; // +8
};

void Rva8D0D80Result::rva006FBB90(Rva8D0D80String *name, Rva8D0D80Value *value)
{
	m_table.add(name, value);
}
