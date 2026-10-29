// cl: /MD
// ?rva000B7074@Rva000B7074@@QAEXXZ 0x000B7074 153B evidence: chain via 0x000B4E23 rowed; +0x9c init via 1.0f then f1 gt0 then f2 eq0 via 0x0028AC7D and 0x002931F5 false then comiss 0.01f div mul g_00DBA4F0 via 0x000B2F38; neighbours 0x000B7029/0x000B7539
extern float g_00DBA4F0;
// g_00DBA4F0: matched references place it at VA 0xdba4f0 (retail .data initial value 200.0f).
float g_00DBA4F0 = 200.0f;

class Rva000B4E23
{
public:
	float rva000B4E23();
};
class Rva000B2F38
{
public:
	bool rva000B2F38(float v);
};
class Object
{
public:
	float rva0028AC7D() const;
	Object *rva002931F5(bool b);
};
struct Cont000B7074
{
	char _p0[0xfc];
	Object *m_obj;
};
class Rva000B7074
{
	char _p0[8];
	Cont000B7074 *m_cont;
	char _p1[0x9c - 8 - 4];
	float m_9c;
public:
	void rva000B7074();
};

void Rva000B7074::rva000B7074()
{
	m_9c = 1.0f;
	float dist = ((Rva000B4E23 *)this)->rva000B4E23();
	if (dist > 0.0f)
	{
		Cont000B7074 *drawable = m_cont;
		Object *object = drawable->m_obj;
		if (object != 0)
		{
			float speed = object->rva0028AC7D();
			if (speed == 0.0f)
			{
				Object *p = object->rva002931F5(false);
				if (p != 0)
					speed = p->rva0028AC7D();
			}
			if (speed > 0.01f)
			{
				float desiredDurationInMsec = dist / speed;
				desiredDurationInMsec *= g_00DBA4F0;
				((Rva000B2F38 *)this)->rva000B2F38(desiredDurationInMsec);
			}
		}
	}
}
