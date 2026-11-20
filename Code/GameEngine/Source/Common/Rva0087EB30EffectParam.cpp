// cl: /O2 /G6 /MD
// Transferred from Open-BFME-1 09f941a50d
// game/GameEngine/Source/Common/Rva0087EB30EffectParam.cpp (BFME1 0x0087EB30,
// 75 B), adapted: game.dat's copy at 0x006BE400 (79 B) follows the transferred
// Rva0087EAA0Copy body as in BFME1 and also sets a second bool at +0x21, so the
// record is 0x22 bytes here. Target evidence: the five stack arguments
// (ret 0x14), the type == 2 select of the second float by x87, the copied
// three-float position at +0x10, the zeroed dword at +0x1C and the two true
// bytes. The class name keeps the donor's BFME1 address token; its original
// identity is not proved in either game.
struct Rva0087EB30Vec3 { float x; float y; float z; };
struct Rva0087EB30EffectParam {
	int m_type;
	int m_index;
	float m_valueA;
	float m_value;
	Rva0087EB30Vec3 m_pos;
	int m_extra;
	bool m_flag;
	bool m_flag2;
	Rva0087EB30EffectParam(int type, int index, float valueA, float valueB, const Rva0087EB30Vec3* pos);
};
Rva0087EB30EffectParam::Rva0087EB30EffectParam(int type, int index, float valueA, float valueB, const Rva0087EB30Vec3* pos)
	: m_type(type), m_index(index), m_valueA(valueA),
	  m_value(type == 2 ? valueB : valueA)
{
	m_pos.x = pos->x;
	m_pos.y = pos->y;
	m_pos.z = pos->z;
	m_extra = 0;
	m_flag = true;
	m_flag2 = true;
}
