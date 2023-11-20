# PiArtFrame

To run the script, first wire up the Raspberry Pi with an e-Ink panel.

Install the needed Python requirements with:

```
pip install -r requirements.txt
```
When you're ready to run, check the following:

1. Set the `DISPLAY_TYPE` variable to the type of e-ink panel you have. [Click here](https://github.com/robweber/omni-epd#displays-implemented) for a list of supported devices.
2. Set the `DEBUG` flag to False inside main.py, otherwise the script will try to show the render via Pillow, not via the e-ink panel.

Then simply run python3 main.py and you should get going!

## Building
This is a very straightforward build, with barely any tools required.

I bought the panel from the Waveshare Amazon store here https://www.amazon.co.uk/Waveshare-HAT-Resolution-Electronic-Controller/dp/B075R4QY3L/ref=sr_1_3?crid=CPHJQO42PSW4&keywords=waveshare+7.5&qid=1698589243&sprefix=waveshare+7.5%2Caps%2C68&sr=8-3

There seems to be multiple posting of these on Amazon, I can't really say if there's any difference between them so I'd say go for the cheapest one that still comes with a Pi Zero header.

For the 7.5 waveshare panel, I'd recommend getting an 18x24cm frame (I got this one www.amazon.co.uk/dp/B07X6QDD5H?psc=1&ref=ppx_yo2ov_dt_b_product_details). I also ordered a custom made picture mount from www.best4frames.co.uk. It worked great and arrived pretty fast. I ordered mine around 15x9.7cm, which is one of the smallest cutouts they can make. Not only is the picture mount good for aesthetics, but I'd also say it offers some extra protection as I'd be worried otherwise about squeezing the eink panel directly against the picture-frame glass. The picture frame tabs are strong enough to hold the eink panel inside - glue/tape is optional.

I cut a small slit on the side of the backpanel of the frame for the ribbon cable to go out of. I attached it to the header which comes with the Waveshare panel, and which goes directly on the Pi Zero. Those of you who are more gifted in building might be able to come up with an enclosure, but in my build the Pi is free-floating.

To run the script in bootup on the Pi, I added the following line to /etc/rc.local:
```
sudo -H -u pi bash -c 'cd /home/pi/PiArtFrame && /usr/bin/python3 main.py'
```
