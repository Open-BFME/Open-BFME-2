// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Retail 0x00396E92, 154B: a behavior member (ret 4, module data at this+4)
// that looks an object's name up in the module data's record vector at +0x5C
// (12-byte BfmeStringRecord00395E75 entries: two strings and a float, copied
// through 0x00395E75 and destroyed through the rowed 0x00395D77) and returns
// the float of the first record whose leading string equals the object's
// string at Object+0x58, else 0.0. Each record is copied out by value before
// the compare, so the copy is destroyed on both paths. Owner and slot name
// not established: address-derived.

#include "ascii_string.h"

typedef float Real;
typedef int Int;

struct Rva00395D77
{
	~Rva00395D77();
};

struct BfmeStringRecord00395E75 : public Rva00395D77
{
	BfmeStringRecord00395E75(const BfmeStringRecord00395E75 &other);
	char *m_name;
	char *m_other;
	Real m_value;
};

class Object
{
public:
	unsigned char m_pad00[0x58];
	AsciiString m_name;
};

struct Rva00396E92ModuleData
{
	unsigned char m_pad00[0x5C];
	BfmeStringRecord00395E75 *m_recordsBegin;
	BfmeStringRecord00395E75 *m_recordsEnd;
	BfmeStringRecord00395E75 *m_recordsCapacity;
};

class Rva00396E92
{
public:
	Real rva00396E92( Object *obj );

private:
	void *m_vtable;
	const Rva00396E92ModuleData *m_moduleData;
};

Real Rva00396E92::rva00396E92( Object *obj )
{
	if( obj == 0 )
		return 0.0f;

	const Rva00396E92ModuleData *d = m_moduleData;
	Int count = d->m_recordsEnd - d->m_recordsBegin;
	for( Int i = 0; i < count; ++i )
	{
		BfmeStringRecord00395E75 record = d->m_recordsBegin[ i ];
		if( *(const AsciiString *)&record.m_name == obj->m_name )
			return record.m_value;
	}

	return 0.0f;
}
