// cl: /O1 /arch:SSE /MD /DNDEBUG
//
// ?rva004A1A69@Rva004A1A69@@QAEXPAVBuildListInfo@@@Z @0x004A1A69 174B.
// Random angle in [0, 2pi), then cos/sin times the int at info+0xC.

enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0
};

class Object
{
public:
	void setStatus(ObjectStatusTypes status, bool set);
};

class Drawable;

class Thing
{
public:
	Drawable *getDrawable() const;
};

class BuildListInfo
{
public:
	char m_pad[0x74];
	int m_74;
};

class Arg2;

class Rva002710AE
{
public:
	void rva002710AE(BuildListInfo *info, Arg2 *arg);
};

class Rva004A1A69Info
{
public:
	char m_pad[0xC];
	int m_c;
	char m_gap[0x5C];
	unsigned char m_6c;
};

extern float g_00BC746C;

float GetGameLogicRandomValueReal(float lo, float hi, char *file, int line);
float Cos(float angle);
float Sin(float angle);

class Rva004A1A69
{
public:
	void rva004A1A69(BuildListInfo *info);
	char m_pad[4];
	Rva004A1A69Info *m_info;
	Object *m_obj;
	char m_gap[0x18];
	int m_24;
	float m_28;
	float m_2c;
	float m_30;
};

void Rva004A1A69::rva004A1A69(BuildListInfo *info)
{
	if (info == 0)
		return;
	float twoPi = g_00BC746C;
	int id = info->m_74;
	Rva004A1A69Info *rec = m_info;
	m_24 = id;
	float angle = GetGameLogicRandomValueReal(
		0.0f, twoPi,
		(char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\SlavedUpdate.cpp",
		0x35E);
	m_28 = 0.0f;
	m_2c = 0.0f;
	m_30 = 0.0f;
	m_28 += Cos(angle) * (float)rec->m_c;
	m_2c += Sin(angle) * (float)rec->m_c;
	if (rec->m_6c != 0)
		m_obj->setStatus((ObjectStatusTypes)3, true);
	Drawable *drawable = ((Thing *)m_obj)->getDrawable();
	if (drawable != 0)
		((Rva002710AE *)drawable)->rva002710AE(info, (Arg2 *)((char *)this + 0x20));
}
