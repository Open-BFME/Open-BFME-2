// Disp8 byte setters: ten-byte __thiscall members with one shape:
//
//     mov al,[esp+4] / mov [ecx+<DISP>],al / ret 4
//
// One byte is taken from the stack argument slot and stored at a fixed
// displacement from `this`. Same macro as DispByteFieldSetters.cpp; every
// displacement here fits disp8 (MSVC 7.1 uses disp8 whenever the offset
// fits, so every offset is below 0x80).
// Identity is not recovered: every name is derived from its address,
// following DispByteFieldSetters.cpp.
// No // cl: line (defaults match the frameless ten-byte shape).
#define BFME_DISP8_BYTE_SETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void set(unsigned char value); \
		char m_lead[DISP]; \
		unsigned char m_value; \
	}; \
	void NAME::set(unsigned char value) \
	{ \
		m_value = value; \
	}

BFME_DISP8_BYTE_SETTER(Rva00318D14ByteSlot, 0x58)
BFME_DISP8_BYTE_SETTER(Rva004D576CByteSlot, 0x1E)
BFME_DISP8_BYTE_SETTER(Rva004D5984ByteSlot, 0x22)
BFME_DISP8_BYTE_SETTER(Rva00050CCEByteSlot, 0x4B)

// BF1 9cbfb551fe20dae985f91f2319d8997287b6a705 clean GameSlot::mute
// (SkirmishGameInfo_xfer.cpp) guides the expression only. Native
// 0x004E3FF0..0x004E3FFA follows INT3 and ends RET4: copy the stack
// argument's low byte to receiver+0x0A. Owner and field purpose unknown.
BFME_DISP8_BYTE_SETTER(Rva004E3FF0ByteSlot, 0x0A)

// BF1 9cb's LANAPIhandlers.cpp GameInfo::setGameInProgress supplies the
// same expression, without proving its name or bool type here. Native
// 0x002E6A9D..0x002E6AA7 follows an independently rowed RET4 and ends
// RET4 before the next getter: store the raw argument byte at receiver+0x0D.
// Original owner and field purpose remain unresolved.
BFME_DISP8_BYTE_SETTER(Rva002E6A9DByteSlot, 0x0D)

// Clean BF1 9cbfb551fe20dae985f91f2319d8997287b6a705 /O1 /arch:SSE /G7
// GameLogic accessor expressions guide these raw byte stores. The donor
// names below are provenance only: native width/offset/ABI proof does not
// establish the same original class, bool type, or field purpose.
// Each independent ten-byte body reads the stack argument low byte, writes
// receiver+disp8, and ends RET4. Every start follows a complete RET except
// 395596, after39558B's ADD ECX98/tail-jump to real StringBase::set366F0.
// Native0x00395596..0x003955A0; low rawbyte at+0x24.
// Donor GameEngine/Source/GameLogic/Map/Rva0019A470ChunkParser.cpp
// ?setInitiallyBuilt@BuildListInfo@@QAEX_N@Z (name and bool type unasserted in target).
BFME_DISP8_BYTE_SETTER(Rva00395596ByteSlot, 0x24)
// Native0x0033F239..0x0033F243; low rawbyte at+0x3A.
// Donor GameEngine/Source/GameLogic/Map/Rva0019A470ChunkParser.cpp
// ?setRepairable@BuildListInfo@@QAEX_N@Z (name and bool type unasserted in target).
BFME_DISP8_BYTE_SETTER(Rva0033F239ByteSlot, 0x3A)
// Native0x003297E1..0x003297EB; low rawbyte at+0x39.
// Donor GameEngine/Source/GameLogic/Map/Rva0019A470ChunkParser.cpp
// ?setUnsellable@BuildListInfo@@QAEX_N@Z (name and bool type unasserted in target).
BFME_DISP8_BYTE_SETTER(Rva003297E1ByteSlot, 0x39)
// Native0x003297D7..0x003297E1; low rawbyte at+0x38.
// Donor GameEngine/Source/GameLogic/Map/Rva0019A470ChunkParser.cpp
// ?setWhiner@BuildListInfo@@QAEX_N@Z (name and bool type unasserted in target).
BFME_DISP8_BYTE_SETTER(Rva003297D7ByteSlot, 0x38)
// Native0x002B2233..0x002B223D; low rawbyte at+0x54.
// Donor GameEngine/Source/GameLogic/AI/AIPlayer.cpp
// ?setUnderConstruction@BuildListInfo@@QAEX_N@Z (name and bool type unasserted in target).
BFME_DISP8_BYTE_SETTER(Rva002B2233ByteSlot, 0x54)
// Native0x00444036..0x00444040; low rawbyte at+0x5D.
// Donor GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// ?setShowBehindBuildingMarkers@GameLogic@@QAEX_N@Z (name and bool type unasserted in target).
BFME_DISP8_BYTE_SETTER(Rva00444036ByteSlot, 0x5D)
// Native0x003674B3..0x003674BD; low rawbyte at+0x5F.
// Donor GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// ?setShowDynamicLOD@GameLogic@@QAEX_N@Z (name and bool type unasserted in target).
BFME_DISP8_BYTE_SETTER(Rva003674B3ByteSlot, 0x5F)
// Native0x002DABFE..0x002DAC08; low rawbyte at+0x8.
// Donor GameEngine/Source/GameLogic/Map/TerrainLogic.cpp
// ?lockGhostObjects@GhostObjectManager@@QAEX_N@Z (name and bool type unasserted in target).
BFME_DISP8_BYTE_SETTER(Rva002DABFEByteSlot, 0x08)
