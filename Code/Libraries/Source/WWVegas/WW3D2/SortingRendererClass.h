// SortingRendererClass: canonical declarations for the members 7 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_SORTINGRENDERERCLASS_H
#define CANONICAL_SORTINGRENDERERCLASS_H

class SphereClass;

class SortingRendererClass
{
public:
	static void Flush();
	static void Insert_Triangles(const SphereClass &, unsigned int, unsigned int, unsigned int, unsigned int);
	static void Insert_Triangles(unsigned short start_index, unsigned short polygon_count, unsigned short min_vertex_index, unsigned short vertex_count);
	static void SetMinVertexBufferSize(unsigned int count);
};

#endif // CANONICAL_SORTINGRENDERERCLASS_H
