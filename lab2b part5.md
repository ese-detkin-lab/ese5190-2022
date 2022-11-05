In part5, we connected the SCL and SDA line to the osciiloscope. We can find out that when we are using only the RGBC function, there are four I2C packet transmitted between broad and sensor : 

![1](https://user-images.githubusercontent.com/44985032/200098859-43a2644c-6068-41c7-b62e-18cddf9f9df2.jpg)

and if we zoom up, we can find out the bit change in each transmission packet. 

If we add another function, for example, calling the gesture method, we can see there are three more packet transmited: ![2](https://user-images.githubusercontent.com/44985032/200098891-0bf38f05-7451-4c43-95b5-ef83fa0d5a48.jpg)

if we only add the proximity method, one more packet is added: 
![3](https://user-images.githubusercontent.com/44985032/200098901-79023a0e-8305-47ab-90bf-0c897ca73302.jpg)



So, we can deduct that the four packets correspond to the r,g,b,c data of the sensor function. Below are the detailed screenshot for each packet. 
![4](https://user-images.githubusercontent.com/44985032/200099024-4d866f34-b69c-44cd-9e7e-158ec461e535.jpg)
![5](https://user-images.githubusercontent.com/44985032/200099026-15e47a2d-eb2f-446a-af0b-c9e3446375d7.jpg)
![6](https://user-images.githubusercontent.com/44985032/200099027-53185dfa-c069-4e5d-ad7f-f7073b5da144.jpg)
![7](https://user-images.githubusercontent.com/44985032/200099028-ef540d0d-a98e-46df-a4b1-2b007719c2ee.jpg)
