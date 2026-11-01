// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG
// TerrainLogic::getSourceFilename, retail 0x00062E72 (27 bytes): slot 17 of
// the TerrainLogic vftable 0x00BFB2C8 and of W3DTerrainLogic's 0x00BC5890
// (whose slot-2 name getters return TerrainLogic / W3DTerrainLogic, so the
// derived class does not override it). Zero Hour's inline
// TerrainLogic::getSourceFilename returns m_filenameString by value; in
// BFME 2 it sits at +0x4C and the copy is the rowed StringBase<char> copy
// constructor 0x000365F0. The name was previously rowed (gen-alias) at
// 0x000DE59C, which is not this body: it copies +0x34, sits in no vftable
// and is reached only by direct calls, so that row is retired here.

#include "ascii_string.h"

#include "../../../Include/GameLogic/TerrainLogic.h"

AsciiString TerrainLogic::getSourceFilename( void )
{
	return field4C;
}
