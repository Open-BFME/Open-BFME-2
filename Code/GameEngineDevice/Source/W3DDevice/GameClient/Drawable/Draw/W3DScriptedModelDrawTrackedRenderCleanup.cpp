// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP=
// Native C7699..C7720 is a 135B zero-argument thiscall cleanup of the
// W3DScriptedModelDraw vector at164 (32B records). Matched constructor
// C0DD8 and destructor C79C9 establish receiver and offset independently.
// BFME2 WB9473C0 supplies record-copy/manager slot3/release/clear order.
// Existing BFDC7 copy fixes 32B scalar/string layout; first word is proven
// a counted object here. Original method and record purpose remain unknown.
// The record string destructor and reference release are visible, giving
// the native EH state and free. Retained neutral prefix names describe ABI.
void __cdecl free(void*);
class RefCountClass {public:virtual void Delete_This();int refs;void Release_Ref(){if(--refs==0)Delete_This();}};
namespace _STL {template<class C>class char_traits;template<class T>class allocator;template<class C,class Tr=char_traits<C>,class A=allocator<C> >class basic_string {public:~basic_string(){if(start)free(start);}C*start,*finish,*end;};}
struct BfmeNarrowRecord000BFDC7 {RefCountClass*word0;_STL::basic_string<char>text;int word1,word2,word3,word4;BfmeNarrowRecord000BFDC7(const BfmeNarrowRecord000BFDC7&);};
class Rva000C24EA;class Rva000C24EAVector {public:Rva000C24EA*eraseRange(Rva000C24EA*,Rva000C24EA*);BfmeNarrowRecord000BFDC7*begin,*end,*cap;};
class RTS3DScene {public:virtual void s0();virtual void s1();virtual void s2();virtual void s3(RefCountClass*);};
class W3DDisplay {public:static RTS3DScene*m_3DScene;};
class Rva000C7699 {public:void rva000C7699();private:char pad[0x164];Rva000C24EAVector list;};
void Rva000C7699::rva000C7699(){for(BfmeNarrowRecord000BFDC7*i=list.begin;i!=list.end;++i){BfmeNarrowRecord000BFDC7 item(*i);RTS3DScene*manager=W3DDisplay::m_3DScene;manager->s3(item.word0);item.word0->Release_Ref();item.word0=0;}Rva000C24EAVector*v=&list;v->eraseRange((Rva000C24EA*)v->begin,(Rva000C24EA*)v->end);}
