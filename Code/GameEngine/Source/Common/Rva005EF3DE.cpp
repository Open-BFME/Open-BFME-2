// cl: /MD /EHsc
// ?rva005EF3DE@Rva005EF3DE@@QAEXXZ retail 0x005EF3DE 8B
// Evidence: forwarder mov ecx,[ecx+4]; jmp rowed 0x005EF283 ?rva005EF283@Rva005EF283@@QAEXXZ; caller 0x005E19FD.
class Rva005EF283
{
public:
	void rva005EF283();
};

class Rva005EF3DE
{
public:
	void rva005EF3DE();
private:
	int m_pad00;
	Rva005EF283 *m_ptr04;
};

void Rva005EF3DE::rva005EF3DE()
{
	return m_ptr04->rva005EF283();
}
