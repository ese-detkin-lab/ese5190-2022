# I2C Trace - Part 05
## Firefly
### SCL(Clock) & SDA of APDS9960 to Logic Analyzer of CRO

- Connect the GND pin of Logic Analyzer to GND of the Adafruit QtPy RP2040 GND
- Connect the D0 pin of Logic Analyzer to SCL (Clock) pin of the APDS 9960 using the STEMMA QT-Male Header pins
- Connect the D1 pin of Logic Analyzer to SDA pin of the APDS 9960 using the STEMMA QT-Male Header pins
- Select Digital mode on the CRO and keep the D0 and D1 pins only selected to display the waveforms on those pins
- Push on the Trigger button to give the waveform triggering details
- Under the Trigger parameters, select Edge Triggered input, for Falling Edge on D0 pin

#### Output
![IMG20221104162239](https://user-images.githubusercontent.com/69215958/200067692-7182bca1-0f3a-4f72-8924-d43d013bc057.jpg)
  Zoomed-in Waveform at one time instant
- Observe that the transitions occur in D1 for falling edges of D0 but not at any rising edge
- Also, at every rising edge of D0, the data of D1 can be read to understand the state of the APDS9960/QTPY RP2040
![IMG20221104161759](https://user-images.githubusercontent.com/69215958/200068027-e4ba56ed-6208-4929-a9c5-c17fbcf74d75.jpg)
  Full Waveform at one time instant
