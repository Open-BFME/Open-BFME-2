// Target facts: retail RVAs unless a table is explicitly marked VA.
// Constructor 0x00256E19 calls SubsystemInterface's 0x001B4E63, installs Snapshot VA 0x00BBB554 at +0x0C, then factory tables VA 0x00BF3FEC at +0 and VA 0x00BF3FDC at +0x0C. Destructor 0x00256E96 installs the same pair, then restores Snapshot VA 0x00BBB554 at 0x00256F1E before calling SubsystemInterface's destructor 0x001B4E74. These are construction and teardown of the same two bases, not alternative factory tables. Their ledger owner is Rva00256E96. Factory 0x00042091 allocates 0x28 bytes, calls 0x00256E19 and replaces only the tables for W3DModuleFactory at 0x000420BA/0x000420C0.
// VA 0x00BF3FEC has 14 slots: 0 destructor 0x002571DD, 1 init 0x00257CB8, 2 loadIniFilesFromLegend 0x001B5384, 3/8/9/10/12 ret 0x000B3FD0, 4/11 false with ret 4 at 0x005CB9FF, 5 false at 0x0047A699, 6 zero at 0x000D43D0, 7/13 ret 4 at 0x0047A69C. VA 0x00BF3FDC has four Snapshot slots: 0 thunk 0x00256E8E subtracts 0x0C and jumps to 0x002571DD, 1 ret 0x000B3FD0, 2 getter 0x000420D6 returns "ModuleFactory", 3 transfer 0x00254CCF. The primary table follows those four entries; a zero word follows its fourteen entries. The class is polymorphic and adds no virtual slot to its bases.
// Constructor 0x00256E53 constructs the 12-byte tree at +0x10; 0x00256E61 constructs the 12-byte pointer vector at +0x1C. Lookup 0x00256768 uses +0x10; 0x0025723E appends data at +0x1C. Registration 0x002573EE stores callbacks at record +0/+4/+8 and the mask at +0x0C (0x00257413/0x00257418/0x00257424/0x0025741E). Callers 0x002567AC, 0x00257220 and 0x002567E1 prove the three callback signatures; mask getter 0x00256F5C reads +0x0C. The record therefore spans at least 16 bytes; three-word private map payloads are incompatible with these accesses. Outer container storage stays opaque.
// Method signatures and access come from the matched ModuleFactory ledger rows at 0x00256783, 0x002571F9, 0x00256F39, 0x002567B9, 0x0025674F and 0x00255C5E. Zero Hour's GeneralsMD Common/ModuleFactory.h supplies the ModuleTemplate, m_createProc and m_createDataProc names; the BFME2 mask uses the neutral name m_tag0C. Snapshot's slot names follow its registered header and retail dispatch; unnamed inherited slots retain the registered parent's placeholders.

#pragma once

#ifndef BFME2_MODULEFACTORYCLASS_H
#define BFME2_MODULEFACTORYCLASS_H

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
#error ModuleFactory requires the const Snapshot name getter
#endif
#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
class Xfer;

class INI;
class Module;
class ModuleData;
class Thing;
class Rva002573EE;
enum ModuleType;
enum NameKeyType;

class ModuleFactory : public SubsystemInterface, public Snapshot
{
	friend class Rva002573EE;
public:
	class ModuleTemplate
	{
	public:
		Module *(__cdecl *m_createProc)(Thing *, const ModuleData *);
		ModuleData *(__cdecl *m_createDataProc)(INI *);
		void (__cdecl *m_create08)(int, int, int);
		int m_tag0C;
	};

	ModuleFactory();
	virtual ~ModuleFactory();
	virtual void init();
	virtual void reset();
	virtual void update();
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
	virtual void LoadPostProcess();
#else
	virtual void loadPostProcess();
#endif
#ifdef BFME_SNAPSHOT_NAME_SLOT
	virtual const char *GetSnapshotName() const;
#else
	virtual void crc(Xfer *xfer);
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

	Module *newModule(Thing *, const AsciiString &, const ModuleData *, ModuleType);
	ModuleData *newModuleDataFromINI(INI *, const AsciiString &, ModuleType, const AsciiString &);
	int findModuleInterfaceMask(const AsciiString &, ModuleType);
	void GetAssetList(const AsciiString &, int, ModuleType, int, int);

protected:
	const ModuleTemplate *findModuleTemplate(const AsciiString &, ModuleType);
	static NameKeyType makeDecoratedNameKey(const AsciiString &, ModuleType);

private:
	unsigned char field_10[0x0C];
	unsigned char field_1C[0x0C];
};

extern ModuleFactory *TheModuleFactory;

#endif
