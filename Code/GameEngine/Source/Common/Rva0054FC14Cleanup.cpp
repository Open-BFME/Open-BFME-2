// cl: /O1 /G7 /arch:SSE /MD /Ireference/shims/bfme2_ascii /ICode/Libraries/Source/WWVegas/WWLib /D_STLP_USE_STATIC_LIB
// stlport
#include "ascii_string.h"
#include "mutex.h"
#include "ThreadClass.h"
#include <map>

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

// The nearby202B locked encoding operation is recovered from retail and its
// WorldBuilder twin01406430. No matching named ZH/BF1 source was found.
// STLport4.5.3 supplies the tree iteration; shared MutexClass and AsciiString
// providers independently verify all calls. Mutex+14, map+74, mapped-word
// node+1C and the two strings are target evidence; original names are open.
// The receiver below is a neutral ABI view, not a recovered original name.
struct ProgressValue0054FCA5 { int opaque[2]; int value; };
// ?rva0054FC14@Rva0054FC14@@QAEXXZ retail 0x0054FC14 70B.
// Clear lock at +0xB0 then stop plus virtual-destroy plus delete 10 thread slots at +0x80.
// Evidence: clear 0x0009990D, Stop 0x006105F0, ::delete (virtual destructor with flag 0, then delete 0x0002FD60), caller 0x0054FFC3.
class Rva0009990D
{
public:
	void set(void *object); // 0x000998EA
	void clear();
private:
	void *m_object; // +0x00
};

struct Rva0054FC14
{
	char _prefix[0x14];
	MutexClass mutex;
	char _middle[0x58];
	_STL::map<int,ProgressValue0054FCA5> values;
	ThreadClass *m_threads[10];
	char _gap[8];
	Rva0009990D m_lock;
	void rva0054FC14();
	AsciiString rva0054FCA5(int scale);
};

void Rva0054FC14::rva0054FC14()
{
	m_lock.clear();
	ThreadClass **thread = m_threads;
	int n = 10;
	do {
		ThreadClass *t = *thread;
		if (t != 0) {
			t->Stop();
			::delete *thread;
			*thread = 0;
		}
		++thread;
	} while (--n != 0);
}

// ?rva0054FCA5@Rva0054FC14@@QAE?AVAsciiString@@H@Z retail0054FCA5 202B.
AsciiString Rva0054FC14::rva0054FCA5(int scale) {
 MutexClass::LockClass lock(mutex);
 AsciiString result, temp;
 for (_STL::map<int,ProgressValue0054FCA5>::iterator it=values.begin();it!=values.end();++it) {
  int v=it->second.value;
  if(v<0 || v>scale) v=scale;
  temp.format("%2.2X",v*255/scale);
  result+=temp;
 }
 return result;
}
