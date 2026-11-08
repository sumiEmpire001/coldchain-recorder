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
