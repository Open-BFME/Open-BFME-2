// cl: /O1 /DNDEBUG /MD
//
// ?rva004B3B42@Rva004B3B42@@QAEXXZ @0x004B3B42 70B.
// Slot 0x20, then copy the controlling player's 128-byte storage at +0x13C
// and OR the bitset at [this-8]+0x284 into it. Slot 1 receives the local.

class Player;

class Object
{
public:
	Player *getControllingPlayer() const;
};

struct BfmeFixedStorage128
{
	BfmeFixedStorage128(const BfmeFixedStorage128 &other);
	char m_bytes[0x80];
};

class Player
{
public:
	char m_pad[0x13C];
	BfmeFixedStorage128 m_storage;
};

namespace _STL
{
	template<size_t N>
	struct _Base_bitset
	{
		void _M_do_or(const _Base_bitset<N> &other);
	};
}

class Rva004B3B42
{
public:
	virtual void s0();
	virtual void s1(BfmeFixedStorage128 *storage);
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5();
	virtual void s6();
	virtual void s7();
	virtual void s8();
	void rva004B3B42();
};

void Rva004B3B42::rva004B3B42()
{
	s8();
	Player *player = (*(Object **)((char *)this - 8))->getControllingPlayer();
	BfmeFixedStorage128 local(player->m_storage);
	Object *obj = *(Object **)((char *)this - 8);
	((_STL::_Base_bitset<32> *)&local)->_M_do_or(
		*(_STL::_Base_bitset<32> *)((char *)obj + 0x284));
	s1(&local);
}
