// Vimal Kumar, Naman Jain
// nxv0154
// 2019-11-11
//----------------------------------------------------------
#include <stdio.h>

#include "bezier.h"
#include "model.h"
#include "triangle.h"
#include "vertex.h"

void _computeCoefficients( double u, double v, double *coefficients );

double power(double a, int b) {
  if(b == 0)  return 1;
  else return (a * power(a, b-1));
}

double factorial(double a) {
  if(a >= 1)  return a * factorial(a-1);
  else        return 1;
}

double nCr(int n, int r) {
  return factorial(n) / ( factorial(n-r) * factorial(r) );
}
//----------------------------------------------------------
void generateBezierPoints( Model *model, int resolution )
{
  // TODO: Iterate through each patch, each value of u, and each
  //       value of v (so three nested loops in that order).
  //       Compute the 16 coefficients for the specific values of
  //       u and v.
  //       Iterate through the 16 coefficients multiplying each by
  //       the corresponding control point and accumulating the
  //       result in the current Bézier surface point.
  //       This is done for that point's x, y, and z coordinates.

  double coefficients[16];
  double u, v;
  int patchVertexIndex = 0;
  for( int patch_index = 0 ; patch_index < model->m_numPatches ; patch_index++ ) {
    for( int u_index = 0 ; u_index < resolution; u_index++ ) {
      u = u_index / ( 1.0 * (resolution - 1) );
      for( int v_index = 0 ; v_index < resolution; v_index++ ) {
        v = v_index / ( 1.0 * (resolution - 1) );
        _computeCoefficients( u, v, coefficients );
        model->m_patchVertex[patchVertexIndex].x = 0;
        model->m_patchVertex[patchVertexIndex].y = 0;
        model->m_patchVertex[patchVertexIndex].z = 0;
        for( int k = 0 ; k < 16; k++ ) {
          model->m_patchVertex[patchVertexIndex].x += coefficients[k] * model->m_vertex[ model->m_patch[patch_index][k] ].x;
          model->m_patchVertex[patchVertexIndex].y += coefficients[k] * model->m_vertex[ model->m_patch[patch_index][k] ].y;
          model->m_patchVertex[patchVertexIndex].z += coefficients[k] * model->m_vertex[ model->m_patch[patch_index][k] ].z;
        }
        patchVertexIndex++;
      }
    }
  }
}

//----------------------------------------------------------
void generateBezierTriangles( Model *model, int resolution )
{
  // TODO: Iterate through each patch, each row of that patch, and
  //       and each column of that patch (so three nested loops in
  //       that order).
  //       Dump the two triangles that correspond to the row and
  //       column positions using the dumpTriangle() routine.
  //       Remember that you have to consider only the first
  //       through the penultimate row and the first through the
  //       penultimate column when generating a patch's triangles.
  //       Ensure that you generate the triangles in the correct
  //       order and use the vertices in the correct order.


  for( int patch_index = 0 ; patch_index < model->m_numPatches ; patch_index++ ) {
    for( int row = 0 ; row < resolution - 1 ; row++ ) {
      int rowStart = row * resolution + (patch_index * resolution * resolution);

      for( int col = 0 ; col < resolution - 1 ; col++ ) {
        int here = rowStart + col;
        int there = here + resolution;
        dumpTriangle( &model->m_patchVertex[here], &model->m_patchVertex[there], &model->m_patchVertex[there + 1] );
        dumpTriangle( &model->m_patchVertex[there + 1], &model->m_patchVertex[here + 1], &model->m_patchVertex[here] );
      }
    }
  }
}

//----------------------------------------------------------
void _computeCoefficients( double u, double v, double *coefficients )
{
  double u2 = u*u;
  double u3 = u2*u;
  double v2 = v*v;
  double v3 = v2*v;
  double u11 = (1-u);
  double u12 = u11*u11;
  double u13 = u12*u11;
  double v11 = (1-v);
  double v12 = v11*v11;
  double v13 = v12*v11;

  coefficients[0] = u13 * v13;
  coefficients[1] = 3 * v * u13 * v12;
  coefficients[2] = 3 * v2 * u13 * v11;
  coefficients[3] = v3 * u13;

  coefficients[4] = 3 * u * u12 * v13;
  coefficients[5] = 9 * u * v * u12 * v12;
  coefficients[6] = 9 * u * v2 * u12 * v11;
  coefficients[7] = 3 * u * v3 * u12;

  coefficients[8] = 3 * u2 * u11 * v13;
  coefficients[9] = 9 * u2 * v * u11 * v12;
  coefficients[10] = 9 * u2 * v2 * u11 * v11;
  coefficients[11] = 3 * u2 * v3 * u11;

  coefficients[12] = u3 * v13;
  coefficients[13] = 3 * v * u3 * v12;
  coefficients[14] = 3 * v2 * u3 * v11;
  coefficients[15] = v3 * u3;

}

//----------------------------------------------------------

