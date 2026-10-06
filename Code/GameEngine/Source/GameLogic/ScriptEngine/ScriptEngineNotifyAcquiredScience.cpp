// cl: /DNDEBUG /MD /EHsc
// ?notifyOfAcquiredScience@ScriptEngine@@QAEXHW4ScienceType@@@Z @0x00357F43 27B
// ScriptEngine::notifyOfAcquiredScience: m_acquiredSciences[playerIndex].push_back(science).
// Donor: ZH ScriptEngine::notifyOfAcquiredScience (ScriptEngine.cpp:7258) one-liner.
// Target evidence: callers Player::addScience 0x002AD7D3 and 0x002AE2DC pass
// TheScriptEngine plus Player+0x54 index and ScienceType, callee rowed push_back
// vector<ScienceType> 0x002E01C6, layout +0x1A3A8 stride 0xC from matched dtor
// m_playerVectors[20].

enum ScienceType
{
	SCIENCE_INVALID = -1
};

namespace _STL
{
	template <class T>
	class allocator
	{
	};

	template <class T, class A>
	class vector
	{
	public:
		void push_back(const T &v);

	private:
		void *m_start;
		void *m_finish;
		void *m_endOfStorage;
	};
}

class ScriptEngine
{
public:
	void notifyOfAcquiredScience(int playerIndex, ScienceType science);

private:
	char m_pad[0x1A3A8];
	_STL::vector<ScienceType, _STL::allocator<ScienceType> > m_acquiredSciences[20]; // +0x1A3A8
};

void ScriptEngine::notifyOfAcquiredScience(int playerIndex, ScienceType science)
{
	m_acquiredSciences[playerIndex].push_back(science);
}
