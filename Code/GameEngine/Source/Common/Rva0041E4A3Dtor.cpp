// cl: /O1 /DNDEBUG /MD /EHs
// ??1Rva0041E4A3@@MAE@XZ retail 0x0041E4C4 129B
// Own vftable 0x00C3AEA8 (slot-0 ??_G at 0x0041E545). Global-deletes every
// owned polymorphic entry of the void* vector at +0x0C, clears it through the
// rowed erase 0x0031BD55, frees its storage, then runs the rowed base dtor
// ??1GameEngineDeletingBase@@UAE@XZ 0x001B4E74.
extern "C" void __cdecl free(void *);

namespace _STL
{
	template <class T> class allocator
	{
	};

	template <class T, class A> class vector
	{
	public:
		__forceinline ~vector()
		{
			if (m_start)
				free(m_start);
		}
		T *begin() { return m_start; }
		T *end() { return m_finish; }
		T *erase(T *first, T *last);
		void clear()
		{
			erase(begin(), end());
		}
		T *m_start;
		T *m_finish;
		T *m_endOfStorage;
	};
}

class Rva0041E4A3Entry
{
public:
	virtual ~Rva0041E4A3Entry();
};

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
private:
	char m_pad04[8];
};

class Rva0041E4A3 : public GameEngineDeletingBase
{
protected:
	virtual ~Rva0041E4A3();
private:
	_STL::vector<void *, _STL::allocator<void *> > m_entries; // +0x0C
};

Rva0041E4A3::~Rva0041E4A3()
{
	for (void **it = m_entries.begin(); it != m_entries.end(); ++it)
		::delete static_cast<Rva0041E4A3Entry *>(*it);
	m_entries.clear();
}
