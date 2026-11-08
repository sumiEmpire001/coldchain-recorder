import unittest
from core import ColdChainRecorder

class RecorderTests(unittest.TestCase):
    def test_alarm_and_recovery(self):
        r = ColdChainRecorder(alarm_after_seconds=30)
        self.assertFalse(r.record(0, 10)["alarm"])
        self.assertTrue(r.record(30, 10)["alarm"])
        self.assertFalse(r.record(31, 5)["alarm"])
        self.assertEqual(r.record(32, 10)["excursion_seconds"], 0)
    def test_invalid(self):
        r = ColdChainRecorder()
        with self.assertRaises(ValueError): r.record(1, float("nan"))
        r.record(1, 5)
        with self.assertRaises(ValueError): r.record(1, 5)
        with self.assertRaises(ValueError): ColdChainRecorder(10, 2)
