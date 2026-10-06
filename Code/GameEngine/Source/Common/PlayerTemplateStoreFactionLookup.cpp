// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva001FD367@PlayerTemplateStore@@QBE_NHPAH@Z @0x001FD367 95B.
// Faction-index lookup over PlayerTemplateStore vector at +0x0C/+0x10 stride
// 0x1DC: calls rowed Rva0033A3F4Lookup on the AsciiString at template +0x18,
// writes the matching index through outIndex and returns true else false.
// Evidence: unlock lane callers at 0x0052203E and 0x00522085 in 0x00521EDA;
// vector layout and stride from sibling PlayerTemplateStoreFind/GetNth TUs.

#include "ascii_string.h"

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
	void *m_vtable;
	Overridable *m_nextOverride;
	int m_isOverride;
	int m_extra0C;
};

class PlayerTemplate : public Overridable
{
public:
	int m_nameKey;
	char m_pad14[4];
	AsciiString m_str18;
	char m_rest[0x1DC - 0x18 - 4];
};

class PlayerTemplateVector
{
public:
	unsigned size() const { return static_cast<unsigned>(m_last - m_first); }
	const PlayerTemplate &operator[](int index) const { return m_first[index]; }
private:
	PlayerTemplate *m_first;
	PlayerTemplate *m_last;
};

class PlayerTemplateStore
{
public:
	bool rva001FD367(int faction, int *outIndex) const;
private:
	char m_pad[0x0C];
	PlayerTemplateVector m_playerTemplates;
};

int Rva0033A3F4Lookup(const AsciiString &name);

bool PlayerTemplateStore::rva001FD367(int faction, int *outIndex) const
{
	for (int i = 0; i < m_playerTemplates.size(); ++i)
	{
		if (Rva0033A3F4Lookup(m_playerTemplates[i].m_str18) == faction)
		{
			*outIndex = i;
			return true;
		}
	}
	return false;
}
