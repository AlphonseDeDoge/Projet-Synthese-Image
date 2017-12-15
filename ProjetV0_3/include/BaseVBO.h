#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#ifndef BASE_VBO
#define BASE_VBO

class BaseVBO
{
    public:
        virtual void draw();
        virtual void update();
        void setBuffers(const GLuint&  buffers);
        void explain();
        GLuint* getId();
        GLfloat* getVertex();
        GLfloat* getColor();
        GLuint getBuffers();

    protected:
        //Id
        int sizeId;
        int sizeOfId;//taille en octets
        GLuint* id;
        //Vertex
        int sizeVertex;
        int sizeOfVertex;//taille en octets
        GLfloat* vertex;
        //Color
        int sizeColor;
        int sizeOfColor;//taille en octets
        GLfloat* color;

        GLuint buffers;
        void initId(int n);
        void initVertex(int n);
        void initColor(int n);
        void fill();
        virtual void fillId();
        virtual void fillVertex();
        virtual void fillColor();

};
#endif // BASE_VBO
