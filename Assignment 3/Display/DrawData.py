# Dalio, Brian A.
# dalioba
# 2019-10-14
#----------------------------------------------------------------------
class DrawData() :
  def __init__( self, inputFile = None ) :
    self.m_FileName = '<unknown>'
    self.m_Width    = 0
    self.m_Height   = 0
    self.m_Lines    = []
    self.m_Polygons = []

    if inputFile is not None :
      self.loadFile( inputFile )

  def getWidth( self ) :
    return self.m_Width

  def getHeight( self ):
    return self.m_Height

  def getLines( self ) :
    return self.m_Lines

  def getPolygons( self ) :
    return self.m_Polygons

  #---------------------------------------  
  def dump( self ) :
    print( f'#-- DrawData({self.m_FileName!r}) --' )
    print( f'# Canvas size  : ({self.getWidth():4d}, {self.getHeight():4d})' )
    print( f'# Num lines    : {len(self.getLines()):5d}' )
    print( f'# Num polygons : {len(self.getPolygons()):5d}' )
    print(  '#---------------------------------------')

  #---------------------------------------  
  def loadFile( self, fName ) :
    self.m_FileName = fName

    with open( fName, 'r' ) as fp :
      lines = fp.read().replace('\r', '' ).split( '\n' )

    for ( index, line ) in enumerate( lines, start = 1 ) :
      line = line.strip()
      if ( line == '' or line[0] == '#' ) :
        continue

      if line[0] == 'c' :
        try :
          _, w, h = line.split()

          w = int( w )
          h = int( h )

          self.m_Width = w
          self.m_Height = h

        except :
          print( f'Line {index} is a malformed canvas spec.' )

      elif line[0] == 'l' :
        try :
          coords = list( [ float( c ) for c in line.split()[1:] ] )

          if len( coords ) != 4 :
            print( f'Line {index} is a malformed line spec.' )

          else :
            self.m_Lines.append( coords )

        except :
          print( f'Line {index} is a malformed line spec.' )

      elif line[0] == 'p' :
        try :
          coords = list( [ float( c ) for c in line.split()[1:] ] )

          if len( coords ) % 2 != 0 :
            print( f'Line {index} is a malformed polygon spec.' )

          else :
            self.m_Polygons.append( coords )

        except :
          print( f'Line {index} is a malformed polygon spec.' )

      else :
        print( f'Line {index} \'{line}\' is unrecognized.' )

#----------------------------------------------------------------------
