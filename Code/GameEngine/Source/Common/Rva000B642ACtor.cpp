// cl: /MD
// ??0Rva000B642A@@QAE@PBHABUPristineBoneInfo@@@Z @0x000B642A 29B:
// 2-arg ctor int plus PristineBoneInfo via rowed copy 0x000B3FD1. Caller
// 0x000BCF96 passes Matrix3D local plus arg. Owner unproven honest Rva.
struct PristineBoneInfo { PristineBoneInfo(const PristineBoneInfo &other); };
struct Rva000B642A {
	Rva000B642A(const int *p, const PristineBoneInfo &q);
	int m_0;
	PristineBoneInfo m_4;
};
Rva000B642A::Rva000B642A(const int *p, const PristineBoneInfo &q)
	: m_0(*p), m_4(q)
{
}
