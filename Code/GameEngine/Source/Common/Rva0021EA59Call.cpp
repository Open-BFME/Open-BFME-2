// cl: /O2 /DNDEBUG /EHsc /MD
// ?rva0021EA59@Rva0021E9D8Call@@QAEHPAX@Z @0x0021EA59 27B
// Target evidence: the 27-byte thiscall wrapper reads the argument block at
// +0/+4/+8/+0xC, passes those three references and the +0xC word to 0x0021E9D8,
// then preserves EAX. The shared address-derived class view is inferred from
// forwarding the unchanged ECX to that direct member call; callee semantics
// remain unresolved.

class AsciiString;

class Rva0021E9D8Call
{
public:
	int rva0021E9D8Call(unsigned int value, const AsciiString &first,
		const AsciiString &second, const AsciiString &third);
	int rva0021EA59(void *arguments);
};

int Rva0021E9D8Call::rva0021EA59(void *arguments)
{
	char *bytes = (char *)arguments;
	unsigned int value = *(unsigned int *)(bytes + 0xC);
	const AsciiString *last = (const AsciiString *)(bytes + 4);
	const AsciiString *middle = (const AsciiString *)bytes;
	const AsciiString *first = (const AsciiString *)(bytes + 8);
	return rva0021E9D8Call(value, *first, *middle, *last);
}
