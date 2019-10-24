#include "Scene.h"

#include "ShaderEyelight.h"
#include "ShaderPhong.h"
#include "PrimTriangle.h"

#include <fstream>

void CScene::ParseOBJ(const std::string& fileName)
{
	std::cout << "Parsing OBJFile : " << fileName << std::endl;

	std::shared_ptr<IShader> pShader = std::make_shared<CShaderEyelight>(RGB(1, 1, 1));

	std::ifstream fileN(fileName);
	if(!fileN){
		std::cout << "Wrong Path!/Incorrect File Name!";
	}
	std::vector<Vec3f> vertices; // a vector of Vec3f-s
	std::vector<int> fx, fy, fz; // used to store the triangle coordinates
	int n = 0; // number of f elements
	while(!fileN.eof()){
		char line;
		fileN >> line; // first character of every line indeed is a letter
		if (line == 'v'){
			Vec3f vertex;
			for (int i=0; i<3; i++){ // read for x, y, z coordinates
				fileN >> vertex[i];
				vertex[i] *= 100; // perform a scaling
				// by trial and error conclude that factorizing is needed
			}
			vertices.push_back(vertex); // add tje vertexes to the huge vector
		}
		else if (line == 'f'){
			int x, y, z;
			fileN >> x >> y >> z;
			// add the coordinates to the vector
			fx.push_back(x);
			fy.push_back(y);
			fz.push_back(z);
			n++;
		}
	}
	for (int i =0; i < n ; i++){ // size of any f-vector is n
		Add(std::make_shared<CPrimTriangle>(vertices[fx[i]-1],
			vertices[fy[i]-1], vertices[fz[i]-1], pShader));
	}

	std::cout << "Finished Parsing" << std::endl;
	fileN.close();
}


/*
refering to the documentation:

v x y z
- specifies a vertex by its three coordinates.
- just points in space

vt u v [w]
- UV (and optionally W) mapping
- grouped with a vertex in a 'f' face command

vn x y z
- specifies a normal vector

f v1[/vt1][/vn1] v2[/vt2][/vn2] v3[/vt3][/vn3]
- specifies a polygon made from the verticies listed
- vt - says how to map the texture at this point
- vn - specifies a normal at this point


*/
