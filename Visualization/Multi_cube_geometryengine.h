#ifndef MULTI_CUBE_GEOMETRYENGINE_H

#define MULTI_CUBE_GEOMETRYENGINE_H

#include <vector>

#include <QOpenGLBuffer>

#include "IGeometryengine.h"

class Multi_cube_geometryengine :
	public IGeometryEngine
{
public:

	struct Cube{
		QVector3D upper_corner;
		QVector3D lower_corner;
	};

	Multi_cube_geometryengine(const std::vector<Cube>& input);
	~Multi_cube_geometryengine();

	void setData(const std::vector<Cube>& data);

	void drawCubeGeometry(QOpenGLShaderProgram *program);

private:

	void add_cube_to_data(const Cube& c);

	struct VertexData
	{
		QVector3D position;
		QVector2D texCoord;
	};

	std::vector<GLushort> indices_vector;
	std::vector<VertexData> vertices_vector;

	QOpenGLBuffer arrayBuf;
	QOpenGLBuffer indexBuf;
};

#endif//#ifndef MULTI_CUBE_GEOMETRYENGINE_H
