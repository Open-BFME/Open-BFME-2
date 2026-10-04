// cl: /O1 /DNDEBUG /MD
//
// ?rva0028DA67@Object@@QAEXXZ @0x0028DA67 82B: Object helper gating on +0x480 flag and template +0x618/+0x61C.
// Checks testStatus 0x57 and 2, then notifies via controlling Player Rva002A9B58 and sets +0x480.
// Evidence: neighbours ObjectRva0028DA28 and ObjectGetVisionRange share Object shard and flags;
// callees testStatus getControllingPlayer and Rva dict are rowed; unblocks 0x002A9D02 and 0x002934E7.
enum ObjectStatusTypes
{
	RVA_2 = 2,
	RVA_57 = 0x57
};
class Player;
struct Rva002A7588In;
class Rva002A9B58
{
public:
	void rva002A9B35(Rva002A7588In *in);
};
class ThingTemplate
{
public:
	unsigned char m_pad00[0x618];
	int m_618; // +0x618
	int m_61C; // +0x61C
};
class Object
{
public:
	void rva0028DA67();
	bool testStatus(ObjectStatusTypes s) const;
	Player *getControllingPlayer() const;
private:
	unsigned char m_pad00[0x04];
	ThingTemplate *m_tmpl; // +0x04
	unsigned char m_pad08[0x480 - 0x08];
	unsigned char m_480; // +0x480
};

void Object::rva0028DA67()
{
	if (m_480 != 0)
		return;
	if (m_tmpl->m_618 <= 0 && m_tmpl->m_61C <= 0)
		return;
	if (testStatus(RVA_57))
		return;
	if (testStatus(RVA_2))
		return;
	((Rva002A9B58 *)getControllingPlayer())->rva002A9B35((Rva002A7588In *)this);
	m_480 = 1;
}
