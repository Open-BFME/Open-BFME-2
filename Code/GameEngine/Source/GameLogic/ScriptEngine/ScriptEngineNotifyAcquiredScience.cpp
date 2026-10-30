// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// ?notifyOfAcquiredScience@ScriptEngine@@QAEXHW4ScienceType@@@Z @0x00357F43 27B
// ScriptEngine::notifyOfAcquiredScience: m_acquiredSciences[playerIndex].push_back(science).
// Donor: ZH ScriptEngine::notifyOfAcquiredScience (ScriptEngine.cpp:7258) one-liner.
// Target evidence: callers Player::addScience 0x002AD7D3 and 0x002AE2DC pass
// TheScriptEngine plus Player+0x54 index and ScienceType, callee rowed push_back
// vector<ScienceType> 0x002E01C6, layout +0x1A3A8 stride 0xC from matched dtor
// m_playerVectors[20].

#include <vector>

enum ScienceType
{
	SCIENCE_INVALID = -1
};

namespace _STL
{
	// Bind vector<ScienceType>::push_back to the rowed worker at 0x002E01C6.
	// Declaration only: the definition lives in the row owner.
	template <class T, class A> class vector;
	template <> class vector<ScienceType, allocator<ScienceType> >
	{
	public:
		void push_back(const ScienceType &v);
	private:
		ScienceType *m_start;
		ScienceType *m_finish;
		ScienceType *m_endOfStorage;
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
