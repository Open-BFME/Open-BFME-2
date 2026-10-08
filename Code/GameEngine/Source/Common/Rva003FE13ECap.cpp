// cl: /MD
//
// ?rva003FE13E@Rva003FE13E@@QAEMXZ @0x003FE13E 129B. __thiscall float method:
// builds a Coord2D from ([+0x50]-[+0x18], [+0x54]-[+0x1C]), takes its rowed
// length as dist, loads [+0x58] as cap, gates a scale by the rowed Keyboard
// check on g_009FE720 plus GlobalData +0x88, and returns min(dist, cap).
// Evidence: rowed length and Keyboard callees; extern names from the packet;
// SSE shape needs arch:SSE2; caller 0x003FE2CF.
// Structural inference: the difference is filled from +0x50/+0x54 before the
// subtractions, the cap scale is the 10.0f literal at 0x00BC2428 applied as
// cap *= 10.0f, and the result is an STL-style min returning the selected
// operand by reference; d lives in its own block so dist reuses its slot.
class Coord2D
{
public:
	float m_x;
	float m_y;
	float length() const;
};

class Keyboard
{
public:
	bool isShift();
};

class Rva0025CEEFHost : public Keyboard
{
};

extern class Keyboard *TheKeyboard;

class GlobalData
{
public:
	char m_pad00[0x88];
	unsigned char m_88;
};

// Native 0x003FE18A reads VA 0x00DFE758 before the +0x88 flag check.
// GameClient.cpp owns this singleton with the class GlobalData spelling.
extern GlobalData *TheWritableGlobalData;

class Rva003FE13E
{
	float m_pad00[6];
	float m_18;
	float m_1C;
	char m_pad20[0x50 - 0x20];
	float m_50;
	float m_54;
	float m_58;

public:
	float rva003FE13E();
};

template <class T> inline const T &Rva003FE13EMin(const T &a, const T &b)
{
	return b < a ? b : a;
}

float Rva003FE13E::rva003FE13E()
{
	float dist;
	{
		Coord2D d;
		d.m_x = m_50;
		d.m_y = m_54;
		d.m_x -= m_18;
		d.m_y -= m_1C;
		dist = d.length();
	}
	float cap = m_58;
	if ((*(Rva0025CEEFHost **)&TheKeyboard)->isShift()) {
		if (TheWritableGlobalData->m_88 != 0)
			cap *= 10.0f;
	}
	return Rva003FE13EMin(dist, cap);
}
