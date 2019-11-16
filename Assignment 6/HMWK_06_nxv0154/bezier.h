// Dalio, Brian A.
// dalioba
// 2019-11-11

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

