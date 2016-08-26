
import numpy as np

lower_freq  = np.linspace(1995000000, 1999500000, 21)
upper_freq  = np.linspace(2005000000, 2000500000, 21)
dist        = np.linspace(  10000000,    1000000, 21) # 10M to 1M
lower3_freq = lower_freq - dist
upper3_freq = upper_freq + dist

def insert_if_new(array, value):
    if len(np.where(array == value)[0]) == 0:
        array = np.append(array, value)
    return array

cal = np.append(lower_freq, upper_freq)
for f in lower3_freq:
    cal = insert_if_new(cal, f)
for f in upper3_freq:
    cal = insert_if_new(cal, f)
cal.sort()