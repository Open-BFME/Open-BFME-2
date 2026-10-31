// Small unrowed .text bodies from the 0x00684BB0..0x0073EE20 (/O2) region.
// Retail bytes establish every shape; no caller is recovered and the owning
// classes are unknown, so each keeps an address-derived name and a view of
// only the fields it touches.

// ?rva006CBDD0@Rva006CBDD0@@QBEIXZ @0x006CBDD0 9B: low 16 bits of the +0x5C word.
class Rva006CBDD0
{
public:
	unsigned rva006CBDD0() const;
private:
	char m_pad[0x5c];
	unsigned m_5c;
};
unsigned Rva006CBDD0::rva006CBDD0() const
{
	return m_5c & 0xffff;
}

// ?rva006F6960@Rva006F6960@@QBEIXZ @0x006F6960 9B: bit 0 of the byte at +0x5E
// (same shape as the rowed Rva006FBCF0ByteBit::bit 0x006FBCF0).
class Rva006F6960
{
public:
	unsigned rva006F6960() const;
private:
	char m_pad[0x5e];
	unsigned char m_bits;
};
unsigned Rva006F6960::rva006F6960() const
{
	return m_bits & 1;
}

// ?Rva00698A30@@YAHPBURva00698A30Record@@@Z @0x00698A30 8B: cdecl read of the
// +0x58 word of the argument.
struct Rva00698A30Record
{
	char m_pad[0x58];
	int m_58;
};
int Rva00698A30(const Rva00698A30Record *record)
{
	return record->m_58;
}

// ?rva006D6350@Rva006D6350@@QAEAAVEAStringC@@ABV2@@Z @0x006D6350 8B: assign
// the +0x08 EAStringC through the rowed EAStringC::operator= 0x006D3030.
class EAStringC
{
	void *m_data;
public:
	EAStringC &operator=(const EAStringC &other);
};
class Rva006D6350
{
public:
	EAStringC &rva006D6350(const EAStringC &value);
private:
	char m_pad[0x08];
	EAStringC m_08;
};
EAStringC &Rva006D6350::rva006D6350(const EAStringC &value)
{
	return m_08 = value;
}

// ?rva006200A0@Rva006200A0@@QBEPAXXZ @0x006200A0 6B: address 12 bytes into the
// record held at +0.
struct Rva006200A0Record
{
	char m_00[0x0c];
	char m_0c[4];
};
class Rva006200A0
{
public:
	void *rva006200A0() const;
private:
	Rva006200A0Record *m_00;
};
void *Rva006200A0::rva006200A0() const
{
	return m_00->m_0c;
}

// ?rva006C1840@Rva006C1840@@QAEXXZ @0x006C1840 14B: clear +0, the +4 byte, +8 and +0x10.
class Rva006C1840
{
public:
	void rva006C1840();
private:
	int m_00;
	unsigned char m_04;
	int m_08;
	int m_0c;
	int m_10;
};
void Rva006C1840::rva006C1840()
{
	m_00 = 0;
	m_04 = 0;
	m_08 = 0;
	m_10 = 0;
}

// ??ERva006CD4B0@@QAEAAV0@XZ @0x006CD4B0 6B and ??FRva006CD4B0@@QAEAAV0@XZ
// @0x006CD5E0 6B: pre-increment / pre-decrement of a pointer over 8-byte
// elements, returning this.
struct Rva006CD4B0Element
{
	int m_words[2];
};
class Rva006CD4B0
{
public:
	Rva006CD4B0 &operator++();
	Rva006CD4B0 &operator--();
private:
	Rva006CD4B0Element *m_cur;
};
Rva006CD4B0 &Rva006CD4B0::operator++()
{
	++m_cur;
	return *this;
}
Rva006CD4B0 &Rva006CD4B0::operator--()
{
	--m_cur;
	return *this;
}

// ?popHead@Rva006CFE30@@QAE?AURva006CFE30Iterator@@H@Z @0x006CFE30 16B:
// unlink the head node (next at +4) and return it by value; the word
// argument is unused (same shape as the rowed 0x002C1F6F).
struct Rva006CFE30Node
{
	int m_00;
	Rva006CFE30Node *m_next;
};
struct Rva006CFE30Iterator
{
	Rva006CFE30Iterator(Rva006CFE30Node *node) : m_node(node) {}
	Rva006CFE30Node *m_node;
};
class Rva006CFE30
{
public:
	Rva006CFE30Iterator popHead(int unused);
private:
	Rva006CFE30Node *m_head;
};
Rva006CFE30Iterator Rva006CFE30::popHead(int)
{
	Rva006CFE30Node *node = m_head;
	m_head = node->m_next;
	return Rva006CFE30Iterator(node);
}

// ?rva006E0160@Rva006E0160@@QBEHH@Z @0x006E0160 18B: the signed low 24 bits of
// the +0x1C word masked by the argument.
class Rva006E0160
{
public:
	int rva006E0160(int mask) const;
private:
	char m_pad[0x1c];
	int m_low : 24;
};
int Rva006E0160::rva006E0160(int mask) const
{
	return m_low & mask;
}

// ?rva0073B640@Rva0073B640@@QBEHHH@Z @0x0073B640 19B: entry [row][column] of a
// table of four 16-bit entries per row starting at +6.
class Rva0073B640
{
public:
	int rva0073B640(int row, int column) const;
private:
	char m_pad[6];
	unsigned short m_table[1][4];
};
int Rva0073B640::rva0073B640(int row, int column) const
{
	return m_table[row][column];
}

// ?unregisterObject@Rva007584F0@@QAEXXZ @0x007584F0 12B and
// ?rva00625870@Rva00625870@@QAEXXZ @0x00625870 12B: hand the +4 word to a
// rowed member of the object held at +0 (CollisionManagerImpl::UnRegisterObject
// 0x007592E0 / PartitionManagerImpl::bfmeDropYQ 0x006278A0).
class Rva009A36F0Param;
class CollisionManagerImpl
{
public:
	void UnRegisterObject(Rva009A36F0Param *param);
};
class Rva007584F0
{
public:
	void unregisterObject();
private:
	CollisionManagerImpl *m_00;
	Rva009A36F0Param *m_04;
};
void Rva007584F0::unregisterObject()
{
	m_00->UnRegisterObject(m_04);
}
class BfmeThingYQ;
class PartitionManagerImpl
{
public:
	void bfmeDropYQ(BfmeThingYQ *thing);
};
class Rva00625870
{
public:
	void rva00625870();
private:
	PartitionManagerImpl *m_00;
	BfmeThingYQ *m_04;
};
void Rva00625870::rva00625870()
{
	m_00->bfmeDropYQ(m_04);
}

// ?rva006FBB70@Rva006FBB70@@QAE_NABVEAStringC@@@Z @0x006FBB70 22B: whether the
// rowed lookup 0x0070B380 on the +0x08 member finds the key.
class Rva0070B380
{
public:
	void *lookup(const EAStringC &key);
};
class Rva006FBB70
{
public:
	bool rva006FBB70(const EAStringC &key);
private:
	char m_pad[0x08];
	Rva0070B380 m_08;
};
bool Rva006FBB70::rva006FBB70(const EAStringC &key)
{
	return m_08.lookup(key) != 0;
}

// ?rva00615230@ChunkLoadClass@@QAEKPAX@Z @0x00615230 15B: a four-byte read
// through the rowed ChunkLoadClass::Read(void *, unsigned long) 0x006151A0.
class ChunkLoadClass
{
public:
	unsigned long Read(void *buffer, unsigned long nbytes);
	unsigned long rva00615230(void *buffer);
};
unsigned long ChunkLoadClass::rva00615230(void *buffer)
{
	return Read(buffer, 4);
}

// Pointer adjustments of the +0 pointer: ?rva0060F120@Rva0060F120@@QBEPAXXZ
// @0x0060F120 6B (8 bytes back), ?rva00620260@Rva00620260@@QBEPAXXZ
// @0x00620260 6B (4 bytes in) and ?rva0060393E@Rva0060393E@@QBEPAXXZ
// @0x0060393E 6B (12 bytes in).
class Rva0060F120
{
public:
	void *rva0060F120() const;
private:
	char *m_00;
};
void *Rva0060F120::rva0060F120() const
{
	return m_00 - 8;
}
class Rva00620260
{
public:
	void *rva00620260() const;
private:
	char *m_00;
};
void *Rva00620260::rva00620260() const
{
	return m_00 + 4;
}
class Rva0060393E
{
public:
	void *rva0060393E() const;
private:
	char *m_00;
};
void *Rva0060393E::rva0060393E() const
{
	return m_00 + 0xc;
}

// ?rva00614D80@Rva00614D80@@QBE_NXZ @0x00614D80 3B: the flag byte at +0.
class Rva00614D80
{
public:
	bool rva00614D80() const;
private:
	bool m_00;
};
bool Rva00614D80::rva00614D80() const
{
	return m_00;
}

// ?rva00620270@Rva00620270@@QBEPAXXZ @0x00620270 6B: the +0 pointer moved 16
// bytes in (a node's +0x10 field) - the shape of an STLport _Rb_tree_iterator
// operator* / operator-> (value field at node +0x10), between this file's
// 0x00620260 adjustment and the map<int,int> erase at 0x00620280; which
// iterator it is is unproven, so the view keeps an address-derived name.
class Rva00620270
{
public:
	void *rva00620270() const;
private:
	char *m_00;
};
void *Rva00620270::rva00620270() const
{
	return m_00 + 0x10;
}

// ??0Rva0065E890@@QAE@XZ @0x0065E890 13B: default ctor zeroing two words and a byte.
class Rva0065E890
{
public:
	Rva0065E890();
private:
	int m_00;
	int m_04;
	bool m_08;
};
Rva0065E890::Rva0065E890() : m_00(0), m_04(0), m_08(false)
{
}

// ?rva0065E8A0@Rva0065E8A0@@QBE_JXZ @0x0065E8A0 6B: the 64-bit value at +0,
// returned in EDX:EAX, just after the 0x0065E890 ctor above.
class Rva0065E8A0
{
public:
	__int64 rva0065E8A0() const;
private:
	__int64 m_00;
};
__int64 Rva0065E8A0::rva0065E8A0() const
{
	return m_00;
}

// ?rva006C5EB0@Rva006C5EB0@@QBENXZ @0x006C5EB0 4B: the double at +0x20.
class Rva006C5EB0
{
public:
	double rva006C5EB0() const;
private:
	char m_pad[0x20];
	double m_20;
};
double Rva006C5EB0::rva006C5EB0() const
{
	return m_20;
}

// ?rva006CFEF0@Rva006CFEF0@@QBEHABV1@@Z @0x006CFEF0 14B: word-pointer distance
// from another iterator.
class Rva006CFEF0
{
public:
	int rva006CFEF0(const Rva006CFEF0 &other) const;
	// ??FRva006CFEF0@@QAEAAV0@XZ @0x006CFF00 6B: pre-decrement by one word.
	Rva006CFEF0 &operator--();
private:
	int *m_cur;
};
int Rva006CFEF0::rva006CFEF0(const Rva006CFEF0 &other) const
{
	return m_cur - other.m_cur;
}
Rva006CFEF0 &Rva006CFEF0::operator--()
{
	--m_cur;
	return *this;
}

// ?rva006FE960@Rva006FE960@@QAEXH@Z @0x006FE960 5B: rowed
// AptBasePtrStack::rva006E3AA0 0x006E3AA0 on the stack at +0.
class AptBasePtrStack
{
public:
	void rva006E3AA0(int value);
};
class Rva006FE960
{
public:
	void rva006FE960(int value);
private:
	AptBasePtrStack m_stack;
};
void Rva006FE960::rva006FE960(int value)
{
	m_stack.rva006E3AA0(value);
}

// ?rva006BF9F0@Rva006BF9F0@@QAEXPAURva0087FDC0Element@@IABU2@@Z @0x006BF9F0
// 5B: fill-insert into the vector at +0 through the rowed _M_fill_insert 0x006BF800.
namespace _STL
{
	template <class T> class allocator;
	template <class T, class A = allocator<T> >
	class vector
	{
	public:
		void _M_fill_insert(T *position, unsigned int count, const T &value);
	};
}
struct Rva0087FDC0Element;
class Rva006BF9F0
{
public:
	void rva006BF9F0(Rva0087FDC0Element *position, unsigned int count, const Rva0087FDC0Element &value);
private:
	_STL::vector<Rva0087FDC0Element> m_vector;
};
void Rva006BF9F0::rva006BF9F0(Rva0087FDC0Element *position, unsigned int count, const Rva0087FDC0Element &value)
{
	m_vector._M_fill_insert(position, count, value);
}

// ?Rva006CE3C0@@YAPAVAptValueNameEntry@@PAV1@HH@Z @0x006CE3C0 5B and
// ?Rva006CE620@@YAPAVRva004A9DF3Element@@PAV1@HH@Z @0x006CE620 5B: cdecl
// forwards to the rowed array resizers 0x006CDBF0 / 0x006CE3D0.
class AptValueNameEntry;
class Rva004A9DF3Element;
AptValueNameEntry *resizeArray(AptValueNameEntry *items, int oldCount, int newCount);
Rva004A9DF3Element *Rva006CE3D0Resize(Rva004A9DF3Element *items, int oldCount, int newCount);
AptValueNameEntry *Rva006CE3C0(AptValueNameEntry *items, int oldCount, int newCount)
{
	return resizeArray(items, oldCount, newCount);
}
Rva004A9DF3Element *Rva006CE620(Rva004A9DF3Element *items, int oldCount, int newCount)
{
	return Rva006CE3D0Resize(items, oldCount, newCount);
}
