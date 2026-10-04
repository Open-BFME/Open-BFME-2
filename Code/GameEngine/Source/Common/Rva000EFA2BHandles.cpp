// Native EFA2B/10 and EFA35/25: return observed pointers and increment word+4.
// Donor1281192f68 Rva007B7CB0Handle.cpp / Rva007B7CC0Pick.cpp, unchanged from6d943.
// Native field offsets/byte condition/word increment established independently.
// Reference-count meaning and original classes are donor leads, not target names.
// Full target object sizes unknown; declarations are minimum ABI prefixes.
// cl: /O1 /G7 /arch:SSE2 /GX- /MD

struct Rva000EFA2BTarget
{
	unsigned char m_unknown00[4];
	unsigned int m_word04;
};

class Rva000EFA2BHandle
{
public:
	Rva000EFA2BTarget *rva000EFA2B();

	char m_pad[0x2c];
	Rva000EFA2BTarget *m_target;
};

Rva000EFA2BTarget *Rva000EFA2BHandle::rva000EFA2B()
{
	++m_target->m_word04;
	return m_target;
}

// cl: /O1 /G7 /arch:SSE2 /GX- /MD

struct Rva000EFA35Target
{
	unsigned char m_unknown00[4];
	unsigned int m_word04;
};

class Rva000EFA35Selector
{
public:
	Rva000EFA35Target *rva000EFA35(unsigned char flag);

	char m_pad[0x30];
	Rva000EFA35Target *m_30;
	Rva000EFA35Target *m_34;
};

Rva000EFA35Target *Rva000EFA35Selector::rva000EFA35(unsigned char flag)
{
	Rva000EFA35Target *target;
	if (flag)
		target = m_34;
	else
		target = m_30;
	if (target)
		++target->m_word04;
	return target;
}
