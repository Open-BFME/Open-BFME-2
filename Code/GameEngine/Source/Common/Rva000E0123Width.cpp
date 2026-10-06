// cl: /MD
// ?rva000E0123@Rva000E0123@@QAEXM@Z @0x000E0123 71B
// Evidence: unlock 4x Set_Width 0x0015E290 rowed; callers 0x000E09E8 0x000E0A0E in 0x000E0856; this+4 +8 +c +10 SegmentedLineClass ptrs; ret 4 float arg.
class SegmentedLineClass
{
public:
	void Set_Width(float width);
	void Set_Opacity(float opacity);
};

class Plus0Base
{
public:
	virtual void d00();
	virtual void d01();
	virtual void d02();
	virtual void d03();
	virtual void d04();
	virtual void d05();
	virtual void d06();
	virtual void d07();
	virtual void d08();
	virtual void d09();
	virtual void d10();
	virtual void d11();
	virtual void d12();
	virtual void d13();
	virtual void d14();
	virtual void d15();
	virtual void d16();
	virtual void d17();
	virtual void d18();
	virtual void d19();
	virtual void d20();
	virtual void d21();
	virtual void d22();
	virtual void virt5c(int v, float f);
};

class Plus0 : public Plus0Base
{
public:
	virtual void e24();
	virtual void e25();
	virtual void e26();
	virtual void e27();
	virtual void e28();
	virtual void e29();
	virtual void e30();
	virtual void e31();
	virtual void e32();
	virtual void e33();
	virtual void e34();
	virtual void e35();
	virtual void e36();
	virtual void e37();
	virtual void e38();
	virtual void e39();
	virtual void e40();
	virtual void e41();
	virtual void e42();
	virtual void e43();
	virtual void e44();
	virtual void e45();
	virtual void e46();
	virtual void e47();
	virtual void e48();
	virtual void e49();
	virtual void e50();
	virtual void e51();
	virtual void e52();
	virtual void e53();
	virtual void e54();
	virtual void e55();
	virtual void e56();
	virtual void e57();
	virtual void e58();
	virtual void e59();
	virtual void e60();
	virtual void e61();
	virtual void e62();
	virtual void e63();
	virtual void e64();
	virtual void e65();
	virtual void e66();
	virtual void e67();
	virtual void e68();
	virtual void e69();
	virtual void e70();
	virtual void e71();
	virtual void e72();
	virtual void e73();
	virtual void e74();
	virtual void e75();
	virtual void e76();
	virtual void e77();
	virtual void e78();
	virtual void e79();
	virtual void e80();
	virtual void e81();
	virtual void e82();
	virtual void e83();
	virtual void e84();
	virtual void e85();
	virtual void e86();
	virtual void e87();
	virtual void e88();
	virtual void e89();
	virtual void e90();
	virtual void e91();
	virtual void e92();
	virtual void e93();
	virtual void e94();
	virtual void e95();
	virtual void e96();
	virtual void e97();
	virtual void e98();
	virtual void e99();
	virtual void e100();
	virtual void e101();
	virtual void e102();
	virtual void e103();
	virtual void e104();
	virtual void e105();
	virtual void e106();
	virtual void e107();
	virtual void e108();
	virtual void e109();
	virtual void e110();
	virtual void virt1bc(int v);
};

class Rva000E0123
{
public:
	void rva000E0123(float width);
	void rva000E00C0(float opacity);
private:
	Plus0 *m_obj00;
	SegmentedLineClass *m_line0;
	SegmentedLineClass *m_line1;
	SegmentedLineClass *m_line2;
	SegmentedLineClass *m_line3;
};

void Rva000E0123::rva000E0123(float width)
{
	m_line0->Set_Width(width);
	m_line1->Set_Width(width);
	m_line2->Set_Width(width);
	m_line3->Set_Width(width);
}

void Rva000E0123::rva000E00C0(float opacity)
{
	m_line0->Set_Opacity(opacity);
	m_line1->Set_Opacity(opacity);
	m_line2->Set_Opacity(opacity);
	m_line3->Set_Opacity(opacity);
	m_obj00->virt1bc(1);
	m_obj00->virt5c(0, opacity);
}
