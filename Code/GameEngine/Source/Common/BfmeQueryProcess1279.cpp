// ?bfmeProcess1279@BfmeWrapper1279@@QAEXPAX@Z, retail 0x006F7230 (96B).
// Adapted from Open-BFME-1 Code/GameEngine/Source/Common/BfmeQueryProcess1279.cpp.
// BFME2 repairs (all retail-proven): node carries the provider at +0x48 and
// the key at +0x8; the provider exposes the lookup at vtable slot 3; the
// key check is the shared singleton-compare helper rowed as IsEmpty; the
// tail unlinks the node (rowed free function) before finishing it. Split-TU
// shard: the forward TU calls this body, so a same-TU definition could
// inline and break its rows.
class BfmeAptValue006DCD20
{
public:
	bool isUndefined() const;
};

class EAStringC
{
public:
	bool IsEmpty() const;
};

struct BfmeKey1279
{
	void *m_keyPtr;
};

class BfmeLookup1279;

class BfmeProvider1279
{
public:
	virtual void reserved0() = 0;
	virtual void reserved1() = 0;
	virtual void reserved2() = 0;
	virtual BfmeLookup1279 *bfmeGetLookup1279() = 0;
};

class BfmeNode1279
{
public:
	void bfmeFinish1279();
	void *m_vtable;
	unsigned int m_flags;
	BfmeKey1279 m_key;
	char m_pad0C[0x48 - 0x0C];
	BfmeProvider1279 *m_provider;
};

class BfmeLookup1279
{
public:
	BfmeNode1279 *bfmeLookup1279(BfmeKey1279 &key);
	void bfmeErase1279(BfmeKey1279 &key);
};

class BfmeNestedBE;

BfmeNestedBE *bfmeUnlinkNestedBE(BfmeNestedBE *item);

class BfmeWrapper1279
{
public:
	void bfmeProcess1279(void *value);
};

// ?bfmeProcess1279@BfmeWrapper1279@@QAEXPAX@Z
void BfmeWrapper1279::bfmeProcess1279(void *value)
{
	BfmeNode1279 *node = (BfmeNode1279 *)value;
	if (node != 0) {
		if (!((BfmeAptValue006DCD20 *)node)->isUndefined()) {
			BfmeProvider1279 *provider = node->m_provider;
			if (provider != 0) {
				BfmeLookup1279 *lookup = provider->bfmeGetLookup1279();
				BfmeKey1279 &key = node->m_key;
				if (!((EAStringC *)&key)->IsEmpty()) {
					if (lookup != 0) {
						if (lookup->bfmeLookup1279(key) == node)
							lookup->bfmeErase1279(key);
					}
				}
			}
			bfmeUnlinkNestedBE((BfmeNestedBE *)node);
			node->bfmeFinish1279();
		}
	}
}
