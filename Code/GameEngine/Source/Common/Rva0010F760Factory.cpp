// cl: /O1 /G7 /MD /EHsc
// Native10F155..10F18548B owns12-byte callback storage. Native
// vtableBCFAB0 has exactly2slots: owned deleting dtor10F7D2 and
// handle-slot1 forwarding8B5D124D. This independently proves the
// ctor owner Rva0010F7EE and its virtual method; header count4 zero
// is scheduled by an inline base ctor before handle copy8.
// The C++ vtable supplies both owned entries, with no literal address.
class OpaqueRefCounted {public:void Release_Ref();};
class Rva0036CA00Str {public:__declspec(nothrow) Rva0036CA00Str(const Rva0036CA00Str&);~Rva0036CA00Str(){if(item)((OpaqueRefCounted*)item)->Release_Ref();}void*item;};
void*__cdecl operator new(unsigned) throw();
struct Rva0010F155Header {volatile long count;__forceinline Rva0010F155Header():count(0){} virtual ~Rva0010F155Header(){}};
class Rva0010F7EE:public Rva0010F155Header {public:Rva0010F7EE(Rva0036CA00Str h);virtual ~Rva0010F7EE();virtual int rva005D124D();Rva0036CA00Str handle;};
Rva0010F7EE::Rva0010F7EE(Rva0036CA00Str h):handle(h){}
class AudioEventInfo;
class AudioEventInfoRef {public:__declspec(nothrow) AudioEventInfoRef(const AudioEventInfo*);~AudioEventInfoRef(){if(item)((OpaqueRefCounted*)item)->Release_Ref();}void*item;};
AudioEventInfoRef Rva0010F760(Rva0036CA00Str h){return AudioEventInfoRef((const AudioEventInfo*)new Rva0010F7EE(h));}

class Rva0010F155Inner {public:virtual void slot0();virtual int slot1();};
int Rva0010F7EE::rva005D124D(){return ((Rva0010F155Inner*)handle.item)->slot1();}
