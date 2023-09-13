# Consigna
Utilizando systick, programar al micro para que cada vez que se produzca una interrupcion externa eint0 se saque por el pin p0.22 una señal digital (0b000010101010000). En caso de llegar otra interrupcion por eint0, la secuencia se cancelará y se enviará un 1 por ese pin. Suponer un clock de 80 Mhz. Tener en cuenta que la señal digital tiene 10 ms de periodo
