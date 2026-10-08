// cl: /O1 /DNDEBUG /MD
// stlport
#include <list>
#include "../../../../Include/GameLogic/ContainmentListView.h"
namespace _STL {template<> _List_base<Rva0036ADF9Element,allocator<Rva0036ADF9Element> >::~_List_base();}


// ?rva00466398@Rva00466398@@QAE?AVRva0036AE51ListView@@XZ retail 0x00466398 26B
// Returns the two-pointer list-view descriptor by value. Its caller at
// 0x00466A50 materializes the returned view through the existing
// Rva0036AE51ListView::rva0036AE51 list-return helper before walking it; the
// caller at 0x0047DF44 reads its second pointer as a list<int>. Target bytes
// show the hidden result pointer in [esp+4], first field this+4-or-null via
// neg/sbb/and, second field this+0x10, and ret 4.
class Rva00466398
{
public:
	Rva0036AE51ListView rva00466398();
private:
	char m_pad[20];
};
Rva0036AE51ListView Rva00466398::rva00466398()
{
	Rva0036AE51ListView out;
	out.a = this ? (void *)((char *)this + 4) : (void *)0;
	out.b = (ContainmentList *)((char *)this + 16);
	return out;
}
