from mandelbrot import Mandelbrot
from PIL import Image as im
import numpy as np

# Disable when running the waveshare panel
DEBUG = False

if not DEBUG:
    from waveshare_epd import epd7in5_V2

mandelbrot = Mandelbrot()

if not DEBUG:
    epd = epd7in5_V2.EPD()
    epd.init()
    epd.Clear()
    epd.sleep()

while True:
    print("Starting render...")
    mandelbrot.render(800,480)
    print("Done!")
    arr = mandelbrot.get_render()
    arr = (np.asarray(arr)*255).astype(np.uint8)
    image = im.fromarray(arr)
    # Save the image as BMP
    image = image.convert("1")

    if DEBUG:
        image.show()
    else:
        epd.init()
        epd.Clear()
        epd.display(epd.getbuffer(image))
        epd.sleep()

    mandelbrot.zoom_on_interesting_area()