// cl: /O1 /MD
// ?rva005E8892@Rva005E888A@@QAEXXZ @0x005E8892 47B
// Gap body between 0x005E888A dtor and 0x005E88C1 deleting dtor; same class
// Rva005E888A (int key at +0, member at +4). Evidence: frameless push esi/edi,
// lea edi,[esi+4] reused for both member calls; rowed callees 0x005F8427,
// 0x005F88D6, 0x005F83F4; caller 0x005E88DD jmp.
class Rva005F8427
{
public:
	void rva005F8427();
};

int __cdecl Rva005F88D6Get(int arg);

struct Rva005F83F4Data
{
	int m_data[3];
};

class Rva005F83F4
{
public:
	void rva005F83F4(const Rva005F83F4Data &src);
};

class Rva005E888A
{
public:
	void rva005E8892();

private:
	int m_00;
	char m_04[8];
};

void Rva005E888A::rva005E8892()
{
	((Rva005F8427 *)&m_04)->rva005F8427();
	int p = Rva005F88D6Get(m_00);
	if (p != 0) {
		int q = *(int *)(p + 0x2c);
		if (q != 0) {
			((Rva005F83F4 *)&m_04)->rva005F83F4(*(const Rva005F83F4Data *)(q + 0x18));
		}
	}
}
