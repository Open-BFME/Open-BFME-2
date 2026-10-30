// cl: /O1 /G7 /arch:SSE /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva003F2F24@Rva003F3F03@@QAEXXZ @0x003F2F24 230B
// Post-INI expansion of the two point lists at +0xE4 and +0xF0 (the member the rowed
// Rva003F3F03::rva003F3F03 runs right after initFromINI): for each list, five passes append
// a copy of every point from the pass start offset by a quarter-turn corner of the square
// (x+d,y-d / x-d,y-d / x+d,y+d / x-d,y+d by pass % 4), d = 0.707 * the float at +0xF4 of the
// singleton at 0x00DFE1C8 (TheLivingWorldManager). Evidence: target bytes and WB debug body
// 0103C4E0 (unnamed) loop/switch structure; push_back provider 0x00539A2E is the vector<BfmeE8>
// body (8-byte elements); the point is a float pair stored through the 8-byte record.
// The class name is the existing pin spelling; the d scaling meaning is inferred.
#include <vector>
struct BfmeE8 {unsigned int a, b;};
namespace _STL {
template<> void vector<BfmeE8>::push_back(const BfmeE8 &);
}

struct Rva003F2F24Point
{
	float x, y;
};

class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;

struct Rva003F2F24ManagerView
{
	char m_pad[0xF4];
	float m_f4;
};

class Rva003F3F03
{
public:
	void rva003F2F24();

private:
	char m_pad[0xE4];
	_STL::vector<BfmeE8> m_e4;
	_STL::vector<BfmeE8> m_f0;
};

void Rva003F3F03::rva003F2F24()
{
	for (int i = 0; i < 2; ++i)
	{
		_STL::vector<BfmeE8> &points = i == 0 ? m_e4 : m_f0;
		int count = points.size();
		float offset = ((Rva003F2F24ManagerView *)TheLivingWorldManager)->m_f4 * 0.707f;
		for (int pass = 0; pass < 5; ++pass)
		{
			for (int j = 0; j < count; ++j)
			{
				const Rva003F2F24Point *src = (const Rva003F2F24Point *)&points[j];
				{
					Rva003F2F24Point point;
					point.x = src->x;
					point.y = src->y;
					switch (pass % 4)
					{
					case 0:
						point.x += offset;
						point.y -= offset;
						break;
					case 1:
						point.x -= offset;
						point.y -= offset;
						break;
					case 2:
						point.x += offset;
						point.y += offset;
						break;
					case 3:
						point.x -= offset;
						point.y += offset;
						break;
					}
					points.push_back(*(BfmeE8 *)&point);
				}
			}
		}
	}
}
