// cl: /Ireference/shims/bfme2_ascii /Ob2 /DNDEBUG /MD /EHsc
// ?rva00213925@Rva000427195@@QAE?AUInsertRet00212A5A@@PBX@Z retail 0x00213925 36 bytes.
// Hashtable insert with grow: loads count at +0x10 inc calls pinned grow
// rva00212858 at 0x00212858 then tail-returns rowed insert rva00212A5A at
// 0x00212A5A with the same hidden return and key. Class proven by +0x10
// count and both callee owners. Callers at 0x00213E05 0x002140B8 0x00214133 0x002141AE.
// Evidence: callees 0x00212858 pinned 0x00212A5A rowed ret 8 struct-return.
// Precedent: Code/GameEngine/Source/GameClient/Rva001F93A3Insert.cpp.
#include "ascii_string.h"

#include "../../Include/GameClient/InsertRet00212A5A.h"

#include "../../Include/GameLogic/Rva000427195.h"

InsertRet00212A5A Rva000427195::rva00213925(const void *key)
{
	rva00212858(m_numElements + 1);
	return rva00212A5A(key);
}

// Retail 0x00213DFD (20B, RET8): the hash container member over this table
// (at +0): the hidden result pointer and the key go straight to the
// insert-with-grow above, its only callee. Owner unresolved, address-named.
class Rva00213DFD
{
public:
	InsertRet00212A5A insert(const void *key);
private:
	Rva000427195 m_table;
};

InsertRet00212A5A Rva00213DFD::insert(const void *key)
{
	return m_table.rva00213925(key);
}

// LivingWorld icon factories, native 0x00214060 / 0x002140DB / 0x00214156.
// Adjacent 0x14-byte tables are observed at +0x26C, +0x280 and +0x294.
// Their registered INI parsers and existing constructors prove each record size.
// Keep the name/pointer pair temporary: its full-expression lifetime lets the
// compiler reuse the allocation slot. InsertRet has native alignment and size 12.

template<class T> struct LivingWorldIconPair
{
    AsciiString first;
    T *second;
    LivingWorldIconPair(const AsciiString &name, T *icon) : first(name), second(icon) {}
};
