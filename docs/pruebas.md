# Pruebas

## Estado

| Tipo de prueba | Estado |
|---|---|
| Lógica del firmware en el PC con una planta simulada | **Realizada** (16 comprobaciones aprobadas) |
| Pruebas de banco con medición (IND236 + simulador de celdas + ESP32) | **Pendiente** |
| Línea base en planta (pesos de sacos, historial de fallas) | **Pendiente** |
| Piloto en una empacadora | **Pendiente** |

## 1. Lógica en el PC (simulación)

```bash
sh tools/pc_test/run.sh
```

Compila el `main.c` y el `control_logic.c` reales con stubs de ESP-IDF y una planta simulada (caudales de grueso, fino y descarga) y comprueba:

- INICIO abre grueso y fino juntos; el grueso cierra cerca de `corte − cola` y el fino cerca de `objetivo − cola`.
- Sin pedal **no** descarga; con un toque la descarga **continúa** aunque se suelte y termina con el balde vacío.
- Con INICIO sostenido, vuelve a llenar solo.
- **PARO** pone las salidas en 0 en el mismo ciclo (10 ms).
- Sobrellenado: alarma 1, llenado bloqueado; **reconocer** la limpia sin que se vuelva a disparar y el llenado sigue bloqueado mientras el peso esté alto.
- **VACIAR BALDE** espera el pedal, descarga y no reinicia el llenado.
- Sin tramas del IND236: alarma 2 a los ~500 ms y llenado cerrado.

Esto valida la **lógica**, no los tiempos del hardware real ni la comunicación con el IND236.

## 2. Plan de pruebas de banco

Hazlas con 3 repeticiones y guarda una foto o captura de cada una.

| Prueba | Procedimiento | Criterio de aceptación | Resultado |
|---|---|---|---|
| Lectura de peso | Variar el simulador (0, 0,5, 1,0, 1,5 y 2,0 mV/V) y comparar IND236 y HMI | Diferencia máxima ≤ 0,1 kg | Pendiente |
| Secuencia de llenado | INICIO con peso creciente | Cierra grueso en `corte − cola` y fino en `objetivo − cola` | Pendiente |
| Descarga con pedal | Un toque y pedal mantenido | Descarga completa; repite si se mantiene | Pendiente |
| Paro inmediato | PARO durante llenado y descarga | Salidas en cero en < 100 ms | Pendiente |
| Sobrellenado | Subir el simulador sobre el límite | Alarma, llenado bloqueado, descarga manual disponible | Pendiente |
| Pérdida de peso | Desconectar el RS-232 | Alarma "sin lectura" y llenado bloqueado | Pendiente |
| Reconocer alarma | Reconocer con la condición normalizada | La alarma se limpia y no se re-dispara | Pendiente |
| Comunicación HMI-ESP32 | Conectar y desconectar el puerto | Estado y comandos correctos | Pendiente |

**Cómo medir el paro:** graba el LED (o el relé) en cámara lenta del celular (240 fps) al presionar PARO y cuenta los cuadros hasta que se apaga (a 240 fps cada cuadro son ≈ 4 ms).

## 3. Línea base en planta

| Indicador | Valor |
|---|---|
| Sacos pesados en la muestra | Pendiente |
| Peso promedio (kg) | Pendiente |
| Desviación estándar (kg) | Pendiente |
| Peso máximo y mínimo (kg) | Pendiente |
| Sobrepeso promedio frente a 50 kg | Pendiente |
| Intervenciones por microswitches en el periodo | Pendiente |
| Tiempo de parada asociado (h) | Pendiente |

Fuentes sugeridas: pesaje de unos 30 sacos por empacadora con una báscula calibrada; tickets de la báscula camionera (peso despachado contra facturado); historial de órdenes de trabajo de mantenimiento.
