// cl: /DNDEBUG /MD /GX-
//
// ?Rva004CDF2BParse@@YAXPAVINI@@PAX1PBX@Z, retail 0x004CDF2B (147B): the
// TriggerSpecialPower FieldParse proc (row 0x00C5FD70). Up to eight
// {name key, mode} entries are kept in the vector at instance + 0xC8: the
// first token is keyed through TheNameKeyGenerator (rowed nameToKey
// 0x00148E1A), the optional second token selects the mode by strcmp against
// the two names at VA 0x00DCF7E8 (default 1), and the entry is appended
// through the 8-byte-element push_back fold 0x00539A2E. Name address-derived.

#define NULL 0

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *nameString);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class INI
{
public:
	const char *getNextTokenOrNull(const char *seps = 0);
};

extern "C" int __cdecl strcmp(const char *a, const char *b);
extern const char *g_00DCF7E8[];

struct Rva004CDF2BTrigger
{
	NameKeyType m_key;
	int m_mode;
};

namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A> class vector;
template <> class vector<Rva004CDF2BTrigger, allocator<Rva004CDF2BTrigger> >
{
public:
	unsigned int size() const { return (unsigned int)(m_finish - m_start); }
	void push_back(const Rva004CDF2BTrigger &x);
private:
	Rva004CDF2BTrigger *m_start;
	Rva004CDF2BTrigger *m_finish;
	Rva004CDF2BTrigger *m_endOfStorage;
};
}

struct Rva004CDF2BOwner
{
	unsigned char m_unreconstructed_00[0xC8];
	_STL::vector<Rva004CDF2BTrigger, _STL::allocator<Rva004CDF2BTrigger> > m_triggers;	// +0xC8
};

// ?Rva004CDF2BParse@@YAXPAVINI@@PAX1PBX@Z
void Rva004CDF2BParse(INI *ini, void *instance, void *, const void *)
{
	_STL::vector<Rva004CDF2BTrigger, _STL::allocator<Rva004CDF2BTrigger> > &triggers = ((Rva004CDF2BOwner *)instance)->m_triggers;
	if (triggers.size() >= 8)
		return;

	const char *token = ini->getNextTokenOrNull();
	if (token == NULL || *token == 0)
		return;

	Rva004CDF2BTrigger trigger;
	trigger.m_key = TheNameKeyGenerator->nameToKey(token);
	trigger.m_mode = 1;

	token = ini->getNextTokenOrNull();
	if (token != NULL && *token != 0)
	{
		for (int i = 0; i < 2; ++i)
		{
			if (strcmp(token, g_00DCF7E8[i]) == 0)
			{
				trigger.m_mode = i;
				break;
			}
		}
	}
	triggers.push_back(trigger);
}
