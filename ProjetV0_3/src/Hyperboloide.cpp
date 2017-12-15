#include "../include/Hyperboloide.h"

void Hyperboloide::update(){}

Hyperboloide::Hyperboloide()
{
    this->n = 8;
    this->rayon = 0.5;
    this->hauteur = 0.5;
    this->decalage = 0.0;
    this->buffers = 0;
    this->initId(n*6);
    this->initVertex(n*6);
    this->initColor(n*6);
    this->fill();
}

Hyperboloide::Hyperboloide(const GLuint& buffers)
{
    this->n = 8;
    this->rayon = 0.5;
    this->hauteur = 0.5;
    this->decalage = 0.0;
    this->buffers = buffers;
    this->initId(n*6);
    this->initVertex(n*6);
    this->initColor(n*6);
    this->fill();
}

void Hyperboloide::fillId()
{
    int j=0;
    for(int i=0;i<n;i++){
        id[j]=i;
        id[j+1]=(i+1)%n;
        id[j+2]=(n+((i+1)%n));

        id[j+3]=(n+((i+1)%n));
        id[j+4]=(n+(i%n));
        id[j+5]=i;
        j=j+6;
    }
}

void Hyperboloide::fillVertex()
{
    int j=0;
    for(int i=0;i<n;i++){
        vertex[j]=rayon*sin((2*i*M_PI)/n);
        vertex[j+1]=-hauteur;
        vertex[j+2]=rayon*cos((2*i*M_PI)/n);

        vertex[3*n+j]=rayon*sin(((2*i*M_PI)/n)+(float)decalage);
        vertex[3*n+(j+1)]=hauteur;
        vertex[3*n+(j+2)]=rayon*cos(((2*i*M_PI)/n)+(float)decalage);
        j=j+3;
    }
}

void Hyperboloide::fillColor()
{
    int j=0;
    for(int i=0;i<n;i++){
        float g,b;
        if(i<=n/2){
            g=(float)i/(float)n;
            b=((float)n-(float)i)/(float)n;
        }
        else{
            b=(float)i/(float)n;
            g=((float)n-(float)i)/(float)n;
        }
        color[j]=0;
        color[j+1]=g;
        color[j+2]=b;

        color[3*n+j]=0;
        color[(j+1)+n*3]=g;
        color[(j+2)+n*3]=b;
        j=j+3;
    }
}

void Hyperboloide::explain()
{
    BaseVBO::explain();
    printf("n:%d \nrayon:%f \nhauteur:%f \ndecalage:%f\n", n, rayon, hauteur, decalage);
}

int Hyperboloide::getN()
{
    return n;
}
