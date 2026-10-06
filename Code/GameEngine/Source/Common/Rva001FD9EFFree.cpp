// cl: /MD
// ?rva001FD9EF@Rva001FD9EF@@QAEXPAX@Z @0x001FD9EF 28B
// Hash-node free: clears the AsciiString key at +0x04 via rowed StringBase clear
// at 0x0048BA39 then frees the node via rowed _free at 0x00030830 with a null guard.
// Callers pass their table this in ecx and the node on the stack (0x0022346D/0x002234A6
// 0x002ADD24 0x003A2A62); the body ignores this. thiscall with one stack arg gives ret 4.
template <typename T>
class StringBase
{
public:
	void clear();
};

typedef StringBase<char> AsciiString;

extern "C" void __cdecl free(void *block);

struct Rva001FD9EFNode
{
	char m_pad[4];
	AsciiString m_key;
};

class Rva001FD9EF
{
public:
	void rva001FD9EF(void *node);
};

void Rva001FD9EF::rva001FD9EF(void *node)
{
	Rva001FD9EFNode *p = static_cast<Rva001FD9EFNode *>(node);
	p->m_key.clear();
	if (p)
		free(p);
}
