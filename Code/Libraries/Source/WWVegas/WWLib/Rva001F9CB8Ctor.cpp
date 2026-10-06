// cl: /DNDEBUG /MD
// ??0Rva001F9CB8@@QAE@XZ @0x001F9CB8 18B: default ctor zeroing +0 then rowed Rva001F9060 at +4 plus return this.
// Evidence: push esi mov esi ecx and [esi] 0 lea ecx [esi+4] call 0x001F9060 mov eax esi pop esi ret; chain from 0x001F9060.
class Rva001F9060
{
public:
	Rva001F9060();
};

class Rva001F9CB8
{
public:
	Rva001F9CB8();
private:
	int m_00;
	Rva001F9060 m_04;
};

Rva001F9CB8::Rva001F9CB8()
	: m_00(0)
{
}
