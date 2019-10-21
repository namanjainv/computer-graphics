# Dalio, Brian A.
# dalioba
# 2019-10-20
#----------------------------------------------------------------------
from pathlib import Path

import tkinter as tk
from tkinter import simpledialog
from tkinter import filedialog

from DrawData      import DrawData

#----------------------------------------------------------------------
class cl_widgets :
  def __init__( self, ob_root_window, ob_world = [] ) :
    self.ob_root_window = ob_root_window
    self.ob_world = ob_world

    self.menu = cl_menu( self )

    self.statusBar_frame = cl_statusBar_frame( self.ob_root_window )
    self.statusBar_frame.pack( side = tk.BOTTOM, fill = tk.X )
    self.statusBar_frame.set( 'This is the status bar' )

    self.ob_canvas_frame = cl_canvas_frame( self )
    self.ob_world.add_canvas( self.ob_canvas_frame.canvas )

#----------------------------------------------------------------------
class cl_canvas_frame :
  def __init__( self, master ) :
    self.master = master
    self.canvas = tk.Canvas(
      master.ob_root_window, width=1, height=1, bg='teal' )

    self.canvas.pack( expand=tk.YES, fill=tk.BOTH )

  def canvas_resized_callback( self, event ) :
    self.resizeCanvas( event.width-4, event.height-4 )

  def resizeCanvas( self, width, height ) :
    # https://stackoverflow.com/a/9002361
    self.canvas.winfo_toplevel().wm_geometry( '' )

    self.canvas.config( width = width, height = height )

    self.master.statusBar_frame.pack( side = tk.BOTTOM, fill = tk.X )
    self.master.statusBar_frame.set(
      f'Canvas width, height ({self.canvas.cget( "width" )}, ' +
      f'{self.canvas.cget( "height" )})' )

    self.canvas.pack()

#----------------------------------------------------------------------
class cl_statusBar_frame( tk.Frame ) :
  def __init__( self, master ) :
    tk.Frame.__init__( self, master )
    self.label = tk.Label( self, bd = 1, relief = tk.SUNKEN, anchor = tk.W )
    self.label.pack( fill = tk.X )

  def set( self, formatStr, *args ) :
    wBefore = self.label.winfo_geometry()

    msg = f'{formatStr % args}'
    print( msg )
    self.label.config( text = msg )

    self.label.update_idletasks()
    wAfter = self.label.winfo_geometry()
    #print( 'statusbar', wBefore, wAfter )

  def clear( self ) :
    self.label.config( text='' )
    self.label.update_idletasks()

#----------------------------------------------------------------------
class cl_menu :
  def __init__( self, master ) :
    self.master = master
    self.menu = tk.Menu( master.ob_root_window )
    master.ob_root_window.config( menu = self.menu )

    dummy = tk.Menu( self.menu )
    self.menu.add_cascade( label = 'File', menu = dummy )
    dummy.add_command( label = 'Open...', command = lambda : self.menu_open_callback() )
    dummy.add_separator()
    dummy.add_command( label = 'Clear', command = lambda : self.menu_clear_callback() )

  def menu_callback( self, which = None ) :
    item = 'menu' if which is None else which
    self.master.statusBar_frame.set( f'{item!r} callback' )

  def menu_clear_callback( self ) :
    self.master.ob_world.reset()

  def menu_open_callback( self ) :
    fName = tk.filedialog.askopenfilename( filetypes = [ ( "Simple Draw File", "*.sdf" ) ] )
    if ( len( fName ) == 0 ) :
        self.master.statusBar_frame.set( "%s", "[Load was cancelled]" )
        return

    drawData = DrawData( fName )
    drawData.dump()
    w = drawData.getWidth()
    h = drawData.getHeight()

    self.master.ob_canvas_frame.resizeCanvas( w, h )
    self.master.ob_canvas_frame.canvas.create_line( 1, 1, w, 1, w, h, 1, h, 1, 1, fill='white' )

    self.master.ob_world.create_graphic_objects( self.master.ob_canvas_frame.canvas, drawData )

    baseFileName = Path( fName ).name
    self.master.statusBar_frame.set( f'Loaded {baseFileName!r}' )

#----------------------------------------------------------------------
