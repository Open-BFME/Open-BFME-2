// cl: /O1 /MD /GX
// ?rva002710EC@Rva002710EC@@QAEXXZ @0x002710EC (28B): pointer-array loop
// calling vslot 39. Retail: esi=[ecx+0x14C]; jmp inc; call [eax+0x9C];
// inc: esi+=4; ecx=[esi]; test; jne call; pop esi; ret. No E8; single
// virtual call; null-terminated array (first element skipped – header?);
// address-derived.
class Rva002710ECInner
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
};

class Rva002710EC
{
public:
	void rva002710EC();
private:
	char m_pad[0x14C];
	Rva002710ECInner **m_array;
};

// ?rva002710EC@Rva002710EC@@QAEXXZ
void Rva002710EC::rva002710EC()
{
	Rva002710ECInner **p = m_array;
	goto check;
loop:
	(*p)->v39();
	p++;
check:
	if (*p != 0)
		goto loop;
}
