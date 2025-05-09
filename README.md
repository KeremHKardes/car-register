# Car Registration System in C

This is a simple C program that collects car information from the user (brand, model, manufacture date, serial number, gas tank capacity), validates it, and writes it into a file named `Cars.txt`.

## 💡 Features

- Input validation for brand/model, date, serial number, and gas tank capacity
- Date format: `day-month-year`
- Saves all valid entries into a file called `Cars.txt`
- Uses C structures and modular design

## 🛠️ How to Compile

You can compile the code using GCC:

```bash
gcc -o car_app main.c
