// cl: /MD
//
// ??1Rva006F8460@@UAE@XZ retail 0x006F8460 37B dtor.
// Evidence: vtable 0x008EC9CC at +0; m_10 freed via member dtor 0x0070A840
// plus pool freeBlock 0x006DB270 size 0x14 with pool 0x00A176E8.
#pragma optimize("t", on)
class Rva0070A840
{
public:
	~Rva0070A840();
};
class Rva006DB270
{
public:
	void freeBlock(void *p, int size);
};
#define ThePool (*(Rva006DB270 *const *)0x00E176E8)
class Rva006F8460
{
public:
	virtual ~Rva006F8460();
private:
	char m_pad[0x0C];
	Rva0070A840 *m_10;
};

Rva006F8460::~Rva006F8460()
{
	Rva0070A840 *p = m_10;
	if (p != 0) {
		p->~Rva0070A840();
		ThePool->freeBlock(p, 0x14);
	}
}
#pragma optimize("", on)
