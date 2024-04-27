# SPI && UART && Interrupt Mechanism
<div align="center"><img src="https://github.com/Mo-Alsehli/BluePill_Projects/assets/98949843/5af90f16-b9ed-4b1b-a998-fdf081e7e382"/></div>

**This Project Aims to use SPI to communicate between Master and Slave MCUs**

## Procedure
1. Created Drivers for UART and SPI.
2. Created The Application Layer.
3. The main application contains the code for both master and slave controlled by `#ifdef` directive.
4. Used Debugging tools to ensure and test code and logic.
5. Run the Project on simulation tools.


## Simulation.
**1. Master Sends Data using a polling mechanism inside the UART Callback function**

https://github.com/Mo-Alsehli/BluePill_Projects/assets/98949843/368c4c3c-8abf-4efc-b85b-47867b9d7f53


**2. Master-Slave Communication:**
- Master used a Polling mechanism to send but the slave used an interrupt mechanism to receive.

https://github.com/Mo-Alsehli/BluePill_Projects/assets/98949843/3bd0bd55-7c67-4f17-a74b-beea7a137f96
