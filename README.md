# Fault Injection on AES: Cryptographic Hardware Attack

### Overview
This project focused on exploiting vulnerabilities in AES encryption by inducing faults into embedded firmware running on an **ATMega328P** microcontroller and analyzing resulting data to recover the cipher key.

### Tech Stack
- **Firmware**: C/C++ on Arduino IDE
- **Microcontroller**: ATMega328P
- **Hardware Tools**: RP2040 (for fault injection), Zynq-7000 FPGA (initial testing)
- **Analysis**: Python (differential analysis)

### Key Features
- Implemented custom AES encryption in C on the victim MCU.
- Designed fault injection mechanism to corrupt encryption rounds.
- Collected and analyzed 1500 ciphertexts to extract partial cipher key.
- Used Python for statistical correlation and trace analysis.

### Development Summary
- Wrote both victim and attacker firmware in C.
- Designed fault injection testbed using GPIO-triggered timing delays.
- Switched to RP2040 for more precise glitching after testing with Zynq FPGA.
- Performed statistical analysis to reverse-engineer AES keys using Python scripts.
