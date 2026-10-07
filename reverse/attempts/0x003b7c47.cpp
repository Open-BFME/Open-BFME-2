// ?rva003B7C47@Rva003B573E@@QAEHABV?$StringBase@D@@@Z
// partial score=0.85 date=2026-10-07
// Native 3B7C47..3B7D90 329B. Reconstructs sorted-key lookup, free-list reuse, growth, linking and reference increment.
// Record layout and operation follow BFME1 StringRecord* leads; target-native fields/callees establish offsets.
// Existing rowed folded vector providers are used without adding alias pins. The sorted values carry indices as opaque four-byte payloads, never dereferenced as ModuleData pointers.
// Still 338B: register scheduling, spill placement and final return differ. This is evidence only.
// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>
#include "ascii_string.h"
class ModuleData;
struct BfmeStringRecord003B3F78 {
 unsigned int word0,word1;
 AsciiString text;
 unsigned char flag;
 unsigned short short0;
 unsigned int word2;
 BfmeStringRecord003B3F78(const BfmeStringRecord003B3F78&);
 BfmeStringRecord003B3F78() : word2(0) {}
};
namespace _STL {
 template<> void vector<const ModuleData *>::reserve(unsigned int);
 template<> vector<const ModuleData *>::iterator vector<const ModuleData *>::insert(vector<const ModuleData *>::iterator,const ModuleData *const&);
 template<> void vector<BfmeStringRecord003B3F78>::push_back(const BfmeStringRecord003B3F78&);
}
class Rva003B573E {
 _STL::vector<const ModuleData *> m_sorted;
 _STL::vector<BfmeStringRecord003B3F78> m_records;
 int m_freeHead;
 int m_tail;
public:
 int rva003B573E(const StringBase<char>&);
 int rva003B7C47(const StringBase<char>&);
};
int Rva003B573E::rva003B7C47(const StringBase<char>&key)
{
 unsigned int position=rva003B573E(key);
 int index;
 int offset;
 if(position < m_sorted.size() && ((const StringBase<char>&)m_records[(int)m_sorted[position]].text).compare(key)==0) {
  index=(int)m_sorted[position];
  offset=index*20;
  if(!m_records[index].flag) return -1;
 } else {
  unsigned int wanted=m_sorted.size()+1;
  if(wanted>m_sorted.capacity()) m_sorted.reserve(wanted+(wanted>>1)+8);
  if(m_freeHead==-1) {
   int freeIndex=m_records.size();
   m_records.push_back(BfmeStringRecord003B3F78());
   m_records.back().word0=-1;
   m_freeHead=freeIndex;
  }
  index=m_freeHead;
  offset=index*20;
  BfmeStringRecord003B3F78 *record=(BfmeStringRecord003B3F78*)((char*)&m_records[0]+offset);
  ((StringBase<char>&)record->text)=key;
  m_sorted.insert(m_sorted.begin()+position, reinterpret_cast<const ModuleData *const&>(index));
  m_freeHead=record->word0;
  if(m_tail!=-1) m_records[m_tail].word1=index;
  record->word1=-1;
  record->word0=m_tail;
  m_tail=index;
  record->short0=0;
 }
 BfmeStringRecord003B3F78 *record=(BfmeStringRecord003B3F78*)((char*)&m_records[0]+offset);
 ++record->short0;
 record->flag=0;
 return index;
}
