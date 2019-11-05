// Dalio, Brian A.
// dalioba
// 2019-11-05
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
  // TODO: Iterate through each patch, each value of u, and each
  //       value of v (so three nested loops in that order).
  //       Compute the 16 coefficients for the specific values of
  //       u and v.
  //       Iterate through the 16 coefficients multiplying each by
  //       the corresponding control point and accumulating the
  //       result in the current Bézier surface point.
  //       This is done for that point's x, y, and z coordinates.
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
}

//----------------------------------------------------------
void _computeCoefficients( double u, double v, double *coefficients )
{
  // TODO: For the given u and v values, generate the 16 Bernstein
  //       coefficients.  Ensure that you compute and store them
  //       in the proper order: c00, c01, c02, c03, c10, c11, c12,
  //       c13, c20, c21, c22, c23, c30, c31, c31, c32, c33.
}

//----------------------------------------------------------

