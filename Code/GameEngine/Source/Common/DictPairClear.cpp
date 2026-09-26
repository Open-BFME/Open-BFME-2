// cl: /O1 /DNDEBUG /MD
// Dict pair clear plus releaseData.
// Reference basis is BFME1 Dict_releaseData.cpp (retail 0x000681C0), which
// carries the Dict layout, the pair switch and releaseData. BFME2 outlines
// the pair switch as its own 43B body and frees through the game _free.

class AsciiString
{
public:
	static const AsciiString TheEmptyString;

	AsciiString(const AsciiString &other);
	~AsciiString();
	AsciiString &operator=(const AsciiString &other);

private:
	char *m_data;
};

template <typename T> class StringBase
{
public:
	StringBase(const StringBase &other);
	void set(const StringBase &other);

private:
	void *m_data;
};

extern "C" void free(void *);

#pragma function(memset)
extern "C" void *memset(void *dst, int value, unsigned int size);

namespace _STL { template <class _Tp> class allocator; template <> class allocator<char> { public: static char *allocate(unsigned int bytes, const void *hint); }; }

__declspec(noreturn) void __stdcall _CxxThrowException(void *pExc, void *pInfo);

class UnicodeString
{
public:
	UnicodeString(const UnicodeString &other)
	{
		((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&other);
	}
	~UnicodeString();
	void releaseBuffer();

	static const UnicodeString TheEmptyString;

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
		void copyFrom(DictPair *that);
	};

	struct DictPairData
	{
		unsigned short m_refCount;
		unsigned short m_numPairsAllocated;
		unsigned short m_numPairsUsed;
	};

public:
  Dict(int numPairsToPreAllocate);
  void clear();
  DataType getType(int key) const;
  bool getBool(int key, bool *exists) const;
  int getInt(int key, bool *exists) const;
  float getReal(int key, bool *exists) const;
 bool getNthBool(int n) const;
 int getNthInt(int n) const;
 float getNthReal(int n) const;
 AsciiString getNthAsciiString(int n) const;
 AsciiString getAsciiString(int key, bool *exists) const;
 UnicodeString getUnicodeString(int key, bool *exists) const;

private:
	void releaseData();
	DictPair *findPairByKey(int key) const;
	void sortPairs();
	DictPair *ensureUnique(int numPairsNeeded, bool preserveData, DictPair *pairToTranslate);

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

// ?copyFrom@DictPair@Dict@@QAEXPAU12@@Z @0x00313404
void Dict::DictPair::copyFrom(DictPair *that)
{
	int curType = m_key & 0xFF;
	int newType = that->m_key & 0xFF;
	if (curType != newType)
		clear();
	switch (newType)
	{
		case DICT_BOOL:
		case DICT_INT:
		case DICT_REAL:
			*this = *that;
			break;
		case DICT_ASCIISTRING:
			m_key = that->m_key;
			*(AsciiString *)&m_value = *(AsciiString *)&that->m_value;
			break;
		case DICT_UNICODESTRING:
			m_key = that->m_key;
			((StringBase<unsigned short> *)&m_value)->set(*(StringBase<unsigned short> *)&that->m_value);
			break;
	}
}

// ?ensureUnique@Dict@@AAEPAUDictPair@1@H_NPAU21@@Z @0x0031346B 265B
// Dict::ensureUnique from ZH Dict.cpp donor (BFME1 0x000683D0). Early-out when
// unique with enough slots, throws 0xDEAD0002 via 0xCFEEE4 info when over
// MAX_LEN, else rounds to 4 via allocate plus memset and copies via copyFrom.
// Callers at 0x00313594 0x003136C3 0x003137C4, layout from DictPairData header.
Dict::DictPair *Dict::ensureUnique(int numPairsNeeded, bool preserveData, DictPair *pairToTranslate)
{
	if (m_data && m_data->m_refCount == 1 && m_data->m_numPairsAllocated >= numPairsNeeded)
		return pairToTranslate;
	if (numPairsNeeded > 32767)
	{
		int marker = 0xdead0002;
		_CxxThrowException(&marker, (void *)0xCFEEE4);
	}
	DictPairData *newData = 0;
	if (numPairsNeeded > 0)
	{
		int minBytes = sizeof(DictPairData) + numPairsNeeded * sizeof(DictPair);
		int actualBytes = ((minBytes + 3) / 4) * 4;
		newData = (DictPairData *)_STL::allocator<char>::allocate(actualBytes, 0);
		memset(newData, 0, actualBytes);
		newData->m_refCount = 1;
		newData->m_numPairsAllocated = (actualBytes - sizeof(DictPairData)) / sizeof(DictPair);
		newData->m_numPairsUsed = 0;
		if (preserveData && m_data)
		{
			int i = 0;
			DictPair *src = (DictPair *)(m_data + 1);
			DictPair *dst = (DictPair *)(newData + 1);
			for (; i < m_data->m_numPairsUsed; ++i, ++src, ++dst)
				dst->copyFrom(src);
			newData->m_numPairsUsed = m_data->m_numPairsUsed;
		}
	}
	int delta = 0;
	if (pairToTranslate && m_data)
		delta = pairToTranslate - (DictPair *)(m_data + 1);
	releaseData();
	m_data = newData;
	if (pairToTranslate && m_data)
		pairToTranslate = (DictPair *)(m_data + 1) + delta;
	return pairToTranslate;
}

// ?clear@Dict@@QAEXXZ @0x00313574
void Dict::clear(void)
{
	releaseData();
	m_data = 0;
}

// ??0Dict@@QAE@H@Z @0x00313581 30B
// Dict ctor from ZH Dict.cpp donor (BFME1 Dict::Dict). Inits m_data to 0 and
// ensures capacity via rowed ensureUnique at 0x0031346B when prealloc nonzero.
// Between clear at 0x00313574 and getAsciiString at 0x0031359F. Callers include
// BfmeThingUBB ctor pin plus 11 unclaimed Dict users. Returns this.
Dict::Dict(int numPairsToPreAllocate) : m_data(0)
{
	if (numPairsToPreAllocate)
		ensureUnique(numPairsToPreAllocate, false, 0);
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

// ?getInt@Dict@@QBEHHPA_N@Z @0x003131CA
int Dict::getInt(int key, bool *exists) const
{
	DictPair *pair = findPairByKey(key);
	if (pair && (pair->m_key & 0xFF) == DICT_INT)
	{
		if (exists)
			*exists = true;
		return *(int *)&pair->m_value;
	}
	if (exists)
		*exists = false;
	return 0;
}

// ?getReal@Dict@@QBEMHPA_N@Z @0x003131FC
float Dict::getReal(int key, bool *exists) const
{
	DictPair *pair = findPairByKey(key);
	if (pair && (pair->m_key & 0xFF) == DICT_REAL)
	{
		if (exists)
			*exists = true;
		return *(float *)&pair->m_value;
	}
	if (exists)
		*exists = false;
	return 0.0f;
}

// ?getNthBool@Dict@@QBE_NH@Z @0x00313232
bool Dict::getNthBool(int n) const
{
	if (m_data)
	{
		DictPair *pair = (DictPair *)(m_data + 1) + n;
		if (pair && (pair->m_key & 0xFF) == DICT_BOOL)
			return *(bool *)&pair->m_value;
	}
	return false;
}

// ?getNthInt@Dict@@QBEHH@Z @0x00313253
int Dict::getNthInt(int n) const
{
	if (m_data)
	{
		DictPair *pair = (DictPair *)(m_data + 1) + n;
		if (pair && (pair->m_key & 0xFF) == DICT_INT)
			return *(int *)&pair->m_value;
	}
	return 0;
}

// ?getNthReal@Dict@@QBEMH@Z @0x00313274
float Dict::getNthReal(int n) const
{
	if (m_data)
	{
		DictPair *pair = (DictPair *)(m_data + 1) + n;
		if (pair && (pair->m_key & 0xFF) == DICT_REAL)
			return *(float *)&pair->m_value;
	}
	return 0.0f;
}

// ?getNthAsciiString@Dict@@QBE?AVAsciiString@@H@Z @0x0031362D 56B
// Dict indexed Ascii getter twin of rowed getNthBool at 0x00313232. Checks pair
// type DICT_ASCIISTRING via m_data peek plus n then copies through pinned
// StringBase narrow copy at 0x000365F0 or returns TheEmptyString. Caller at
// 0x00307E56. Prev getUnicodeString next SidesList getter.
AsciiString Dict::getNthAsciiString(int n) const
{
	if (m_data)
	{
		DictPair *pair = (DictPair *)(m_data + 1) + n;
		if (pair && (pair->m_key & 0xFF) == DICT_ASCIISTRING)
			return *(AsciiString *)&pair->m_value;
	}
	return AsciiString::TheEmptyString;
}

// ?sortPairs@Dict@@AAEXXZ @0x00313299
void Dict::sortPairs()
{
	if (m_data == 0)
		return;
	for (int gap = m_data->m_numPairsUsed >> 1; gap > 0; gap >>= 1)
	{
		for (int i = gap; i < m_data->m_numPairsUsed; ++i)
		{
			for (int j = i - gap; j >= 0; j -= gap)
			{
				DictPair *a = (DictPair *)(m_data + 1) + j;
				DictPair *b = (DictPair *)(m_data + 1) + j + gap;
				if ((int)((unsigned int)a->m_key >> 8) > (int)((unsigned int)b->m_key >> 8))
				{
					DictPair tmp = *a;
					*a = *b;
					*b = tmp;
				}
				else
					break;
			}
		}
	}
}

// ?getAsciiString@Dict@@QBE?AVAsciiString@@HPA_N@Z @0x0031359F
AsciiString Dict::getAsciiString(int key, bool *exists) const
{
	DictPair *pair = findPairByKey(key);
	if (pair && (pair->m_key & 0xFF) == DICT_ASCIISTRING)
	{
		if (exists)
			*exists = true;
		return *(AsciiString *)&pair->m_value;
	}
	if (exists)
		*exists = false;
	return AsciiString::TheEmptyString;
}

// ?getUnicodeString@Dict@@QBE?AVUnicodeString@@HPA_N@Z @0x003135E6 71B
// Dict Unicode getter twin of rowed getAsciiString at 0x0031359F. Checks for
// DICT_UNICODESTRING via rowed findPairByKey at 0x0031313B then copies through
// the pinned StringBase wide copy at 0x00037050 or returns TheEmptyString.
// Caller at 0x002AFD6F. Prev getAsciiString next SidesList getter.
UnicodeString Dict::getUnicodeString(int key, bool *exists) const
{
	DictPair *pair = findPairByKey(key);
	if (pair && (pair->m_key & 0xFF) == DICT_UNICODESTRING)
	{
		if (exists)
			*exists = true;
		return *(UnicodeString *)&pair->m_value;
	}
	if (exists)
		*exists = false;
	return UnicodeString::TheEmptyString;
}
