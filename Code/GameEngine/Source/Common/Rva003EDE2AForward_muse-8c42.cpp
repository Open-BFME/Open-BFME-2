// cl: /DNDEBUG /MD
// ?rva003EDE2A@Rva003EDE2A@@QBE_NPBX@Z @0x003EDE2A 26B
// Forwarder to 4-dword tester ?testMasks@Rva0026157E (0x0026157E) with this+0xC0/+0xD0.
// Sibling of 0x003EDE16 (19-dword forwarder) same page same shape larger disp32.
// Callers 0x003EDE44 0x003EDF69 0x003EDFD8.
class Rva0026157E
{
public:
	bool testMasks(const void *required, const void *exempt) const;
};

class Rva003EDE2A
{
public:
	bool rva003EDE2A(const void *other) const;
private:
	unsigned char m_pad[0xC0];
	unsigned m_req[4]; // +0xC0
	unsigned m_ban[4]; // +0xD0
};

bool Rva003EDE2A::rva003EDE2A(const void *other) const
{
	const Rva0026157E *o = (const Rva0026157E *)other;
	return o->testMasks(m_req, m_ban);
}
