// Vimal Kumar, Naman Jain
// nxv0154
// 2019-11-22
//----------------------------------------------------------
#include <stdio.h>

#include "bezier.h"
#include "model.h"
#include "triangle.h"
#include "vertex.h"

void _computeCoefficients( double u, double v, double *c );

//----------------------------------------------------------
void generateBezierPoints( Model *model, int resolution )
{
  Vertex *vx = &model->m_patchVertex[0];

  for ( int p=0; p<model->m_numPatches; p++ ) {
    for ( int u=0; u<resolution; u++ ) {
      for ( int v=0; v<resolution; v++ ) {
        double coeffs[16];

        _computeCoefficients( u*1.0/(resolution-1), v*1.0/(resolution-1), &coeffs[0] );

        for ( int i=0; i<16; i++ ) {
          vx->x += coeffs[i] * model->m_vertex[ model->m_patch[p][i] ].x;
          vx->y += coeffs[i] * model->m_vertex[ model->m_patch[p][i] ].y;
          vx->z += coeffs[i] * model->m_vertex[ model->m_patch[p][i] ].z;
        }

        vx++;
      }
    }
  }
}

//----------------------------------------------------------
void generateBezierTriangles( Model *model, View *view, Projection *projection )
{
  int resolution = view->m_resolution;

  for ( int p=0; p<model->m_numPatches; p++ ) {
    int patchOffset = p*resolution*resolution;

    for ( int row=0; row<resolution-1; row++ ) {
      int rowStart = patchOffset + row*resolution;

      for ( int col=0; col<resolution-1; col++ ) {
        int here  = rowStart + col;
        int there = here + resolution;

        // TODO: Call cullProjectDumpTriangle() with the proper
        //       arguments for the generated triangles.
      }
    }
  }
}

//----------------------------------------------------------
void _computeCoefficients( double u, double v, double *c )
{
  double u2 = u*u;
  double u3 = u2*u;

  double mu  = 1.0 - u;
  double mu2 = mu*mu;
  double mu3 = mu2*mu;

  double v2 = v*v;
  double v3 = v2*v;

  double mv  = 1.0 - v;
  double mv2 = mv*mv;
  double mv3 = mv2*mv;

  c[ 0] =      mu3*mv3; c[ 1] = 3   *v*mu3*mv2; c[ 2] = 3   *v2*mu3*mv; c[ 3] =      v3*mu3;
  c[ 4] = 3*u *mu2*mv3; c[ 5] = 9*u *v*mu2*mv2; c[ 6] = 9*u *v2*mu2*mv; c[ 7] = 3*u *v3*mu2;
  c[ 8] = 3*u2*mu *mv3; c[ 9] = 9*u2*v*mu *mv2; c[10] = 9*u2*v2*mu *mv; c[11] = 3*u2*v3*mu;
  c[12] =   u3    *mv3; c[13] = 3*u3*v    *mv2; c[14] = 3*u3*v2    *mv; c[15] =   u3*v3;
}

//----------------------------------------------------------

