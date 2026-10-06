// cl: /DNDEBUG /MD
//
// ?rva0044E7A8@Rva0044E7A8@@QAE_NH@Z @0x0044E7A8 182B:
// Kind validator: required kinds from +0xA0 flags (0xD6 plus 0x12D plus 0x3D
// via rowed ?isKindOf@Object@@QBE_NW4KindOfType@@@Z), forbidden kinds from
// +0xA4 flags (same three ids, inverted), then +0xB6-gated rowed
// ?rva0028F4BC@Object@@QAEPAVRva00373EC6@@XZ predicate with +0x31 check.
// Caller at 0x0044EDB8 forwards its arg (unused here); landing unblocks
// 0x0044EDA6 plus 0x00451FA2.
enum KindOfType
{
	KIND_DUMMY = 0
};

class Rva00373EC6;

class Object
{
public:
	bool isKindOf(KindOfType kind) const;
	Rva00373EC6 *rva0028F4BC();
};

struct Rva0044E7A8Req
{
	char m_pad0[0xA0];
	unsigned int m_flags0; // +0xA0
	unsigned int m_flags1; // +0xA4
	char m_pad1[0xB6 - 0xA8];
	unsigned char m_b6; // +0xB6
};

class Rva0044E7A8
{
public:
	bool rva0044E7A8(int arg);
private:
	char m_pad0[4];
	Rva0044E7A8Req *m_req; // +0x04
	Object *m_obj; // +0x08
};

bool Rva0044E7A8::rva0044E7A8(int arg)
{
	(void)arg;
	Rva0044E7A8Req *req = m_req;
	Object *obj = m_obj;
	unsigned int f0 = req->m_flags0;
	if ((f0 & 1) != 0 && !obj->isKindOf((KindOfType)0xD6))
		return false;
	if ((f0 & 2) != 0 && !obj->isKindOf((KindOfType)0x12D))
		return false;
	if ((f0 & 4) != 0 && !obj->isKindOf((KindOfType)0x3D))
		return false;
	unsigned int f1 = req->m_flags1;
	if ((f1 & 1) != 0 && obj->isKindOf((KindOfType)0xD6))
		return false;
	if ((f1 & 2) != 0 && obj->isKindOf((KindOfType)0x12D))
		return false;
	if ((f1 & 4) != 0 && obj->isKindOf((KindOfType)0x3D))
		return false;
	if (req->m_b6 == 0)
		return true;
	Rva00373EC6 *found = obj->rva0028F4BC();
	if (found != 0 && ((const unsigned char *)found)[0x31] != 0)
		return false;
	return true;
}
