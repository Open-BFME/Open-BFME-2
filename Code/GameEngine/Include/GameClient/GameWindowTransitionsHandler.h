// GameWindowTransitionsHandler: canonical declarations for the members 19 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_GAMEWINDOWTRANSITIONSHANDLER_H
#define CANONICAL_GAMEWINDOWTRANSITIONSHANDLER_H

class AsciiString;
namespace _STL {
template <class T> class allocator;
template <class T, class A> class list;
}

class GameWindowTransitionsHandler
{
public:
	bool isFinished();
	void rva001DC57C(_STL::list<int, _STL::allocator<int> > *dest);
	void remove(AsciiString groupName, bool skipPending);
	void reverse(AsciiString groupName);
	void setGroup(AsciiString groupName, bool immediate);
};

#endif // CANONICAL_GAMEWINDOWTRANSITIONSHANDLER_H
