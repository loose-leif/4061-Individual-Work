#include <stdio.h>
#include <stdlib.h>

// declarations of provided page table setup/teardown functions
// you don't need to do anything with this
int ***setup_page_table();
void free_page_table(int ***);

// TODO: Complete this function to translate virtual addresses to physical addresses
int translate(int virtual_addr, int ***page_table) {
	int physical_addr;

	// Your code goes here!
	// Split the virtual address into 3 indexes and an offset
	// Then index into page_table and combine the result with the offset

	//printf("%x\n", virtual_addr);

	//printf("hallo\n");

	int first = virtual_addr & 0b111111111100000000000000000000;
	first = first >> 20;

	//printf("%d\n", first);

	int sec = virtual_addr & 0b000000000011111100000000000000;
	sec = sec >> 14;

	//printf("%d\n", sec);

	int third = virtual_addr & 0b000000000000000011111100000000;
	third = third >> 8;

	//printf("%d\n", third);

	int off = virtual_addr & 0b000000000000000000000011111111;

	physical_addr = off | (page_table[first][sec][third] << 8 );

	return physical_addr;
}

int main(int argc, char *argv[]) {
	int ***page_table = setup_page_table();

	int addrs[4] = {0x0012ff67, 0x001459ea, 0x009999ff, 0x00abcdef};

	for (int i = 0; i < 4; i++) {
		printf("Translation of %x: %x\n", addrs[i], translate(addrs[i], page_table));
	}

	free_page_table(page_table);
	return 0;

}



