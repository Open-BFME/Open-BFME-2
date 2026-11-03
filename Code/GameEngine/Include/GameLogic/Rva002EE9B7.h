// Target facts: Rva002EE9B7 has no virtual functions, vptr or vftable. Constructor RVA 0x000D3A71 calls 0x002F0BF4 at 0x000D3A80; destructor 0x002F0B52 calls clear 0x002EE9B7 at 0x002F0B67 and frees the header at 0x002F0B77. Neither stores a vptr; VA 0x00B78E00 loaded at 0x002F0B52 is the EH handler, not an object table.
// Target facts: initializer 0x002F0BF4 reads the header pointer at +0 and zeroes the four-byte count at +4 (0x002F0C04). Clear 0x002EE9B7 tests and zeroes that count and restores the header's links at +4/+8/+0x0C. HordeContain constructs this member at +0x170 (0x0046F5D8..0x0046F5DE), constructs its next member at +0x17C (0x0046F5E3..0x0046F5ED), and destroys it through 0x002F0B52 at 0x0046FA29. EmotionTrackerUpdate constructs it at +0xA4 (0x004B220F..0x004B221F) before its scalar at +0xB0 (0x004B2224): extent 0x0C; the trailing word's meaning is unproved.
// Target facts: ledger methods 0x0046A967 and 0x0046EDEF erase an iterator range and a referenced int key respectively. The former calls clear at 0x0046A980; the latter calls the range erase at 0x0046EE2B. These and both lifetime methods remain out of line. The constructor is ICF-shared with several STLport instantiations; its bytes do not establish a payload type or an application name.
// Target facts: Team's destructor loads this header at +0x130 (0x003A358A), follows its +8 link (0x003A3590), passes the four-byte key at node+0x10 (0x003A3594), and tests this count at +0x134 (0x003A359E). Its rowed source calls these inlined operations front and empty; the nested node view describes only those accessed bytes.

#pragma once
#ifndef BFME2_RVA002EE9B7_H
#define BFME2_RVA002EE9B7_H

struct _Rva002EADB4Node;

namespace _STL {
template <class First, class Second> struct pair;
template <class Value> struct _Nonconst_traits;
template <class Value, class Traits> struct _Rb_tree_iterator;
}

class Rva002EE9B7
{
public:
    Rva002EE9B7();
    ~Rva002EE9B7();
    void rva002EE9B7();
    void rva0046A967(
        _STL::_Rb_tree_iterator<_STL::pair<const int, void *>, _STL::_Nonconst_traits<_STL::pair<const int, void *> > > first,
        _STL::_Rb_tree_iterator<_STL::pair<const int, void *>, _STL::_Nonconst_traits<_STL::pair<const int, void *> > > last);
    unsigned int rva0046EDEF(const int &key);

    bool empty() const { return field04 == 0; }
    const int &front() const
    {
        return reinterpret_cast<const Node *>(reinterpret_cast<const Node *>(field00)->field08)->field10;
    }

    _Rva002EADB4Node *field00;
    unsigned int field04;
    unsigned int field08;

private:
    struct Node
    {
        unsigned char pad00[8];
        const Node *field08;
        unsigned char pad0C[4];
        int field10;
    };
};

typedef char Rva002EE9B7RetailSize[(sizeof(Rva002EE9B7) == 0x0C) ? 1 : -1];

#endif
