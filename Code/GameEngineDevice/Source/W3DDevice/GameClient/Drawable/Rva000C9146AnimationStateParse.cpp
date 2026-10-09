// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva000C9146@@YAXPAVINI@@PAX1PBX@Z retail 0x000C9146..0x000C9240 (250 bytes
// EH cdecl): the INI block parser that the draw-module FieldParse table at
// 0x007CB468 binds to "IdleAnimationState" (userData 1) / "TransitionState"
// (userData 2) / "AnimationState" (userData 0). That table also holds
// ModelConditionState and DefaultModelConditionState (0x000C8914) and
// TrackMarks / ExtraPublicBone / AttachToBoneInAnotherModule; the parser
// sits beside W3DScriptedModelDrawModuleData::parseAttachModel (0x000C8748).
// It stores the userData into the first entry of the native AnimationState
// FieldParse table at VA 0x00DB4EA8 (Animation / StateName / Flags /
// ShareAnimation / EnteringStateFX / BeginScript ...). Then it builds a
// 248-byte BfmePod248 record (rowed ctor 0x000C6A4D and dtor 0x000C6D44) and
// a zeroed 76-byte flag block. AnimationState parses the flags (rowed
// Rva000B937E 0x000B937E). TransitionState takes an optional name token
// (rowed INI::getNextTokenOrNull). The record gets the name at +0 and the
// flags at +4 and is filled by INI::initFromINI from that table. It is
// inserted at the front of the instance's +0x24 record vector for
// IdleAnimationState (rowed insert 0x000C8E19) and appended otherwise
// (rowed push_back 0x000C8DDF).
//
// Evidence: retail body / EH map and the rowed callees. The WB twin
// 0x009261C0 (score 3.0 callgraph) has the same three-way userData split
// and container tail. The WB name is unproven so the parser keeps an
// address-qualified name; parseAnimationState on the scripted draw module
// data is the likely original. The record-position temporary reproduces
// retail evaluating begin() before pushing the record reference.
#include <string.h>
#include "ascii_string.h"

struct FieldParse
{
	const char *token;
	void *parse;
	const void *userData;
	int offset;
};

class INI
{
public:
	const char *getNextTokenOrNull(const char *seps);
	void initFromINI(void *what, const FieldParse *parseTable);
};

class Rva000B937E
{
public:
	void rva000B937E(INI *ini, void *unused);
};

struct Rva000C9146Flags
{
	unsigned int m_words[19];
};

struct BfmePod248
{
	AsciiString m_name;						// +0x00
	Rva000C9146Flags m_flags;				// +0x04
	unsigned char m_rest[0xF8 - 0x50];		// +0x50
	BfmePod248();
	~BfmePod248();
};

namespace _STL
{
template <class T> class allocator;
template <class T, class A> class vector
{
public:
	T *insert(T *position, const T &value);
	void push_back(const T &value);
	T *m_start;
	T *m_finish;
	T *m_end;
};
}

struct Rva000C9146Owner
{
	unsigned char m_pad00[0x24];
	_STL::vector<BfmePod248, _STL::allocator<BfmePod248> > m_states;	// +0x24
};

struct Rva000C9146Position
{
	BfmePod248 *m_position;
	Rva000C9146Position(BfmePod248 *position) : m_position(position) {}
	operator BfmePod248 *() const { return m_position; }
};

extern FieldParse g_00DB4EA8[];

void rva000C9146(INI *ini, void *instance, void *store, const void *userData)
{
	g_00DB4EA8[0].userData = userData;
	BfmePod248 entry;
	Rva000C9146Flags flags;
	memset(&flags, 0, sizeof(flags));
	AsciiString name;
	if ((int)userData == 0)
	{
		reinterpret_cast<Rva000B937E *>(&flags)->rva000B937E(ini, 0);
	}
	else if ((int)userData == 1)
	{
	}
	else if ((int)userData == 2)
	{
		const char *token = ini->getNextTokenOrNull(0);
		if (token)
			name = token;
	}
	entry.m_name = name;
	entry.m_flags = flags;
	ini->initFromINI(&entry, g_00DB4EA8);
	Rva000C9146Owner *owner = static_cast<Rva000C9146Owner *>(instance);
	if ((int)userData == 1)
		owner->m_states.insert(Rva000C9146Position(owner->m_states.m_start), entry);
	else
		owner->m_states.push_back(entry);
}
