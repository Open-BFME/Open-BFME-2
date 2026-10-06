// cl: /DNDEBUG /MD /EHsc
// ?rva002ABA9B@Player@@QAEXXZ @0x002ABA9B (11B): Player::rva002ABA9B clears int list at +0x700.
// Evidence: tail-jmp to rowed ?clear@?$_List_base@HV?$allocator@H@_STL@@@_STL@@QAEXXZ @0x0023DAA5; callers at 0x003C60A1 and 0x003C60B1 in FUN_007C606C pass Player* from PlayerList lookup at 0x002A7B91; add ecx 0x700 plus jmp is tail return m_list.clear at /O1.
namespace _STL {
	template <class _Tp> class allocator;
	template <class _Tp, class _Alloc> class _List_base {
	public:
		void clear();
	};
	typedef _List_base<int, allocator<int> > ListBaseInt;
}

class Player
{
	char m_pad[0x700];
	_STL::ListBaseInt m_list;
public:
	void rva002ABA9B();
};

// ?rva002ABA9B@Player@@QAEXXZ
void Player::rva002ABA9B()
{
	return m_list.clear();
}
