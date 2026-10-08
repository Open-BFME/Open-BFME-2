// ?bfmeSetZH@BfmeObjZH@@QAEXPBUBfmeVecZH@@PBVBFMERetailAsciiString@@@Z
// Retail stores a 16-byte ZH element in the vector at +0x38.

#include <string.h>

inline void *operator new(unsigned int, void *where)
{
	return where;
}

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text) throw();
	void releaseBuffer() throw();
	void *m_data;
};

class BfmeObjZH;
struct BfmeElemCD;

template <typename T> class StringBase
{
public:
	StringBase() : m_data(0) {}
	void set(const StringBase &other);
	void set(const T *text, int length);

private:
	void releaseBuffer();
	friend struct BfmeElemCD;
	friend class BfmeObjZH;

private:
	void *m_data;
private:
	StringBase(const StringBase &other);
	friend class BFMERetailAsciiString;
	friend class BfmeElemCD;
	friend class BfmeFalseCD;
	friend class BfmeObjZH;
	friend class BfmeVecCD;
	friend class BfmeVecZH;
};

// LINK-COMDAT: StringBase<char> default ctor kept as /O1 (and [eax],0) from
// ModuleDataCtor.cpp; this TU needs default flags for its bfmeSetZH row, which
// inlines the ctor as mov. Specialize only the member under "s" so our emitted
// copy matches the kept one while inlined uses keep default flags.
#pragma optimize("s", on)
template<> StringBase<char>::StringBase() : m_data(0) {}
#pragma optimize("", on)


struct BfmeVecZH
{
	float x;
	float y;
	float z;
};

struct BfmeFalseCD
{
};

struct BfmeElemCD
{
	float x;
	float y;
	float z;
	StringBase<char> name;
};

class BfmeVecCD
{
public:
	void overflow(BfmeElemCD *position, const BfmeElemCD &value,
		const BfmeFalseCD &, unsigned int fill, bool atEnd);

	BfmeElemCD *m_start;
	BfmeElemCD *m_finish;
	BfmeElemCD *m_end;
};



class BfmeObjZH
{
public:
	void bfmeSetZH(const BfmeVecZH *value,
		const BFMERetailAsciiString *name);

private:
	unsigned char m_pad[0x38];
	BfmeVecCD m_values;
	BfmeVecZH m_maximum;
	friend void Rva006BFBD0Parse(class INI *, void *, void *, const void *);
};

void BfmeObjZH::bfmeSetZH(const BfmeVecZH *value,
	const BFMERetailAsciiString *name)
{
	BfmeElemCD local;
	BfmeObjZH *owner = this;
	volatile const BfmeVecZH *vector = value;
	local.x = vector->x;
	local.y = vector->y;
	local.z = vector->z;
	local.name.set(reinterpret_cast<const StringBase<char> &>(*name));

	BfmeVecCD *values = &owner->m_values;
	BfmeElemCD *position = values->m_finish;
	if (position != values->m_end)
	{
		if (position != 0)
			new (position) BfmeElemCD(local);
		++values->m_finish;
	}
	else
	{
		BfmeFalseCD tag;
		values->overflow(position, local, tag, 1, true);
	}

	local.name.releaseBuffer();
}

class INI
{
public:
	const char *getNextSubToken(const char *separators) throw();
	const char *getNextTokenOrNull(const char *separators) throw();
	float scanReal(const char *token) throw();
};

class BfmeObjEB;
void bfmeApplyEB(BfmeObjEB *object);

// Native boundary 006BFBD0..006BFCA5 (213B). Target evidence proves the
// X/Y/Z tokens at VA BBE3C8/C4/C0, store argument, maximum at +44 and
// calls to the rowed bfmeSetZH/scanReal/bfmeApplyEB/StringBase providers.
// BFME1 donor BfmeConv2151.cpp at ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f
// supplies the parsing algorithm; its static scanner becomes thiscall here.
// BfmeObjZH is an existing donor view; the target's original class name
// and parser name remain unknown. Retail has no unwind cleanup for the
// scratch string, so release it explicitly on the normal exit.
void Rva006BFBD0Parse(INI *ini, void *, void *store, const void *)
{
	BFMERetailAsciiString name("");
	BfmeVecZH value;
	value.x = ini->scanReal(ini->getNextSubToken("X"));
	value.y = ini->scanReal(ini->getNextSubToken("Y"));
	value.z = ini->scanReal(ini->getNextSubToken("Z"));

	const char *token = ini->getNextTokenOrNull(0);
	if (token != 0)
		((StringBase<char> *)&name)->set(token, strlen(token));

	BfmeObjZH *object = (BfmeObjZH *)store;
	object->bfmeSetZH(&value, &name);
	if (object->m_maximum.z < value.z)
		object->m_maximum = value;
	bfmeApplyEB((BfmeObjEB *)object);
	name.releaseBuffer();
}
