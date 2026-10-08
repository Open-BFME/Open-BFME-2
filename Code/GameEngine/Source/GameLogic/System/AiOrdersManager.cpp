// WorldBuilder registerOrder (0x00DF7F50; AiOrdersManager.cpp line383)
// calls addOrderToObjectQueues (0x00DF7740). Retail's registerOrder at
// 0x003558A3 calls 0x003557B7, whose 236-byte body reproduces that operation.
// WB's order-based placement at 0x00355096 is refuted by the retail call site.
// Native Ghidra extents: 3558A3/51 and 3557B7/236; queue ctor and range-clear /
// insert bodies independently establish the consumed 20-byte queue ABI.
// GroupOrder supplies a vector of 32-bit object IDs at +4 and an order ID +10.
// Native inserts at manager +0x24 use the existing pointer-valued insert ABI.
// Its first eight returned bytes are the node/table iterator, followed by bool.
// The typed _M_find specialization preserves STLport4.5.3 identity hash /
// equality semantics and the independently verified 20-byte table layout.
// It reads the bucket vector through a nested layout view so the TU does not
// emit optimized copies of canonical /Od vector<void*> accessors. Its complete
// 47 bytes are identical to the existing key-only lookup owner, with no relocs.
// cl: /O1 /G7 /arch:SSE /EHsc /MD /DNDEBUG /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
#include <hash_map>
#include <vector>
#include <new>
enum ObjectID { INVALID_ID=0 };
namespace rts { template<class T> struct hash { size_t operator()(const T& x) const { return (size_t)x; } }; }
class Rva0054840A {
public:
    Rva0054840A(ObjectID);
    void rva005482E9(int);
    void rva00548464(int,int);
private: unsigned char opaque[0x14];
};
class GroupOrder {
public:
    unsigned char opaque[4];
    _STL::vector<ObjectID> objects;
    int id;
    int unknown14;
};
struct NameKeyBucket { NameKeyBucket* next; int key; void* value; };
class NameKeyGenerator {
public: class KeyToBucketMap {
public:
    struct value_type { int first; void* second; };
    struct insert_result { NameKeyBucket* first; KeyToBucketMap* second; bool inserted; };
    insert_result insert(const value_type&);
};
};
typedef _STL::hash_map<ObjectID,Rva0054840A*,rts::hash<ObjectID>,_STL::equal_to<ObjectID> > QueueMap;
typedef QueueMap::iterator::_Hashtable QueueTable;
typedef _STL::_Hashtable_node<QueueTable::value_type> QueueNode;
namespace _STL {
template<> template<> QueueNode* QueueTable::_M_find<ObjectID>(const ObjectID& id) const;
}
struct QueueBucketVector {
    void** begin;
    void** end;
    void** capacityEnd;
    unsigned size() const { return (unsigned)(end-begin); }
    void* const& at(unsigned index) const { return begin[index]; }
};
struct QueueBucketsView { unsigned char functors[4]; QueueBucketVector buckets; unsigned count; };
namespace _STL {
template<> template<> QueueNode* QueueTable::_M_find<ObjectID>(const ObjectID& id) const {
    const QueueBucketsView* view=reinterpret_cast<const QueueBucketsView*>(this);
    unsigned key=_M_hash(id);
    unsigned bucket=key % view->buckets.size();
    QueueNode* node=static_cast<QueueNode*>(view->buckets.at(bucket));
    while(node && !_M_equals(_M_get_key(node->_M_val),id)) node=node->_M_next;
    return node;
}
}
class Object;
class ObjectLookupMap { public: Object** findSlot(int*); private: unsigned char opaque[0x14]; };
class AiOrdersManager {
public: void addOrderToObjectQueues(int,GroupOrder*);
    void registerOrder(int,GroupOrder*);
private: unsigned char opaque[0x10]; ObjectLookupMap orders; QueueMap queues;
};
void AiOrdersManager::addOrderToObjectQueues(int mode,GroupOrder* order) {
    int clearFlags=0;
    int insertFlags;
    switch(mode) {
    case 0: clearFlags=1; insertFlags=1; break;
    case 1: clearFlags=2; insertFlags=1; break;
    case 2: insertFlags=2; break;
    default: return;
    }
    for (_STL::vector<ObjectID>::iterator i=order->objects.begin(); i!=order->objects.end(); ++i) {
        ObjectID id=*i;
        QueueMap::iterator queue=queues.find(id);
        if (queue==queues.end()) {
            Rva0054840A* value=new Rva0054840A(id);
            NameKeyGenerator::KeyToBucketMap::value_type pair={ (int)id,value };
            NameKeyGenerator::KeyToBucketMap::insert_result result=reinterpret_cast<NameKeyGenerator::KeyToBucketMap*>(&queues)->insert(pair);
            struct ResultView { QueueMap::iterator first; bool inserted; };
            queue = reinterpret_cast<ResultView*>(&result)->first;
        }
        queue->second->rva005482E9(clearFlags);
        queue->second->rva00548464(insertFlags,order->id);
    }
}

void AiOrdersManager::registerOrder(int mode,GroupOrder* order) {
    if (order) {
        int id=order->id;
        *reinterpret_cast<GroupOrder**>(orders.findSlot(&id))=order;
        addOrderToObjectQueues(mode,order);
    }
}
