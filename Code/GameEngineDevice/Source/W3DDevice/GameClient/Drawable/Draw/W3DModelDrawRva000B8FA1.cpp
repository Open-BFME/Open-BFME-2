// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /Ireference/shims/bfme2_ascii
//
// ?rva000B8FA1@Rva000B8FA1@@QAEXPBUNameSpan@@@Z, retail 0x000B8FA1
// (124 bytes, RET 4): the house-colour sibling of 0x000B901D in the same
// W3DModelDraw-family secondary table (drawable at -4, render object at
// +0x44). With a drawable whose Object (+0xFC) has a controlling player and
// a render object, the player's colour (+0x280) goes to render-object slot
// +0x1F8 in the 16-byte option block (3-bit field 1, next two cleared, top
// bit kept, colour, two zeros) with the first of the given names or none
// for an empty list. WB 0x00942D20 has the two calls as separate branches;
// retail tail-merges them on the shared EDI zero. Address-derived names.
#include "ascii_string.h"

typedef int Int;

struct Rva000B8FA1HouseColor
{
	unsigned int m_a : 3;
	unsigned int m_b : 27;
	unsigned int m_c : 1;
	unsigned int m_d : 1;
	Int m_color;
	Int m_reserved0;
	Int m_reserved1;
};

struct NameSpan
{
	AsciiString *m_begin;
	AsciiString *m_end;
};

class Player
{
public:
	unsigned char m_pad000[0x280];
	Int m_color;	// +0x280
};

#include "../../../../../../GameEngine/Source/GameLogic/Object/object.h"

struct Rva000B8FA1Drawable
{
	unsigned char m_pad000[0xFC];
	Object *m_object;	// +0xFC
};

#define RSLOT(n) virtual void s##n();
class Rva000B8FA1RenderObj
{
public:
	RSLOT(000) RSLOT(001) RSLOT(002) RSLOT(003) RSLOT(004) RSLOT(005) RSLOT(006) RSLOT(007) RSLOT(008) RSLOT(009)
	RSLOT(010) RSLOT(011) RSLOT(012) RSLOT(013) RSLOT(014) RSLOT(015) RSLOT(016) RSLOT(017) RSLOT(018) RSLOT(019)
	RSLOT(020) RSLOT(021) RSLOT(022) RSLOT(023) RSLOT(024) RSLOT(025) RSLOT(026) RSLOT(027) RSLOT(028) RSLOT(029)
	RSLOT(030) RSLOT(031) RSLOT(032) RSLOT(033) RSLOT(034) RSLOT(035) RSLOT(036) RSLOT(037) RSLOT(038) RSLOT(039)
	RSLOT(040) RSLOT(041) RSLOT(042) RSLOT(043) RSLOT(044) RSLOT(045) RSLOT(046) RSLOT(047) RSLOT(048) RSLOT(049)
	RSLOT(050) RSLOT(051) RSLOT(052) RSLOT(053) RSLOT(054) RSLOT(055) RSLOT(056) RSLOT(057) RSLOT(058) RSLOT(059)
	RSLOT(060) RSLOT(061) RSLOT(062) RSLOT(063) RSLOT(064) RSLOT(065) RSLOT(066) RSLOT(067) RSLOT(068) RSLOT(069)
	RSLOT(070) RSLOT(071) RSLOT(072) RSLOT(073) RSLOT(074) RSLOT(075) RSLOT(076) RSLOT(077) RSLOT(078) RSLOT(079)
	RSLOT(080) RSLOT(081) RSLOT(082) RSLOT(083) RSLOT(084) RSLOT(085) RSLOT(086) RSLOT(087) RSLOT(088) RSLOT(089)
	RSLOT(090) RSLOT(091) RSLOT(092) RSLOT(093) RSLOT(094) RSLOT(095) RSLOT(096) RSLOT(097) RSLOT(098) RSLOT(099)
	RSLOT(100) RSLOT(101) RSLOT(102) RSLOT(103) RSLOT(104) RSLOT(105) RSLOT(106) RSLOT(107) RSLOT(108) RSLOT(109)
	RSLOT(110) RSLOT(111) RSLOT(112) RSLOT(113) RSLOT(114) RSLOT(115) RSLOT(116) RSLOT(117) RSLOT(118) RSLOT(119)
	RSLOT(120) RSLOT(121) RSLOT(122) RSLOT(123) RSLOT(124) RSLOT(125)
	virtual void setHouseColor(const Rva000B8FA1HouseColor &params, const char *name);	// +0x1F8
};
#undef RSLOT

class Rva000B8FA1
{
public:
	void rva000B8FA1(const NameSpan *names);
private:
	Rva000B8FA1Drawable *drawable() const { return *(Rva000B8FA1Drawable *const *)((const char *)this - 4); }
	unsigned char m_pad00[0x44];
	Rva000B8FA1RenderObj *m_renderObject;	// +0x44
};

void Rva000B8FA1::rva000B8FA1(const NameSpan *names)
{
	Rva000B8FA1Drawable *draw = drawable();
	if (!draw)
		return;
	Object *object = draw->m_object;
	if (!object)
		return;
	Player *player = object->getControllingPlayer();
	if (!player)
		return;
	Int color = player->m_color;
	if (!m_renderObject)
		return;

	if (names->m_begin == names->m_end)
	{
		Rva000B8FA1HouseColor params;
		params.m_a = 1;
		params.m_b = 0;
		params.m_c = 0;
		params.m_color = color;
		params.m_reserved0 = 0;
		params.m_reserved1 = 0;
		m_renderObject->setHouseColor(params, 0);
	}
	else
	{
		const char *name = names->m_begin[0].str();
		Rva000B8FA1HouseColor params;
		params.m_a = 1;
		params.m_b = 0;
		params.m_c = 0;
		params.m_color = color;
		params.m_reserved0 = 0;
		params.m_reserved1 = 0;
		m_renderObject->setHouseColor(params, name);
	}
}
