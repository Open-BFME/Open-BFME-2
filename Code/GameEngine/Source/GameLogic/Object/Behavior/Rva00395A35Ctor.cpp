// cl: /DNDEBUG /MD /EHsc
// Native C1A268 slots are deleting dtor 395A19, the already rowed
// PartitionFilterRejectByKindOf::allow 26115D, and all-players mask 36CC7A.
// Its 395A35 constructor copies two 28-byte masks to +8/+24. Reconcile the
// former neutral constructor view with the existing named predicate, using
// the ZH PartitionManager.h reject-filter definition as the semantic guide.
// Derived ordinary/deleting dtors are the same 7/28B native folds as the
// other kind filters; preserve their real three-slot interface.
class Object;
class Rva000421C8 {
public:
 Rva000421C8() : m_next(0) {}
 virtual ~Rva000421C8() {}
 virtual bool allow(Object *) = 0;
 virtual int getPlayerMask() { return -1; }
 Rva000421C8 *m_next;
};
class BfmeFixedStorage0004543D {
 char m_bytes[28];
public:
 __declspec(nothrow) BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &);
};
class PartitionFilterRejectByKindOf : public Rva000421C8 {
public:
 PartitionFilterRejectByKindOf(const BfmeFixedStorage0004543D &,const BfmeFixedStorage0004543D &);
 __declspec(noinline) virtual ~PartitionFilterRejectByKindOf();
 virtual bool allow(Object *);
private:
 BfmeFixedStorage0004543D m_08,m_24;
};
PartitionFilterRejectByKindOf::PartitionFilterRejectByKindOf(const BfmeFixedStorage0004543D &a,const BfmeFixedStorage0004543D &b)
 : m_08(a),m_24(b) {}
inline PartitionFilterRejectByKindOf::~PartitionFilterRejectByKindOf() {}
