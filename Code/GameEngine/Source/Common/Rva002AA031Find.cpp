// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?find@Rva002AA031Holder@@QAEPAURva002AA031Node@@H@Z @ 0x002AA031 (27B):
// list search (mov eax,[ecx+0x9c] / jmp test / mov ecx,[eax+4] / cmp ecx,[esp+4]
// / je ret / mov eax,[eax+0xc] / test eax,eax / jne loop / ret 4). Callers at
// 0x002ADAD2 and 0x002AE33C unlink via +0xc/+0x10 like an Upgrade list, but the
// Player::findUpgrade donor in RTS/Player.cpp uses +0x40/+0x08/+0x10, so the
// layout differs and identity stays opaque address-derived. Prev 0x002A9F0F
// (// cl: /O1) and next 0x002AA08E (// cl: /O1 /DNDEBUG /MD) share /O1.
struct Rva002AA031Node
{
	int m_pad0;
	int m_key;
	int m_pad8;
	Rva002AA031Node *m_next;
};
class Rva002AA031Holder
{
public:
	Rva002AA031Node *find(int key);
	char m_pad[0x9c];
	Rva002AA031Node *m_head;
};
Rva002AA031Node *Rva002AA031Holder::find(int key)
{
	for (Rva002AA031Node *n = m_head; n; n = n->m_next)
		if (n->m_key == key)
			return n;
	return 0;
}
