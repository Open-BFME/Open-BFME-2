// ?rva00262E24@AIUpdateInterface@@QAEXPAUCoord3D@@@Z
// partial score=0.93 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /arch:SSE
struct Coord3D { float x, y, z; };
struct Rva003642DFNode;
struct Rva003642DFResult { Rva003642DFNode *m_node; Coord3D m_pos; };
class Path { public: Rva003642DFResult rva003642DF(float dist); };
class Thing { public: const Coord3D *getUnitDirectionVector2D() const; };
extern float g_00BC736C;
#define VM10(p) virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); virtual void p##4(); virtual void p##5(); virtual void p##6(); virtual void p##7(); virtual void p##8(); virtual void p##9();
class Slot42Target { public: VM10(t0_) VM10(t1_) VM10(t2_) VM10(t3_) virtual void t40(); virtual void t41(); virtual void vslot42(int zero); };
class Object { public: char m_pad00[0x38]; Coord3D m_position; float m_angle; char m_pad48[0x74-0x48]; unsigned int m_id; char m_pad78[0x250-0x78]; Slot42Target *m_ptr250; };
class AIUpdateInterfaceBase { public: VM10(v0_) VM10(v1_) VM10(v2_) VM10(v3_) VM10(v4_) VM10(v5_) VM10(v6_) virtual void v70(); virtual void dummy71(void*a,void*b,void*c); virtual void v72(); virtual void v73(); virtual void v74(); virtual void v75(); virtual void v76(); virtual void v77(); virtual void v78(); virtual void v79(); virtual void v80(); virtual void v81(); virtual void v82(); virtual void v83(); virtual void v84(); virtual void v85(); virtual void v86(); virtual void v87(); virtual void vslot88(); virtual void v89(); VM10(v9_) VM10(v10_) virtual void v110(); virtual bool pb111() const; virtual void v112(); virtual bool pb113() const; virtual bool pb114() const; virtual bool pb115() const; virtual bool pb116() const; virtual void v117(); virtual void v118(); virtual void v119(); VM10(v12_) VM10(v13_) VM10(v14_) virtual void *makeStateMachine(); };
class AIUpdateInterface : public AIUpdateInterfaceBase {
  char m_pad04[4]; Object *m_obj; char m_pad0C[0x30-0x0C]; void *m_machine; void *m2; void *m3; char m_pad3C[0x4C-0x3C]; int m_guardMode; char m_pad50[0x54-0x50]; int m_guardTargetType; Coord3D m_guardPos; char m_pad64[0x140-0x64]; Path *m_path140; char m_pad144[0x198-0x144]; unsigned int m_field198; unsigned int m_field19C; float m_guardAngle; char m_pad1A4[0x1FC-0x1A4]; int m_field1FC; Coord3D m_coord200;
public: void rva00262E24(Coord3D *out); };
// ?rva00262E24@AIUpdateInterface@@QAEXPAUCoord3D@@@Z present-unmatched
void AIUpdateInterface::rva00262E24(Coord3D *out)
{
	Object *obj = m_obj;
	int mode = m_field1FC;
	if (mode == 2 || mode == 4)
	{
		out->x = m_coord200.x;
		out->y = m_coord200.y;
		out->z = m_coord200.z;
		return;
	}
	if (mode == 1)
	{
		Path *path = m_path140;
		if (path != 0)
		{
			Rva003642DFResult tmp = path->rva003642DF(g_00BC736C);
			out->x = tmp.m_pos.x;
			out->y = tmp.m_pos.y;
			out->z = tmp.m_pos.z;
			return;
		}
	}
	const Coord3D *dir = ((Thing *)obj)->getUnitDirectionVector2D();
	float dx = dir->x;
	float dy = dir->y;
	float dz = dir->z;
	float s = g_00BC736C;
	out->x = obj->m_position.x + dx * s;
	out->y = obj->m_position.y + dy * s;
	out->z = obj->m_position.z + dz * s;
}
