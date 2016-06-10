
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<assert.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include <sys/ioctl.h>
#include "../driver/edge-detect-algo.h"

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
	fd = open(filename, O_CREAT|O_WRONLY, 0660);
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

void setAlgorithm(EdgeDetectAlgorithm_T algo, int fp)
{
	int result = -1;

	result = ioctl(fp,SET_ALGO,algo);
	if(result == -1)
	{
		printf("Could not set algorithm: %s\n",strerror(errno));
	}

}


void setWindowSize(int x, int y, int fp)
{
	int result = -1;
	int * dim = malloc(2*sizeof(int));
	dim[0] = x;
	dim[1] = y;

	result = ioctl(fp,SET_MASK_SIZE,dim);
	if(result == -1)
	{
		printf("Could not set algorithm: %s\n",strerror(errno));
	}

}


int main(int argc, char *argv[])
{
	char * buffer;
	int bytes;
	ssize_t length;
	char * filename = argv[1];
	char * outfile = argv[2];
	int fp;
	EdgeDetectAlgorithm_T algorithm = SOBEL;

	buffer = loadFile( filename, &length);
	printf("File size = %lu\n", length);

	fp= open("/dev/edge",O_RDWR);

	setAlgorithm(algorithm, fp);
	setWindowSize(5, 5, fp);

	bytes  = write(fp, buffer, length);
	free(buffer);

	setAlgorithm(PREWITT, fp);
	setWindowSize(10, 10, fp);

	buffer = malloc(length);
	memset(buffer,0,length);
	bytes = read(fp,buffer,length);
	if(bytes == -1)
	{
		printf("Could not read from driver: %s\n",strerror(errno));
	}
	else
	{
		writeFile(outfile,buffer,length);
	}
	free(buffer);

	close(fp);
	return 0;
}
