// Target facts: ctor RVA 0x00243177 and dtor RVA 0x004398D8 store VA 0x00BEE024 at +0. The dtor restores Snapshot's VA 0x00BBB554 at RVA 0x0043990F. VA 0x00BEE024 has four slots: deleting dtor RVA 0x002431AF, empty RVA 0x000B3FD0, name getter RVA 0x002431A9 ("InvisibilityManager" at VA 0x00BEE034), and transfer RVA 0x0043A047.
// GameLogic::init allocates 0x18 bytes at RVA 0x002440F4, calls that ctor at 0x0024410C, stores the result at GameLogic+0x178 at 0x0024411A, and calls RVA 0x0043821C. That initializer writes float +0x10 and dword +0x14; RVA 0x00439965 compares and updates +0x14. RVA 0x00438FF4 reads the tree header at +4 and count at +8. Bytes +0x0C..+0x0F are opaque container storage.
// The transfer slot calls RVAs 0x00439F3F and 0x00438FF4 with the unchanged receiver. Their ledger rows and the other annotated member rows prove this class spelling and the non-virtual method signatures below. The ctor and dtor rows spell the same object Rva000D3FA0Map; this header declares bodies out of line and defines no competing table or special-member body.

#pragma once

#ifndef BFME2_RVA00439E0C_H
#define BFME2_RVA00439E0C_H

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

class Object;
struct Coord3D;
struct Rva004393D6;
struct Rva004393D6Entry;
struct Rva004389DBInfo;
enum ObjectID;

class Rva00439E0C : public Snapshot
{
public:
	virtual ~Rva00439E0C();

	void rva0043822E(Rva004393D6 *, unsigned int); // 0x0043822E
	void rva004384F2(Object *, int); // 0x004384F2
	bool rva004387B1(Object *, unsigned int); // 0x004387B1
	void rva0043888E(Rva004393D6 *); // 0x0043888E
	void rva004389DB(Object *, Rva004389DBInfo *, int); // 0x004389DB
	void rva00438C6C(Object *, void *, int, bool); // 0x00438C6C
	void rva00438D58(Object *); // 0x00438D58
	bool rva00438E5B(Object *, int, Rva004393D6 *, Rva004389DBInfo *, unsigned int); // 0x00438E5B
	void rva00438FF4(Xfer *); // 0x00438FF4
	bool rva00439428(Object *, const Coord3D *, Rva004393D6Entry *, int, int, ObjectID *); // 0x00439428
	bool rva004395D3(Object *, const Coord3D *, Rva004393D6Entry *); // 0x004395D3
	int rva0043966A(Object *, const Coord3D *, Rva004393D6 *, Rva004389DBInfo *); // 0x0043966A
	bool rva0043979D(Object *, Rva004393D6 *); // 0x0043979D
	bool detected(Object *, Object *, int, int); // 0x00439E0C
	void rva00439F3F(Xfer *); // 0x00439F3F

	void *field04;
	int field08;
	unsigned char field0C[4];
	float field10;
	unsigned int field14;

protected:
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
	virtual void LoadPostProcess();
#else
	virtual void loadPostProcess();
#endif
#ifdef BFME_SNAPSHOT_NAME_SLOT
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
	virtual const char *GetSnapshotName();
#else
	virtual const char *GetSnapshotName() const;
#endif
#else
	virtual void crc(Xfer *);
#endif
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
	virtual void DoXfer(Xfer &);
#else
	virtual void DoXfer(Xfer *);
#endif
#else
	virtual void xfer(Xfer *);
#endif
};

#endif
