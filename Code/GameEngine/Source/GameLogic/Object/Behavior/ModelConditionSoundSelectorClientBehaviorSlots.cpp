// cl: /O1 /DNDEBUG /MD
//
// ModelConditionSoundSelectorClientBehavior's three overrides on its +0x0C
// interface table 0x00BF3210 (installed by the matched ctor 0x00254B82), so
// `this` is that subobject (module data at -0x08, the owner at -0x04). Each
// asks the module data's selector entries (0x220-byte records in the vector
// at +0x08, each led by a condition-flag set) about the owner's current
// condition flags at +0x258. Names by address.
//   slot 0, retail 0x004CAC2F (28 bytes): the rowed
//           Rva004CABE5Store::find(index, dest, flags).
//   slot 1, retail 0x004CAC9C (28 bytes): the module data's 0x004CAC4B
//           (key lookup in each matching record's map; pinned by address).
//   slot 2, retail 0x004CABCD (24 bytes): rva004CAB8B below.
// rva004CAB8B, retail 0x004CAB8B (66 bytes): the first record whose flags
// the given flags test (the rowed Rva000CF0D6::test) and whose +0x21C flag
// is set hands back its +0x218 value; false when none does.
class Rva000CF0D6
{
public:
	bool test(const Rva000CF0D6 *other) const;
	unsigned int m_bits[19];
};
struct Rva002C99FB;
class AsciiString;
struct Rva004CAB8BRecord
{
	Rva000CF0D6 m_flags;		// +0x000
	unsigned char m_pad04C[0x218 - 0x4C];
	int m_218;			// +0x218
	bool m_21C;			// +0x21C
	unsigned char m_pad21D[0x220 - 0x21D];
};
class Rva004CABE5Store
{
public:
	bool find(int idx, Rva002C99FB *dest, const Rva000CF0D6 *tester);
	bool rva004CAC4B(const AsciiString &key, Rva002C99FB *dest, const Rva000CF0D6 *tester);
	bool rva004CAB8B(int *dest, const Rva000CF0D6 *tester);
private:
	unsigned char m_pad00[0x08];
	Rva004CAB8BRecord *m_begin;	// +0x08
	Rva004CAB8BRecord *m_end;	// +0x0C
};
class Drawable
{
public:
	unsigned char m_pad000[0x258];
	Rva000CF0D6 m_conditionFlags;	// +0x258
};
class ClientModuleBase
{
public:
	virtual ~ClientModuleBase();
protected:
	Rva004CABE5Store *m_moduleData;	// +0x04
	Drawable *m_drawable;		// +0x08
};
class Rva00BF3210Iface
{
public:
	virtual bool rva004CAC2F(int idx, Rva002C99FB *dest) = 0;
	virtual bool rva004CAC9C(const AsciiString &key, Rva002C99FB *dest) = 0;
	virtual bool rva004CABCD(int *dest) = 0;
};
class ModelConditionSoundSelectorClientBehavior : public ClientModuleBase, public Rva00BF3210Iface
{
public:
	virtual bool rva004CAC2F(int idx, Rva002C99FB *dest);
	virtual bool rva004CAC9C(const AsciiString &key, Rva002C99FB *dest);
	virtual bool rva004CABCD(int *dest);
};

bool Rva004CABE5Store::rva004CAB8B(int *dest, const Rva000CF0D6 *tester)
{
	Rva004CAB8BRecord *it = m_begin;
	Rva004CAB8BRecord *end = m_end;
	while (it != end)
	{
		if (tester->test(&it->m_flags) && it->m_21C)
		{
			*dest = it->m_218;
			return true;
		}
		++it;
	}
	return false;
}

bool ModelConditionSoundSelectorClientBehavior::rva004CAC2F(int idx, Rva002C99FB *dest)
{
	return m_moduleData->find(idx, dest, &m_drawable->m_conditionFlags);
}

bool ModelConditionSoundSelectorClientBehavior::rva004CAC9C(const AsciiString &key, Rva002C99FB *dest)
{
	return m_moduleData->rva004CAC4B(key, dest, &m_drawable->m_conditionFlags);
}

bool ModelConditionSoundSelectorClientBehavior::rva004CABCD(int *dest)
{
	return m_moduleData->rva004CAB8B(dest, &m_drawable->m_conditionFlags);
}
