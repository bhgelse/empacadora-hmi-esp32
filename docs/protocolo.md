# Protocolo ESP32 ↔ HMI

Puerto serial USB (UART0) a **115200 baudios, 8N1**. Un mensaje JSON por línea, terminado en `\n`. Los logs del ESP32 están apagados para que el puerto lleve solo JSON.

> El ESP32 reconoce los comandos por coincidencia de texto: escribe cada clave y valor **sin espacios** (`"cmd":"stop"`, no `"cmd": "stop"`). La HMI ya los envía así.

## ESP32 → HMI (estado)

Se envía cada 100 ms y al instante cuando cambia algo.

```json
{"peso":49.71,"grueso":0,"fino":0,"descarga":0,"auto":1,"estado":2,"bIni":1,"bPar":0,"pedal":0,"alarma":0,"run":1,"pOk":1,"man":0,"purga":0,"obj":50.00,"corte":40.00,"cg":0.50,"cf":0.30}
```

| Campo | Significado |
|---|---|
| `peso` | Peso en kg, ya con cero y span aplicados |
| `grueso`, `fino`, `descarga` | Salidas (0/1) |
| `auto` | 1 = modo automático, 0 = manual |
| `estado` | 0 detenida · 1 llenando · 2 llena (espera pedal) · 3 descargando |
| `bIni`, `bPar` | Entradas de INICIO (incluye bypass) y PARO |
| `pedal` | Pedal efectivo (físico, virtual o bypass) |
| `alarma` | 0 sin alarma, 1 a 4 (ver abajo) |
| `run` | 1 si la secuencia no está detenida |
| `pOk` | 1 si el peso es válido (trama reciente) |
| `man` | Bits de las compuertas manuales: 1 grueso, 2 fino, 4 descarga |
| `purga` | 1 durante VACIAR BALDE |
| `obj`, `corte`, `cg`, `cf` | Objetivo, corte de grueso, cola de grueso y cola de fino |

**Códigos de alarma:** 1 sobrellenado · 2 sin lectura de peso · 3 tiempo de llenado excedido · 4 descarga incompleta.

## HMI → ESP32 (comandos)

| Comando | Ejemplo |
|---|---|
| Modo | `{"cmd":"mode","value":"auto"}` o `"manual"` |
| Compuerta manual | `{"cmd":"manual","valvula":"grueso","value":true}` (`grueso`, `fino`, `descarga`) |
| Configuración | `{"cmd":"config","objetivo":50,"grueso":40,"colaG":0.5,"colaF":0.3}` |
| Inicio / paro | `{"cmd":"start"}` · `{"cmd":"stop"}` |
| Reconocer alarma | `{"cmd":"ack"}` |
| Vaciar balde | `{"cmd":"vaciar"}` |
| Pedal virtual | `{"cmd":"pedal","value":true}` (la HMI lo repite cada 1 s mientras se mantiene; el ESP32 lo suelta solo a los 3 s sin refresco) |
| Bypass | `{"cmd":"bypass","pedal":true}` · `{"cmd":"bypass","inicio":true}` |
| Cero | `{"cmd":"zero"}` |
| Span | `{"cmd":"span","patron":20}` |

El PARO y el reconocimiento de alarmas **no tienen bypass** a propósito.
