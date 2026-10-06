// cl: /Ireference/shims/bfme2_ascii /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// ??1Rva00427311@@UAE@XZ @0x00427311 129B
// Dtor storing vtable 0x0083C5DC frees WindowVideoMap at +0xc then base.
// Evidence: calls rowed begin 0x00427195 and iterator inc 0x0041E832 releaseBuffer 0x00036410 delete 0x0002FD60 hashtable dtor 0x004271D9 base dtor 0x001B4E74 caller 0x004274AB deleting dtor.
#include <hash_map>
#include "ascii_string.h"

class GameWindow;
class WindowVideo;

class WindowVideoManager
{
public:
	struct hashConstGameWindowPtr
	{
		size_t operator()(const GameWindow *const &) const;
	};
};

class GameEngineDeletingBase
{
public:
	GameEngineDeletingBase();
	virtual ~GameEngineDeletingBase();
};

class Rva004271D9
{
public:
	Rva004271D9();
	~Rva004271D9();
private:
	char m_pad[4];
	void *m_start;
	void *m_finish;
	void *m_end;
};

typedef std::hash_map<const GameWindow *, WindowVideo *,
	WindowVideoManager::hashConstGameWindowPtr,
	std::equal_to<const GameWindow *> > Rva00427311Map;

class Rva00427311 : public GameEngineDeletingBase
{
public:
	Rva00427311();
	virtual ~Rva00427311();
private:
	char m_pad[8];
	Rva004271D9 m_playingVideos;
};

Rva00427311::Rva00427311()
{
}

Rva00427311::~Rva00427311()
{
	Rva00427311Map &map = (Rva00427311Map &)m_playingVideos;
	Rva00427311Map::iterator it = map.begin();
	while (it != map.end())
	{
		AsciiString *p = (AsciiString *)it->second;
		if (p)
			delete p;
		++it;
	}
}
