// ?rva00364A37@Rva00364A37@@QAEXXZ
// cl: /DNDEBUG /MD
//
// Rva00364A37 clearer, retail 0x00364A37, 41 bytes: if +4 is null return
// else free [0]+4 via rowed 0x0036426E then re-init [0]+8=[0] and [0]+4=0
// and [0]+12=[0] and +4=0. Evidence: callers/callees plus free-list helper
// 0x0036426E row; Path neighbours prove /O1 flags.
struct FreeNode
{
	void *m_unknown00;
	void *m_unknown04;
	FreeNode *m_next;
	FreeNode *m_child;
};

class Rva0036426E
{
public:
	void rva0036426E(FreeNode *head);
};

struct Header
{
	void *m_unknown00;
	FreeNode *m_head;
	Header *m_next;
	Header *m_child;
};

class Rva00364A37
{
public:
	void rva00364A37();

private:
	Header *m_header;
	void *m_flag04;
};

void Rva00364A37::rva00364A37()
{
	if (m_flag04 == 0)
		return;
	((Rva0036426E *)this)->rva0036426E(m_header->m_head);
	m_header->m_next = m_header;
	m_header->m_head = 0;
	m_header->m_child = m_header;
	m_flag04 = 0;
}
