// Vimal Kumar, Naman Jain
// nxv0154
// 2019-11-22

//----------------------------------------------------------
#include <math.h>
#include <stdio.h>

#include "cull.h"
#include "vertex.h"

//----------------------------------------------------------
int cull( Vertex *v1, Vertex *v2, Vertex *v3, Vertex *cameraPosition )
{
  // TODO: Compute the toTriangle vector.  Compute the triangle
  //       normal vector.  Compute the dot product of these two
  //       vectors.  Return an indication of whether this triangle
  //       should be culled.
  // printf("\nV1: ");
  // dumpVertex(v1);
  // printf("\nV2: ");
  // dumpVertex(v2);
  // printf("\nV3: ");
  // dumpVertex(v3);
  // printf("\nCamera Position: ");
  // dumpVertex(cameraPosition);
  Vertex toTriangle;
  toTriangle.x = v1->x - cameraPosition->x;
  toTriangle.y = v1->y - cameraPosition->y;
  toTriangle.z = v1->z - cameraPosition->z;
  // printf("\nTo Triange: ");
  // dumpVertex(&toTriangle);

  Vertex Vector1;
  Vector1.x = v1->x - v2->x;
  Vector1.y = v1->y - v2->y;
  Vector1.z = v1->z - v2->z;
  // printf("\nVector 1: ");
  // dumpVertex(&Vector1);

  Vertex Vector2;
  Vector2.x = v3->x - v2->x;
  Vector2.y = v3->y - v2->y;
  Vector2.z = v3->z - v2->z;
  // printf("\nVector 2: ");
  // dumpVertex(&Vector2);

  Vertex normal;
  normal.x = ( Vector1.y * Vector2.z ) - ( Vector1.z * Vector2.y );
  normal.y = ( Vector1.z * Vector2.x ) - ( Vector1.x * Vector2.z );
  normal.z = ( Vector1.x * Vector2.y ) - ( Vector1.y * Vector2.x );
  // printf("\nNormal: ");
  // dumpVertex(&normal);
  
  double dot = ( toTriangle.x * normal.x ) + ( toTriangle.y * normal.y ) + ( toTriangle.z * normal.z );
  // printf("\nDot: %f\n", dot);
  if(dot > 0) {
    return 1;
  }
  else {
    return 0;
  }
}

//----------------------------------------------------------
