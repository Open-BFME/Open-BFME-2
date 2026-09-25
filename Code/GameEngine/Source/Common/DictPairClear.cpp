// cl: /O1 /DNDEBUG /MD
// Dict pair clear plus releaseData.
// Reference basis is BFME1 Dict_releaseData.cpp (retail 0x000681C0), which
// carries the Dict layout, the pair switch and releaseData. BFME2 outlines
// the pair switch as its own 43B body and frees through the game _free.

class AsciiString
{
public:
	~AsciiString();

private:
	char *m_data;
};

extern "C" void free(void *);

class UnicodeString
{
public:
	void releaseBuffer();

private:
	unsigned short *m_data;
};

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
	};

	struct DictPairData
	{
		unsigned short m_refCount;
		unsigned short m_numPairsAllocated;
		unsigned short m_numPairsUsed;
	};

public:
	void clear();
	DataType getType(int key) const;
	bool getBool(int key, bool *exists) const;

private:
	void releaseData();
	DictPair *findPairByKey(int key) const;

	DictPairData *m_data;
};

// ?clear@DictPair@Dict@@QAEXXZ @0x0031334A
void Dict::DictPair::clear()
{
	switch (m_key & 0xFF)
	{
		case DICT_NONE:
			break;
		case DICT_BOOL:
		case DICT_INT:
		case DICT_REAL:
			m_value = 0;
			break;
		case DICT_ASCIISTRING:
			((AsciiString *)&m_value)->~AsciiString();
			break;
		case DICT_UNICODESTRING:
			((UnicodeString *)&m_value)->releaseBuffer();
			break;
	}
}

// ?releaseData@Dict@@AAEXXZ @0x0031339C
void Dict::releaseData()
{
	if (m_data == 0)
		return;
	if (--m_data->m_refCount != 0)
	{
		m_data = 0;
		return;
	}
	DictPair *src = (DictPair *)(m_data + 1);
	for (int i = 0; i < m_data->m_numPairsUsed; ++i, ++src)
		src->clear();
	free(m_data);
	m_data = 0;
}

// ?setNameAndType@DictPair@Dict@@QAEXHW4DataType@Dict@@@Z @0x00313376
void Dict::DictPair::setNameAndType(int key, DataType type)
{
	if ((m_key & 0xFF) != type)
		clear();
	m_key = (key << 8) | type;
}

// ?clear@Dict@@QAEXXZ @0x00313574
void Dict::clear(void)
{
	releaseData();
	m_data = 0;
}

// ?findPairByKey@Dict@@ABEPAUDictPair@1@H@Z @0x0031313B
Dict::DictPair *Dict::findPairByKey(int key) const
{
	DictPairData *data = m_data;
	if (data == 0)
		return 0;
	int lo = 0;
	int hi = data->m_numPairsUsed;
	if (hi <= 0)
		return 0;
	do {
		int mid = (hi + lo - 1) >> 1;
		DictPair *pair = (DictPair *)(data + 1) + mid;
		int pairKey = (int)((unsigned int)pair->m_key >> 8);
		if (key > pairKey)
			lo = mid + 1;
		else if (key < pairKey)
			hi = mid;
		else
			return pair;
	} while (lo < hi);
	return 0;
}

// ?getType@Dict@@QBE?AW4DataType@1@H@Z @0x0031317C
Dict::DataType Dict::getType(int key) const
{
	DictPair *pair = findPairByKey(key);
	if (pair)
		return (DataType)(pair->m_key & 0xFF);
	return DICT_NONE;
}

// ?getBool@Dict@@QBE_NHPA_N@Z @0x00313198
bool Dict::getBool(int key, bool *exists) const
{
	DictPair *pair = findPairByKey(key);
	if (pair && (pair->m_key & 0xFF) == DICT_BOOL)
	{
		if (exists)
			*exists = true;
		return *(bool *)&pair->m_value;
	}
	if (exists)
		*exists = false;
	return false;
}
