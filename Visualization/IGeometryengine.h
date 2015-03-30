/**
interface for drawing geometry onto a openGL window
is used in mainwidget class
*/

#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

class IGeometryEngine : protected QOpenGLFunctions
{
public:

   virtual void drawCubeGeometry(QOpenGLShaderProgram *program) = 0;
};

#endif // GEOMETRYENGINE_H
