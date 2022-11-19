    Akshaya Nidhi Bhati
      LinkedIn: https://www.linkedin.com/in/akshaya-nidhi-bhati-6467841b3/?originalSubdomain=in

# LED on a chip: #

Here, we modified part 8(adps_protocol) to work with the QTPy board. The code was uploaded, with minor changes to the attached CMakeLists given in the example.

## Output: 

The output terminal:

![terminal](https://user-images.githubusercontent.com/73771085/202676764-cec2b402-1228-4e7f-b07a-ff19ff04246e.jpeg)

We can see the the color of LED changing with the color detected by the ADPS sensor. The LED is clear that is if we cover the board then, no LED will glow. 

As shown below (in the Dark Mode): 

https://user-images.githubusercontent.com/114259992/202831232-ae160937-bc99-4cfe-8a09-f0ee1c6043f4.mp4


Output for the Dark Mode on Putty 

![Part 9 Output](https://user-images.githubusercontent.com/114259992/202832718-803570e5-dadf-4805-b7a0-bffd34467d9f.jpeg)

We can see the change in brightness according to the sensor input. As shown below (in the Dark Mode):

For Red color inputs 

https://user-images.githubusercontent.com/114259992/202832139-5376218d-a0fe-4522-9797-58e9d81f3559.mp4

For Green color inputs 

https://user-images.githubusercontent.com/114259992/202832148-9385ba7e-5c2e-456f-85a2-c028ea965c95.mp4

For Blue color inputs

https://user-images.githubusercontent.com/114259992/202832167-2c4a6b15-dbff-43bc-b503-d2ae303d9386.mp4

In LAB 2B we are measuring this timing ‘jitter’ directly instead of just modeling it.
The PWM on the neopixel is out of sync with the PIO RGB packets. The timing fluctuates between when the neopixel turns on and when a packet is delivered. So we can measure this Jitter. 

When we take the video in light mode, we saw that it takes some time to take input from the sensor and for the LED to give the output. Sometimes it even shows an error for the Light Mode. 
We examined that the free running PWM on the neopixel is out of sync with the PIO RGB packets in LAB 2A, so the timing between when a packet is delivered and when the neopixel turns on will fluctuate accordingly.

As shown below: 

https://user-images.githubusercontent.com/114259992/202832047-7567852f-cd23-422e-ae68-fa70f6bf9e8d.mp4

We can see that even for the Brightness it occurs sometimes:

For Red color inputs 

https://user-images.githubusercontent.com/114259992/202832603-e35e7344-0bce-4412-8380-c561f5d7fa84.mp4

For Green color inputs 

https://user-images.githubusercontent.com/114259992/202832588-72d2a7c2-149f-4106-b14c-4344f7b2e869.mp4

For Blue color inputs 

https://user-images.githubusercontent.com/114259992/202832615-52ffd5b8-da13-4407-ac09-d393ac49a53a.mp4
