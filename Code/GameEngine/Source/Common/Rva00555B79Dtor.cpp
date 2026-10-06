// cl: /MD
//
// ??1Rva00555B79@@QAE@XZ, retail 0x00555B79, 8 bytes. Unlock lane: empty dtor
// over member at +4 via pinned ??1Gen_uw_00385371@@QAE@XZ (add ecx,4; jmp).
// Unblocks 0x00556050 and 0x00555BB9.
class Gen_uw_00385371
{
public:
	~Gen_uw_00385371();
};

class Rva00555B79
{
public:
	~Rva00555B79();

private:
	int m_pad0;
	Gen_uw_00385371 m_member;
};

Rva00555B79::~Rva00555B79()
{
}
