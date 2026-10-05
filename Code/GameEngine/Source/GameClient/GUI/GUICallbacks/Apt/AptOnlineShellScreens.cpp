// cl: /O1 /DNDEBUG /MD
//
// BFME2's online shell Apt callback "AptOnline::ShellUnloadScreen",
// 0x005171A3, bound by that name as a member pointer by the shell's
// registration; that binding is its only reference. The class is named for
// the string's prefix (AptOnlineShellCallbacks.cpp views the same object).

extern "C" int __cdecl strcmp(const char *left, const char *right);

namespace _STL
{
template <class T> class allocator;
template <class T, class A> class vector
{
public:
	// Rowed 0x001FF51F.
	T *erase(T *position);

	T *m_start;
	T *m_finish;
	T *m_end;
};
}

// A loaded sub-screen: its name at +0x5C, deleted through vslot 0 and a
// separate operator delete (AnimateWindowManager.cpp's spelling).
struct AptOnlineSubScreen
{
	virtual void *deleteInstance(int flags);

	unsigned char m_pad04[0x5C - 0x04];
	const char *m_name; // +0x5C
};

class AptOnline
{
public:
	void ShellUnloadScreen(const char *name);

private:
	unsigned char m_pad000[0x280];
	_STL::vector<void *, _STL::allocator<void *> > m_screens; // +0x280
	unsigned char m_pad28c[0x290 - 0x28C];
	AptOnlineSubScreen *m_current; // +0x290
};

// Retail 0x005171A3, 100 bytes: "AptOnline::ShellUnloadScreen" deletes the
// loaded sub-screen with that name.
void AptOnline::ShellUnloadScreen(const char *name)
{
	for (void **it = m_screens.m_start; it != m_screens.m_finish; ++it)
	{
		AptOnlineSubScreen *screen = (AptOnlineSubScreen *)*it;
		const char *screenName = screen->m_name;
		if (strcmp(screenName, name) == 0)
		{
			if (m_current == screen)
				m_current = 0;
			::operator delete(screen->deleteInstance(0));
			m_screens.erase(it);
			return;
		}
	}
}
