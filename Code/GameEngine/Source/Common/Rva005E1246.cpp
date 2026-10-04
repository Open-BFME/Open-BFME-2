// cl: /O1 /MD
// ?rva005E1246@Rva005E1246@@QAEXXZ @0x005E1246 26B chain via 0x005E0DC0 landing.
// Evidence: retail push esi mov esi [ecx] and [ecx] 0 test je call rowed ??1Rva005E0DC0@@QAE@XZ @0x005E0DC0 then rowed ??3@YAXPAX@Z @0x0002FD60; caller at 0x005E12B9 via lea ecx [esi+8]; neighbours 0x005E11E8 0x005E1260.
class Rva005E0DC0
{
public:
	~Rva005E0DC0();
};

class Rva005E1246
{
	Rva005E0DC0 *m_ptr;
public:
	void rva005E1246();
};

void Rva005E1246::rva005E1246()
{
	Rva005E0DC0 *p = m_ptr;
	m_ptr = 0;
	delete p;
}
