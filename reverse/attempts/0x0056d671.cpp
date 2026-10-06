// ??0Rva0056D690@@QAE@PBVLocomotorTemplate@@@Z
// partial score=0.9 date=2026-10-06
// cl: /MD
//
// ??0Rva0056D690@@QAE@PBVLocomotorTemplate@@@Z, retail 0x0056D671, 31 bytes.
// Ctor of Rva0056D690: base Locomotor ctor with template, vtable 0x0086DAC4,
// clear AsciiString at +0x26C via default. Evidence: vtable store, sibling
// dtor Rva0056D690Dtor with same vtable and AsciiString layout, caller
// 0x0041024A, ret 4.

class LocomotorTemplate;

class Locomotor
{
public:
	Locomotor(const LocomotorTemplate *tmpl);
	virtual ~Locomotor();
private:
	char m_pad[0x26C - 4];
};

class Rva0056D690 : public Locomotor
{
public:
	Rva0056D690(const LocomotorTemplate *tmpl);
	virtual ~Rva0056D690();
private:
	int m_26C;
};

Rva0056D690::Rva0056D690(const LocomotorTemplate *tmpl)
	: Locomotor(tmpl)
{
	m_26C &= 0;
}
