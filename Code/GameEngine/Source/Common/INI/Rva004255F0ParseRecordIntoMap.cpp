// cl: -DNDEBUG -MD -EHsc
// Open-BFME7: INI block parser at 0x004255F0 (105 B): a zeroed (AsciiString
// name + 4-byte value) record local is filled through INI::initFromINI with
// the field table at VA 0x010F1B34 then inserted into the map the store
// argument points at (the red-black tree insert_unique at 0x00424BA0 whose
// pair result comes back through the hidden pointer) and destroyed by the
// record destructor at 0x00423280.  Address-derived names.

class INI;
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);
#include "../../../Include/Common/INI/FieldParse.h"

#include "../../../Include/Common/INI/INI.h"

// The record is the rowed BfmeRecord001DD3BC (dtor 0x001DD1FF) and the store is
// the set whose rowed insert is 0x001DE7B5 (stlport_set_record_001dd3bc_insert.cpp).
struct BfmeRecord001DD3BC
{
	BfmeRecord001DD3BC() : m_value( 0 ) {}
	~BfmeRecord001DD3BC();

	AsciiString m_name;
	int m_value;
};

namespace _STL {
template <class T> struct less;
template <class T> class allocator;
template <class T> struct _Const_traits;
template <class T, class Traits> struct _Rb_tree_iterator { void *_M_node; };
template <class A, class B> struct pair { pair(); A first; B second; };
template <class K, class Compare = less<K>, class Alloc = allocator<K> >
class set
{
public:
	pair<_Rb_tree_iterator<K, _Const_traits<K> >, bool> insert( const K &value );
};
}
typedef _STL::set<BfmeRecord001DD3BC> Rva004255F0Map;



// Retail VA 0x00BDC048: the record's two fields and the zero sentinel.
extern const FieldParse Rva004255F0FieldParseTable[] = {
	{ "Side", &INI::parseAsciiString, 0, 0x0 },
	{ "Sound", &INI::parseAudioEventRTS, 0, 0x4 },
	{ 0, 0, 0, 0 }
};

class Rva004255F0
{
public:
	static void parseRecordIntoMap( INI *ini, void *instance, void *store, const void *userData );
};

// ?parseRecordIntoMap@Rva004255F0@@SAXPAVINI@@PAX1PBX@Z
void Rva004255F0::parseRecordIntoMap( INI *ini, void *, void *store, const void * )
{
	BfmeRecord001DD3BC record;
	ini->initFromINI( &record, Rva004255F0FieldParseTable );
	((Rva004255F0Map *)store)->insert( record );
}
