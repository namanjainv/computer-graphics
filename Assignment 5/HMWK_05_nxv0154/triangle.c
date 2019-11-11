// Vimal Kumar, Naman Jain
// nxv0154
// 2019-11-05
//----------------------------------------------------------
#include <stdio.h>

#include "line.h"
#include "triangle.h"

View *_view = NULL;

//----------------------------------------------------------
void dumpTriangle( Vertex *v1, Vertex *v2, Vertex *v3 )
{
  // TODO:  Draw the three lines that are made from v1, v2, and
  //        v3.  Be sure you use clipLine() first to see if the
  //        line needs to be drawn.  Use dumoLine() to generate
  //        the actual line.
  Line line;

  line.p1X = v1->x;
  line.p1Y = v1->y;
  line.p2X = v2->x;
  line.p2Y = v2->y;
  if(clipLine(_view, &line) == 1)
    dumpLine(&line);

  line.p1X = v2->x;
  line.p1Y = v2->y;
  line.p2X = v3->x;
  line.p2Y = v3->y;
  if(clipLine(_view, &line) == 1)
    dumpLine(&line);

  line.p1X = v3->x;
  line.p1Y = v3->y;
  line.p2X = v1->x;
  line.p2Y = v1->y;
  if(clipLine(_view, &line) == 1)
    dumpLine(&line);
}

//----------------------------------------------------------
void setPortal( View *v )
{
  // TODO:  Remember the view so it can be clipped against when
  //        triangles are drawn later.
  _view = v;
}

//----------------------------------------------------------

