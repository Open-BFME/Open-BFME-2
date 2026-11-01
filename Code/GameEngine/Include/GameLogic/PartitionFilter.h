/* Target facts (game.dat 1.06; function addresses are RVAs, tables are VAs):
 * Rva000421C8 ctor 0x000421C8 clears dword +4 and installs 0x00BC26E0 at +0.
 * Its copy ctor 0x004CCDD6 installs that table and copies only dword +4.
 * Table 0x00BC26E0 has three slots: deleting dtor 0x000421D5, __purecall
 * 0x0003B810, and getPlayerMask 0x0036CC7A (returns -1); non-code follows.
 * allows 0x00625720 calls slot 1 with Object* and follows +4; link 0x00625790
 * appends to the +4 chain. The rowed And body names this link m_next;
 * the ledger/pin spellings establish the methods, without renaming the class.
 * Rva0026119DFilter ctor 0x0026FFA4 clears +4 and installs 0x00BFAD10:
 * slots 0..2 are 0x00395A19, allow 0x0026119D, and 0x0036CC7A.
 * Rva002611BFFilter ctor 0x002623AB clears +4, installs 0x00BF91BC and
 * stores its const Object* argument at +8. Its table's slots 0..2 are
 * 0x00395A19, allow 0x002611BF, and 0x0036CC7A; non-code follows.
 * allow 0x0026119D tests the candidate's +0x438 bit 0; allow 0x002611BF
 * compares +0x438 bit 3 of the candidate and the Object* at this+8.
 * Destructor 0x0049C38A restores 0x00BC26E0. The derived tables' wrapper
 * 0x00395A19 calls it at 0x00395A1C before conditional operator delete.
 * That store is base teardown, not either derived class's construction table.
 * RousingSpeechUpdate 0x004AD176 builds adjacent same-map and alive filters
 * at EBP-0x28 and EBP-0x1C: sizes 12 and 8; +8 is the first derived field.
 * Zero Hour PartitionManager.h declares the same-map Object* as m_obj;
 * its PartitionFilter has only allow, so its slot order is not BFME2's.
 */
#pragma once

#ifndef BFME2_PARTITIONFILTER_H
#define BFME2_PARTITIONFILTER_H

class Object;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	Rva000421C8(const Rva000421C8 &);
	virtual ~Rva000421C8();
	virtual bool allow(Object *) = 0;
	virtual int getPlayerMask();
	bool allows(Object *);
	Rva000421C8 *link(Rva000421C8 *);

	Rva000421C8 *m_next;
};

#endif
