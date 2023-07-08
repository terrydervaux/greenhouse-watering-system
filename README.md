# Greenhouse Watering System

## Wiring

![wiring](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/terrydervaux/greenhouse-watering-system/master/doc/wiring.iuml)

## How to build and flash the firmware

1. Download VScode
1. Install platformIO extension on VScode
1. Clone the repository using git
1. Create a file ``src/wifi_secrets.h`` containing

    ```cpp
    #define WIFI_SSID "your_wifi_ssid"
    #define WIFI_PASSWORD "your_wifi_password"
    ```

1. Build and flash the firmware using PlateformIO

## Hardware

### Board: LC-relais-ESP12-1R-D8

- [Amazon link](https://www.amazon.fr/dp/B083QJPTVK?psc=1&ref=ppx_yo2ov_dt_b_product_details)
- [Technical documentation](http://www.chinalctech.com/m/view.php?aid=479)

### Serial Connection: DSD TECH SH-U06B USB

- [Amazon link](https://www.amazon.fr/dp/B09PYQL5J6?psc=1&ref=ppx_yo2ov_dt_b_product_details)
- [Technical documentation](https://tasmota.github.io/docs/Getting-Started/#serial-connection)

### Pump: Grothen G328

- [Amazon link](https://www.amazon.fr/dp/B07XMPNB1T?psc=1&ref=ppx_yo2ov_dt_b_product_details)
