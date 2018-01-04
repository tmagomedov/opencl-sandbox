#include <CL/opencl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  printf("Hello world!\n");
  if(argc != 2)
  {
    printf("Usage: %s kernel_file\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  //TODO: load kernel to string
  //TODO: platforms loop
  //TODO: devices loop
  //TODO: build program
  //TODO: run program
}
