# Lab2B_ESP

## Challenges
- Which parts of the lab specification have you found most confusing or difficult to understand?

  - Lab parts 8,9 were really confusing. Part 08 required us to control the APDS using the PIO module, but that was very vague and it was difficult to figure out what that means or how we approach it. 
  - Lab 9 says that the timings modeled in the last lab may be used to capture color, but delivery, packet delivery, and brightness change. But we were not sure how to implement that.

- Which lab topics have you found most confusing or difficult to understand?

  - Understanding the PIO and its working
  - Using the right header file in my code
  - Part 9: lab on a chip:
  - "Add APDS9960 support to your sensor, then set your system up to capture the following timing info:
    - color packet delivered to PIO module
    - bit delivered to WS2812 (24x/packet)
    - full packet delivered to WS2812
    - brightness changed on APDS"

  - The above question could have been phrased in a better way with an example (something like a block diagram) to help us better understand.

- Which parts of the lab have you found most difficult to implement? 
  
  - In the 6th part of the lab, modifying the DMA Logic analyser code from the pico-examples was a bit tricky to be honest(even though we got it to working towards the end). There were many new things which we have never explored with respect to the DMA/PIO and had to implement them directly for this lab submission which got difficult due to the short duration. Also a bit of background about what DMA is, how it can be implemented or what it's example code meant, if was covered in the lecture would have been really helpful.
  - Part 09 was tricky as well, having to use the timing modelling to capture color, bit, packet with APDS. We are still working on this and might be able to complete by tonight with help from some peers.

- What steps have you taken to resolve these difficulties?
  
  - Refer youtube videos. Some of them are:
    - https://www.youtube.com/watch?v=JSis2NU65w8
    - https://www.youtube.com/watch?v=zeudTftbTmw
    - https://www.youtube.com/watch?v=Au-oc4hxj-c
  - Found the repo of Ruturaj to be very helpful.
