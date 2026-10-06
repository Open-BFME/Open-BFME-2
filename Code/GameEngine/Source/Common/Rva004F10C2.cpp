// cl: /MD
// ?rva004F10C2@Rva004F10C2@@QAE_NXZ @ 0x004F10C2 33B evidence: caller 0x004F19D3 tests result then walks GameWindow list via 0x0030F45F row; offsets this+0x14 head node+0x04 obj node+0x0C next node+0x19 flag obj+0x109 bit 0x40; true path jumps to next true getter at 0x004F10E3; prev S3IteratorMakers next ConstBoolTrueGetters
struct Rva004F10C2Obj
{
	unsigned char m_pad[0x109];
	unsigned char m_flag109;
};

struct Rva004F10C2Node
{
	unsigned char m_pad0[4];
	Rva004F10C2Obj *m_obj;
	unsigned char m_pad8[4];
	Rva004F10C2Node *m_next;
	unsigned char m_pad10[9];
	unsigned char m_flag19;
};

struct Rva004F10C2
{
	unsigned char m_pad[0x14];
	Rva004F10C2Node *m_head;
	bool rva004F10C2();
};

class GameWindow
{
public:
	unsigned int winGetStatus();
};

struct Rva004F19D3
{
	unsigned char m_pad04[4];
	Rva004F10C2 *m_head;
	bool rva004F19D3();
};

bool Rva004F10C2::rva004F10C2()
{
	Rva004F10C2Node *node = m_head;
	while (node != 0) {
		if ((node->m_obj->m_flag109 & 0x40) != 0 && node->m_flag19 == 0)
			return true;
		node = node->m_next;
	}
	return false;
}

bool Rva004F19D3::rva004F19D3()
{
	Rva004F10C2 *p = m_head;
	while (p != 0) {
		if (p->rva004F10C2())
			return true;
		p = (Rva004F10C2 *)((GameWindow *)p)->winGetStatus();
	}
	return false;
}
