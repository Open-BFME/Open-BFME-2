// cl: /DNDEBUG /MD /EHsc
// ?rva0029B17C@Rva0029B17C@@QAEXXZ @0x0029B17C 11B.
// Forwarder: loads member at +0x7F4 then tail-jumps to its vtable slot 9
// (0x24). Callers at 0x00213B3B 0x002B8A27 0x003F7FD2 pass singleton in ecx
// with no stack args and ignore return; same 11B shape as other disp8
// virtual forwards.
struct Helper0029B17C {
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual void f4();
	virtual void f5();
	virtual void f6();
	virtual void f7();
	virtual void f8();
	virtual void slot9();
};
class Rva0029B17C {
public:
	void rva0029B17C();
private:
	char m_pad[0x7F4];
	Helper0029B17C *m_7F4;
};
void Rva0029B17C::rva0029B17C()
{
	m_7F4->slot9();
}
// ?rva0029B1A1@Rva0029B1A1@@QAEXXZ @0x0029B1A1 11B.
// Forwarder: loads member at +0x7F4 then tail-jumps to
// ?rva004E5803@Rva004E57E6@@QAEXXZ. Evidence: caller 0x0056ABB3 passes
// TheInGameUI in ecx with no stack args and ignores return; callee rowed in
// Code/GameEngine/Source/Common/Bfme/Rva004E57E6Method.cpp; same 11B disp32
// forward shape as 0x0029B17C.
struct Rva004E57E6Pair {
	int m_0;
	int m_4;
};
class Rva004E57E6 {
public:
	void rva004E5803();
	void rva004E57E6(Rva004E57E6Pair *p, float f);
};
class Rva0029B1A1 {
public:
	void rva0029B1A1();
private:
	char m_pad[0x7F4];
	Rva004E57E6 *m_7F4;
};
void Rva0029B1A1::rva0029B1A1()
{
	m_7F4->rva004E5803();
}
// ?rva0029B187@Rva0029B187@@QAEXPAURva004E57E6Pair@@M@Z @0x0029B187 26B.
// Forwarder with float+pair args: loads member at +0x7F4 then calls
// ?rva004E57E6@Rva004E57E6@@QAEXPAURva004E57E6Pair@@M@Z. Evidence: caller
// 0x0056AB7A passes pair and float; callee rowed in Rva004E57E6Method.cpp;
// same +0x7F4 subsystem as 0x0029B17C/0x0029B1A1; ret 8 matches 8B args.
class Rva0029B187 {
public:
	void rva0029B187(Rva004E57E6Pair *p, float f);
private:
	char m_pad[0x7F4];
	Rva004E57E6 *m_7F4;
};
void Rva0029B187::rva0029B187(Rva004E57E6Pair *p, float f)
{
	m_7F4->rva004E57E6(p, f);
}
