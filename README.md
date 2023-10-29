# PiArtFrame

To run the script, first wire up the Raspberry Pi with a waveshare 7inch panel.
Then you need to install the waveshare Python library from https://www.waveshare.com/wiki/7.5inch_e-Paper_HAT_Manual#Working_With_Raspberry_Pi and place the waveshare_epd folder inside this folder. If someone has a more seamless way of installing this I'd be keen to update it.

You'll need to install Pillow and Numpy via Pip to run the script.

Go inside the main.py and make sure that DEBUG is set to False, otherwise the script will try to show the render via Pillow, not via the eink panel.

Then simply run python3 main.py and you should get going!
