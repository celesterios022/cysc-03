# Control Proporcional

## Consigna

Se debe desarrollar una aplicacion de control proporcional de temperatura de doble nucleo.

### Nucleo 0

1- Inicializacion de perifericos

2- Hacer una lectura de temperatura del NTC

3- Hacer una lectura del potenciometro. Convertirlo a una referencia de temperatura (0-35 C)

4- Enviar ambas temperaturas al nucleo 1 con una `queue`.

### Nucleo 1

1- Esperar a que haya un dato listo en la `queue` para leer.

2- Si la temperatura indicada por el potenciometro es mayor a la del NTC, encender proporcionalmente el LED azul (PWM)

3- Si la temperatura indicada por el potenciometro es menor a la del NTC, encender proporcionalmente el LED rojo (PWM)


Hacer un `README.md` con el siguiente contenido:

```markdown
# Control Proporcional - Dualcore


Alumno: Nombre y apellido

Curso: Curso

Materia: Computadoras y Sistemas de Control
```

## Orientacion

- Datasheet del [RP2040][rp2040].
- Datasheet de la [Raspberry Pico][pico].
- Raspberry Pico [SDK][sdk] para C/C++.
- Documentacion de [Wokwi][wokwi].
- Pinout de la Raspberry Pico:

![pinout][pinout]

## Entrega

- Crear un repositorio con el nombre `cysc-02`
- Subir el `README.md` y el `main.c`

[rp2040]: https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf
[pico]: https://datasheets.raspberrypi.com/pico/pico-datasheet.pdf
[sdk]: https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-c-sdk.pdf
[wokwi]: https://docs.wokwi.com/?utm_source=wokwi
[pinout]: https://www.raspberrypi.com/documentation/microcontrollers/images/Pico-R3-SDK11-Pinout.svg
