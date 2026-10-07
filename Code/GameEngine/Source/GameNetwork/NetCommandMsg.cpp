// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /DWIN32 /MD /EHsc /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it

#include "PreRTS.h"

#include "GameNetwork/NetCommandMsg.h"

class BfmeNetGameMessageArgument
{
public:
	BfmeNetGameMessageArgument() {}
	virtual ~BfmeNetGameMessageArgument() {}

	BfmeNetGameMessageArgument *m_next;
	GameMessageArgumentType m_data;
	GameMessageArgumentDataType m_type;
};

// ??1NetCommandMsg@@MAE@XZ present-unmatched
inline NetCommandMsg::~NetCommandMsg()
{
}

void NetGameCommandMsg::addArgument(
	const GameMessageArgumentDataType type, GameMessageArgumentType arg)
{
	if (m_argTail == NULL) {
		BfmeNetGameMessageArgument *newArg = new BfmeNetGameMessageArgument;
		m_argList = reinterpret_cast<GameMessageArgument *>(newArg);
		m_argTail = m_argList;
		m_argList->m_data = arg;
		m_argList->m_type = type;
		m_argList->m_next = NULL;
		return;
	}

	GameMessageArgument *newArg = reinterpret_cast<GameMessageArgument *>(
		new BfmeNetGameMessageArgument);
	newArg->m_data = arg;
	newArg->m_type = type;
	newArg->m_next = NULL;
	m_argTail->m_next = newArg;
	m_argTail = newArg;
}

// Full retail detach body (including negative counts) is in NetCommandMsg_detach.cpp.

NetWrapperCommandMsg::~NetWrapperCommandMsg()
{
	if (m_data != NULL) {
		delete m_data;
		m_data = NULL;
	}
}

void NetWrapperCommandMsg::setData(UnsignedByte *data, UnsignedInt dataLength)
{
	if (m_data != NULL) {
		delete m_data;
		m_data = NULL;
	}

	m_data = NEW UnsignedByte[dataLength];
	memcpy(m_data, data, dataLength);
	m_dataLength = dataLength;
}

UnsignedByte * NetWrapperCommandMsg::getData()
{
	return m_data;
}

UnsignedInt NetWrapperCommandMsg::getDataLength()
{
	return m_dataLength;
}

UnsignedInt NetWrapperCommandMsg::getDataOffset()
{
	return m_dataOffset;
}

// ?setDataOffset@NetWrapperCommandMsg@@QAEXI@Z present-unmatched
void NetWrapperCommandMsg::setDataOffset(UnsignedInt offset)
{
	m_dataOffset = offset;
}

UnsignedInt NetWrapperCommandMsg::getTotalDataLength()
{
	return m_totalDataLength;
}

// ?setTotalDataLength@NetWrapperCommandMsg@@QAEXI@Z present-unmatched
void NetWrapperCommandMsg::setTotalDataLength(UnsignedInt totalDataLength)
{
	m_totalDataLength = totalDataLength;
}

// ?getChunkNumber@NetWrapperCommandMsg@@QAEIXZ present-unmatched
UnsignedInt NetWrapperCommandMsg::getChunkNumber()
{
	return m_chunkNumber;
}

// ?setChunkNumber@NetWrapperCommandMsg@@QAEXI@Z present-unmatched
void NetWrapperCommandMsg::setChunkNumber(UnsignedInt chunkNumber)
{
	m_chunkNumber = chunkNumber;
}

UnsignedInt NetWrapperCommandMsg::getNumChunks()
{
	return m_numChunks;
}

// ?setNumChunks@NetWrapperCommandMsg@@QAEXI@Z present-unmatched
void NetWrapperCommandMsg::setNumChunks(UnsignedInt numChunks)
{
	m_numChunks = numChunks;
}

UnsignedShort NetWrapperCommandMsg::getWrappedCommandID()
{
	return m_wrappedCommandID;
}

void NetWrapperCommandMsg::setWrappedCommandID(UnsignedShort wrappedCommandID)
{
	m_wrappedCommandID = wrappedCommandID;
}

void NetFileCommandMsg::setFileData(UnsignedByte *data, UnsignedInt dataLength)
{
	m_dataLength = dataLength;
	m_data = NEW UnsignedByte[dataLength];
	memcpy(m_data, data, dataLength);
}

// ?getCommandID@NetAckBothCommandMsg@@QAEGXZ present-unmatched
UnsignedShort NetAckBothCommandMsg::getCommandID()
{
	return m_commandID;
}

// ?getOriginalPlayerID@NetAckBothCommandMsg@@QAEEXZ present-unmatched
UnsignedByte NetAckBothCommandMsg::getOriginalPlayerID()
{
	return m_originalPlayerID;
}

// ?getCommandID@NetAckStage1CommandMsg@@QAEGXZ present-unmatched
UnsignedShort NetAckStage1CommandMsg::getCommandID()
{
	return m_commandID;
}

// ?getOriginalPlayerID@NetAckStage1CommandMsg@@QAEEXZ present-unmatched
UnsignedByte NetAckStage1CommandMsg::getOriginalPlayerID()
{
	return m_originalPlayerID;
}

// ?getSortNumber@NetAckStage1CommandMsg@@UAEHXZ present-unmatched
Int NetAckStage1CommandMsg::getSortNumber()
{
	return m_commandID;
}

// ?getCommandID@NetAckStage2CommandMsg@@QAEGXZ present-unmatched
UnsignedShort NetAckStage2CommandMsg::getCommandID()
{
	return m_commandID;
}

// ?getOriginalPlayerID@NetAckStage2CommandMsg@@QAEEXZ present-unmatched
UnsignedByte NetAckStage2CommandMsg::getOriginalPlayerID()
{
	return m_originalPlayerID;
}

// NetProgressCommandMsg::getPercentage: defined in NetProgressCommandMsgGetPercentage.cpp (its row's unit).

// ?setPercentage@NetProgressCommandMsg@@QAEXE@Z present-unmatched
void NetProgressCommandMsg::setPercentage(UnsignedByte percent)
{
	m_percent = percent;
}

// Seven disconnect-message accessors whose ledger rows claimed 5-byte
// incremental-link thunks. The definitions had been trimmed out of this file, so
// nothing emitted the symbols; these are the reference's bodies unchanged.

// ?getDisconnectSlot@NetDisconnectPlayerCommandMsg@@QAEEXZ present-unmatched
UnsignedByte NetDisconnectPlayerCommandMsg::getDisconnectSlot() {
	return m_disconnectSlot;
}

// ?setDisconnectSlot@NetDisconnectPlayerCommandMsg@@QAEXE@Z present-unmatched
void NetDisconnectPlayerCommandMsg::setDisconnectSlot(UnsignedByte slot) {
	m_disconnectSlot = slot;
}

// ?setDisconnectFrame@NetDisconnectPlayerCommandMsg@@QAEXI@Z present-unmatched
// BFME 2 keeps the frame at +0x24: retail's body (0x005739F6, the folded 10-byte
// dword setter its callers reach) is mov eax,[esp+4]; mov [ecx+0x24],eax; ret 4,
// and the slot setter it pairs with writes +0x1C, so a dword BFME 2 added sits
// at +0x20. The ZH header this unit compiles against puts m_disconnectFrame at
// +0x20, which the link census proved wrong (wrong_selected for NetPacket.cpp's
// call); the store names BFME 2's offset until the class gets a BFME 2 header.
void NetDisconnectPlayerCommandMsg::setDisconnectFrame(UnsignedInt frame) {
	*(UnsignedInt *)((char *)this + 0x24) = frame;
}

// ?setSlot@NetDisconnectVoteCommandMsg@@QAEXE@Z present-unmatched
void NetDisconnectVoteCommandMsg::setSlot(UnsignedByte slot) {
	m_slot = slot;
}

// ?setVoteFrame@NetDisconnectVoteCommandMsg@@QAEXI@Z present-unmatched
void NetDisconnectVoteCommandMsg::setVoteFrame(UnsignedInt voteFrame) {
	m_voteFrame = voteFrame;
}

// ?getDisconnectFrame@NetDisconnectFrameCommandMsg@@QAEIXZ present-unmatched
UnsignedInt NetDisconnectFrameCommandMsg::getDisconnectFrame() {
	return m_disconnectFrame;
}

// ?getNewFrame@NetDisconnectScreenOffCommandMsg@@QAEIXZ present-unmatched
UnsignedInt NetDisconnectScreenOffCommandMsg::getNewFrame() {
	return m_newFrame;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?count@XmlNameSlotList@@QAEHXZ=?getTotalDataLength@NetWrapperCommandMsg@@QAEIXZ")

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?getSortNumber@NetCommandMsg@@UAEHXZ=?IsCRC@Xfer@@UBE_NXZ")
