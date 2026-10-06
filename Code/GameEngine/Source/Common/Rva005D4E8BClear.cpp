// cl: /MD
// ?rva005D4E8B@Rva005D4E8B@@QAEXXZ, RVA 0x005D4E8B, 29B. Unlock lane holder clear:
// releases TreeHintRef embedded at [ptr]+4+[[ptr+4]+4] via rowed fastcall
// 0x0007DEEF then nulls holder. Evidence: retail mov eax,[esi]; test-je;
// mov ecx,[eax+4]; mov ecx,[ecx+4]; lea ecx,[ecx+eax+4]; call row; and [esi],0;
// caller 0x005D4F19 uses as this+0xC with tail jmp to Rva002BED91::clear.
struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
struct Rva005D4E8BDesc
{
	int m_00;
	int m_off04;
};
struct Rva005D4E8BObj
{
	void *m_00;
	Rva005D4E8BDesc *m_desc04;
};
class Rva005D4E8B
{
public:
	void rva005D4E8B();
private:
	Rva005D4E8BObj *m_ptr;
};
void Rva005D4E8B::rva005D4E8B()
{
	Rva005D4E8BObj *p = m_ptr;
	if (p != 0)
	{
		ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)((char *)p + 4 + p->m_desc04->m_off04));
		m_ptr = 0;
	}
}
