// ??1Rva003EF36E@@UAE@XZ
// partial score=0.72 date=2026-10-09
// cl: /O1 /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include <hash_map>
#include "ascii_string.h"
typedef bool Bool;
#include "subsystem_interface.h"
class GameWindow;class WindowVideo;
class WindowVideoManager {public:struct hashConstGameWindowPtr {size_t operator()(const GameWindow*)const;};};
typedef _STL::pair<const GameWindow* const,WindowVideo*> S3WindowPair;
typedef _STL::hashtable<S3WindowPair,const GameWindow*,WindowVideoManager::hashConstGameWindowPtr,_STL::_Select1st<S3WindowPair>,_STL::equal_to<const GameWindow*>,_STL::allocator<S3WindowPair> > S3BucketWalk;
class Rva003EF14A {public:~Rva003EF14A();};
class Rva000411084 {public:void*next();};
class Rva000427195 {public:void rva003A2A41();};
void Rva00030830GameFree(void*);
struct S3RegionBucketStorage {~S3RegionBucketStorage(){if(begin)Rva00030830GameFree(begin);}void**begin;void**end;void**capacity;};
struct Rva003EF22B {void*unused;S3RegionBucketStorage buckets;unsigned count;~Rva003EF22B();};
Rva003EF22B::~Rva003EF22B(){((Rva000427195*)this)->rva003A2A41();}
class Rva003EF36E :public SubsystemInterface {
public:virtual ~Rva003EF36E();virtual void init(){}virtual void reset(){}virtual void update(){}
private:Rva003EF22B table;
};
Rva003EF36E::~Rva003EF36E()
{
 Rva003EF22B &owner=table;
 S3BucketWalk&walk=*(S3BucketWalk*)&owner;
 for(S3BucketWalk::iterator it=walk.begin();it!=walk.end();((Rva000411084*)&it)->next()) {
  Rva003EF14A*&manager=*(Rva003EF14A**)&it._M_cur->_M_val.second;
  delete manager;manager=0;
 }
 ((Rva000427195*)&owner)->rva003A2A41();
}
