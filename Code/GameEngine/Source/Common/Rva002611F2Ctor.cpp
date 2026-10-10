// cl: /O1 /DNDEBUG /MD /EHsc
// Native 2611F2..261246 RET4, 84B; WB E5CA50 names the reject-buildings
// constructor and its controlling-player check. Native BF8FF0 has exactly
// three slots: deleting dtor395A19, predicate261B7E, inherited mask36CC7A.
// The base link at4, object at8 and boolean atC are target accesses.
// The base destructor resets BC26E0; the native EH cleanup tail-calls that
// seven-byte body49C38A. Its real virtual layout replaces the old dummy
// slot and non-polymorphic base. Keep the derived reset outlined, as the
// native deleting destructor calls it. Original base class name is unproven;
// the established Rva000421C8 provider is retained. BFME1 575ba2b supplied
// a semantic cross-check; its offsets and predicate differ from this target.
class Player
{
public:
	char m_pad[0x5C];
	int m_field5C;
};
class Object
{
public:
	Player *getControllingPlayer() const;
};
class Rva000421C8 {
public:
 Rva000421C8():m_next(0){}
 virtual ~Rva000421C8(){}
 virtual bool allow(Object *)=0;
 virtual int getPlayerMask();
 Rva000421C8 *m_next;
};
class PartitionFilterRejectBuildings:public Rva000421C8 {
public:
 PartitionFilterRejectBuildings(Object *obj);
 __declspec(noinline) virtual ~PartitionFilterRejectBuildings();
 virtual bool rva00261B7E(Object *);
private:
 Object *m_obj;
 bool m_flag;
};
PartitionFilterRejectBuildings::PartitionFilterRejectBuildings(Object *obj) {
 m_obj=obj;m_flag=false;
 if(obj->getControllingPlayer()!=0) {
  if(m_obj->getControllingPlayer()->m_field5C==1)m_flag=true;
 }
}

inline PartitionFilterRejectBuildings::~PartitionFilterRejectBuildings(){}
