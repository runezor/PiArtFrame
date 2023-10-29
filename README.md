# PiArtFrame

To run the script, first wire up the Raspberry Pi with a waveshare 7.5inch panel.
Then you need to install the waveshare Python library from https://www.waveshare.com/wiki/7.5inch_e-Paper_HAT_Manual#Working_With_Raspberry_Pi and place the waveshare_epd folder inside this folder. If someone has a more seamless way of installing this I'd be keen to update it.

You'll need to install Pillow, Numpy and tqdm via Pip to run the script.

Go inside the main.py and make sure that DEBUG is set to False, otherwise the script will try to show the render via Pillow, not via the eink panel.

Then simply run python3 main.py and you should get going!

## Building
This is a very straightforward build, with barely any tools required.

For the 7.5 waveshare panel, I'd recommend getting an 18x24cm frame (I got this one www.amazon.co.uk/dp/B07X6QDD5H?psc=1&ref=ppx_yo2ov_dt_b_product_details). I also ordered a custom made picture mount from www.best4frames.co.uk. It worked great and arrived pretty fast. I ordered mine around 15x9.7cm, which is one of the smallest cutouts they can make. Not only is the picture mount good for aesthetics, but I'd also say it offers some extra protection as I'd be worried otherwise about squeezing the eink panel directly against the picture-frame glass. The picture frame tabs are strong enough to hold the eink panel inside - glue/tape is optional.

I cut a small slit on the side of the backpanel of the frame for the ribbon cable to go out of. I attached it to the header which comes with the Waveshare panel, and which goes directly on the Pi Zero. Those of you who are more gifted in building might be able to come up with an enclosure, but in my build the Pi is free-floating.

To run the script in bootup on the Pi, I added the following line to /etc/rc.local:
sudo -H -u pi bash -c 'cd /home/pi/PiArtFrame && /usr/bin/python3 main.py'
