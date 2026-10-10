// ?rva00601A8D@Rva00601BBCHelper@@QAEXXZ
// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// The 0x34-byte helper BFME 2 added to INI at +0x838 (INI_ctor.cpp):
//   ??0Rva00601BBCHelper@@QAE@XZ   0x00601BBC  constructor
//   ??1Rva00601BBCHelper@@UAE@XZ   0x00601BF3  destructor
//   ??_GRva00601BBCHelper@@UAEPAXI@Z 0x00602056 scalar deleting destructor
// Layout from these bodies: a one-slot vtable (0x00C7A6B0, slot 0 the
// deleting destructor), a 0x18-byte member at +4 built by the rowed
// Rva00524415 constructor (two vectors) and torn down by 0x00601AE9, and two
// four-byte-element vectors at +0x1C and +0x28 whose storage is freed
// directly. The constructor runs the once-only table init 0x006016C9; the
// destructor first clears everything through 0x00601A8D. The class's identity
// (a token/lexer table, by its ctype-table init) is not established, so the
// names stay address-derived; the callees are pinned.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include <vector>

void Rva006016C9Init() throw();

// ?rva00601C53@@YAXPAXH000@Z @0x00601C53 1027B worker (unrowed): __cdecl 5-param
// (outer, flag, m_1C, m_28, &m_04); address-derived ABI from the native call; semantic identity remains unknown.
void __cdecl rva00601C53(void *outer, int flag, void *vec1, void *vec2, void *member);

struct Rva00524415
{
	Rva00524415();
	~Rva00524415();
	char m_body[0x18];
};

class Rva00601BBCHelper
{
public:
	Rva00601BBCHelper();
	Rva00601BBCHelper(void *outer);
	virtual ~Rva00601BBCHelper();

	void rva00601A8D();
	bool rva00602072(void *outer);

private:
	Rva00524415 m_04;            // +0x04
	_STL::vector<int> m_1C;      // +0x1C
	_STL::vector<int> m_28;      // +0x28
};

Rva00601BBCHelper::Rva00601BBCHelper()
{
	Rva006016C9Init();
}

Rva00601BBCHelper::~Rva00601BBCHelper()
{
	rva00601A8D();
}

// ?rva00602072@Rva00601BBCHelper@@QAE_NPAX@Z @0x00602072 31B wrapper: forwards
// outer/1/m_1C/m_28/&m_04 into worker 0x00601C53, returns true. Retail:
// 8d4104 push &m_04, 8d4128 push m_28, 83c11c push m_1C, 6a01 push 1,
// ff742414 push outer, e8 -> 0x00601C53, 83c414, b001, c20400.
bool Rva00601BBCHelper::rva00602072(void *outer)
{
	rva00601C53(outer, 1, &m_1C, &m_28, &m_04);
	return true;
}

// ??0Rva00601BBCHelper@@QAE@PAX@Z @0x00602091 95B: same member init
// as the void ctor (vtable + m_04 + two vectors + once-only init) then tail
// forwards the incoming outer pointer through the rowed 0x00602072 wrapper.
// __thiscall 1-arg ret4; wrapper result discarded. EH unwinds members if the
// worker throws (init itself is throw()).
Rva00601BBCHelper::Rva00601BBCHelper(void *outer)
{
	Rva006016C9Init();
	rva00602072(outer);
}

class Rva00601B30 {public:void clear();char storage[0x18];};
void Rva00601BBCHelper::rva00601A8D(){
 ((Rva00601B30*)&m_04)->clear();
 _STL::vector<int>& blocks=m_28;
 for(unsigned int i=0;i<blocks.size();++i){
  _ReadWriteBarrier();
		if(blocks[i]){
   delete[] (char*)blocks[i];
   blocks[i]=0;
  }
 }
 _STL::vector<void*>& pointers=(_STL::vector<void*>&)blocks;
 pointers.erase(pointers.begin(),pointers.end());
 _STL::vector<void*>& keys=(_STL::vector<void*>&)m_1C;
 keys.erase(keys.begin(),keys.end());
}
