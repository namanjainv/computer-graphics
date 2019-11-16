// Vimal Kumar, Naman Jain
// nxv0154
// 2019-11-22

#if !defined( __BEZIER_H__ )
#define __BEZIER_H__

//----------------------------------------------------------
#include "model.h"
#include "projection.h"
#include "view.h"

//----------------------------------------------------------
void generateBezierPoints( Model *model, int resolution );
void generateBezierTriangles( Model *model, View *view, Projection *projection );

//----------------------------------------------------------
#endif

