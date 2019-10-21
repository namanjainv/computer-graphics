# Dalio, Brian A.
# dalioba
# 2019-10-14
#----------------------------------------------------------------------
class cl_world :
  def __init__( self, objects = [], canvases = [] ) :
    self.objects = objects
    self.canvases = canvases

  def add_canvas( self, canvas ) :
    self.canvases.append( canvas )
    canvas.world = self

  def reset( self ) :
    self.objects = []
    for canvas in self.canvases :
      canvas.delete( 'all' )

  def create_graphic_objects( self, canvas, drawData ) :
    #width  = int( canvas.cget( 'width' ) )
    #height = int( canvas.cget( 'height' ) )

    for line in drawData.getLines() :
      canvas.create_line( *line )

    for polygon in drawData.getPolygons() :
      canvas.create_line( *polygon, *polygon[0:2] )

def drawTriangle( canvas, v1, v2, v3 ) :
  #print( f'( {v1[0]:.3f}, {v1[1]:.3f} ) ( {v2[0]:.3f}, {v2[1]:.3f} ) ( {v3[0]:.3f}, {v3[1]:.3f} )' )

  if doClip :
    for ( vax, vay, _ ), ( vbx, vby, _ ) in [
      ( v1, v2 ), ( v2, v3 ), ( v3, v1 ) ] :
      doDraw, vax, vay, vbx, vby = clipLine( vax, vay, vbx, vby, portal )

      if doDraw :
        canvas.create_line( vax, vay, vbx, vby )

  else :
    canvas.create_line( *v1[:-1], *v2[:-1], *v3[:-1], *v1[:-1] )

#----------------------------------------------------------------------
