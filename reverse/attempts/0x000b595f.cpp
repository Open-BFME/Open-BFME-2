// ?rva000B595F@Rva000B595F@@QAEXXZ
// partial score=0.98 date=2026-10-07
// cl: /MD /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7
// ?rva000B595F@Rva000B595F@@QAEXXZ at 0x000B595F, 275 bytes.
// Retail vtable evidence places this body in several W3D draw hierarchies,
// without proving one owning class or original method name. The field offsets,
// GameEngine call, and build-rate call below follow the retail instructions.

class Rva00225D38Host
{
public:
	bool rva00225D38();
};

class GameEngine
{
public:
	private: bool rva00225D38();
	friend class Rva000B595F;

private:
	unsigned char m_unmodelled00[0x3C];
public:
	float m_buildRate;
};

extern GameEngine *TheGameEngine;

class Rva0028B6A2Host
{
public:
	float rva0028B6A2();

private:
	unsigned char m_unmodelled00[0x280];
public:
	float m_buildProgress;
};

class Rva000B595FDrawable
{
public:
	unsigned char m_unmodelled00[0xFC];
	Rva0028B6A2Host *m_buildObject;
};

class Rva000B595FModuleData
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual int getNumFrames();
};

class Rva000B595F
{
public:
	void rva000B595F();

private:
	unsigned char m_unmodelled00[8];
	Rva000B595FDrawable *m_drawable;
	unsigned char m_unmodelled0C[0x110 - 0x0C];
	Rva000B595FModuleData *m_moduleData;
	float m_currentFrame;
	float m_maxFrame;
	unsigned char m_unmodelled11C[0x184 - 0x11C];
	unsigned int m_flags;
	unsigned char m_unmodelled188[0x26C - 0x188];
	float m_buildProgress;
};

void Rva000B595F::rva000B595F()
{
	unsigned int flags = m_flags;
	flags >>= 5;
	if ((flags & 1) != 0 && m_moduleData != 0)
	{
		Rva0028B6A2Host *object = m_drawable->m_buildObject;
		if (object != 0)
		{
			if (TheGameEngine->rva00225D38())
				m_buildProgress = object->m_buildProgress;

			if (m_buildProgress == 0.0f)
			{
				m_maxFrame = 0.0f;
				m_currentFrame = 0.0f;
			}
			else
			{
				float buildRate = object->rva0028B6A2();
				float progressChange = TheGameEngine->m_buildRate * buildRate;
				float scaledProgress = m_buildProgress * 0.01f;
				float progress = progressChange + scaledProgress;
				float one = 1.0f;
				float *selectedProgress = &one;
				if (!(progress > one))
					selectedProgress = &progress;

				float lastFrame = (float)(m_moduleData->getNumFrames() - 1);
				float scaledFrame = lastFrame * *selectedProgress;
				float *selectedFrame = &lastFrame;
				if (!(scaledFrame > lastFrame))
					selectedFrame = &scaledFrame;
				float frame = *selectedFrame;

				if (frame > m_currentFrame)
				{
					m_maxFrame = m_currentFrame;
					m_currentFrame = frame;
				}
			}
		}
	}
}
