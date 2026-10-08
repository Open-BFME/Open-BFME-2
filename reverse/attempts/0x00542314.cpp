// ?readData@Rva00542314@@QAE_NPAVDataChunkInput@@PAUDataChunkInfo@@@Z
// partial score=0.96 date=2026-10-08
// cl: /O1 /arch:SSE /Ob0
// ?rva00540B48@Rva00540B48@@QAE_NPAVDataChunkInput@@PAX@Z @0x00540B48 101B
// Banked attempt reverse/attempts/0x00540b48.cpp, re-verified exact against the current ledger
// (its callees have since been rowed or pinned); landed unchanged by the
// banked-attempt sweep. Identity and evidence: see reverse/re_attempts.log.
// ??0Rva0053FDE6@@QAE@XZ, retail 0x0053FDE6, 68 bytes.
// Constructor: int 2 at +0, six floats 0.0 at +4 +8 +0xC +0x10 +0x14 +0x18
// via xorps/movss, 1.0f at +0x1C, global float 0x00BC74F0 at +0x20.
// Same int-2-plus-zeros-plus-global shape as rowed Rva00540D67 (45B) and
// Rva00540E82 (27B) in Rva00540E82Init.cpp. Evidence: no calls; callers at
// 0x00540013 and 0x00540B85; unblocks 0x0054000B and 0x00540B48.
extern float g_Va00BBB8D8;
extern float g_Va00BC74F0;

class Rva0053FDE6
{
public:
	Rva0053FDE6();
	Rva0053FDE6(const Rva0053FDE6 &o);
 bool readData(class DataChunkInput*,void*);
	int m_00;
	float m_04;
	float m_08;
	float m_0c;
	float m_10;
	float m_14;
	float m_18;
	float m_1c;
	float m_20;
};

Rva0053FDE6::Rva0053FDE6() : m_00(2), m_04(0.0f), m_08(0.0f), m_0c(0.0f), m_10(0.0f), m_14(0.0f), m_18(0.0f), m_1c(g_Va00BBB8D8), m_20(g_Va00BC74F0)
{
}


class DataChunkInput { public: int readInt(); };
class Rva0054000B { char bytes[40]; };
struct Rva00540B48Vector {
 Rva0054000B *first,*last,*capacity;
 Rva0054000B *erase(Rva0054000B*,Rva0054000B*);
 void reserve(unsigned int);
};
class Rva00540B48 {
public:
 bool rva00540B48(DataChunkInput*,void*);
 void append(int,const Rva0053FDE6&);
 char prefix[16];
 Rva00540B48Vector values;
};
bool Rva00540B48::rva00540B48(DataChunkInput*file,void*info) {
 Rva00540B48Vector &v=values; v.erase(v.first,v.last);
 int count=file->readInt();
 values.reserve(count);
 for (int i=count;i>0;--i) {
  int key=file->readInt();
  Rva0053FDE6 value;
  value.readData(file,info);
  append(key,value);
 }
 return true;
}

// Native 542314 is the 20-byte element channel's sibling of 540B48.
// Its vector subobject starts at +10; the erase/reserve identities and
// 20-byte stride are independently rowed STLport facts. Only declarations
// are needed here: the implementation belongs to the existing vector TUs.
class Rva0054103E;
namespace _STL {
template<class T> class allocator;
template<class T,class Allocator> class vector {
public:
 T *first,*last,*capacity;
 T *erase(T*,T*);
 void reserve(unsigned int);
};
}
class Rva00540E82 {
public:
 Rva00540E82();
 int m_00;
 float m_04,m_08,m_0c;
};
struct DataChunkInfo;
class Rva00540CB2 {
public:
 bool rva00540CB2(DataChunkInput*,DataChunkInfo*);
 int m_00;
 float m_04,m_08,m_0c;
};
class Rva00542314 {
public:
 bool readData(DataChunkInput*,DataChunkInfo*);
 void append(int,const Rva00540E82&);
 char prefix[16];
 _STL::vector<Rva0054103E,_STL::allocator<Rva0054103E> > values;
};

// Ghidra [542314,542379)101B RET8. The 16-byte stack value is built by
// rowed 540E82 and read through rowed 540CB2 (tag + three floats).
// 5420AD consumes the key and the value address; its inspected body writes
// a 20-byte key/value element. These address-derived views assert no donor
// class identity or original names.
bool Rva00542314::readData(DataChunkInput *file,DataChunkInfo *info) {
 _STL::vector<Rva0054103E,_STL::allocator<Rva0054103E> > &v=values;
 v.erase(v.first,v.last);
 int count=file->readInt();
 values.reserve(count);
 for (int i=count;i>0;--i) {
  int key=file->readInt();
  Rva00540E82 value;
  reinterpret_cast<Rva00540CB2*>(&value)->rva00540CB2(file,info);
  append(key,value);
 }
 return true;
}
