// cl: /O1 /MD
// ?rva00577944@Rva005F83B9@@QAEXXZ, retail 0x00577944, 20 bytes. Calls pinned helpers on member at +4 then tail-jmps.
// Evidence: retail mov ecx [esi+4] call 0x005C6D9C then mov ecx [esi+4] jmp 0x005C674A; caller at 0x005F83BD in Rva005F83B9Notify; gap between 0x00577936 and 0x00577966 in Rva000AD6F4Members.
class Rva005C6D4D
{
public:
	void rva005C6D9C();
};

class Rva005C674A
{
public:
	void rva005C674A();
};

class Rva005F83B9
{
public:
	void rva00577944();
private:
	char m_pad0[4];
	void *m_p4;
};

void Rva005F83B9::rva00577944()
{
	((Rva005C6D4D *)m_p4)->rva005C6D9C();
	((Rva005C674A *)m_p4)->rva005C674A();
}
