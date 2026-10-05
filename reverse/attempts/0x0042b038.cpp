// ?rva0042B038@Rva0042B038@@QAEXPAX000@Z
// partial score=0.95 date=2026-10-05
// ?rva0042B038@Rva0042B038@@QAEXPAX000@Z
// partial score=0.95 date=2026-10-05
// cl: /O2 /EHsc /MD /Oy-
// ?rva0042B038@Rva0042B038@@QAEXPAXPAXPAXPAX@Z, retail 0x0042B038 (48B).
// Unlock: missing callee of 0x0042B068; landing makes 0x0042B068 ready.
// Calls rowed ?Rva00239D02Insert@@YGPAPAXPAPAXPAX0@Z 0x00239D02 (void
// **out, void *pos, void **allocArg); caller 0x0042B07D; neighbours 0x004296C2
// and 0x0042C083 share Common dir; __thiscall ret 0x10 (this=ecx, four stack
// args at [ebp+8]/[ebp+c]/[ebp+10]/[ebp+14]).
//
// RETAIL SEMANTICS, decoded from the bytes (the earlier bank had them wrong):
//   esi = cur = start([ebp+0xc]); this -> edi
//   loop over a cursor, reloading pos([ebp+8]) and end([ebp+0x10]) from the
//   frame every iteration, until cur == end:
//       Insert(out = &start, pos = pos, allocArg = &cur->field08)
//       cur = cur->m_next
//   so it walks [start, end) inserting a node before every existing node whose
//   payload lives at +8. arg4([ebp+0x14]) is unused.
//   The bank had out = &start as the FIRST Insert arg and allocArg = &field08,
//   which is what retail does, but it also hoisted end into a register and the
//   do/while form lost the ebp frame. This while form reproduces retail's
//   prologue (push ebp/mov ebp,esp/push esi/mov esi,[ebp+0xc]/push edi/mov
//   edi,ecx/jmp test) and epilogue byte-for-byte; the body differs by 2 bytes
//   (the redundant seed+store for the by-value pos, mov eax,esp/mov [eax],ecx).
// Retail sets ecx (from edi) before this call, although the rowed callee at
// 0x00239D02 is a plain __stdcall free function that ignores ecx. Both
// conventions emit `ret 0xc` for three stack arguments, so the rowed global
// name ?Rva00239D02Insert@@YGPAPAXPAPAXPAX0@Z does not distinguish them: a
// __thiscall member taking three arguments pops the same 12 bytes and leaves
// ecx untouched, which is exactly retail's shape. Calling it as a member of
// this class is what puts `this` (already live in edi) into ecx without
// spending a fourth push.
struct Rva0042B038Node
{
	void *m_next;
	int m_pad04;
	void *m_field08;
};

class Rva0042B038
{
public:
	void rva0042B038(void *pos, void *start, void *end, void *extra);

	void *rva00239d02Insert(void **out, void *pos, void **allocArg);
};

 // ?rva0042B038@Rva0042B038@@QAEXPAX000@Z present-unmatched
void Rva0042B038::rva0042B038(void *pos, void *start, void *end, void *extra)
{
	Rva0042B038Node *cur = (Rva0042B038Node *)start;
	(void)extra;
	while (cur != (Rva0042B038Node *)end) {
		rva00239d02Insert((void **)&start, pos, (void **)&cur->m_field08);
		cur = (Rva0042B038Node *)cur->m_next;
	}
}