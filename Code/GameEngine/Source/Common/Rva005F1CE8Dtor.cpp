// cl: /MD
// ??1Rva005F1CE8@@UAE@XZ @0x005F1CE8 14B: virtual dtor sets vtable g_00C79138 then tail-jmps to rowed holder clear 0x005F1B90.
// Evidence: vtable store plus add ecx 4 plus jmp to rowed 0x005F1B90; caller deleting dtor 0x005F1D2B plus thunk 0x005E3585.
class Rva005F1B90
{
public:
	void rva005F1B90();
private:
	void *m_00;
};
extern const void *const g_00C79138[];
class Rva005F1CE8
{
public:
	__declspec(noinline) virtual ~Rva005F1CE8();
private:
	Rva005F1B90 m_04;
};

Rva005F1CE8::~Rva005F1CE8()
{
	m_04.rva005F1B90();
}

// Native005E3585 five-byte JMP to the owned provider; address-derived dtor
// spelling is the existing deleting-caller pin, original class unknown.
class Rva005E3585 { public: ~Rva005E3585(); };
Rva005E3585::~Rva005E3585()
{
    reinterpret_cast<Rva005F1CE8 *>(this)->Rva005F1CE8::~Rva005F1CE8();
}
