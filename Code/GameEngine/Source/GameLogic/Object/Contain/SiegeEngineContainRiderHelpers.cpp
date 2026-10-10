// cl: /O1 /MD /DNDEBUG /I.
// stlport
// ?rva0047BDED@Rva0047BDED@@QAEX_N@Z @0x0047BDED 54B: drain the contained list, calling
// virtual slot 41 on each non-null node value with the flag, then removeAllContained.
#include <list>
class OpenContain {public: virtual void removeAllContained(bool);};
class Rva0047BDED;
struct Rva0047BDEDNode
{
	Rva0047BDEDNode *m_next;
	char m_pad04[4];
	void *m_value;
};

class Rva0047BDEDList
{
public:
	Rva0047BDEDNode *m_head;
};

class Rva0047BDED
{
public:
	virtual void rva0047BDEDV00();
	virtual void rva0047BDEDV01();
	virtual void rva0047BDEDV02();
	virtual void rva0047BDEDV03();
	virtual void rva0047BDEDV04();
	virtual void rva0047BDEDV05();
	virtual void rva0047BDEDV06();
	virtual void rva0047BDEDV07();
	virtual void rva0047BDEDV08();
	virtual void rva0047BDEDV09();
	virtual void rva0047BDEDV10();
	virtual void rva0047BDEDV11();
	virtual void rva0047BDEDV12();
	virtual void rva0047BDEDV13();
	virtual void rva0047BDEDV14();
	virtual void rva0047BDEDV15();
	virtual void rva0047BDEDV16();
	virtual void rva0047BDEDV17();
	virtual void rva0047BDEDV18();
	virtual void rva0047BDEDV19();
	virtual void rva0047BDEDV20();
	virtual void rva0047BDEDV21();
	virtual void rva0047BDEDV22();
	virtual void rva0047BDEDV23();
	virtual void rva0047BDEDV24();
	virtual void rva0047BDEDV25();
	virtual void rva0047BDEDV26();
	virtual void rva0047BDEDV27();
	virtual void rva0047BDEDV28();
	virtual void rva0047BDEDV29();
	virtual void rva0047BDEDV30();
	virtual void rva0047BDEDV31();
	virtual void rva0047BDEDV32();
	virtual void rva0047BDEDV33();
	virtual void rva0047BDEDV34();
	virtual void rva0047BDEDV35();
	virtual void rva0047BDEDV36();
	virtual void rva0047BDEDV37();
	virtual void rva0047BDEDV38();
	virtual void rva0047BDEDV39();
	virtual void rva0047BDEDV40();
	virtual void rva0047BDEDVirt41(void *value, bool flag);
	void rva0047BE23(int unused);
	void rva0047BDED(bool flag);

private:
	char m_pad00[0xFC - 4];
	_STL::list<void*> m_fc;
};

// Native47BDED..47BE23 and47BE23..47BE4C retain RET4: the latter ignores its
// word argument. WB11AB070 confirms the first drain and owned base cleanup.
// Target rider list is the interface receiver's +FC (full owner+11C).
// ZH OpenContain list iteration guides semantics; distinct slot names/owner
// remain address-derived. Iterator dereference at dispatch closes native
// loop shape/registers; a separately cached payload does not.
void Rva0047BDED::rva0047BDED(bool flag)
{
 for(;;) {
  _STL::list<void*>::iterator it=m_fc.begin();
  if(it._M_node==m_fc.end()._M_node) break;
  if(*it) rva0047BDEDVirt41(*it,flag);
 }
 reinterpret_cast<OpenContain*>(this)->OpenContain::removeAllContained(flag);
}
void Rva0047BDED::rva0047BE23(int unused)
{
 for(;;) {
  _STL::list<void*>::iterator it=m_fc.begin();
  if(it._M_node==m_fc.end()._M_node) break;
  if(*it) rva0047BDEDVirt41(*it,false);
 }
}
