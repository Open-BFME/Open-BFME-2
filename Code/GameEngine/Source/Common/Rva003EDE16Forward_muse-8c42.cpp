// cl: /DNDEBUG /MD
// ?rva003EDE16@Rva003EDE16@@QBE_NPBX@Z @0x003EDE16 20B
// Chain of 0x001DFE56 (19-dword dual-mask tester): forwards this+0x28/+0x74 as required/exempt
// against the passed-in mask. Prev stlport_rb_tree next ConstIntGetters.
// Callers 0x003EDE44 0x003EDF69 0x003EDFD8 pass 76-byte masks.
class Rva001DFE56
{
public:
	bool rva001DFE56(const void *required, const void *exempt) const;
};

class Rva003EDE16
{
public:
	bool rva003EDE16(const void *other) const;
private:
	unsigned char m_pad[0x28];
	unsigned m_req[19]; // +0x28
	unsigned m_ban[19]; // +0x74
};

bool Rva003EDE16::rva003EDE16(const void *other) const
{
	const Rva001DFE56 *o = (const Rva001DFE56 *)other;
	return o->rva001DFE56(m_req, m_ban);
}
