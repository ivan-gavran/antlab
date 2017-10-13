from config import settings
import pdb

def gridUnitsToMeters(x_grid, y_grid):
    return (x_grid * settings.IMPLAN_UNIT_SIZE,  (settings.IMPLAN_MAP_WIDTH - y_grid)*settings.IMPLAN_UNIT_SIZE)
    
    
def metersToGridUnits(x_meter, y_meter):
    return ( round(x_meter / settings.IMPLAN_UNIT_SIZE), round(settings.IMPLAN_MAP_WIDTH - (y_meter/settings.IMPLAN_UNIT_SIZE * 1.0) ))

def pixelUnitsToMeters(x_pixel, y_pixel, resolution, width_pixels, length_pixels = None ):
    return ( x_pixel*resolution, (width_pixels-y_pixel)*resolution )

def metersToPixelUnits(x_meters, y_meters, resolution, width_pixels, length_pixels = None):
    return ( round(x_meters / resolution), width_pixels - round(y_meters/resolution) )