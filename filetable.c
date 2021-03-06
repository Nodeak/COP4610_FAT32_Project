#include "filetable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct FileTable* root = NULL;

void FTAdd(const char* fileName, const char* mode) {
	if (FTIsOpen(fileName)) {
		printf("File already open.\n");
	}
	else {
		struct FileTable* tmp = calloc(1, sizeof(struct FileTable));
		strcpy(tmp->name, fileName);
		strcpy(tmp->mode, mode);
		tmp->next = NULL;
		if (root == NULL) {
			root = tmp;
		}
		else {
			struct FileTable* itr = root;
			while (itr->next != NULL) {
				itr = itr->next;
			}
			itr->next = tmp;
		}
	}
}

void FTRemove(const char* fileName) {
	struct FileTable* itr1;
	struct FileTable* itr2 = NULL;
	for (itr1 = root; itr1 != NULL; itr2 = itr1, itr1 = itr1->next) {
		if (strcmp(itr1->name, fileName) == 0) {
			if (itr2 == NULL) {
				root = itr1->next;
			}
			else {
				itr2->next = itr1->next;
			}
			free(itr1);
			return;
		}
	}
}

int FTIsOpen(const char* fileName) {
	struct FileTable* itr;
	for (itr = root; itr != NULL; itr = itr->next) {
		if (strcmp(itr->name, fileName) == 0) {
			return 1;
		}
	}
	return 0;
}

int FTIsOpenInRead(const char* fileName) {
	struct FileTable* itr;
	for (itr = root; itr != NULL; itr = itr->next) {
		if (strcmp(itr->name, fileName) == 0) {
			if (strstr(itr->mode, "r") != NULL) {
				return 1;
			}
		}
	}
	return 0;
}

int FTIsOpenInWrite(const char* fileName) {
	struct FileTable* itr;
	for (itr = root; itr != NULL; itr = itr->next) {
		if (strcmp(itr->name, fileName) == 0) {
			if (strstr(itr->mode, "w") != NULL) {
				return 1;
			}
		}
	}
	return 0;
}

void FTPrint() {
	printf("\n\nFILE TABLE: \n");
	if (root != NULL) {
		struct FileTable* itr = root;
		FTPrintEntry(root);
		while (itr->next != NULL) {
			FTPrintEntry(itr->next);
			itr = itr->next;
		}
	}
}

void FTPrintEntry(struct FileTable* ent) {
	printf("--------------------------------\n");
	printf("File name: %s\nFile mode: %s\n", ent->name, ent->mode);
	printf("--------------------------------\n");
}

void FTCleanup() {
	struct FileTable* itr1 = root;
	struct FileTable* itr2;
	while (itr1 != NULL) {
		itr2 = itr1->next;
		free(itr1);
		itr1 = itr2;
	}
	root = NULL;
}
