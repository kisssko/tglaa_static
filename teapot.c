
#include "tgl.h"
#include "teapot_data.h"

void renderTeapot(GLfloat scale)
{
	int i, numV=sizeof(strip_vertices)/4;

    glEnable( GL_NORMALIZE );
//    glEnable( GL_AUTO_NORMAL );
//    glEnable( GL_MAP2_VERTEX_3 );
//    glEnable( GL_MAP2_TEXTURE_COORD_2 );

    glPushMatrix();
    glRotatef( 270.0, 1.0, 0.0, 0.0 );
    glScalef( 0.5 * scale, 0.5 * scale, 0.5 * scale );
    glTranslatef( 0.0, 0.0, -1.5 );

    glRotatef( 90.0, 1.0, 0.0, 0.0 );
    glBegin( GL_TRIANGLE_STRIP );

    for( i = 0; i < numV-1; i++ )
    {
        int vidx = strip_vertices[i],
            nidx = strip_normals[i];

        if( vidx != -1 )
        {
            glNormal3fv((float*)(normals[nidx]));
            glVertex3fv((float*)(vertices[vidx]));
        }
        else
        {
            glEnd();
            glBegin( GL_TRIANGLE_STRIP );
        }
    }
    glEnd();
    glPopMatrix();
}


