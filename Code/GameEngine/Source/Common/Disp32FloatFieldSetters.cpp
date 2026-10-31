// Disp32 float setters: seventeen-byte __thiscall members with one shape:
//
//     movss xmm0,[esp+4] / movss [ecx+<DISP>],xmm0 / ret 4
//
// One float argument is stored at a fixed 32-bit displacement from `this`.
// MSVC 7.1 emits `F3 0F 10 44 24 04` plus `F3 0F 11 81 DISP32` plus
// `C2 04 00` for seventeen bytes total with /arch:SSE. Identity is not
// recovered: every name is derived from its address.
// cl: /MD /DNDEBUG
#define BFME_DISP32_FLOAT_SETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void set(float newValue); \
		char m_leadingPadding[DISP]; \
		float m_floatValue; \
	}; \
	void NAME::set(float newValue) \
	{ \
		m_floatValue = newValue; \
	}
BFME_DISP32_FLOAT_SETTER(Rva00167F15FloatField, 0xFC)
BFME_DISP32_FLOAT_SETTER(Rva00167F37FloatField, 0x100)
// Native210C91..210CA2 stores a float at ECX+98 and returns with RET4.
// Audio callers433498 and4331C6 select this SSE body, not RenderObjClass's
// distinct integer-MOV body at E43E7. Original owner/field name unresolved.
BFME_DISP32_FLOAT_SETTER(Rva00210C91FloatField, 0x98)
// Native270678..270689 stores a float at ECX+E0 and returns with RET4, inside the
// GameClient run around Rva002706A8. It was rowed as LightClass::Set_Spot_Exponent
// by a stale Zero Hour layout; BFME 2 keeps LightClass::SpotExponent at +0x110
// (Get_Spot_Exponent 0x0011C760). Original owner/field name unresolved.
BFME_DISP32_FLOAT_SETTER(Rva00270678FloatField, 0xE0)
BFME_DISP32_FLOAT_SETTER(Rva0029A767FloatField, 0x764)
BFME_DISP32_FLOAT_SETTER(Rva002AA0CDFloatField, 0x6F8)

// 0x002A9E25 is a Player member: ScavengerSpecialPower::doSpecialPower
// 0x004C4401, 0x004C4430 and the linear campaign carryover call it on
// Object::getControllingPlayer() results and Player pointers. The field
// purpose at +0x314 is unresolved.
class Player
{
public:
	void rva002A9E25(float newValue);
	char m_leadingPadding[0x314];
	float m_floatValue;
};
void Player::rva002A9E25(float newValue)
{
	m_floatValue = newValue;
}

// Native30F2BA..30F2C7 is a complete float-argument store at ECX+0,
// between independently bounded RET4 at30F2B7 and known getter30F2C7.
// Found beside the BF1 9cb WaterRenderObjConstructor Boxed<float> placement;
// adjacency does not establish its original class or field purpose.
class Rva0030F2BAFloatField
{
public:
    void set(float value);
    float m_value;
};
void Rva0030F2BAFloatField::set(float value)
{
    m_value=value;
}

// BF1 f98983a7d3 GameLogic/Object/Body/InactiveBodyCtorThunk.cpp is the
// clean store-and-return source guide, compiled at /O1 /arch:SSE2 /G6.
// Its InactiveBody identity and 1.0f initializer are not target facts.
// Native432E4E..432E5D follows the complete jump/lookup tables of432B18:
// seven DWORD targets at432E22 and sixteen byte selectors at432E3E,
// bounded by CMP 0xF. Known independent432E5D follows its own RET.
// The body writes ECX+0 from actual BD5E50=00004842 (50.0f), returns
// the same pointer in EAX and takes no stack arguments. No calls or
// image address references establish its original owner/constructor role.
// This free fastcall view states only the observed float output contract.
float *__fastcall Rva00432E4EInitialize(float *output)
{
    *output = 50.0f;
    return output;
}

