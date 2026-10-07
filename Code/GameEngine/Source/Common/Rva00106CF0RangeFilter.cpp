// cl: /DNDEBUG /MD /O1 /G7
//
// ?rva00106CF0@Rva00106CF0@@QAEXXZ at 0x00106CF0, 102 bytes. Target
// evidence: clears the output count at +0x10, gets 16-byte records through
// the address-derived source operation at the owner's +0xC4, and compares
// the input bytes at each record's +8/+0xC indices. Unequal bytes emit the
// record's two endpoints at +0xC in byte-dependent order. Concrete class and
// owner identities remain unresolved.

struct Rva00106CF0Record
{
	unsigned int first;
	unsigned int second;
	unsigned int begin;
	unsigned int end;
};

class Rva0016E450Source
{
public:
	void *rva0016E450(int *count);
};

class Rva00106CF0Owner
{
	unsigned char m_pad00[0xC4];

public:
	Rva0016E450Source *m_source;
};

class Rva00106CF0
{
	Rva00106CF0Owner *m_owner;
	unsigned int m_pad04;
	const unsigned char *m_input;
	unsigned int *m_output;
	int m_outputCount;

public:
	void rva00106CF0();
};

void Rva00106CF0::rva00106CF0()
{
	Rva00106CF0Owner *owner = m_owner;
	m_outputCount = 0;
	Rva0016E450Source *source = owner->m_source;
	unsigned int *output = m_output;
	int count;
	Rva00106CF0Record *record = (Rva00106CF0Record *)source->rva0016E450(&count);
	if (count != 0)
	{
		do
		{
			unsigned char first = m_input[record->begin];
			if (first != m_input[record->end])
			{
				if (first != 0)
				{
					output[0] = record->first;
					output[1] = record->second;
				}
				else
				{
					output[0] = record->second;
					output[1] = record->first;
				}
				output += 2;
				++m_outputCount;
			}
			--count;
			++record;
		} while (count != 0);
	}
}
