nasm -f elf64 square.asm -o square.o &&
gcc -Wall -g  -c main.c -o main.o &&
gcc -no-pie -o main main.o square.o && 
./main -r 10000 tests/rnd_3/output.txt tests/rnd_3/output_sorted.txt
