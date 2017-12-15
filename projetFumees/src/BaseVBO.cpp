#include <stdio.h>
#include "../include/BaseVBO.h"

/** Define empty functions that will be detailed in daughter classes
*/

void BaseVBO::fillId(){}
void BaseVBO::fillVertex(){}
void BaseVBO::fillColor(){}
void BaseVBO::update(){}


/** Initializes the ID matrix of the elements to draw
*/
void BaseVBO::initId(int size)
{
    this->sizeId = size;
    this->sizeOfId = sizeof(GLuint) * size;
    this->id = new GLuint[size];
}

/** Initializes the Vertex matrix of the elements to draw
*/
void BaseVBO::initVertex(int size)
{
    this->sizeVertex = size;
    this->sizeOfVertex = sizeof(GLfloat) * size;
    this->vertex = new GLfloat[size];
}

/** Initializes the Color matrix of the elements to draw
*/
void BaseVBO::initColor(int size)
{
    this->sizeColor = size;
    this->sizeOfColor = sizeof(GLfloat) * size;
    this->color = new GLfloat[size];
}

/** Sets the buffers of the current object
*/
void BaseVBO::setBuffers(const GLuint&  buffers)
{
    this->buffers = buffers;
}

/** Rturns the buffers of the current object
*/
GLuint BaseVBO::getBuffers()
{
    return this->buffers;
}

/** Calls to the fil functions of the 3 matrix (ID, Vertex, Color)
*/
void BaseVBO::fill()
{
    fillId();
    fillVertex();
    fillColor();
}

/** Debug echo
*/
void BaseVBO::explain()
{
    printf("taille id: %lu \ntaille vertex: %lu \ntaille color: %lu \nbuffer: %lu\n", sizeId, sizeVertex, sizeColor, buffers);
}

/** Returns the ID matrix
*/
GLuint* BaseVBO::getId()
{
    return id;
}

/** Returns the Vertex matrix
*/
GLfloat* BaseVBO::getVertex()
{
    return vertex;
}

/** Returns the Color matrix
*/
GLfloat* BaseVBO::getColor()
{
    return color;
}

/** Draw function, puts the Vertex and Color matrix into buffers that are send to the VBO
*/
void BaseVBO::draw()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, buffers);
    glBufferData(GL_ARRAY_BUFFER, sizeOfVertex+sizeOfColor, 0,GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeOfVertex, vertex);
    // copy vertices starting from 0 offest
    glBufferSubData(GL_ARRAY_BUFFER, sizeOfVertex, sizeOfColor, color); // copy colours after vertices

    glVertexPointer(3, GL_FLOAT, 0, 0);
    // offset different en VBO et VA
    glColorPointer(3, GL_FLOAT,0,(void*)(sizeOfVertex));

    glDrawElements(GL_TRIANGLES, sizeId, GL_UNSIGNED_INT, id);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
