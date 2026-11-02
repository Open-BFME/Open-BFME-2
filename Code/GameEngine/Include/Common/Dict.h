// Target facts (BFME2 1.06, RVAs): Dict is four bytes with no virtual functions or base-class calls. Constructor 0x00313581 writes only its data pointer at +0, copy constructor 0x00329D50 copies it and increments its pointee's 16-bit reference count, and nonvirtual destructor 0x000ABB82 jumps to releaseData (0x0031339C). None stores a vptr or vbptr. SidesInfo's constructor calls Dict(0) on +4 at 0x0032C681 and constructs ScriptList at +8 at 0x0032C68D, bounding Dict's extent to four bytes. Assignment 0x003133E1 releases the old data, copies the pointer and increments the reference count. These special members remain out of line.
// Target layout: releaseData (0x0031339C) reads the reference count at data+0 and the used count at data+4, with eight-byte pairs starting at data+6. ensureUnique (0x0031346B) reads the allocated count at data+2 and caps requests at 32767. findPairByKey (0x0031313B) reads a pair's four-byte key at +0; getBool/getInt/getReal (0x00313198/0x003131CA/0x003131FC) read its value at +4 and test tags 0/1/2. getType (0x0031317C) returns key&255 or -1; setNameAndType (0x00313376) stores (name<<8)|type. String tags 3/4 are tested at 0x003135B3/0x003135FA. writeDict reads the used count inline at 0x00307DA2. SidesInfo::swap exchanges Dict's pointers inline at 0x0032B080..0x0032B089. The rowed cleanup forwarder 0x000ABB82 and global teardown 0x007B7B14 call the private releaseData provider directly.
// Target member rows (RVAs): nth key/type 0x00306BA9/0x00306BCD, nth bool/int/real 0x00313232/0x00313253/0x00313274, strings 0x0031359F/0x003135E6, nth strings 0x0031362D/0x00313665, known 0x002A9880, clear 0x00313574, nullable copy 0x00329CF0, sortPairs 0x00313299, setPrep 0x0031369D, setters 0x003136F6/0x00313716/0x00313736/0x0031375A/0x00313781, remove/copyPairFrom 0x003137A8/0x003137EE, pair clear/copyFrom 0x0031334A/0x00313404 and unnamed pair bit accessors 0x00306B8F/0x00306B97/0x00306B9F. Both ledger key spellings of getAsciiString share 0x0031359F. Donor (Zero Hour Common/Dict.h) facts: class, field, enum and inline accessor names, and the empty release-build validate helper; its six-byte DictPairData and eight-byte DictPair agree with the target accesses. No donor header is included.

#pragma once

#ifndef __BFME2_DICT_H_
#define __BFME2_DICT_H_

class AsciiString;
class UnicodeString;
enum NameKeyType;
struct Rva000ABB82CleanupForward;
void __cdecl rva007B7B14();

class Dict
{
	friend struct Rva000ABB82CleanupForward;
	friend void __cdecl rva007B7B14();

public:

	enum { MAX_LEN = 32767 };
	enum DataType
	{
		DICT_NONE = -1,
		DICT_BOOL = 0,
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
		static unsigned int Rva00306B8FNameBits(unsigned int key);
		unsigned int Rva00306B97TypeBits() const;
		unsigned int Rva00306B9FNameBits() const;
		DataType getType() const { return (DataType)((unsigned int)m_key & 0xFF); }
		NameKeyType getName() const { return (NameKeyType)((unsigned int)m_key >> 8); }
		bool *asBool() { return (bool *)&m_value; }
		int *asInt() { return (int *)&m_value; }
		float *asReal() { return (float *)&m_value; }
		AsciiString *asAsciiString() { return (AsciiString *)&m_value; }
		UnicodeString *asUnicodeString() { return (UnicodeString *)&m_value; }
	};

	struct DictPairData
	{
		unsigned short m_refCount;
		unsigned short m_numPairsAllocated;
		unsigned short m_numPairsUsed;

		DictPair *peek() { return (DictPair *)(this + 1); }
	};

	Dict(int numPairsToPreAllocate = 0);
	Dict(const Dict &src);
	~Dict();
	Dict &operator=(const Dict &src);

	void clear();
	void swap(Dict &other)
	{
		DictPairData *data = m_data;
		m_data = other.m_data;
		other.m_data = data;
	}
	int getPairCount() const { return m_data ? m_data->m_numPairsUsed : 0; }
	NameKeyType getNthKey(int n) const;
	DataType getType(int key) const;
	DataType getNthType(int n) const;
	bool known(NameKeyType key, DataType type) const;
	bool getBool(int key, bool *exists = 0) const;
	int getInt(int key, bool *exists = 0) const;
	float getReal(int key, bool *exists = 0) const;
	AsciiString getAsciiString(int key, bool *exists = 0) const;
	AsciiString getAsciiString(NameKeyType key, bool *exists = 0) const;
	UnicodeString getUnicodeString(int key, bool *exists = 0) const;
	bool getNthBool(int n) const;
	int getNthInt(int n) const;
	float getNthReal(int n) const;
	AsciiString getNthAsciiString(int n) const;
	UnicodeString getNthUnicodeString(int n) const;
	void setBool(int key, bool value);
	void setInt(int key, int value);
	void setReal(int key, float value);
	void setAsciiString(int key, const AsciiString &value);
	void setUnicodeString(int key, const UnicodeString &value);
	bool remove(int key);
	void copyPairFrom(const Dict &that, int key);
	void Rva00329CF0(const Dict *src);

private:

	void validate() const { }
	void releaseData();
	DictPair *findPairByKey(int key) const;
	void sortPairs();
	DictPair *ensureUnique(int numPairsNeeded, bool preserveData, DictPair *pairToTranslate);
	DictPair *setPrep(int key, DataType type);
	DictPairData *m_data;
};

#endif
