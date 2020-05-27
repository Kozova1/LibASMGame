test:
	cp testasm.asm testasm
	./asm.py testasm
	printf '\xff\xff' >> testasm
	cp ./testasm ../vm/testasm
	hexdump -C testasm

clean:
	rm testasm
