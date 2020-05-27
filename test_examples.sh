pio ci --board=uno --lib=src ./examples/heartbeat
pio ci --board=uno --lib=src ./examples/periodic
pio ci --board=uno --lib=src ./examples/timeout

pio ci --board=esp32dev --lib=src ./examples/heartbeat
pio ci --board=esp32dev --lib=src ./examples/periodic
pio ci --board=esp32dev --lib=src ./examples/timeout
