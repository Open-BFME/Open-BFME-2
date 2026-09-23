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
// Donor: BFME1 dx8renderer.cpp, Vertex_Split_Table::Peek_Shader.
// Target Add_Mesh calls this value-return helper at 1443D0. CurMatDesc is
// +94; shader arrays and single values are +F8/+98 in that descriptor.
// Keep the donor's inline MeshModelClass wrapper: its returned temporary
// determines the target MSVC 7.1 hidden-result copy sequence.
class ShaderClass {
public:
	unsigned int ShaderBits;
	ShaderClass() : ShaderBits(0) {}
	ShaderClass(const unsigned int bits) : ShaderBits(bits) {}
	ShaderClass(ShaderClass const &other) : ShaderBits(other.ShaderBits) {}
	void Set_NPatch_Enable() { ShaderBits |= 0x20000; }
};
class MeshMatDescClass {
public:
	ShaderClass Get_Shader(int index,int pass) const;
	ShaderClass Get_Single_Shader(int pass) const;
};
class MeshModelClass {
public:
    ShaderClass Get_Shader(int index, int pass) const {
        return (*reinterpret_cast<MeshMatDescClass *const *>(reinterpret_cast<const char *>(this) + 0x94))->Get_Shader(index, pass);
    }

};
class Vertex_Split_Table {
	MeshModelClass *mmc;
	bool npatch_enable;
	unsigned int polygon_count;
	void *polygon_array;
public:
	ShaderClass Peek_Shader(unsigned int index,unsigned int pass);
};
ShaderClass Vertex_Split_Table::Peek_Shader(unsigned int index,unsigned int pass)
{
	char *model = reinterpret_cast<char *>(mmc);
	char *desc = *reinterpret_cast<char **>(model + 0x94);
	unsigned int *shader_array = reinterpret_cast<unsigned int *>(desc + 0xF8);
	if (shader_array[pass] != 0) {
		ShaderClass shader(0x0010441b);
		if (index < *reinterpret_cast<unsigned int *>(model + 0x24))
			shader = mmc->Get_Shader(index,pass);
		if (npatch_enable)
			shader.Set_NPatch_Enable();
		return shader;
	}
	if (!npatch_enable)
		return *reinterpret_cast<ShaderClass *>(desc + 0x98 + pass * 4);
	ShaderClass shader = *reinterpret_cast<ShaderClass *>(desc + 0x98 + pass * 4);
	shader.Set_NPatch_Enable();
	return shader;
}
