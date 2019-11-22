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

  cameraPosition->z = cameraPosition->z == 0 ? INFINITY : cameraPosition->z;

  Vertex toTriangle;
  toTriangle.x = v1->x - cameraPosition->x;
  toTriangle.y = v1->y - cameraPosition->y;
  toTriangle.z = v1->z - cameraPosition->z;

  Vertex Vector1;
  Vector1.x = v1->x - v2->x;
  Vector1.y = v1->y - v2->y;
  Vector1.z = v1->z - v2->z;

  Vertex Vector2;
  Vector2.x = v3->x - v2->x;
  Vector2.y = v3->y - v2->y;
  Vector2.z = v3->z - v2->z;

  Vertex normal;
  normal.x = ( Vector1.y * Vector2.z ) - ( Vector1.z * Vector2.y );
  normal.y = ( Vector1.z * Vector2.x ) - ( Vector1.x * Vector2.z );
  normal.z = ( Vector1.x * Vector2.y ) - ( Vector1.y * Vector2.x );
  
  double dot = ( toTriangle.x * normal.x ) + ( toTriangle.y * normal.y ) + ( toTriangle.z * normal.z );
  if(dot > 0) {
    return 1;
  }
  else {
    return 0;
  }
}

//----------------------------------------------------------
