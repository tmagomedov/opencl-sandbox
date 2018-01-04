#include <CL/opencl.h>
#include <stdio.h>
#include <stdlib.h>

void printUsage(const char* programName)
{
  printf("Tester for OpenCL C runtime compilers behaviour. It compiles given program and calls all kernels inside it.\n");
  printf("Usage: %s <OpenCL program file>\n", programName);
}

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    printUsage(argv[0]);
    exit(EXIT_FAILURE);
  }
  // Load OpenCL program source code to string
  FILE* sourceFile = fopen(argv[1], "r");
  if (!sourceFile)
  {
    perror(argv[1]);
    printUsage(argv[0]);
    exit(EXIT_FAILURE);
  }
  fseek(sourceFile, 0, SEEK_END);
  size_t size = ftell(sourceFile);
  char *source = calloc(size + 1, sizeof(char));
  if (!source)
  {
    fprintf(stderr, "Failed to allocate %zu bytes\n", size + 1);
    exit(EXIT_FAILURE);
  }
  rewind(sourceFile);
  fread(source, sizeof(char), size, sourceFile);
  fclose(sourceFile);

  printf("OpenCL source code:\n\"%s\"\n", source);
  //TODO: platforms loop
  //TODO: devices loop
  //TODO: build program
  //TODO: run all kernels in program, one by one
}
