// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// Dict::setReal plus float movss shape.
// Reference basis is ZH Dict.cpp setReal via rowed setPrep at 0x0031369D
// and rowed sortPairs at 0x00313299. Retail moves float via xmm.

#include "ascii_string.h"


enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

#include "unicode_string.h"

class Dict
{
public:
	enum DataType
	{
		DICT_NONE = -1,
		DICT_BOOL,
		DICT_INT,
		DICT_REAL,
		DICT_ASCIISTRING,
		DICT_UNICODESTRING
	};

	struct DictPair
	{
		int m_key;
		void *m_value;

		void clear();
		void setNameAndType(int key, DataType type);
		void copyFrom(DictPair *that);
	};

	struct DictPairData
	{
		unsigned short m_refCount;
		unsigned short m_numPairsAllocated;
		unsigned short m_numPairsUsed;
	};

public:
	void setReal(int key, float value);

private:
	DictPair *findPairByKey(int key) const;
	void sortPairs();
	DictPair *ensureUnique(int numPairsNeeded, bool preserveData, DictPair *pairToTranslate);
	DictPair *setPrep(int key, DataType type);

	DictPairData *m_data;
};

// ?setReal@Dict@@QAEXHM@Z @0x00313736 36B
// Dict::setReal from ZH Dict.cpp donor. Rowed setPrep at 0x0031369D plus
// float store via xmm plus rowed sortPairs at 0x00313299. Callers at
// 0x0008AAAC 0x0023B8D3 0x0030792A.
void Dict::setReal(int key, float value)
{
	DictPair *pair = setPrep(key, DICT_REAL);
	*(float *)&pair->m_value = value;
	sortPairs();
}
