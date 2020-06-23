#include "stdafx.h"
#include "Model.h"

Model::Model()
{
	offsetPos.x = 0;
	offsetPos.y = 0;
	offsetPos.z = 0;
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_IBO);
}

Model::~Model()
{
	glDeleteBuffers( 1, &m_VBO );
	glDeleteBuffers( 1, &m_IBO );
}

void Model::InitModel(char* filename)
{
	int buffer;
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");
	}
	else {
		// Read number of vertices
		fscanf_s(file, "NrVertices: %d", &m_verticesCount);
		//printf("Scanning %d vertices\n", m_verticesCount);
		Vertex *verticesData = new Vertex[m_verticesCount];
		for (int i = 0; i < m_verticesCount; i++) {
			// Read vertex data with specified format
			fscanf_s(file, "%d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];", &buffer,
				&verticesData[i].pos.x, &verticesData[i].pos.y, &verticesData[i].pos.z,
				&verticesData[i].normal.x, &verticesData[i].normal.y, &verticesData[i].normal.z,
				&verticesData[i].binormal.x, &verticesData[i].binormal.y, &verticesData[i].binormal.z,
				&verticesData[i].tangent.x, &verticesData[i].tangent.y, &verticesData[i].tangent.z,
				&verticesData[i].uv.x, &verticesData[i].uv.y);
			// Offset position
			verticesData[i].pos.x += offsetPos.x;
			verticesData[i].pos.y += offsetPos.y;
			verticesData[i].pos.z += offsetPos.z;
			// All color is set to green
			/*printf("Vertex %d scanned, values: %f %f %f, %f %f %f, %f %f %f, %f %f %f, %f %f\n", buffer,
				verticesData[i].pos.x, verticesData[i].pos.y, verticesData[i].pos.z,
				verticesData[i].normal.x, verticesData[i].normal.y, verticesData[i].normal.z,
				verticesData[i].binormal.x, verticesData[i].binormal.y, verticesData[i].binormal.z,
				verticesData[i].tangent.x, verticesData[i].tangent.y, verticesData[i].tangent.z,
				verticesData[i].uv.x, verticesData[i].uv.y);*/
		}
		// Read "NrIndices:" and remove
		char s[81];
		fscanf_s(file, "%s", s, 80);
		fscanf_s(file, "%d", &m_indicesCount);
		//fscanf_s(file, "NrIndices:");
		//printf("Scanning %d indices\n", m_indicesCount);
		//m_indicesCount = 2154;
		int *pindices = new int[m_indicesCount];
		for (int i = 0; i < m_indicesCount; i += 3) {
			fscanf_s(file, "%d. %d, %d, %d",
				&buffer, &pindices[i], &pindices[i + 1], &pindices[i + 2]);
			//printf("Index %d scanned\n", buffer);
		}
		fclose(file);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_verticesCount, verticesData,
			GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_indicesCount, pindices,
			GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		if (verticesData) delete[] verticesData;
		if (pindices) delete[] pindices;
	}
}
