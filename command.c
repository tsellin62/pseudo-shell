#include "command.h"
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

 void listDir() {
	//ls
	return;
 }
 
 void showCurrentDir() {
	//pwd
	char path[256];
	memset(path, 0, sizeof(path));
	if (getcwd(path, sizeof(path)) == NULL) {
		perror("getcwd");
	}
	write(1, &path, strlen(path));
 }

 void makeDir(char *dirName) {
	//mkdir
	if (mkdir(dirName, 0755) == -1) {
		perror("mkdir failed");
	}
 }

 void changeDir(char *dirName) {
	//cd
	return;
 }
 
 void copyFile(char *sourcePath, char *destinationPath) {
	//cp
	return;
 }

 void moveFile(char *sourcePath, char *destinationPath) {
	 //mv
	 return;
}
 
 void deleteFile(char *filename) {
	 //rm
	 return;
}

 void displayFile(char *filename) {
	 //cat
	 return;
}
