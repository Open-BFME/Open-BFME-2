// cl: /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?rva00505AF1@AITacticsGenerator@@AAEXXZ, retail 0x00505AF1, 201 bytes.
// A private member of the AITacticsGenerator object (AITacticsGenerator.cpp), whose
// update pass 0x005069B4 calls it first.
// Evidence: 4 voidptr vectors at +0x10 +0x28 +0x40 +0x58 pruned via byte at +0x28 virtual slot0(0) plus rowed delete 0x0002FD60 and rowed erase 0x001FF51F; caller 0x005069B7.
#include <vector>

// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
}

class Rva00505AF1Elem
{
public:
	virtual void *rva(int);
	char m_pad[0x24];
	unsigned char m_28;
};

class AsciiString;
class Team;
class Xfer;
struct Rva00506909Gen;
struct Rva00506909Item;
struct Rva00506909Request;

class AITacticsGenerator
{
public:
	void Register(Team *unit);
	void UnRegister(Team *unit);
	AITacticsGenerator(void *owner);
	~AITacticsGenerator();
	void DoXfer(Xfer *xfer);
	void rva005069B4();
	bool activateTactic(Rva00506909Request *request, void *arg);
private:
	Rva00506909Item *rva00505D91(const AsciiString &name);
	Rva00506909Item *rva00505DC4(const AsciiString &name);
	Rva00506909Item *rva00505DF7(const AsciiString &name);
	Rva00506909Item *rva00505E2A(const AsciiString &name);
	void rva00505E5D();
	void rva00505F80();
	void rva00505FD0();
	void updateTactics();
	void rva00506020();
	void rva00505AF1();
	bool rva00506411(void *owner);
	bool rva00506178(Rva00506909Request *request, void *arg);
	bool rva00506265(Rva00506909Request *request, void *arg);
	bool rva0050633B(Rva00506909Request *request, void *arg);

	void *m_owner;					// +0x00
	_STL::vector<Rva00506909Gen *> m_04;
	_STL::vector<Rva00506909Item *> m_10;
	_STL::vector<Rva00506909Gen *> m_1C;
	_STL::vector<Rva00506909Item *> m_28;
	_STL::vector<Rva00506909Gen *> m_34;
	_STL::vector<Rva00506909Item *> m_40;
	_STL::vector<Rva00506909Gen *> m_4C;
	_STL::vector<Rva00506909Item *> m_58;
};

void AITacticsGenerator::rva00505AF1()
{
	for (_STL::vector<Rva00506909Item *>::iterator it = m_10.begin(); it != m_10.end(); ) {
		Rva00505AF1Elem *element = (Rva00505AF1Elem *)*it;
		if (element->m_28 != 0) {
			void *payload = element->rva(0);
			::operator delete(payload);
			it = (_STL::vector<Rva00506909Item *>::iterator)(((_STL::vector<void *> *)&m_10)->erase((void **)it));
		} else {
			++it;
		}
	}
	for (_STL::vector<Rva00506909Item *>::iterator it = m_28.begin(); it != m_28.end(); ) {
		Rva00505AF1Elem *element = (Rva00505AF1Elem *)*it;
		if (element->m_28 != 0) {
			void *payload = element->rva(0);
			::operator delete(payload);
			it = (_STL::vector<Rva00506909Item *>::iterator)(((_STL::vector<void *> *)&m_28)->erase((void **)it));
		} else {
			++it;
		}
	}
	for (_STL::vector<Rva00506909Item *>::iterator it = m_40.begin(); it != m_40.end(); ) {
		Rva00505AF1Elem *element = (Rva00505AF1Elem *)*it;
		if (element->m_28 != 0) {
			void *payload = element->rva(0);
			::operator delete(payload);
			it = (_STL::vector<Rva00506909Item *>::iterator)(((_STL::vector<void *> *)&m_40)->erase((void **)it));
		} else {
			++it;
		}
	}
	for (_STL::vector<Rva00506909Item *>::iterator it = m_58.begin(); it != m_58.end(); ) {
		Rva00505AF1Elem *element = (Rva00505AF1Elem *)*it;
		if (element->m_28 != 0) {
			void *payload = element->rva(0);
			::operator delete(payload);
			it = (_STL::vector<Rva00506909Item *>::iterator)(((_STL::vector<void *> *)&m_58)->erase((void **)it));
		} else {
			++it;
		}
	}
}
