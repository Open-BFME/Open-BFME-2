// cl: /DNDEBUG /MD

// ??0Path@@QAE@XZ, retail 0x00363DC8, 49 bytes. Path constructor: clears the
// node list and cached-point state. Donor: BFME1 AIPathfind.cpp Path::Path
// (m_path NULL, m_pathTail NULL, m_isOptimized FALSE plus cpop zeroing).
// Target evidence: new(0x28) then this ctor at 0x00265820 in 0x002657CE and
// at 0x002EDF01 in 0x002EDEAB, each followed by Path::appendNode 0x002655E3
// with pool 0x00A01E94; layout head +4 tail +8 optimized +0xC matches
// PathAppendNode.cpp and PathPrependNode.cpp; dtor ??1Path@@QAE@XZ at
// 0x00364A89. /O1 gives or [0x24],-1 for the -1 store, /arch:SSE gives
// xorps+movss for the float zeroes.

typedef int Int;
typedef float Real;
typedef bool Bool;

struct PathNode
{
	PathNode *m_next;
};

class Path
{
public:
	Path();

private:
	void *m_unknown00;
	PathNode *m_path;
	PathNode *m_pathTail;
	Bool m_isOptimized;
	Bool m_unknown0D;
	Int m_unknown10;
	Real m_unknown14;
	Real m_unknown18;
	Real m_unknown1C;
	Real m_unknown20;
	Int m_unknown24;
};

Path::Path()
{
	m_unknown24 = -1;
	m_unknown00 = 0;
	m_path = 0;
	m_pathTail = 0;
	m_isOptimized = false;
	m_unknown0D = false;
	m_unknown10 = 0;
	m_unknown14 = 0.0f;
	m_unknown18 = 0.0f;
	m_unknown1C = 0.0f;
	m_unknown20 = 0.0f;
}
