// cl: /MD
// ?rva006DE150@Rva006DE150@@QAEXXZ @0x006DE150 12B.
// Sets bit 3 of the flag word at +4 then tail-calls
// AptNativeHash::DestroyGCPointers on the member at +8 (add ecx,8 plus jmp).
// Callers are three jmp thunks. No donor; retail-shaped.
class AptNativeHash
{
public:
	void DestroyGCPointers();
};

class Rva006DE150
{
public:
	char m_pad[4];
	unsigned int m_flags;
	AptNativeHash m_table;
	void rva006DE150();
};

void Rva006DE150::rva006DE150()
{
	m_flags |= 8;
	m_table.DestroyGCPointers();
}
