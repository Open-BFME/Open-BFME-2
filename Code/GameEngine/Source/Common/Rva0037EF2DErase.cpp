// cl: /MD /Oi
// ?rva0037EF2D@Rva0037EF2D@@QAEXI@Z @0x0037EF2D 48B. Search 0xD8-byte array at
// this+4 for element with dword +0xA4 == key then erase via rowed 0x002E204D.
// Evidence: call 0x002E204D rowed in Rva002E204DErase.cpp, ret 4, caller
// 0x0037EF5D, neighbours Rva0037EB1DCopy.cpp and VTableInstalls.cpp.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class Rva002E0D93
{
public:
	char m_pad00[0xA4];
	int m_keyA4;
	char m_padA8[0xD8 - 0xA8];
};
class Rva002E204D
{
public:
	Rva002E0D93 *rva002E204D(Rva002E0D93 *pos);
	Rva002E0D93 *m_start00;
	Rva002E0D93 *m_finish04;
	Rva002E0D93 *m_end08;
};
class Rva0037EF2D
{
	int m_unk00;
	Rva002E204D m_vec04;
public:
	void rva0037EF2D(unsigned int key);
	void rva0037EEFC(int index);
};
void Rva0037EF2D::rva0037EF2D(unsigned int key)
{
	for (Rva002E0D93 *p = m_vec04.m_start00; p != m_vec04.m_finish04; ++p) {
		if (p->m_keyA4 == (int)key) {
			m_vec04.rva002E204D(p);
			break;
		}
	}
}
void Rva0037EF2D::rva0037EEFC(int index)
{
	if (index < 0)
		return;
	int finish = *(volatile int *)((char *)this + 8);
	Rva002E204D &vec = m_vec04;
	int count = (finish - (int)vec.m_start00) / 0xD8;
	if ((unsigned int)index >= (unsigned int)count)
		return;
	_ReadWriteBarrier();
	vec.rva002E204D(vec.m_start00 + index);
}
