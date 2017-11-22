#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

typedef unsigned int uint_t;
typedef struct process {
	uint_t pid;
	char *handle;
	uint_t access_ring;
} process_t;

process_t plist[65536];
uint_t plist_idx = 0; size_t plist_size = 0;

process_t make_process(char *h, uint_t access_lvl) {
	srand(time(NULL));
	uint_t p = (uint_t)(rand() % 10000);
	for(uint_t i = 0; i < plist_idx; i++) if(p == plist[i].pid) { p = (uint_t)(rand() % 10000); i = 0; }
	process_t ret;
		ret.pid  = p;
		ret.handle = h;
		ret.access_ring = access_lvl;
	plist[plist_idx++] = ret; plist_size += sizeof(ret);
	return ret;
}

void pid_kill(uint_t pid) {
	for(uint_t i = 0; i < plist_idx; i++) if(pid == plist[i].pid) { plist[i] = plist[plist_idx]; plist_idx--; printf("\nKilled\n"); return;}
	printf("\n=================\nNo such PID found\n=================\n"); return;
}

void handle_kill(char *handle) {
	for(uint_t i = 0; i < plist_idx; i++) if(handle == plist[i].handle) { plist[i] = plist[plist_idx]; plist_idx--; printf("\nKilled\n"); return;}
	printf("\n===================\nNo such Handle found\n====================\n"); return;
}

void print_process_list() {
       	printf("--------------------------------------------------------------------------------\n");
	printf("PID\t\tHANDLE\t\tACCESS\n");
	for(uint_t i = 0; i < plist_idx; i++) {
		process_t p = plist[i];
		printf("%d\t\t%s\t\t%d\n",p.pid, p.handle, p.access_ring);
	}
	printf("--------------------------------------------------------------------------------\n");
	return;
}

int main(int argc, char **argv) { if(argc != 2) { printf("Usage: %s PROCESSCOUNT", argv[0]); return 1; }
	srand(time(NULL));
	for(uint_t i = 0; i < atoi(argv[1]); i++) {
		char *tmp = "test";
		make_process(tmp, rand() %3);
	} print_process_list();
	return 0;
}	
