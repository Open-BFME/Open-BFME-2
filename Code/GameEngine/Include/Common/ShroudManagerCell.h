// Target facts (code addresses are RVAs): ShroudManagerCell has no virtual functions, vftable or evidenced base class. Constructor 0x0073B600 stores zero at +0 and +0xA4, then initializes twenty eight-byte records at +4 with status 0xFFFF and three zero counter words (0x0073B613..0x0073B634).
// Array construction at 0x0073DD28..0x0073DD3E and 0x0073E070..0x0073E08B passes constructor 0x0073B600, destructor 0x0069E440 and stride 0xA8; 0x0073E053 allocates 0xAC including the four-byte cookie. Destructor 0x0069E440 is a bare RET, with no table stores. Reader 0x0073EA44 loads the unsigned status at this+4+player*8; adjuster 0x0073EA5B accesses counters at this+6+player*8+counter*2. Transfer 0x0073EBB0 uses twenty records and calls 0x0073EB00 for three counter words; its legacy path at 0x0073EBFE calls 0x0073EA90 for two words and clears the third at 0x0073EC14.
// Rows prove the method spellings: xfer 0x0073EBB0, adjustPlayerCounter008FC1F0 0x0073EA50, getPlayerStatus_Rva0073EA40 0x0073EA40, AddLooker 0x0073EC70, updatePlayerCells008FC3B0 0x0073ED20 and ShroudIfFogged 0x0073EDC0. AddLooker loads the cell-node head at 0x0073ECC3 and follows node+0x0C at 0x0073ECDB, proving cellNodes; getPlayerStatus and xfer prove the per-player status/counter records named playerStates. These descriptive labels do not establish original source spellings. The node and player-record types retain neutral existing address-derived spellings; m_A4 is an existing neutral label for the unnamed dword at +0xA4.

#pragma once

#ifndef BFME2_SHROUDMANAGERCELL_H
#define BFME2_SHROUDMANAGERCELL_H

class ShroudManagerImpl;
class ShroudManagerImpl008FBA40Node;
class Xfer;

struct ShroudManagerImpl008FBA40PlayerState
{
	unsigned short status;
	unsigned short counters[3];
};

class ShroudManagerCell
{
public:
	__declspec(noinline) ShroudManagerCell();
	__declspec(noinline) ~ShroudManagerCell();
	void xfer(Xfer *xfer);
	void adjustPlayerCounter008FC1F0(int playerIndex, int counterIndex, int amount);
	__declspec(noinline) int getPlayerStatus_Rva0073EA40(int playerIndex);
	void AddLooker(ShroudManagerImpl *manager, int playerIndex);
	void updatePlayerCells008FC3B0(ShroudManagerImpl *manager, int playerIndex);
	void ShroudIfFogged(ShroudManagerImpl *manager, int playerIndex);

private:
	ShroudManagerImpl008FBA40Node *cellNodes;
	ShroudManagerImpl008FBA40PlayerState playerStates[20];
	int m_A4;
	friend class ShroudManagerImpl;
};

typedef char ShroudManagerCellSizeIs0xA8[(sizeof(ShroudManagerCell) == 0xA8) ? 1 : -1];

#endif
