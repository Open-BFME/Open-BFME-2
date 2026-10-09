// ?rva0052BFE1@Rva0052BFE1@@QAEPAURva005657FEElement@@ABV?$StringBase@D@@PBURva005657FEHolder@@@Z
// cl: /O1 /G7 /arch:SSE /MD
// Native85B52BFE1..52C036; campaign-manager caller3B8CE0 tail reaches
// this entry; target calls typed103B search5657FE per opaque184B entry.
// Target stride/header fields established; application entry identity unknown.
// The matched103B provider supplies current StringBase/holder/pointer-result
// ABI, refuting the old bool/integer guess. Volatile entry-read view reproduces
// the explicit native reload separately from end-minus-begin; it does not assert
// original field qualifiers. Named begin/entry scopes select EAX plus LEA and
// keep the unsigned counter/local and EBX byte-offset induction exactly native.
// BFME1/reference name search found no applicable clean donor for this entry;
// known campaign-manager caller and the matched stride-search sibling supplied
// the semantic guide, with native accesses establishing this184-byte layout.
template<class T> class StringBase;
struct Rva005657FEElement;
struct Rva005657FEHolder;
class Rva005657FEOwner {
public: Rva005657FEElement *rva005657FE(const StringBase<char>&,const Rva005657FEHolder*) const;
};
struct CampaignEntry184 {unsigned char opaque[184];};
struct CampaignRange184 {CampaignEntry184 *begin,*end;};
class Rva0052BFE1 {
public: Rva005657FEElement *rva0052BFE1(const StringBase<char>&,const Rva005657FEHolder*);
private: unsigned char prefix[12];CampaignEntry184 *m_begin,*m_end;
};
Rva005657FEElement *Rva0052BFE1::rva0052BFE1(const StringBase<char>&key,const Rva005657FEHolder*holder) {
 for(unsigned i=0;i<(unsigned)(m_end-m_begin);++i) {
  CampaignEntry184 *begin=((const volatile CampaignRange184 *)&m_begin)->begin;
  Rva005657FEOwner *entry=(Rva005657FEOwner *)(begin+i);
  Rva005657FEElement *result=entry->rva005657FE(key,holder);
  if(result) return result;
 }
 return 0;
}
