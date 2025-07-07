gcc -c wordle.c -o wordle.o
ar rcs libwordle.a wordle.o
go run api.go
