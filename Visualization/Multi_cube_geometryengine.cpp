
#include <iostream>
#include "Multi_cube_geometryengine.h"


Multi_cube_geometryengine::Multi_cube_geometryengine(const std::vector<Cube>& input)
	: indexBuf(QOpenGLBuffer::IndexBuffer)
{
	initializeOpenGLFunctions();

	// Generate 2 VBOs
	arrayBuf.create();
	indexBuf.create();

	// Initializes cube geometry and transfers it to VBOs
	setData(input);
}

Multi_cube_geometryengine::~Multi_cube_geometryengine()
{
	arrayBuf.destroy();
	indexBuf.destroy();
}


void Multi_cube_geometryengine::add_cube_to_data(const Cube& c){ // For cube we would need only 8 vertices but we have to
	// duplicate vertex for each face because texture coordinate
	// is different.
	//QVector3D diagonal = c.upper_corner - c.lower_corner;
	const QVector3D& l = c.lower_corner;
	const QVector3D& u = c.upper_corner;

	VertexData vertices[] = {
		// Vertex data for face 0
		{ QVector3D(l.x(), l.y(), u.z()), QVector2D(0.0f, 0.0f) },  // v0
		{ QVector3D(u.x(), l.y(), u.z()), QVector2D(0.33f, 0.0f) }, // v1
		{ QVector3D(l.x(), u.y(), u.z()), QVector2D(0.0f, 0.5f) },  // v2
		{ QVector3D(u.x(), u.y(), u.z()), QVector2D(0.33f, 0.5f) }, // v3

		// Vertex data for face 1
		{ QVector3D(u.x(),l.y(),u.z()), QVector2D(0.0f, 0.5f) }, // v4
		{ QVector3D(u.x(),l.y(),l.z()), QVector2D(0.33f, 0.5f) }, // v5
		{ QVector3D(u.x(), u.y(), u.z()), QVector2D(0.0f, 1.0f) },  // v6
		{ QVector3D(u.x(), u.y(), l.z()), QVector2D(0.33f, 1.0f) }, // v7

		// Vertex data for face 2
		{ QVector3D(u.x(), l.y(), l.z()), QVector2D(0.66f, 0.5f) }, // v8
		{ QVector3D(l.x(), l.y(), l.z()), QVector2D(1.0f, 0.5f) },  // v9
		{ QVector3D(u.x(), u.y(), l.z()), QVector2D(0.66f, 1.0f) }, // v10
		{ QVector3D(l.x(), u.y(), l.z()), QVector2D(1.0f, 1.0f) },  // v11

		// Vertex data for face 3
		{ QVector3D(l.x(), l.y(), l.z()), QVector2D(0.66f, 0.0f) }, // v12
		{ QVector3D(l.x(), l.y(), u.z()), QVector2D(1.0f, 0.0f) },  // v13
		{ QVector3D(l.x(), u.y(), l.z()), QVector2D(0.66f, 0.5f) }, // v14
		{ QVector3D(l.x(), u.y(), u.z()), QVector2D(1.0f, 0.5f) },  // v15

		// Vertex data for face 4
		{ QVector3D(l.x(), l.y(), l.z()), QVector2D(0.33f, 0.0f) }, // v16
		{ QVector3D(u.x(), l.y(), l.z()), QVector2D(0.66f, 0.0f) }, // v17
		{ QVector3D(l.x(), l.y(), u.z()), QVector2D(0.33f, 0.5f) }, // v18
		{ QVector3D(u.x(), l.y(), u.z()), QVector2D(0.66f, 0.5f) }, // v19

		// Vertex data for face 5
		{ QVector3D(l.x(), u.y(), u.z()), QVector2D(0.33f, 0.5f) }, // v20
		{ QVector3D(u.x(), u.y(), u.z()), QVector2D(0.66f, 0.5f) }, // v21
		{ QVector3D(l.x(), u.y(), l.z()), QVector2D(0.33f, 1.0f) }, // v22
		{ QVector3D(u.x(), u.y(), l.z()), QVector2D(0.66f, 1.0f) }  // v23
	};

	// Indices for drawing cube faces using triangle strips.
	// Triangle strips can be connected by duplicating indices
	// between the strips. If connecting strips have opposite
	// vertex order then last index of the first strip and first
	// index of the second strip needs to be duplicated. If
	// connecting strips have same vertex order then only last
	// index of the first strip needs to be duplicated.
	int off = vertices_vector.size();
	GLushort indices[] = {
		off + 0, off + 1, off + 2, off + 3, off + 3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
		off + 4, off + 4, off + 5, off + 6, off + 7, off + 7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
		off + 8, off + 8, off + 9, off + 10, off + 11, off + 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
		off + 12, off + 12, off + 13, off + 14, off + 15, off + 15, // Face 3 - triangle strip (v12, v13, v14, v15)
		off + 16, off + 16, off + 17, off + 18, off + 19, off + 19, // Face 4 - triangle strip (v16, v17, v18, v19)
		off + 20, off + 20, off + 21, off + 22, off + 23      // Face 5 - triangle strip (v20, v21, v22, v23)
	};



	vertices_vector.insert(vertices_vector.end(), vertices, vertices + 24);

	indices_vector.insert(indices_vector.end(), indices, indices + 34);


}

void Multi_cube_geometryengine::setData(const std::vector<Cube>& data)
{
	for (int i = 0; i < data.size(); i++){
		add_cube_to_data(data[i]);
	}

	arrayBuf.bind();
	arrayBuf.allocate(vertices_vector.data(), vertices_vector.size() * sizeof(VertexData));

	// Transfer index data to VBO 1
	indexBuf.bind();
	indexBuf.allocate(indices_vector.data(), indices_vector.size() * sizeof(GLushort));
}

void Multi_cube_geometryengine::drawCubeGeometry(QOpenGLShaderProgram *program)
{
	// Tell OpenGL which VBOs to use
	arrayBuf.bind();
	indexBuf.bind();

	// Offset for position
	quintptr offset = 0;

	// Tell OpenGL programmable pipeline how to locate vertex position data
	int vertexLocation = program->attributeLocation("a_position");
	program->enableAttributeArray(vertexLocation);
	program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

	// Offset for texture coordinate
	offset += sizeof(QVector3D);

	// Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
	int texcoordLocation = program->attributeLocation("a_texcoord");
	program->enableAttributeArray(texcoordLocation);
	program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

	// Draw cube geometry using indices from VBO 1

	int cube_count = vertices_vector.size() / 24;
	for (int i = 0; i < cube_count; i++){
		glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_SHORT, (void*)(i*34 * sizeof(GLushort)));
	}
}