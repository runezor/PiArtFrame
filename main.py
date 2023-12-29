from mandelbrot import Mandelbrot
from PIL import Image as im
import numpy as np
import sys

# Set to the name of your e-ink device (https://github.com/robweber/omni-epd#displays-implemented)
DISPLAY_TYPE = "waveshare_epd.epd7in5_V2"

#
# Disable when running the waveshare panel
# DEBUG = True display Mandelbrot image on Raspberry Pi monitor
# 12/28 04:32
#
#12/29

DEBUG = False

if not DEBUG:
    from omni_epd import displayfactory, EPDNotFoundError

mandelbrot = Mandelbrot()

# default height and width - need to hardcode for debug mode
WIDTH = 800
HEIGHT = 480
if not DEBUG:
    try:
        epd = displayfactory.load_display_driver(DISPLAY_TYPE)
    except EPDNotFoundError:
        print(f"Couldn't find {DISPLAY_TYPE}")
        sys.exit()

    WIDTH = epd.width
    HEIGHT = epd.height

    epd.prepare()
    epd.clear()
    epd.sleep()

while True:
    print("Starting render...")
    mandelbrot.render(WIDTH,HEIGHT)
    print("Done!")
    arr = mandelbrot.get_render()
    arr = (np.asarray(arr)*255).astype(np.uint8)
    image = im.fromarray(arr)
    # Save the image as BMP
    image = image.convert("1")

    if DEBUG:
        image.show()
    else:
        epd.prepare()
        epd.clear()
        epd.display(image)
        epd.sleep()

    mandelbrot.zoom_on_interesting_area()
