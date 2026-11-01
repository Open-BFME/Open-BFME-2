// Retail 0x006E9160.  Fill the three-dword output with the three fixed
// runtime values returned by the neighboring global accessors.

namespace Debug_Statistics
{
	int Get_DX8_Vertices( void );
	int Get_DX8_Skin_Vertices( void );
	int Get_Sorting_Vertices( void );
}

struct Gen_006e9160_Triple
{
	int m_dx8Vertices;
	int m_dx8SkinVertices;
	int m_sortingVertices;
};

void __stdcall Rva006E9160Init( Gen_006e9160_Triple *output )
{
	output->m_dx8Vertices = Debug_Statistics::Get_DX8_Vertices();
	output->m_dx8SkinVertices = Debug_Statistics::Get_DX8_Skin_Vertices();
	output->m_sortingVertices = Debug_Statistics::Get_Sorting_Vertices();
}
