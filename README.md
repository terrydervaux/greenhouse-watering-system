# Greenhouse Watering System

## Wiring

![wiring](https://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/terrydervaux/greenhouse-watering-system/master/doc/wiring.iuml?token=GHSAT0AAAAAACDOM6BHJFFS5SKESB4Z2GXGZFJLRPQ)

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

## How to control the watering system using the API

- Find the watering system IP on your internet router

```bash
export GREENHOUSE_WATERING_SYSTEM_IP="your_watering_system_ip"
```

- Retrieve current pump status

```bash
curl -vvv -X GET http://$GREENHOUSE_WATERING_SYSTEM_IP/relay
```

- Enable the pump

```bash
curl -X POST http://$GREENHOUSE_WATERING_SYSTEM_IP/relay -d 'relayActivation=true’ 
```

- Disable the pump

```bash
curl -vvv -X POST http://$GREENHOUSE_WATERING_SYSTEM_IP/relay -d 'relayActivation=false’
```

## How to control the watering system from HomeAssistant

- Add the watering system into your `configuration.yaml`

```yaml
switch:
  - platform: command_line
    switches:
      relay_switch:
        command_on: 'curl -X POST http://$GREENHOUSE_WATERING_SYSTEM_IP/relay -d relayActivation=true'
        command_off: 'curl -X POST http://$GREENHOUSE_WATERING_SYSTEM_IP/relay -d relayActivation=false'
        command_state: 'curl -X GET http://$GREENHOUSE_WATERING_SYSTEM_IP/relay'
        value_template: '{{ value == "{relayActivation=true}" }}'
        friendly_name: Watering System
```

- Replace `$GREENHOUSE_WATERING_SYSTEM_IP` by your watering system IP that can be
  found on your internet router
- Restart HomeAssistant

## Hardware

### Board: LC-relais-ESP12-1R-D8

- [Amazon link](https://www.amazon.fr/dp/B083QJPTVK?psc=1&ref=ppx_yo2ov_dt_b_product_details)
- [Technical documentation](http://www.chinalctech.com/m/view.php?aid=479)

### Serial Connection: DSD TECH SH-U06B USB

- [Amazon link](https://www.amazon.fr/dp/B09PYQL5J6?psc=1&ref=ppx_yo2ov_dt_b_product_details)
- [Technical documentation](https://tasmota.github.io/docs/Getting-Started/#serial-connection)

### Pump: Grothen G328

- [Amazon link](https://www.amazon.fr/dp/B07XMPNB1T?psc=1&ref=ppx_yo2ov_dt_b_product_details)
