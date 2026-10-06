// ?rva0039D92A@Rva0039D92AOwner@@QAEPAURva0039D92ANode@@H@Z
// partial score=0.9 date=2026-10-06
// cl: /DNDEBUG /MD
// ?rva0039D92A@Rva0039D92AOwner@@QAEPAURva0039D92ANode@@H@Z, retail 0x0039D92A, 42 bytes.
// Find node by +0x34 key in +0x334 DLINK list via member-pointer next (rowed 0x005C4AF5 +0x40 getter).
// Evidence: packet disassembly mov eax [ecx+0x334] push esi push edi xor esi mov edi func jmp test mov ecx [eax+0x34] cmp je lea ecx [esi+eax] call edi, caller 0x0039F784 TeamFactory::findTeamByID, prev/next Team files, +0x334 DLINK head in TeamPrototypeTeamIterators.
#pragma pointers_to_members(multiple_inheritance)
class Rva005C4AF5DwordField
{
public:
	int get() const;
};
typedef int (Rva005C4AF5DwordField::*Rva0039D92ANext)() const;
struct Rva0039D92ANode
{
	char m_pad[0x34];
	int m_key;
};
class Rva0039D92AOwner
{
public:
	Rva0039D92ANode *rva0039D92A(volatile int key);
private:
	char m_pad[0x334];
	Rva0039D92ANode *m_head;
};
Rva0039D92ANode *Rva0039D92AOwner::rva0039D92A(volatile int key)
{
	Rva0039D92ANode *p = m_head;
	Rva0039D92ANext next = &Rva005C4AF5DwordField::get;
	while (p != 0) {
		if (p->m_key == key)
			break;
		p = (Rva0039D92ANode *)(((Rva005C4AF5DwordField *)p->*next)());
	}
	return p;
}
