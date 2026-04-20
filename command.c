#include "command.h"
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

 void listDir() {
	//ls
	printf("this is ls: not implemented yet\n");
	return;
 }
 
 void showCurrentDir() {
	//pwd
	char path[256];
	memset(path, 0, sizeof(path));
	if (getcwd(path, sizeof(path)) == NULL) {
		perror("getcwd");
	}
	write(STDOUT_FILENO, path, strlen(path));
	write(STDOUT_FILENO, "\n", 1);
 }

 void makeDir(char *dirName) {
	//mkdir
	if (mkdir(dirName, 0755) == -1) {
		perror("mkdir failed");
	}
 }

 void changeDir(char *dirName) {
	//cd
	printf("this is cd: not implemented yet\n");
	return;
 }
 
 void copyFile(char *sourcePath, char *destinationPath) {
	//cp
	printf("this is cp: not implemented yet\n");
	return;
 }

 void moveFile(char *sourcePath, char *destinationPath) {
	 //mv
	 printf("this is mv: not implemented yet\n");
	 return;
}
 
 void deleteFile(char *filename) {
	 //rm
	 printf("this is rm: not implemented yet\n");
	 return;
}

 void displayFile(char *filename) {
	 //cat
	 printf("this is cat: not implemented yet\n");
	 return;
}
