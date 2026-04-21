#include "command.h"
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <libgen.h>
#include <fcntl.h>

void listDir() {
	//ls
	DIR* ptr;
	struct dirent* read_dir;
	ptr = opendir(".");

	while ((read_dir = readdir(ptr)) != NULL) {
		write(STDOUT_FILENO, read_dir->d_name, strlen(read_dir->d_name));
		write(STDOUT_FILENO, " ", 1);
	}

	write(STDOUT_FILENO, "\n", 1);
	closedir(ptr);
}
 
void showCurrentDir() {
	//pwd
	char path[256];
	memset(path, 0, sizeof(path));
	if (getcwd(path, sizeof(path)) == NULL) {
		char msg[] = "Could not print working directory.\n";
		write(STDOUT_FILENO, msg, strlen(msg)); 
	}
	write(STDOUT_FILENO, path, strlen(path));
	write(STDOUT_FILENO, "\n", 1);
}

void makeDir(char *dirName) {
	//mkdir
	if (mkdir(dirName, 0755) == -1) {
		char msg[] = "Directory already exists!\n";
		write(STDOUT_FILENO, msg, strlen(msg));
	}
 }

void changeDir(char *dirName) {
	//cd
	if (chdir(dirName) == -1) {
		char msg[] = "Failed to change directory\n";
		write(STDOUT_FILENO, msg, strlen(msg));
	}
}
 
void copyFile(char *sourcePath, char *destinationPath) {
	//cp
	char dst[1024];
	struct stat st;
	if (stat(destinationPath, &st) == 0 && S_ISDIR(st.st_mode)) {
		char* name = basename(sourcePath);
		size_t i = 0;
		while (i < strlen(destinationPath)) {
			dst[i] = destinationPath[i];
			i++;
		}
		dst[i] = '/';
		i++;
		for (size_t j = 0; j < strlen(name); j++) {
			dst[i] = name[j];
			i++;
		}	
		dst[i] = '\0';
	}
	else {
		size_t i = 0;
		while (i < strlen(destinationPath)) {
			dst[i] = destinationPath[i];
			i++;
		}
		dst[i] = '\0';
	}
	int src_fd = open(sourcePath, O_RDONLY);
	if (src_fd == -1) {
		char msg[] = "Could not find file\n";
		write(STDOUT_FILENO, msg, strlen(msg));	
		return;
	}
	int dst_fd = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (dst_fd == -1) {
		char msg[] = "Destination error\n";
		write(STDOUT_FILENO, msg, strlen(msg));
		close(src_fd);
	}

	char buf[4096];
	ssize_t bytes;
	while ((bytes = read(src_fd, buf, sizeof(buf))) > 0) {
		write(dst_fd, buf, bytes);
	}	
	close(src_fd);
	close(dst_fd);	
}

void moveFile(char *sourcePath, char *destinationPath) {
	//mv
	char dst[1024];
	struct stat st;
	 
	if (stat(destinationPath, &st) == 0 && S_ISDIR(st.st_mode)) {
		char* name = basename(sourcePath);
		size_t i = 0;
		while (i < strlen(destinationPath)) {
			dst[i] = destinationPath[i];
			i++;
		}
		dst[i] = '/';
		i++;
		for (size_t j = 0; j < strlen(name); j++) {
			dst[i] = name[j];
			i++;
		}
		dst[i] = '\0';
	}
	else {
		size_t i = 0;
		while (i < strlen(destinationPath)) {
			dst[i] = destinationPath[i];
			i++;
		}
		dst[i] = '\0';
	}
	int src_fd = open(sourcePath, O_RDONLY);
	int dst_fd = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0644);

	char buf[4096];
	ssize_t bytes;
	while ((bytes = read(src_fd, buf, sizeof(buf))) > 0) {
		write(dst_fd, buf, bytes);
	}	
	close(src_fd);
	close(dst_fd);
	unlink(sourcePath);
}
 
void deleteFile(char *filename) {
	//rm
	if (remove(filename) == -1) {
		char msg[] = "Could not remove file\n";	
		write(STDOUT_FILENO, msg, strlen(msg));
	}
}

void displayFile(char *filename) {
	//cat
	char buf[4096];
	int fd = open(filename, O_RDONLY);
	ssize_t bytes;
	while ((bytes = read(fd, buf, sizeof(buf))) > 0) {
		write(STDOUT_FILENO, buf, bytes);
	}
	close(fd);			
}
