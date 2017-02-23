rf433:rf433.c
	gcc -o rf433 rf433.c -lwiringPi
client:client.c
	gcc -o client client.c -lwiringPi

