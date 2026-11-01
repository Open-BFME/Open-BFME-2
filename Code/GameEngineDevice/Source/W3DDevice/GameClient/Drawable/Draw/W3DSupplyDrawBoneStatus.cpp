// cl: /Ireference/shims/bfme2_ascii /GX /MD /DNDEBUG /O1 /arch:SSE /G7
// Native 0x000CAFA6..0x000CB0EE (RET 8), vtable slot 8 at 0x007CBEF8.
// Donor (semantic guide only): Zero Hour W3DSupplyDraw::updateDrawModuleSupplyStatus
// (maxSupply, currentSupply): count the supply bones once, show
// ceil(total * current / max) of them and walk the changed index range.
// Target deltas from retail: the receiver is a sub-interface (module data via
// this-8 +0x188 bone prefix, drawable via this-4), there is no base-class call,
// and each "%s%02d" name goes to virtual +0x88 as (name, !hide, 0, 0.0f, 0.0f)
// instead of a hide/show list. Statement shapes from the WorldBuilder twin
// 0x00916BA0: reference min/max helpers over the bone counts, the bone-prefix
// str() inline in both calls and a bool hide flag. Class and method keep
// address-derived names; target identity of the receiver is unproven.
#include <stdio.h>
#include <math.h>

struct Coord3D;
class Matrix3D;

#include "../../../../../../GameEngine/Include/GameClient/Drawable.h"

struct StringHeader
{
	int refs;
	unsigned short length;
	unsigned short capacity;
	char data[1];
};

template <class T>
class StringBase
{
public:
	StringHeader *m_data;
	StringBase(const StringBase<T> &that);
	StringBase(const char *text);
	~StringBase();
	const char *c_str() const { return m_data ? m_data->data : ""; }
	const char *str() const { return m_data ? m_data->data : ""; }
};

class Rva000CAFA6
{
public:
	virtual void pad00(); virtual void pad01(); virtual void pad02(); virtual void pad03();
	virtual void pad04(); virtual void pad05(); virtual void pad06(); virtual void pad07();
	virtual void pad08(); virtual void pad09(); virtual void pad10(); virtual void pad11();
	virtual void pad12(); virtual void pad13(); virtual void pad14(); virtual void pad15();
	virtual void pad16(); virtual void pad17(); virtual void pad18(); virtual void pad19();
	virtual void pad20(); virtual void pad21(); virtual void pad22(); virtual void pad23();
	virtual void pad24(); virtual void pad25(); virtual void pad26(); virtual void pad27();
	virtual void pad28(); virtual void pad29(); virtual void pad30(); virtual void pad31();
	virtual void pad32(); virtual void pad33();
	virtual void setFrame(const StringBase<char> &name, bool reverse, int flags, float start, float end);
	char m_pad04[0x2D8];
	int m_totalBones;
	int m_lastNumberShown;
	void updateDrawModuleSupplyStatus(int maxSupply, int currentSupply);
};

template <class T> inline const T &BfmeMin(const T &lhs, const T &rhs) { return rhs < lhs ? rhs : lhs; }
template <class T> inline const T &BfmeMax(const T &lhs, const T &rhs) { return lhs > rhs ? lhs : rhs; }
void Rva000CAFA6::updateDrawModuleSupplyStatus(int maxSupply, int currentSupply)
{
	char *owner = *(char **)((char *)this - 8);
	StringBase<char> prefix(*(StringBase<char> *)(owner + 0x188));
	if (m_totalBones == -1) {
		const char *name = prefix.str();
		Drawable *draw = *(Drawable **)((char *)this - 4);
		m_totalBones = draw->getPristineBonePositions(name, 1, 0, 0, 0x7fffffff, 0);
		m_lastNumberShown = m_totalBones;
	}
	float scaled = (float)currentSupply / (float)maxSupply * m_totalBones;
	currentSupply = (int)(float)ceil(scaled);
	currentSupply = BfmeMin(m_totalBones, currentSupply);
	if (currentSupply != m_lastNumberShown) {
		int low = BfmeMin(currentSupply, m_lastNumberShown);
		int high = BfmeMax(m_lastNumberShown, currentSupply);
		bool hide = currentSupply < m_lastNumberShown;
		for (int i = low + 1; i <= high; ++i) {
			char buffer[16];
			sprintf(buffer, "%s%02d", prefix.str(), i);
			StringBase<char> animationName(buffer);
			setFrame(animationName, !hide, 0, 0.0f, 0.0f);
		}
		m_lastNumberShown = currentSupply;
	}
}
