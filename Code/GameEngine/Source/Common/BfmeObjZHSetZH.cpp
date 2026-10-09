// cl: /Ireference/shims/bfme2_ascii
#include <string.h>
#define BFME_ASCII_DTOR_DECL
#include "ascii_string.h"
inline void *operator new(unsigned int, void *where) { return where; }

// Native 006BFB20..006BFBC5 stores a 16-byte element in the vector at +38.
// Its three scalar words and the string at +0C are copied separately;
// the temporary string is released only on the normal exit, with no EH
// cleanup. Keep that explicit lifetime using the shared AsciiString contract.
// clear() is its existing canonical releaseBuffer36410 contract. The normal
// exit releases the buffer before ending this manually constructed storage;
// a declared destructor keeps the native deleting-dtor COMDAT contract.
// BfmeObjZH/BfmeElemCD remain the existing opaque donor views, not recovered
// original target class names. BFME1 ee4ca97eb0ae removed this same family
// of private StringBase aliases; its canonical dependency is reconciled here
// against the verified BFME2 providers, not adopted as an address/name proof.
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
	// Aligned storage for the explicitly constructed canonical string.
	unsigned int nameStorage;
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
		const AsciiString *name);

private:
	unsigned char m_pad[0x38];
	BfmeVecCD m_values;
	BfmeVecZH m_maximum;
	friend void Rva006BFBD0Parse(class INI *, void *, void *, const void *);
};

void BfmeObjZH::bfmeSetZH(const BfmeVecZH *value,
	const AsciiString *name)
{
	BfmeElemCD local;
	AsciiString &localName = *new (&local.nameStorage) AsciiString;
	BfmeObjZH *owner = this;
	volatile const BfmeVecZH *vector = value;
	local.x = vector->x;
	local.y = vector->y;
	local.z = vector->z;
	localName = *name;

	BfmeVecCD *values = &owner->m_values;
	BfmeElemCD *position = values->m_finish;
	if (position != values->m_end)
	{
		if (position != 0)
		{
			position->x = local.x;
			position->y = local.y;
			position->z = local.z;
			reinterpret_cast<AsciiString *>(&position->nameStorage)->AsciiString::AsciiString(localName);
		}
		++values->m_finish;
	}
	else
	{
		BfmeFalseCD tag;
		values->overflow(position, local, tag, 1, true);
	}

	localName.clear();
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
	unsigned int nameStorage;
	AsciiString &name = *new (&nameStorage) AsciiString("");
	BfmeVecZH value;
	value.x = ini->scanReal(ini->getNextSubToken("X"));
	value.y = ini->scanReal(ini->getNextSubToken("Y"));
	value.z = ini->scanReal(ini->getNextSubToken("Z"));

	const char *token = ini->getNextTokenOrNull(0);
	if (token != 0)
		reinterpret_cast<StringBase<char> *>(&name)->set(token, (int)strlen(token));

	BfmeObjZH *object = (BfmeObjZH *)store;
	object->bfmeSetZH(&value, &name);
	if (object->m_maximum.z < value.z)
		object->m_maximum = value;
	bfmeApplyEB((BfmeObjEB *)object);
	name.clear();
}
