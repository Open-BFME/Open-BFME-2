// ?rva0046BC30@HordeContain@@UAEXXZ
// partial score=0.96 date=2026-10-08
// Banked attempt for HordeContain::rva0046BC30 (0x0046BC30, 320 bytes).
// Target unit: Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp
// (same cl line). Below: the declarations added to that file (Iface6 gap50 ->
// virtual void rva0046BC30() = 0; plus the members shown), then the body.
// Remaining diff: SSE CSE register choice in the rotation (12 lines).
#if 0
	bool GetGoalPosition(Coord3D *out) const;
	float GetGoalAngle() const;
	int GetGoalLayer() const;
	void rva0028ACEE(const Coord3D *pos, int layer);
class Rva0046ACF6
{
public:
	int rva0046ACF6(int id);
};
	virtual void rva0046BC30() = 0; virtual void rva0046BD70() = 0; virtual void rva0046BE0E() = 0; virtual void gap53() = 0;
	virtual void rva0046BC30();
	__forceinline const _STL::list<Object *> *slot70Items()
	{
		Rva0046247DPair p;
		rva0046D27ASlot70(p);
		return p.m04;
	}

extern "C" double __cdecl sin(double angle);
extern "C" double __cdecl cos(double angle);
struct Rva0046BC30Offset
{
	Rva0046BC30Offset() {}
	Rva0046BC30Offset(const Rva0046BC30Offset &o) { x = o.x; y = o.y; }
	void rotSC(float s, float c) { float nx = c * x - s * y; float ny = c * y + s * x; x = nx; y = ny; }
	void rotSC2(float s, float c) { float tx = x; x = x * c - y * s; y = tx * s + y * c; }
	void rotSC3(float s, float c) { float tx = x; x = c * x - s * y; y = c * y + s * tx; }
	void rotate(float angle)
	{
		struct Trig
		{
			float sine;
			float cosine;
		} trig;
		trig.sine = (float)sin((double)angle);
		trig.cosine = (float)cos((double)angle);
		__asm
		{
			fld angle
			fsincos
			fstp trig.cosine
			fstp trig.sine
		}
		float &sine = trig.sine;
		float &cosine = trig.cosine;
		float rx = x * cosine - y * sine;
		y = y * cosine + x * sine;
		x = rx;
	}
	float x;
	float y;
};
//V{
//V}
#endif
void HordeContain::rva0046BC30()
{
	if (m_2A0 != 0)
		return;
	Coord3D goal;
	if (!m_object->GetGoalPosition(&goal))
		return;
	float angle = m_object->GetGoalAngle();
	Rva0046247DPair p;
	rva0046D27ASlot70(p);
	for (_STL::list<Object *>::const_iterator it = p.m04->begin(); it != p.m04->end(); ++it)
	{
		Object *obj = *it;
		if (obj->isEffectivelyDead())
			continue;
		int index = ((Rva0046ACF6 *)(UpdateModule *)this)->rva0046ACF6(obj->getID());
		Rva0046BC30Offset offset;
		const Rva0046BC30Offset *src = (const Rva0046BC30Offset *)((const char *)&m_188Begin[index] + 4);
		offset.x = src->x;
		offset.y = src->y;
		float sine = (float)sin((double)angle);
		float cosine = (float)cos((double)angle);
		__asm
		{
			fld angle
			fsincos
			fstp cosine
			fstp sine
		}
		float nx = cosine * offset.x - sine * offset.y;
		float ny = cosine * offset.y;
		ny += sine * offset.x;
		offset.y = ny;
		offset.x = nx;
		Coord3D pos;
		pos.x = goal.x + offset.x;
		pos.y = goal.y + offset.y;
		pos.z = goal.z;
		obj->rva0028ACEE(&pos, m_object->GetGoalLayer());
	}
}

#if 0
// Notes 2026-10-10 w5-g3 (variant score ~.90, rotation scheduling only):
// slot proven 50 by reading vtable 0x00C44C58 (rename iface gap50, override in
// HordeContain for +0x11C this). Record fields: float *offs =
// &m_188Begin[idx].m_04 with r0 = offs[0], r4 = offs[1] reproduces the single
// imul plus folded +4 lea (rec188/begin188 calls add a call; record-address
// first loses the fold). rva0028ACEE is rowed (int,int), so a landing TU must
// declare void rva0028ACEE(int,int) and cast the position. Trig homes come
// free from the asm block; sin/cos CRT calls plus fsincos is the
// Rva00468E98Rotate idiom, exact. Tried for the rotation: plain, parenthesized,
// xoff/yoff locals, sine/cosine refs (all land the frame, prologue, calls,
// homes; only the SSE mul/add schedule differs).
//
// Variant body (needs the decls above plus sin/cos externs and float m_04/m_08
// on Rva00472329Record):
void HordeContain::rva0046BC30_g3()
{
	if (m_2A0 != 0)
		return;
	Coord3D goal;
	if (!m_object->GetGoalPosition(&goal))
		return;
	float angle = m_object->GetGoalAngle();
	Rva0046247DPair p;
	rva0046D27ASlot70(p);
	for (_STL::list<Object *>::const_iterator it = p.m04->begin(); it != p.m04->end(); ++it)
	{
		Object *obj = *it;
		if (obj->isEffectivelyDead())
			continue;
		int idx = ((Rva0046ACF6 *)(UpdateModule *)this)->rva0046ACF6(obj->getID());
		float *offs = &m_188Begin[idx].m_04;
		float r0 = offs[0];
		float r4 = offs[1];
		float s = (float)sin(angle);
		float c = (float)cos(angle);
		__asm
		{
			fld angle
			fsincos
			fstp c
			fstp s
		}
		Coord3D pos;
		float &sine = s;
		float &cosine = c;
		pos.x = goal.x + r0 * cosine - r4 * sine;
		pos.y = goal.y + r4 * cosine + r0 * sine;
		pos.z = goal.z;
		obj->rva0028ACEE((int)&pos, m_object->GetGoalLayer());
	}
}
#endif
