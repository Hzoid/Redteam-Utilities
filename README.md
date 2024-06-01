# Red Team Utilities

A collection of simple red team utilities for various system information checks and tasks.

## Table of Contents

- [Introduction](#introduction)
- [Utilities](#utilities)
  - [Installed Software Checker](#installed-software-checker)
  - [Disk Space Usage Checker](#disk-space-usage-checker)
- [Installation](#installation)
- [Contributing](#contributing)
- [License](#license)

## Introduction

This repository contains a collection of utilities designed to aid red team engagements by providing various system information checks. While a lot of this information can be pulled with other pentesting tools, these tools tend to flag AV / SIEM solutions, and so these binaries were programmed with evasion in mind.

## Utilities

### Installed Software Checker

This utility targets common install filepaths (such as Program Files) and retrieves installed software and their versions.

#### Usage

Without arguments, this utility will display installed programs and versions. To directly obtain the current Windows Defender version, pass the /defender argument.

```
.\schk.exe

Software: 7-Zip | Version: 22.1.0.0
Software: Audacity | Version: 3.4.2.0
Software: Greenshot | Version: 1.2.10.6
...
```

This is a WIP - it only performs one degree of folder checks of current, so folders like "Common Files" will be flagged as software.

### Disk Space Usage Checker

This utility provides information about disk space usage on the target system.

#### Usage

By default, the program will just display the disk usage of the current drive. If "/all" or "--all" is passed, it will iterate through the available drives and list their usage statistics. The program also differentiates between local and network based drives.

```
.\dchk.exe /all

C:\ (LOCAL)             458.55/465.12GB
D:\ (LOCAL)             261.15/2794.50GB
E:\ (UNKNOWN)           0.00/31.99GB
X:\ (LOCAL)             104.81/931.51GB
```

## Installation

To build and install these utilities, follow these steps:

1. Clone the repository:
    ```
    git clone https://github.com/yourusername/redteam-utilities.git
    ```
2. Navigate to the repository directory:
    ```
    cd redteam-utilities
    ```
3. Build the utilities using a C++ compiler (e.g., `g++`):
    ```
    g++.exe -std=c++17 -o schk.exe .\softwarecheck.cpp -lversion
    g++.exe -std=c++17 -o dchk.exe .\diskcheck.cpp
    ```

## Contributing

We welcome contributions! Please follow these steps to contribute:

1. Fork the repository.
2. Create a new branch for your feature or bugfix.
3. Commit your changes.
4. Push your branch and create a pull request.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
