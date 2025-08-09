Bare metal implementation  of an SPI driver to interface with ADXl345 accelerometer using STM32 development board 
## Features
- SPI2 initialization with peripheral clock = 1MHz.
- SPI 4-wires enabled for both SPI devices
- SPI mode 3
- 8-bit spi data frame 
## Requirements
### Hardware
- Discovery STM32 development board (STM32F411x series)
- Multimeter (optional for debugging)
- AZ-Delivery Logic Analyzer (optional for debugging)
- 4.7 KOhm resistor (SDO pin in ADXl345 needs to be pulled up after desoldering the original existing resistor on ADXl345 IC
  since SDO pin is originally pulled down to the ground)
  <img width="355" height="458" alt="image" src="https://github.com/user-attachments/assets/c3988879-7749-44fa-ade2-d27ec480c732" />
- Soldering device
- Bread Board 

### Software
- STM32CubeIDE or compatible toolchain
- PulseView (for debugging purpose)
Reading of the device ID : 

<img width="1515" height="604" alt="image" src="https://github.com/user-attachments/assets/9974e630-c594-4902-92f8-a22f160ae115" />

Reading of data axis 

<img width="1902" height="950" alt="image" src="https://github.com/user-attachments/assets/6e4f1753-33f8-483a-8cf9-bbf833388234" />

<img width="1889" height="965" alt="image" src="https://github.com/user-attachments/assets/9bc523a2-840f-4699-8d60-537df6814d1b" />


## Installation
1. Clone this repository:
   ```bash
   git clone https://github.com/Asma-Prog-Eng/SPI_ADXL345_DRIVER
   
2. Import project into STM32CubeIDE:
File → Import... → Existing Projects into Workspace

3. Update the include path directories ,  to CMSIS folder ( under Project properties -> C/C++ General -> Includes : delete existing CMSIS path directory and  add the path to CMSIS folder <br />,
   that is included in the project, : Add -> File System <br />

4. Rebuild project dependenciesFile 

## Usage
Initialization : adxl_init() () <br />
Read data axis : adxl_read_values(DATA_START_ADDR, data_rec,6)
## Project Structure

├── Core<br />
├── Inc<br />  → adxl345.h , spi.h <br />
├── Src<br /> → asxl345.c, spi.c <br /> → main.c

## Troubleshooting

No data received on z axis and data for x and y axis are not really varying while shaking the adxl345: <br />
- Verify CS signal (polarity should be active low)

Data consistency while reading device ID: <br />
- Verify CS signal <br />
- Verify spi mode
- Check voltage levels at CS pin and at SDO pin <br />

## Known Limitations
- Calibration not yet implemented : axis offset
- limited to 4g resolution for adxl345
## Contributing
Pull requests are welcome. For major changes, open an issue first.

## License
MIT License <br />
Copyright (c) [2025] [Asma Askri]
