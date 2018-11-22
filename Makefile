passenger: ttc.h passenger.c test_passenger.c
	gcc -Wall ttc.h passenger.c test_passenger.c -o passenger
train: ttc.h train.c test_train.c
	gcc -Wall ttc.h train.c test_train.c -o train
station: ttc.h passenger.c station.c test_station.c
	gcc -Wall ttc.h passenger.c station.c test_station.c -o station
ttc: ttc.h passenger.c train.c station.c ttc.c 
	gcc -Wall -O6 ttc.h passenger.c train.c station.c ttc.c -o ttc
