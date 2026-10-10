// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// Retail 0x005AE5EE..0x005AE60B (29 bytes), __thiscall, ret 4.
//
// Copies a four-dword record into the 16-byte slot at this+0x90 through the
// shared four-argument setter at 0x00237E45 (rowed as Vector4::Set; ICF folds
// every four-dword member setter onto that body). Its only caller is the
// GameSpy response handler 0x005AF12F (call at 0x005AF56F) which passes the
// response record's +0x11C block into its local staging object.
//
// The arguments are pushed straight from memory (push dword ptr [eax+N]),
// which /O1 emits only for integer-typed arguments: a float-typed argument
// is moved through fld/fstp. The record is therefore integer data and the
// setter is reached through its folded Vector4::Set name.
struct Rva005AE5EEQuad
{
	int a;
	int b;
	int c;
	int d;
};

class Vector4
{
public:
	void Set(float x, float y, float z, float w);
	float X, Y, Z, W;
};

class Rva005AE5EE
{
public:
	void rva005AE5EE(const Rva005AE5EEQuad *value);
	char m_pad[0x90];
	Vector4 m_value;
};

typedef void (Vector4::*Rva005AE5EEQuadSetter)(int, int, int, int);

void Rva005AE5EE::rva005AE5EE(const Rva005AE5EEQuad *value)
{
	(m_value.*reinterpret_cast<Rva005AE5EEQuadSetter>(&Vector4::Set))(value->a, value->b, value->c, value->d);
}
