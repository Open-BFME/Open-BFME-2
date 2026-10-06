// cl: /DNDEBUG /MD /GX
// RenderableRiverArea::createTexture, retail 0x0007EEBE, 119 bytes.
// Per-index particle texture load: string holder at +0x40 via rowed
// Rva0030BBA9 getter, skip when isEmpty, filename at buf+8 or "",
// BFME2LoadParticleTexture into temp then RefCountPtr op= to slot +0x44[i].
// The slots are BFME2ParticleTextureHandle (the loader's return type): its
// implicit inline copy-assign forwards to the rowed RefCountPtr op= and forms
// the slot address before the push, as retail does. Callers 0x82061/0x820CA loop 4 entries with set insert.
class Rva0030BBA9
{
public:
	void *rva0030BBA9(int i);
};

template <typename T>
class StringBase
{
public:
	bool isEmpty() const;
	const char *m_data;
};

typedef StringBase<char> AsciiString;

class TextureBaseClass
{
public:
	void Release_Ref();
};

class TextureClass : public TextureBaseClass
{
	int m_pad[2];
};

template <class T>
class RefCountPtr
{
public:
	const RefCountPtr &operator=(const RefCountPtr &other);
	~RefCountPtr() { if (m_ptr) m_ptr->Release_Ref(); }
	T *m_ptr;
};

class BFME2ParticleTextureHandle : public RefCountPtr<TextureClass>
{
};

BFME2ParticleTextureHandle __cdecl BFME2LoadParticleTexture(const char *filename, int a, int b);

class RenderableRiverArea
{
public:
	void createTexture(int index);
private:
	char m_pad[0x40];
	Rva0030BBA9 *m_holder;
	BFME2ParticleTextureHandle m_textures[4];
};

void RenderableRiverArea::createTexture(int index)
{
	AsciiString *s = (AsciiString *)m_holder->rva0030BBA9(index);
	if (!s->isEmpty()) {
		const char *name = s->m_data ? s->m_data + 8 : "";
		m_textures[index] = BFME2LoadParticleTexture(name, 0, 0);
	}
}
