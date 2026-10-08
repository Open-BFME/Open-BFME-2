// cl: /O1 /DNDEBUG /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc
// ObjectSellInfo's destructors, the BuildAssistant sell-list entry.
//
// Target evidence: each ObjectSellInfo is 12 bytes from operator new:
// vftable 0x00C1A074, whose one slot is the deleting destructor 0x003919D9
// that inlines the empty destructor 0x003916A4 (both store that vftable),
// then ZH's m_id and m_sellFrame. BuildAssistant::xferTheSellList, which
// news these entries, lives in BuildAssistantXferSellList.cpp.

typedef unsigned int UnsignedInt;

enum ObjectID
{
	INVALID_ID = 0
};

class ObjectSellInfo
{
public:
	ObjectSellInfo( void ) : m_id( INVALID_ID ), m_sellFrame( 0 ) {}
	virtual ~ObjectSellInfo( void );

	ObjectID m_id;																														///< 0x04
	UnsignedInt m_sellFrame;																									///< 0x08
};

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
ObjectSellInfo::~ObjectSellInfo( void )
{

}  // end ~ObjectSellInfo
