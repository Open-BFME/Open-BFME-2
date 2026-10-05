// cl: /Ireference/shims/bfme2_ascii /O1 /EHs
// stlport
//
// Retail 0x0020A7C9 (144 bytes): ScriptEngine clears the +0x1A120 vector,
// then records each world object's non-empty name and pointer. Target calls
// the already-matched vector erase at 0x00207F0D, GameLogic::getFirstObject
// at 0x0023CAD2, and the rowed string/vector helpers used by the loop.
#include "ascii_string.h"
#include <vector>

struct FXBoneInfo
{
	AsciiString m_boneName;
	const void *m_template;
};

// This TU only calls the erase implementation owned by FXBoneInfoVectorErase.cpp.
// Keep this view declaration-only so STLport does not emit a second
// __copy_ptrs<FXBoneInfo *> COMDAT here.
namespace _STL
{
template <> class vector<FXBoneInfo, allocator<FXBoneInfo> >
{
public:
	typedef FXBoneInfo *iterator;
	iterator begin() { return m_start; }
	iterator end() { return m_finish; }
	iterator erase(iterator first, iterator last);

private:
	iterator m_start;
	iterator m_finish;
	iterator m_endOfStorage;
};
}

class Object;

struct Rva0020A227Element
{
	AsciiString key;
	Object *obj;
	Rva0020A227Element() : obj(0) {}
};

class Object
{
public:
	Object *getNextObject() { return m_next; }

	char m_pad[0x88];
	AsciiString m_name88;
	Object *m_next;
};

class GameLogic
{
public:
	Object *getFirstObject();
};
extern GameLogic *TheGameLogic;

class ScriptEngine
{
public:
	void rva0020A7C9();

private:
	char m_pad[0x1A120];
	_STL::vector<Rva0020A227Element> m_vec;
};

void ScriptEngine::rva0020A7C9()
{
	_STL::vector<FXBoneInfo> &fv = (_STL::vector<FXBoneInfo> &)m_vec;
	fv.erase(fv.begin(), fv.end());
	GameLogic *g = TheGameLogic;
	if (g == 0)
		return;
	Object *obj = g->getFirstObject();
	if (obj == 0)
		return;
	for (; obj != 0; obj = obj->getNextObject()) {
		if (((StringBase<char> *)&obj->m_name88)->isEmpty())
			continue;
		Rva0020A227Element tmp;
		tmp.key.set(obj->m_name88);
		tmp.obj = obj;
		m_vec.push_back(tmp);
	}
}
