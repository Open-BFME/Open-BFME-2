// Target facts (addresses are RVAs): 0x0046247D writes two four-byte pointers at +0 and +4, respectively the null-preserving owner+0x20 and owner+0x54; 0x004631FA reserves exactly eight bytes at [ebp-8] for this output and reads its second word at 0x0046320B. Thus sizeof is 0x08, with no base or vptr: retail has no virtual functions for this record.
// 0x0047C018 and 0x0047D087 write the null-preserving ContainModuleInterface conversion to +0 and a list address to +4. OpenContain's 0x00464A16/0x00464A5C install that registered +0x20 interface's tables (VAs 0x00C430E8/0x00C433B0); the latter's slot 1 is 0x004647CD (this-0x20), and slot 70 is 0x004647D8 (the same two-pointer output). 0x0046431B copies both words; 0x0036AE51 tests and clears +0 and passes +4 to the list copier.
// The matched 0x0046247D, 0x00587204 and 0x0046F7FF signatures spell the record as struct (U). They are methods of other classes; no ledger row or private declaration defines a constructor, destructor or other member of Rva0046247DPair. Original field names and the list's element identity are unproved, so the fields use neutral offset names and +4 remains opaque.
#pragma once

class ContainModuleInterface;

struct Rva0046247DPair
{
	ContainModuleInterface *m00;
	void *m04;
};
