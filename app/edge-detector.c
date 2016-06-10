
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<assert.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>

char* loadFile( char* filename, size_t * length)
{
	int fd;
	int bytes;
	char* buffer;
	printf("opening file %s\n", filename);
	fd = open(filename, O_RDONLY);
	*length = lseek(fd, 0, SEEK_END) + 1;
	close(fd);
	fd = open(filename, O_RDONLY);
	printf("File size = %lu\n", *length);
	buffer = malloc(*length);
	bytes = read(fd, buffer, *length);
	printf("Read %d bytes\n", bytes);
	close(fd);
	return buffer;
}

void writeFile(char* filename, char * buffer, ssize_t length)
{
	int fd;
	ssize_t bytes;
	printf("Saving to file %s\n", filename);
	fd = open(filename, O_CREAT|O_WRONLY, 0770);
	if(fd == -1)
	{
			printf("Could not open file for writting: %s\n",strerror(errno));
	}
	printf("File size = %lu\n", length);
	bytes = write(fd, buffer, length);
	if(bytes == -1)
	{
		printf("Could not write to file: %s\n",strerror(errno));
	}
	printf("%lu bytes written\n", bytes);
	close(fd);
	return ;
}

int main(int argc, char *argv[])
{
	char * buffer;
	int bytes;
	ssize_t length;
	char * filename = argv[1];
	char * outfile = argv[2];
	int fp;

	buffer = loadFile( filename, &length);
	printf("File size = %lu\n", length);

	fp= open("/dev/edge",O_RDWR);
	bytes  = write(fp, buffer, length);
	free(buffer);

	buffer = malloc(length);
	memset(buffer,0,length);
	bytes = read(fp,buffer,length);
	writeFile(outfile,buffer,length);
	free(buffer);

/*
	int i=0;
	while(i<11)
	{
		memset(buffer,65+i,50);




		if(bytes  < 0)
		{
			printf("Error in buffer read\n");
			exit(1);
		}
		printf("\n Buffer: %s\n" , buffer);
		i++;

	}
*/
	close(fp);
	return 0;
}