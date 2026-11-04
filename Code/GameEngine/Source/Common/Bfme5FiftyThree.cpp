// A pointer-key index-of search (trimmed from a four-body donor; the other
// three are declared-only here).

class BfmeThingCX
{
public:
	int m_bfmeHead;						// +0x00
	unsigned short m_bfmeRefs;				// +0x04
};

class BfmeHandleCX
{
public:
	BfmeThingCX *m_bfmeThing;				// +0x00
};

class BfmeTripleDW
{
public:
	int m_bfmeFirst;					// +0x00
	int m_bfmeTail[2];					// +0x04
};

class BfmeQuadDW
{
public:
	int m_bfmeHead[2];					// +0x00
	void *m_bfmeKey;					// +0x08
	int m_bfmeTail;						// +0x0C
};

class Gen_008A06C0
{
public:
	int bfmeIndexOf(void *key) const;

private:
	int m_bfmeHead[8];					// +0x00
	int m_bfmeCount;					// +0x20
	BfmeQuadDW *m_bfmeEntries;				// +0x24
};

// ?bfmeIndexOf@Gen_008A06C0@@QBEHPAX@Z
int Gen_008A06C0::bfmeIndexOf(void *key) const
{
	int count = m_bfmeCount;

	int index = 0;

	if (index < count)
	{
		BfmeQuadDW *entry = m_bfmeEntries;

		do
		{
			if (entry->m_bfmeKey == key)
				return index;

			++index;
			++entry;
		}
		while (index < count);
	}

	return -1;
}

class BfmePairDW
{
public:
	int m_bfmeTag;						// +0x00
	BfmeHandleCX m_bfmeHandle;				// +0x04
};

BfmePairDW __cdecl bfmeMakePair(const int *tag, const BfmeHandleCX *handle);
