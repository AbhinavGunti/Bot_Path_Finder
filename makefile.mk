a : client.o function.o gcc
    client.o function.o client.o : client.o header.h gcc
    - c client.c function.o : function.o header.h gcc
    - c function.c