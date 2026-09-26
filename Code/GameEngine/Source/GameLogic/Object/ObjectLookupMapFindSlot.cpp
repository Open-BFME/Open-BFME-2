// cl: /O1 /DNDEBUG /MD

// ObjectLookupMap::findSlot, retail 0x0041F4E5, 63 bytes: find-or-insert
// over the GameLogic object lookup table (sole caller is
// addObjectToLookupTable, 0x00242AC2, which stores the object through the
// returned slot). The map itself is a KeyToBucketMap (same bucket vector
// at +0x04/+0x08/+0x0C and count at +0x10, same rowed resize/allocateNode
// callees as NameKeyGeneratorMapInsert.cpp): the find and the blind
// insert worker are addressed through it at offset +0, so no this
// adjustment appears.
//
// Protocol: the find (pinned twin 0x00148B27) fills an out-pair
// {node, map} and returns it; on miss the pair slot is reused for the
// worker's {key, NULL} value (the node half is dead, the map half is
// never read back), which is why the frame stays a single 8-byte push
// pair and the NULL surfaces as and [ebp-4],0. The worker hands back
// the key slot, so findSlot bumps +4 to land on the value slot; a hit
// lands there directly (+8). Returning the bumped worker result is what
// keeps retail's add-after-call instead of a second lea.

class Object;

class NameKeyGenerator
{
public:
	class KeyToBucketMap
	{
		friend class ObjectLookupMap;

	public:
		struct value_type
		{
			int first;
			void *second;
		};

		struct Slot
		{
			void *node;
			KeyToBucketMap *map;
		};

		Slot *find( Slot &out, const int *key );

	private:
		int *insertNode( const value_type &value );
		char m_pad[ 0x14 ];
	};
};

struct ObjectLookupNode
{
	void *next;			// +0x00
	int key;			// +0x04
	Object *value;		// +0x08
};

class ObjectLookupMap
{
public:
	Object **findSlot( int *key );

private:
	NameKeyGenerator::KeyToBucketMap m_map;		// +0x00
};


// ?findSlot@ObjectLookupMap@@QAEPAPAVObject@@PAH@Z
Object **ObjectLookupMap::findSlot( int *key )
{
	NameKeyGenerator::KeyToBucketMap::Slot out;
	m_map.find( out, key );
	ObjectLookupNode *node = (ObjectLookupNode *)out.node;
	if ( node == 0 )
	{
		// Reuse out's slot for the worker pair: the node half is dead and
		// the map half is never read back, so the key/NULL pair shares it.
		out.node = (void *)*key;
		out.map = 0;
		return (Object **)(m_map.insertNode( (const NameKeyGenerator::KeyToBucketMap::value_type &)out ) + 1);
	}
	return &node->value;
}
