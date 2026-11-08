from math import isfinite

class ColdChainRecorder:
    def __init__(self, min_c=2, max_c=8, alarm_after_seconds=300):
        if not all(isfinite(v) for v in (min_c, max_c)) or min_c >= max_c:
            raise ValueError("invalid temperature range")
        if type(alarm_after_seconds) is not int or alarm_after_seconds < 0:
            raise ValueError("invalid alarm duration")
        self.minimum, self.maximum, self.delay = min_c, max_c, alarm_after_seconds
        self.last_time = None
        self.excursion_start = None
        self.events = []

    def record(self, timestamp, temperature_c):
        if type(timestamp) is not int or timestamp < 0 or (self.last_time is not None and timestamp <= self.last_time):
            raise ValueError("invalid or out-of-order timestamp")
        if not isinstance(temperature_c, (int, float)) or not isfinite(temperature_c):
            raise ValueError("invalid temperature")
        self.last_time = timestamp
        outside = temperature_c < self.minimum or temperature_c > self.maximum
        if outside and self.excursion_start is None:
            self.excursion_start = timestamp
        duration = timestamp - self.excursion_start if outside else 0
        result = {"timestamp": timestamp, "temperature_c": temperature_c,
                  "out_of_range": outside, "excursion_seconds": duration,
                  "alarm": outside and duration >= self.delay}
        if not outside:
            self.excursion_start = None
        self.events.append(result)
        return result
