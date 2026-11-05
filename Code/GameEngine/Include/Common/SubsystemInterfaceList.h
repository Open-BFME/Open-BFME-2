// Target facts: SubsystemInterfaceList has no virtual functions or base class.
// Constructor 0x001B4FB8 calls vector-base 0x00211E58 at +0, +0x0C and +0x18,
// then clears +0x24; destructor 0x001B5207 calls 0x001B51C0 and frees those
// buffers in reverse order. Neither body stores a vptr. Allocation 0x0022E335
// pushes 0x28 before operator new at 0x0022E343 and construction at 0x0022E356.
// initSubsystem 0x001B5266 appends the subsystem and its slot as two dwords
// through 0x00539A2E; make_pair 0x00539A18 names their pair type. Walks at
// 0x001B4E49, 0x001B4F6D and 0x001B5018 step these records by eight bytes.
// removeSubsystem 0x001B4E82 searches the pointer vector at +0x0C; 0x001B5140
// collects subsystem pointers into +0x18, and 0x001B4FE9 dispatches and clears it.
// Both pointer vectors contain subsystem objects: 0x001B5140 collects their
// pointers from +0 and +0x0C into +0x18 before 0x001B4FE9 dispatches them.
// 0x0022E464 stores a BFMECRCWriter (constructed at 0x0022E450) at +0x24;
// 0x0021A3E8 reads that field for INI::loadFile at 0x0021A408. getXfer exposes
// that read; no separately rowed accessor body exists.
// Rowed methods: 0x001B4E21, 0x001B4E49, 0x001B4E82, 0x001B4F6D,
// 0x001B4FE9, 0x001B5018, 0x001B505F, 0x001B51C0, 0x001B5266 and
// addSubsystem 0x0047A69C (ret 4). Unknown method names retain their RVA tokens.
// Donor names: Zero Hour Common/SubsystemInterface.h names m_subsystems and
// m_allSubsystems. Its two pointer-vector layout does not describe BFME2.

#pragma once

#include <vector>
#include <utility>

class AsciiString;
class SubsystemInterface;
class Xfer;

class SubsystemInterfaceList
{
public:
	SubsystemInterfaceList();
	~SubsystemInterfaceList();

	void initSubsystem(SubsystemInterface *sys, void *slot, const char *path1,
		const char *path2, const char *dirpath, Xfer *xfer, AsciiString name);
	void addSubsystem(SubsystemInterface *sys);
	void removeSubsystem(SubsystemInterface *sys);
	void postProcessLoadAll();
	void resetAll();
	unsigned char rva001B4E21(SubsystemInterface *sys, unsigned char *flag);
	void rva001B4FE9();
	void rva001B5018(SubsystemInterface *sys);
	unsigned char notifySubsystems();
	void rva001B51C0();
	Xfer *getXfer() const { return m_xfer; }

private:
	std::vector<std::pair<SubsystemInterface *, void *> > m_subsystems;
	std::vector<SubsystemInterface *> m_allSubsystems;
	std::vector<SubsystemInterface *> field18;

public:
	Xfer *m_xfer;
};
