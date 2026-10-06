// cl: /Os /MD
// ?rva002FE13D@Rva002FE13D@@QAEEPAVObject@@@Z @0x002FE13D 86B evidence: REF table slot 0x008071B8 neighbours FileClass Get_File_Handle; flags Object+0x438 bits 1 8; ptr+0x25c bool check pinned 0x00390533; block+0x10e 0x40 +0x115 0x20; final pinned Object getRelationship 0x0028D156
enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

class Object;
class Rva00390533
{
public:
	bool rva00390533();
};

struct FlagBlock
{
	char m_pad[0x10E];
	unsigned char m_10E;
	char m_pad10F[0x115 - 0x10E - 1];
	unsigned char m_115;
};

class Object
{
public:
	Relationship getRelationship(const Object *that) const;

public:
	void *m_vtbl;
	FlagBlock *m_block4;
	char m_pad08[0x25C - 8];
	Rva00390533 *m_p25C;
	char m_pad260[0x438 - 0x260];
	unsigned char m_flags438;
};

class Rva002FE13D
{
public:
	unsigned char rva002FE13D(Object *obj);
	Object *m_pad0;
	Object *m_pad4;
	Object *m_target;
};

unsigned char Rva002FE13D::rva002FE13D(Object *obj)
{
	unsigned char flags = obj->m_flags438;
	if (flags & 1)
		return 0;
	else {
		if (flags & 8)
			return 0;
		if (obj->m_p25C != 0) {
			if (obj->m_p25C->rva00390533())
				return 0;
		}
		FlagBlock *blk = obj->m_block4;
		if ((blk->m_10E & 0x40) != 0)
			return 0;
		if ((blk->m_115 & 0x20) != 0)
			return 0;
		return m_target->getRelationship(obj) == ENEMIES;
	}
}
