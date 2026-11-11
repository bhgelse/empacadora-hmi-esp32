# Diagnóstico de la planta

Fotos y hallazgos del sistema actual de cuatro empacadoras de sacos de 50 kg. Las imágenes se publican sin la dirección MAC de los equipos.

## Proceso actual

Cada empacadora tiene dos niveles. En el **piso superior** están la tolva, la compuerta de alimentación (cilindro neumático) y el balde de pesaje sobre una base en U. En el **piso inferior** están el ducto de descarga al saco y la banda transportadora. El **pesaje es por contrapeso**: al vencer el contrapeso, el balde presiona un microswitch que da por cumplidos los 50 kg. Otro microswitch, accionado por el pedal, habilita la descarga, y sin el interruptor de arranque no se llena ni se descarga. La banda la arranca el operador con un sistema aparte.

| | |
|---|---|
| ![Vista general](images/planta/01-vista-general.jpg) **1.** Vista general del área de empaque | ![Piso superior](images/planta/02-piso-superior.jpg) **2.** Piso superior: tolva, compuerta, balde y caja eléctrica |
| ![Base del balde](images/planta/03-base-balde.jpg) **3.** Base del balde con ventanas de inspección | ![Cilindro y compuerta](images/planta/04-cilindro-compuerta.jpg) **4.** Cilindro neumático acoplado por palanca a la compuerta |
| ![Microswitch y contrapeso](images/planta/05-microswitch-contrapeso.jpg) **5.** Microswitch y varilla suspendida del pesaje por contrapeso | ![Corrosión](images/planta/06-corrosion-ducto.jpg) **6.** Interior de un ducto con corrosión severa y sales |
| ![Piso inferior](images/planta/07-piso-inferior-banda.jpg) **7.** Piso inferior: ducto de descarga, saco y banda | ![Tablero Micro810](images/planta/08-tablero-micro810.jpg) **8.** Tablero local: Micro810, temporizador LADR2 y anotaciones de tiempos |

## Tablero de totalización

El conteo de sacos se hace con sensores ópticos al final de la banda. Las señales llegan a un tablero con un **Micro820**, un servidor serial **EKI-1524** de cuatro puertos con salida Ethernet y una HMI Allen-Bradley que muestra los totalizadores por turno y generales. Los contadores se reinician con tarjetas RFID por empacadora.

| | |
|---|---|
| ![HMI de totalización](images/planta/09-hmi-totalizacion.jpg) **9.** Frente del tablero: HMI y etiquetas RFID | ![Interior del tablero](images/planta/10-tablero-totalizacion.jpg) **10.** Interior: Micro820, EKI-1524, relés y fuente de 24 V |
| ![Micro820](images/planta/11-micro820.jpg) **11.** Micro820 con las ranuras de expansión cubiertas | ![EKI-1524](images/planta/12-eki1524.jpg) **12.** EKI-1524, servidor serial de cuatro puertos |

## Inventario de equipos observados

| Equipo | Ubicación |
|---|---|
| PLC Allen-Bradley **Micro810** (12AWA) | Tablero local de la empacadora |
| Temporizador Schneider **LADR2** y minidisyuntores | Tablero local |
| PLC Allen-Bradley **Micro820** (2080-LC20-20QWB) | Tablero de totalización |
| Servidor serial **EKI-1524** (4 puertos) | Tablero de totalización |
| Fuente Allen-Bradley **1606-XLP** (24 V) | Tablero de totalización |
| HMI Allen-Bradley con totalizadores y etiquetas RFID | Frente del tablero de totalización |

## Hallazgos

- **Precisión limitada:** el peso se infiere de un único disparo mecánico que depende del ajuste del contrapeso; no se mide ni se registra el peso real de cada saco.
- **Corrosión severa** en soportes, mecanismos de disparo, ductos, mangueras y tableros, con fallas de contacto y desajustes.
- **Lógica dispersa:** microswitches, contactor con temporizador y PLC, con tiempos ajustados a mano (en el tablero se ve la anotación manuscrita "TREBOTE = 400" y "T = 1200").
- **Sin trazabilidad ni supervisión integrada** de pesos, estados y alarmas.
- **Capacidad instalada sin aprovechar:** entradas, salidas, relés y ranuras de expansión del Micro820 y puertos del EKI-1524.

## Recomendaciones para el entorno corrosivo

- Celdas de carga **selladas y de acero inoxidable**.
- Gabinetes **IP66** o de acero inoxidable, con prensaestopas y sellos adecuados.
- **Recubrimiento protector** en las tarjetas electrónicas y tubería flexible hermética.
- Reemplazar los microswitches expuestos por sensores con carcasa sellada.
- Plan de limpieza e inspección periódica de los tableros.
- Revisar con el área de seguridad y salud en el trabajo la clasificación del área por polvo.
