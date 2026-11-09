# coldchain-recorder

Temperature-excursion tracking with configurable acceptable range, duration-based alarms and recovery resets. In-memory prototype only: not certified for medical or food cold-chain monitoring, and missing readings are not automatically detected.

## Requirements and tests

Python 3.10+; standard library only.

```bash
python -m unittest discover -s tests -v
```

## Example

```python
from core import ColdChainRecorder
recorder = ColdChainRecorder()
print(recorder.record(0, 9))
print(recorder.record(300, 9))
```

GitHub Actions runs the unit tests across Python 3.10, 3.12 and 3.13. Check CI status before treating a push as verified.

## C++ Arduino / ESP32 implementation

The Python recorder is retained. An Arduino-compatible C++11 recorder at
`arduino/ColdChainRecorder/src/ColdChainRecorder.h` tracks temperature
excursions, delay before alarm and return-to-range. Invalid or out-of-order
readings produce an alarm-worthy invalid status for investigation.

`arduino/ColdChainRecorder/examples/IndicatorDemo` simulates temperatures
using a potentiometer and indicates the advisory alarm with an LED. It does
not use a calibrated temperature sensor. Pin mapping: Uno A0/D8; classic
ESP32 GPIO34/GPIO18. Add an actual calibrated temperature probe, logger,
clock, retained storage and independent alarm system for real monitoring.

C++ local verification:
```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```
GitHub Actions attempts host C++ and Uno/ESP32 firmware builds. Real devices,
sensor wiring, power interruptions, storage and long-duration timing are
untested. **Not approved for medication, vaccines, food safety or other
regulated cold-chain use.**
