// cl: /O1 /DNDEBUG /MD
//
// ?rva004AB9A2@Rva004AB9A2@@QAEXXZ @0x004AB9A2 51B.
// When the byte at +0x8D is set, register the member at +0x24 with the
// host at g_00DFE1A8, wake on the object at +8, and clear the byte.

class Rva0028572AHost;

class Rva0020D959Host
{
public:
	void rva0020D959(Rva0028572AHost *o);
};

extern Rva0020D959Host *g_00DFE1A8;

class Object;

enum UpdateSleepTime
{
	USLEEP_FOREVER = 0x3FFFFFFF
};

class UpdateModule
{
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
};

class Rva004AB9A2 : public UpdateModule
{
public:
	void rva004AB9A2();

private:
	char m_pad[8];
	Object *m_obj;
	char m_padC[0x24 - 0x0C];
	char m_at24;
	char m_pad25[0x8D - 0x25];
	unsigned char m_flag;
};

void Rva004AB9A2::rva004AB9A2()
{
	if (m_flag == 0)
		return;
	g_00DFE1A8->rva0020D959((Rva0028572AHost *)&m_at24);
	setWakeFrame(m_obj, USLEEP_FOREVER);
	m_flag = 0;
}
