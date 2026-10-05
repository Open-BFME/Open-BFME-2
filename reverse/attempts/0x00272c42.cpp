// ?rva00272C42@Rva00272C42@@QAEXH@Z
// partial score=0.9 date=2026-10-05
// cl: /O2 /MD /GX
// ?rva00272C42@Rva00272C42@@QAEXH@Z @0x00272C42 (25B): forwarder tail-jumping
// to the inner object's vslot 53 (0xD4) with the caller's int argument.
// Retail: eax=[ecx+0x14C]; eax=[eax]; je ret; edx=[eax]; ecx=eax;
// jmp [edx+0xD4]; ret 4. No E8 calls; address-derived names.
class Rva00272C42Inner
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v40();
	virtual void v41();
	virtual void v42();
	virtual void v43();
	virtual void v44();
	virtual void v45();
	virtual void v46();
	virtual void v47();
	virtual void v48();
	virtual void v49();
	virtual void v50();
	virtual void v51();
	virtual void v52();
	virtual void v53(int arg);
};

struct Rva00272C42Holder
{
	Rva00272C42Inner *m_inner;
};

class Rva00272C42
{
public:
	void rva00272C42(int arg);
private:
	char m_pad[0x14C];
	Rva00272C42Holder *m_holder;
};

// ?rva00272C42@Rva00272C42@@QAEXH@Z
void Rva00272C42::rva00272C42(int arg)
{
	Rva00272C42Inner *inner = m_holder->m_inner;
	if (inner == 0)
		return;
	inner->v53(arg);
}
