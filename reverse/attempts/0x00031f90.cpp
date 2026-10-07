// ?rva00031F90@GeneralAllocator@Allocator@EA@@QAEIPAX@Z
// partial score=0.4550898204 date=2026-10-07
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void*);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void*);
namespace EA {namespace Allocator {
struct Lock { char pad[0x18]; volatile int count; };
class GeneralAllocator {
public: unsigned int rva00031F90(void*); unsigned int rva00031D00(void*);
private: char pad0[0x440];void *top;char pad444[0x4e4-0x444];Lock *lock;
};
unsigned int GeneralAllocator::rva00031F90(void *block) {
 Lock *held=lock;
 if(held) {EnterCriticalSection(held);++held->count;}
 unsigned int result=rva00031D00(block);
 unsigned int *chunk=(unsigned int*)block;
 unsigned int header=chunk[1];
 if(!(header&2)) {
  result+=((unsigned char)~(*(unsigned char*)((char*)block+(header&0x7ffffff8)+4)))&1;
  unsigned int header2=chunk[1];
  unsigned int *next=(unsigned int*)((char*)block+(header2&0x7ffffff8));
  if(!(header2&1)) {
   unsigned int *prev=(unsigned int*)((char*)block-chunk[0]);
   result+=(unsigned int*)((char*)prev+(prev[1]&0x7ffffff8))!=chunk;
  }
  if(next==top) {
   result+=((unsigned char)~(*(unsigned char*)(next+1)))&1;
   result+=(next[1]&0x7ffffff8)<0x10;
  }
 }
 if(held) {--held->count;LeaveCriticalSection(held);}
 return result;
}
}}
