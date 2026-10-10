// Open-BFME5: clean C++ conversion of the four-entry CDC cache destructor.

// g_destroy is the import slot __imp__DeleteDC@4 (data ledger); call the
// import directly so nothing dangles.
extern "C" __declspec(dllimport) int __stdcall DeleteDC(void *hdc);

class CDCCache
{
public:
	~CDCCache();

private:
	void *m_allocations[4];
};

CDCCache::~CDCCache()
{
	for (int index = 0; index < 4; ++index)
	{
		if (m_allocations[index] != 0)
			DeleteDC(m_allocations[index]);
	}
}
