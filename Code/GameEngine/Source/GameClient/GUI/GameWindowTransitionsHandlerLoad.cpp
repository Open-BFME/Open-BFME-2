// cl: /Ireference/shims/bfme2_ascii /O1 /MD /GX /DNDEBUG /D_CRTIMP= /G7 /arch:SSE
//
// GameWindowTransitionsHandler::load, retail 0x001DC7E1 (780 bytes): registers the
// window-transition INI field parsers under their name keys in the handler's lookup
// map (+0x0C), then reads Data\INI\WindowTransitions.ini through a local INI
// (rowed ctor 0x0002CDB0, loadFile 0x0002DC75, dtor 0x0002CE5B). ZH load supplies the
// purpose; the nineteen registrations are BFME 2 additions read from the bytes.
// The parsers keep their ledger signatures under neutral names and are stored through
// casts to the four-argument cdecl field-parser type.
//
// Frame size: retail's cl saw the whole name-key map walk (ObjectLookupMap::findSlot
// 0x0041F4E5 -> KeyToBucketMap::find 0x00148B27 -> _M_find 0x002888D4) and knew none
// of them keeps the address of the key temporary. Without that knowledge the key
// temporary and the saved ESP of the by-value path argument cannot share a slot
// (frame 0x884 instead of 0x880). The three bodies are therefore defined here as
// noinline members with the retail bytes; their COMDAT copies stay exact.
#include "ascii_string.h"
class Xfer;
enum INILoadType {INI_LOAD_INVALID, INI_LOAD_OVERWRITE};
class INI {public: INI(); ~INI(); unsigned char loadFile(AsciiString,INILoadType,Xfer*); private: char storage[0x87C];};
enum NameKeyType {NAMEKEY_INVALID=0,NAMEKEY_MAX=1<<23,FORCE_NAMEKEYTYPE_LONG=0x7fffffff};
class NameKeyGenerator;
extern NameKeyGenerator* TheNameKeyGenerator;
class Object;
struct KeyBucketNode { KeyBucketNode *next; int key; Object *value; };
struct KeyBucketTable
{
	KeyBucketNode **start;
	KeyBucketNode **finish;
	KeyBucketNode **storageEnd;
	unsigned size() const { return (unsigned)(finish - start); }
	KeyBucketNode *&at( unsigned n ) { return *( start + n ); }
};
// ObjectLookupMap is retail's lookup table for name keys (the find-and-insert
// walk 0x0041F4E5; its two callees are ledger-known spellings, shared with
// ObjectLookupMapFindSlot.cpp: KeyToBucketMap::find 0x00148B27 and the blind
// insertNode worker). Local spellings of those callees made this TU's findSlot
// copy unreprovable by retail truth, and since this TU links before the home
// unit the census kept an unproven copy for every referencing unit. The
// KeyToBucketMap base at +0 keeps the call/protocol identical, with no this
// adjustment anywhere.
struct KeyHashInt { unsigned operator()( int x ) const { return (unsigned)x; } };
struct KeyEqualInt { bool operator()( int a, int b ) const { return a == b; } };
class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char * );
	class KeyToBucketMap
	{
		friend class ObjectLookupMap;
	public:
		struct Slot { void *node; KeyToBucketMap *map; };
		__declspec(noinline) Slot *find( Slot &out, const int *key )
		{
			out.node = _M_find( *key );
			out.map = this;
			return &out;
		}
	private:
		struct value_type { int first; void *second; };
		int *insertNode( const value_type &value );
		unsigned tableSize() const { return m_table.size(); }
		KeyBucketNode *&tableAt( unsigned n ) { return m_table.at( n ); }
		unsigned bkt_num_key( int key ) const { return m_hash( key ) % tableSize(); }
		__declspec(noinline) void *_M_find( const int &key ) const
		{
			unsigned n = bkt_num_key( key );
			KeyBucketNode *first;
			for ( first = ( (KeyToBucketMap *)this )->tableAt( n ); first && !m_equals( first->key, key ); first = first->next )
			{
			}
			return first;
		}
		KeyHashInt m_hash;
		KeyEqualInt m_equals;
		char m_pad2[2];
		KeyBucketTable m_table;
		unsigned m_count;
	};
};
class ObjectLookupMap : public NameKeyGenerator::KeyToBucketMap
{
public:
	__declspec(noinline) Object **findSlot( int *key )
	{
		KeyToBucketMap::Slot out;
		find( out, key );
		KeyBucketNode *node = (KeyBucketNode *)out.node;
		if ( node == 0 )
		{
			out.node = (void *)*key;
			out.map = 0;
			return (Object **)( insertNode( (const KeyToBucketMap::value_type &)out ) + 1 );
		}
		return &node->value;
	}
	Object **slot( const NameKeyType &key ) { return findSlot( reinterpret_cast<int *>( const_cast<NameKeyType *>( &key ) ) ); }
};
typedef void (__cdecl *Factory)(INI*,void*,void*,const void*);
struct Gen_00489270;
void s5parse0059DE10(INI*, Gen_00489270*);
class Rva00360298Holder;
void Rva00360298Parse(INI*, Rva00360298Holder*);
class Rva003600D6Holder;
void Rva003600D6Parse(INI*, Rva003600D6Holder*);
class Rva003600D6Holder;
void Rva0035FD73Parse(INI*, Rva003600D6Holder*);
struct Gen_00489270;
void s4ParseFieldsRva005A01F0(INI*, Gen_00489270*);
class Rva003600D6Holder;
void Rva0035F6E2Parse(INI*, Rva003600D6Holder*);
class Rva0035F4E7Holder;
void Rva0035F4E7Parse(INI*, Rva0035F4E7Holder*);
struct Gen_00489270;
void s5parse0059D600(INI*, Gen_00489270*);
class Rva0035EEA7Holder;
void Rva0035EEA7Parse(INI*, Rva0035EEA7Holder*);
class Rva0035E650Holder;
void Rva0035E650Parse(INI*, Rva0035E650Holder*);
class Rva0035E327Holder;
void Rva0035E327Parse(INI*, Rva0035E327Holder*);
struct Gen_00489270;
void s4parse0059E860(INI*, Gen_00489270*);
struct Gen_00489270;
void s4parse0059E290(INI*, Gen_00489270*);
class Gen_00489270;
void rva0059EB90(INI*, Gen_00489270*);
class Rva0059B8F0Nugget {public: static void parse(INI*,void*,void*,const void*);};
class Rva0035D6F9Holder;
void Rva0035D6F9Parse(INI*, Rva0035D6F9Holder*);
struct Gen_00489270;
void s4ParseFieldsRva0059EE10(INI*, Gen_00489270*);
struct Gen_00489270;
void s5parse0059FB50(INI*, Gen_00489270*);
struct Gen_00489270;
void s4ParseFieldsRva0059D1F0(INI*, Gen_00489270*);
class GameWindowTransitionsHandler {public: void load(); private: char prefix[0xC]; ObjectLookupMap m_table;};
void GameWindowTransitionsHandler::load() {
    INI ini;
    *reinterpret_cast<Factory*>(m_table.slot(TheNameKeyGenerator->nameToKey("IMAGEFADE"))) = reinterpret_cast<Factory>(&s5parse0059DE10);
    *reinterpret_cast<Factory*>(m_table.slot(TheNameKeyGenerator->nameToKey("IMAGECROSSFADE"))) = reinterpret_cast<Factory>(&Rva00360298Parse);
    *reinterpret_cast<Factory*>(m_table.slot(TheNameKeyGenerator->nameToKey("SCREENFADE"))) = reinterpret_cast<Factory>(&Rva003600D6Parse);
    *reinterpret_cast<Factory*>(m_table.slot(TheNameKeyGenerator->nameToKey("TYPETEXT"))) = reinterpret_cast<Factory>(&Rva0035FD73Parse);
    *reinterpret_cast<Factory*>(m_table.slot(TheNameKeyGenerator->nameToKey("TEXTONFRAME"))) = reinterpret_cast<Factory>(&s4ParseFieldsRva005A01F0);
    *reinterpret_cast<Factory*>(m_table.slot(TheNameKeyGenerator->nameToKey("COUNTUP"))) = reinterpret_cast<Factory>(&Rva0035F6E2Parse);
    *reinterpret_cast<Factory*>(m_table.slot(TheNameKeyGenerator->nameToKey("WINFADE"))) = reinterpret_cast<Factory>(&Rva0035F4E7Parse);
    *reinterpret_cast<Factory*>(m_table.slot(TheNameKeyGenerator->nameToKey("FULLFADE"))) = reinterpret_cast<Factory>(&s5parse0059D600);
    *reinterpret_cast<Factory*>(m_table.slot(TheNameKeyGenerator->nameToKey("FLASH"))) = reinterpret_cast<Factory>(&Rva0035EEA7Parse);
    *reinterpret_cast<Factory*>(m_table.slot(TheNameKeyGenerator->nameToKey("BUTTONFLASH"))) = reinterpret_cast<Factory>(&Rva0035E650Parse);
    *reinterpret_cast<Factory*>(m_table.slot(TheNameKeyGenerator->nameToKey("WINSCALEUP"))) = reinterpret_cast<Factory>(&Rva0035E327Parse);
    *reinterpret_cast<Factory*>(m_table.slot(TheNameKeyGenerator->nameToKey("MAINMENUSCALEUP"))) = reinterpret_cast<Factory>(&s4parse0059E860);
    *reinterpret_cast<Factory*>(m_table.slot(TheNameKeyGenerator->nameToKey("MAINMENUMEDIUMSCALEUP"))) = reinterpret_cast<Factory>(&s4parse0059E290);
    *reinterpret_cast<Factory*>(m_table.slot(TheNameKeyGenerator->nameToKey("MAINMENUSMALLSCALEDOWN"))) = reinterpret_cast<Factory>(&rva0059EB90);
    *reinterpret_cast<Factory*>(m_table.slot(TheNameKeyGenerator->nameToKey("CONTROLBARARROW"))) = reinterpret_cast<Factory>(&Rva0059B8F0Nugget::parse);
    *reinterpret_cast<Factory*>(m_table.slot(TheNameKeyGenerator->nameToKey("SCORESCALEUP"))) = reinterpret_cast<Factory>(&Rva0035D6F9Parse);
    *reinterpret_cast<Factory*>(m_table.slot(TheNameKeyGenerator->nameToKey("REVERSESOUND"))) = reinterpret_cast<Factory>(&s4ParseFieldsRva0059EE10);
    *reinterpret_cast<Factory*>(m_table.slot(TheNameKeyGenerator->nameToKey("SOUNDFADE"))) = reinterpret_cast<Factory>(&s5parse0059FB50);
    *reinterpret_cast<Factory*>(m_table.slot(TheNameKeyGenerator->nameToKey("FREEZE_POST_LOAD_SOUNDS"))) = reinterpret_cast<Factory>(&s4ParseFieldsRva0059D1F0);
    ini.loadFile(AsciiString("Data\\INI\\WindowTransitions.ini"),INI_LOAD_OVERWRITE,0);
}
