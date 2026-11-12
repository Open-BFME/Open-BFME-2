// Rva002A8AB1Record: canonical declarations for the members 25 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA002A8AB1RECORD_H
#define CANONICAL_RVA002A8AB1RECORD_H

class AsciiString;
class Object;
class TeamPrototype;

struct Rva002A8AB1Record
{
	void rva002C6A3D(Object *object);
	void rva002C6A4E(Object *obj);
	void *rva002C6ACB();
	void rva002C717E(const AsciiString &key, int value);
	int rva002C7196(const AsciiString &key);
	void rva004EC07D(TeamPrototype *proto);
	void *rva004EC088(int kind, void *list, const void *name);
};

#endif // CANONICAL_RVA002A8AB1RECORD_H
