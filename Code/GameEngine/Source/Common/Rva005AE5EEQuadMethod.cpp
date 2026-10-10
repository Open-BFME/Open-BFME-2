// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// Retail 0x005AE5EE..0x005AE60B (29 bytes), __thiscall, ret 4.
//
// Copies a four-dword record into the 16-byte slot at this+0x90 through the
// four-int setter at 0x00237E45 (Rva00237E45::rva00237E45). Its only caller is
// the GameSpy response handler 0x005AF12F (call at 0x005AF56F) which passes the
// response record's +0x11C block into its local staging object.
//
// The arguments are pushed straight from memory (push dword ptr [eax+N]),
// which /O1 emits only for integer-typed arguments: a float-typed argument
// is moved through fld/fstp. The record is therefore integer data, and so is
// the setter: its body copies through eax, where /arch:SSE would use movss
// for floats.
struct Rva005AE5EEQuad
{
	int a;
	int b;
	int c;
	int d;
};

class Rva00237E45
{
public:
	void rva00237E45(int a, int b, int c, int d);
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
};

class Rva005AE5EE
{
public:
	void rva005AE5EE(const Rva005AE5EEQuad *value);
	char m_pad[0x90];
	Rva00237E45 m_value;
};

void Rva005AE5EE::rva005AE5EE(const Rva005AE5EEQuad *value)
{
	m_value.rva00237E45(value->a, value->b, value->c, value->d);
}
