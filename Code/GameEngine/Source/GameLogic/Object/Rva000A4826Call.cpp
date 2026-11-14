// cl: /DNDEBUG /MD
// ?rva000A4826@Rva000A4826@@QAEXMMMMMH@Z retail 0x000A4826 79B.
// Virtual forwarder: calls slot 0xD4 then slot 0xEC with same five floats plus int
// then slot 0x100; x87 fld/fstp spills with EBP frame and ret 0x18.
// Evidence: callees are vtable slots 53/59/64; callers 0x000A4F58 0x000A5617 0x000A5C37;
// neighbour Rva000A4999Get 0x000A4999 same flags.
// ?rva000A47DE@Rva000A4826@@QAEXMMMMH@Z retail 0x000A47DE 72B.
// Sibling forwarder in same class: slot 0xD4 then slot 0xE8 with four floats plus int
// then slot 0x100; same x87 shape with ret 0x14.
// Evidence: caller 0x000A5A99; prev byte getter 0x000A47A7 same neighbourhood.
#include "../../../../GameEngineDevice/Include/W3DDevice/GameClient/Rva000A4826.h"

void Rva000A4826::rva000A4826(float startX, float startY, float width, float height, float percent, int color)
{
	v053();
	v059(startX, startY, width, height, percent, color);
	v064();
}

void Rva000A4826::rva000A47DE(float startX, float startY, float width, float height, int color)
{
	v053();
	v058(startX, startY, width, height, color);
	v064();
}

void Rva000A4826::rva000A4875(float startX, float startY, float width, float height, float percent, int color)
{
	v053();
	v060(startX, startY, width, height, percent, color);
	v064();
}

void Rva000A4826::rva000A48C4(int image, float startX, float startY, float endX, float endY, float percent, int color)
{
	v053();
	v061(image, startX, startY, endX, endY, percent, color);
	v064();
}
