// cl: /MD

class Rva005C46D9
{
public:
	Rva005C46D9(const Rva005C46D9 &source);
	virtual ~Rva005C46D9();

private:
	char m_fields[24];
};

// ?rva0052B5C6@@YGPAXPBX@Z @0x0052B5C6 55B
// Target evidence: allocates 0x1C bytes, skips construction on null, calls 0x005C46D9 with
// the stack argument, and returns the constructor result under an EH frame.
// Structural inference: model this as a stdcall address-derived factory for a 28B polymorphic
// copy-source type. The source object's full identity and layout remain unknown.
void *__stdcall rva0052B5C6(const void *source)
{
	return new Rva005C46D9(*(const Rva005C46D9 *)source);
}
