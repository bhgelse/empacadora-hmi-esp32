# Hoja de ruta

| Fase | Actividades | Estado |
|---|---|---|
| 1. Diagnóstico y línea base | Pesaje de sacos, historial de fallas, inventario de tableros y señales | Parcial: registro fotográfico e inventario hechos; línea base pendiente |
| 2. Prototipo en banco | IND236, simulador de celdas, MAX3232, ESP32, firmware y HMI | Construido; pruebas de banco con medición pendientes |
| 3. Piloto en una empacadora | Celdas inoxidables, IND236 y gabinete sellado, en paralelo al sistema actual | Pendiente |
| 4. Integración industrial | Lógica en el Micro820 existente, IND236 integrado y HMI industrial | Pendiente |
| 5. Extensión | Replicar en las otras tres empacadoras con capacitación | Pendiente |

## Integración con la infraestructura existente

El tablero de totalización ya tiene un **Micro820** con ranuras de expansión libres y un **EKI-1524** de cuatro puertos seriales con salida Ethernet (uno por empacadora). La idea es trasladar la lógica validada en el ESP32 al Micro820 y llevar el peso de cada IND236 por el puerto serial del PLC o a través del EKI-1524, con una HMI industrial más grande. La forma exacta se valida con la documentación del fabricante y el área de automatización.

## Pendientes

- [ ] Ejecutar las pruebas de banco con medición ([docs/pruebas.md](pruebas.md)).
- [ ] Levantar la línea base en planta.
- [ ] Confirmar el GPIO real del cuarto interruptor (`PIN_BTN_RESET`).
- [ ] Definir el diagrama de conexión definitivo y el cableado en gabinete sellado.
- [ ] Piloto en una empacadora, con el sistema actual como respaldo.
