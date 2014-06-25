concurrentes
============

FIUBA - 1 Cuatrimestre - 2014 - Técnicas de Programación Concurrente

Para eliminar recursos ipc

Semaforos:

ipcs | grep -A 4 "nsems" | cut -d ' ' -f 2 | grep [0-9] | xargs -L 1 ipcrm -s

Colas:

ipcs | grep -A 4 "utilizados mensajes" | cut -d ' ' -f 2 | grep [0-9] | xargs -L 1 ipcrm -q

Para ver procesos corriendo usar "htop"