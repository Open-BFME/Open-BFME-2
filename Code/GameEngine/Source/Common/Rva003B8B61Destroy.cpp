// cl: /MD
// ?Rva003B8B61Destroy@@YAXPAURva003B8B61Elem@@0H@Z @0x003B8B61 26B.
// Range destroy stepping 0x68 calling virtual slot 0 with 0.
// Evidence: retail push esi; mov esi,[esp+8]; jmp check; mov eax,[esi]; push 0; mov ecx,esi;
// call [eax]; add esi,0x68; cmp esi,[esp+0xC]; jne loop; pop esi; ret. Caller at 0x003B8E21
// (pinned _Destroy for BfmeAssignRecord104) pushes first+last+tag and cleans 0xC (__cdecl).
struct Rva003B8B61Elem
{
	virtual void destroy(int);
	char m_pad[0x68 - 4];
};

void __cdecl Rva003B8B61Destroy(Rva003B8B61Elem *first, Rva003B8B61Elem *last, int unused)
{
	for (; first != last; first = (Rva003B8B61Elem *)((char *)first + 0x68))
		first->destroy(0);
}
