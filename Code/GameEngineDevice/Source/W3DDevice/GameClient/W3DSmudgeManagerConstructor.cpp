// cl: /Ob0

// Class views mirror the kept copy in W3DSmudge.cpp (Zero Hour W3DSmudge.h /
// Smudge.h): SmudgeManager carries init/reset plus inline empty
// ReleaseResources/ReAcquireResources after the dtor, and W3DSmudgeManager
// overrides dtor/init/reset. The same virtual order keeps the vftable the
// linked build keeps.
class SmudgeManager
{
public:
	SmudgeManager();
	virtual ~SmudgeManager();
	virtual void init();
	virtual void reset();
	virtual void ReleaseResources();
	virtual void ReAcquireResources();

private:
	char m_pad[0x20];
};

class W3DSmudgeManager : public SmudgeManager
{
public:
	W3DSmudgeManager();
	virtual ~W3DSmudgeManager();
	virtual void init();
	virtual void reset();
	void ReleaseResources(void);
	void ReAcquireResources(void);

private:
	void *m_smudgeGroup;
	void *m_posBuffer;
	void *m_RGBABuffer;
	void *m_sizeBuffer;
	void *m_indexBuffer;
	int m_backBufferWidth;
	int m_backBufferHeight;
	unsigned int m_probeColor;
};

W3DSmudgeManager::W3DSmudgeManager()
{
	m_smudgeGroup = 0;
	m_posBuffer = 0;
	m_RGBABuffer = 0;
	m_sizeBuffer = 0;
	m_indexBuffer = 0;
	m_backBufferWidth = 0;
	m_backBufferHeight = 0;
	m_probeColor = 0x00FFEEDD;
}
