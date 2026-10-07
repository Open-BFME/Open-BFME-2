// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc

class HAnimClass;

class Rva005ECFE4
{
public:
	static void *rva005ED15D(void *, void *, void *);
};

// ?rva005CFB9E@Rva005CFB9E@@QAEXPAX00@Z @0x005CFB9E 36B
// Target evidence: central table slot 2 at 0x0087557C; adjacent entries are
// RenderObjClass::Set_Animation slots. Class identity remains address-derived.
// The +0x14 field and lazy helper relationship are inferred from target bytes.
class Rva005CFB9E
{
public:
	void rva005CFB9E(void *, void *, void *);

private:
	char m_padToField[0x14];
	void *m_field;
};

void Rva005CFB9E::rva005CFB9E(void *animation, void *frame, void *mode)
{
	if (m_field == 0)
		m_field = Rva005ECFE4::rva005ED15D(animation, frame, mode);
}
