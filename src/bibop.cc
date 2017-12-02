#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_PAGE 9

enum type {
	Integer,
	Float,
	Char
};

enum state {
	Free,
	Used
};

typedef struct value {
        union {
			int i;
			float f;
			char c;
        } as;
} value;

typedef struct page_info {
	type t;
	void* p;
	int state;
} page_info;

void print_page_info(page_info* pages) {
	int i;

	for (i = 0; i < MAX_PAGE; i++) {
		fprintf(stdout, "page[%d]: \n", i);

		switch (pages[i].t) {
		case Integer:
			fprintf(stdout, "\ttype is Integer\n");
			if (pages[i].state == Free) fprintf(stdout, "\tState: free\n");
			else fprintf(stdout, "\tValue: %d\n", *((int*)(pages[i].p)));
			break;
		case Float:
			fprintf(stdout, "\ttype is Float\n");
			if (pages[i].state == Free) fprintf(stdout, "\tState: free\n");
			else fprintf(stdout, "\tValue: %f\n", *((float*)(pages[i].p)));
			break;
		case Char:
			fprintf(stdout, "\ttype is Char\n");
			if (pages[i].state == Free) fprintf(stdout, "\tState: free\n");
			else fprintf(stdout, "\tValue: %c\n", *((char*)(pages[i].p)));
			break;
		}
	}
}

int main(int argc, char** argv) {
	int i;

	page_info pages[MAX_PAGE];

	void *start_address, *end_address;
	size_t page_size;

	page_size = sizeof(value);
	start_address = sbrk(0);

	if (start_address == NULL) {
		fprintf(stderr, "Failed to get start_address\n");
		exit(1);
	}

	end_address = sbrk(page_size * MAX_PAGE);

	if (end_address == NULL) {
		fprintf(stderr, "Failed to get size of page_size * MAX_PAGE\n");
		exit(1);
	}

	fprintf(stdout, "start_address: %p\n", start_address);
	fprintf(stdout, "end_address: %p\n", end_address);

	for (i = 0; i < MAX_PAGE; i++) {
		pages[i].t = (type)(i % 3);
		pages[i].p = start_address + (page_size * i);
		pages[i].state = Free;
	}

	print_page_info(pages);


	fprintf(stdout, "\n\nTry allocate integer value 100 to pages[3]\n");

	int* same_value = (int*)pages[3].p;
	pages[3].state = Used;
	*same_value = 100;

	print_page_info(pages);

	return 0;
}
