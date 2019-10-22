// Vimal Kumar, Naman Jain
// nxv0154
// 2019-10-21
//----------------------------------------------------------
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "projection.h"

//----------------------------------------------------------
Projection *allocProjection()
{
  Projection *p;

  p = (Projection *) calloc( 1, sizeof( Projection ) );
  if ( p == NULL ) {
    fprintf( stderr, "allocProjection: Unable to allocate Projection.\n" );
    exit( 1 );
  }

  return p;
}

//----------------------------------------------------------
Projection *computeProjection( View *v )
{
  Projection *p = allocProjection();

  p->m_fx = -v->m_worldXMin; 
  p->m_fy = -v->m_worldYMin;

  p->m_gx = v->m_width*v->m_viewportXMin;
  p->m_gy = v->m_height*v->m_viewportYMin;

  p->m_sx = v->m_width*(v->m_viewportXMax - v->m_viewportXMin)/(v->m_worldXMax - v->m_worldXMin);
  p->m_sy = v->m_height*(v->m_viewportYMax - v->m_viewportYMin)/(v->m_worldYMax - v->m_worldYMin);

  p->m_ax = p->m_fx*p->m_sx + p->m_gx;
  p->m_ay = p->m_fy*p->m_sy + p->m_gy;

  p->m_cameraDistance = v->m_cameraDistance;
  
  return p;
}

//----------------------------------------------------------
void dumpProjection( Projection *p )
{
  printf( "#- Projection parameters ---------------\n" );
  printf( "(fx, fy) : ( %13.6f, %13.6f )\n", p->m_fx, p->m_fy );
  printf( "(gx, gy) : ( %13.6f, %13.6f )\n", p->m_gx, p->m_gy );
  printf( "(sx, sy) : ( %13.6f, %13.6f )\n", p->m_sx, p->m_sy );
  printf( "(ax, ay) : ( %13.6f, %13.6f )\n", p->m_ax, p->m_ay );
  printf( "Camera distance : %13.6f\n", p->m_cameraDistance );
  printf( "#---------------------------------------\n" );
}

//----------------------------------------------------------
void freeProjection( Projection *p )
{
  free( p );
}

//----------------------------------------------------------
void projectVertexList( Projection *p, Vertex *v, int numVertices )
{
  for ( int i=0; i<numVertices; i++ ) {
    if(p->m_cameraDistance != 0) {
      v[i].x = v[i].x / (1-v[i].z/p->m_cameraDistance);
      v[i].y = v[i].y / (1-v[i].z/p->m_cameraDistance);
    }
    v[i].x = p->m_sx*v[i].x + p->m_ax;
    v[i].y = p->m_sy*v[i].y + p->m_ay;
    v[i].z = 0;
  }
}

//----------------------------------------------------------
#define DEGREES_TO_RADIANS(d) (M_PI*(d)/180.0)

void rotateVertexList( View *view, Vertex *vertex, int numVertices, Vertex center )
{
  double phi = DEGREES_TO_RADIANS(view->m_phi);
  double theta = DEGREES_TO_RADIANS(view->m_theta);
  double psi = DEGREES_TO_RADIANS(view->m_psi);

  double r00 = cos(psi)*cos(theta);
  double r01 = -cos(theta)*sin(psi);
  double r02 = sin(theta);
  double r10 = cos(phi)*sin(psi) + cos(psi)*sin(phi)*sin(theta);
  double r11 = cos(phi)*cos(psi) - sin(phi)*sin(psi)*sin(theta);
  double r12 = -cos(theta)*sin(phi);
  double r20 = -cos(phi)*cos(psi)*sin(theta) + sin(phi)*sin(psi);
  double r21 = cos(phi)*sin(psi)*sin(theta) + cos(psi)*sin(phi);
  double r22 = cos(phi)*cos(theta);

  // // https://www.andre-gaschler.com/rotationconverter/
  // printf( "  [%5f]  ",r00);
  // printf( "  [%5f]  ",r01);
  // printf( "  [%5f]  ",r02);
  // printf("\n");
  // printf( "  [%5f]  ",r10);
  // printf( "  [%5f]  ",r11);
  // printf( "  [%5f]  ",r12);
  // printf("\n");
  // printf( "  [%5f]  ",r20);
  // printf( "  [%5f]  ",r21);
  // printf( "  [%5f]  ",r22);
  // printf("\n");

  double ex = -r00*center.x - r01*center.y - r02*center.z + center.x;
  double ey = -r10*center.x - r11*center.y - r12*center.z + center.y;
  double ez = -r20*center.x - r21*center.y - r22*center.z + center.z;

  for ( int i=0; i<numVertices; i++ ) {
    double x = vertex[i].x;
    double y = vertex[i].y;
    double z = vertex[i].z;
    vertex[i].x = r00*x + r01*y + r02*z + ex;
    vertex[i].y = r10*x + r11*y + r12*z + ey;
    vertex[i].z = r20*x + r21*y + r22*z + ez;
  }
}

//----------------------------------------------------------

