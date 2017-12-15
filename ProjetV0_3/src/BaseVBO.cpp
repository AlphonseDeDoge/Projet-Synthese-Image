#include <stdio.h>
#include "../include/BaseVBO.h"

void BaseVBO::fillId(){}
void BaseVBO::fillVertex(){}
void BaseVBO::fillColor(){}
void BaseVBO::update(){ printf("couco2u\n"); }

void BaseVBO::initId(int size)
{
    this->sizeId = size;
    this->sizeOfId = sizeof(GLuint) * size;
    this->id = new GLuint[size];
}

void BaseVBO::initVertex(int size)
{
    this->sizeVertex = size;
    this->sizeOfVertex = sizeof(GLfloat) * size;
    this->vertex = new GLfloat[size];
}

void BaseVBO::initColor(int size)
{
    this->sizeColor = size;
    this->sizeOfColor = sizeof(GLfloat) * size;
    this->color = new GLfloat[size];
}

void BaseVBO::setBuffers(const GLuint&  buffers)
{
    this->buffers = buffers;
}

GLuint BaseVBO::getBuffers()
{
    return this->buffers;
}
void BaseVBO::fill()
{
    fillId();
    fillVertex();
    fillColor();
}

void BaseVBO::explain()
{
    printf("taille id: %lu \ntaille vertex: %lu \ntaille color: %lu \nbuffer: %lu\n", sizeId, sizeVertex, sizeColor, buffers);
}

GLuint* BaseVBO::getId()
{
    return id;
}
GLfloat* BaseVBO::getVertex()
{
    return vertex;
}
GLfloat* BaseVBO::getColor()
{
    return color;
}

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
