from mandelbrot import Mandelbrot
from PIL import Image as im
import numpy as np
import sys

# Set to the name of your e-ink device (https://github.com/robweber/omni-epd#displays-implemented)
DISPLAY_TYPE = "waveshare_epd.epd7in5_V2"

# Disable when running the waveshare panel
DEBUG = False

if not DEBUG:
    from omni_epd import displayfactory, EPDNotFoundError

mandelbrot = Mandelbrot()

if not DEBUG:
    try:
        epd = displayfactory.load_display_driver(DISPLAY_TYPE)
    except EPDNotFoundError:
        print(f"Couldn't find {DISPLAY_TYPE}")
        sys.exit()

    epd.prepare()
    epd.clear()
    epd.sleep()

print(epd.width)
print(epd.height)
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
        epd.prepare()
        epd.clear()
        epd.display(image)
        epd.sleep()

    mandelbrot.zoom_on_interesting_area()
