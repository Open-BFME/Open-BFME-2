// cl: /Ireference/shims/bfme2_ascii /O1 /MD /GX /DNDEBUG
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

class TerrainLogic
{
public:
	virtual ~TerrainLogic();
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual void slot07(); virtual void slot08(); virtual void slot09();
	virtual void slot10(); virtual void slot11(); virtual void slot12();
	virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16();
	virtual AsciiString getSourceFilename( void );
private:
	char m_unrecovered04[ 0x4C - 0x04 ];
	AsciiString m_filenameString;	///< 0x4C
};

AsciiString TerrainLogic::getSourceFilename( void )
{
	return m_filenameString;
}
