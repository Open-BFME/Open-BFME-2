// cl: /G7 /DNDEBUG /MD /EHsc
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// BFME1 donor semantic guide: Vertex_Split_Table texture selection in
// reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/dx8renderer.cpp.
// Target evidence: FUN_00544380 at RVA 0x144380 has a 76-byte body ending
// ret 16; its receiver points to MeshModelClass at +0, and target MeshModelClass
// stores CurMatDesc at +0x94. It forwards an owning RefCountPtr result to the
// matched MeshModelClass texture getters at 0x143560 / 0x0D206A.
class TextureClass {
public:
	void Add_Ref() { ++RefCount; }
	void Release_Ref();
private:
	void *VTable;
	unsigned short RefCount; // target +4
};
template<class T> class RefCountPtr {
public:
	RefCountPtr() : Referent(0) {}
	RefCountPtr(RefCountPtr const &other) : Referent(other.Referent) { if (Referent) Referent->Add_Ref(); }
	~RefCountPtr() { if (Referent) Referent->Release_Ref(); }
	T *Referent;
};
class MeshModelClass {
public:
	RefCountPtr<TextureClass> Peek_Texture(int index,int pass,int stage) const;
	RefCountPtr<TextureClass> Peek_Single_Texture(int pass,int stage) const;
};
class Vertex_Split_Table {
	MeshModelClass *mmc;
	bool npatch_enable;
	unsigned int polygon_count;
	void *polygon_array;
public:
	RefCountPtr<TextureClass> Peek_Texture(unsigned int index,unsigned int pass,unsigned int stage);
};
RefCountPtr<TextureClass> Vertex_Split_Table::Peek_Texture(unsigned int index,unsigned int pass,unsigned int stage)
{
	char *model = reinterpret_cast<char *>(mmc);
	char *desc = *reinterpret_cast<char **>(model + 0x94);
	unsigned int texture_array_index = 0x32 + pass * 2 + stage;
	if (*reinterpret_cast<void **>(desc + texture_array_index * 4) != 0)
		return mmc->Peek_Texture(index,pass,stage);
	return mmc->Peek_Single_Texture(pass,stage);
}
