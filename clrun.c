#include <CL/opencl.h>
#include <stdio.h>
#include <stdlib.h>

void printUsage(const char* programName)
{
  printf("Tester for OpenCL C runtime compilers behaviour. It compiles given program and calls all kernels inside it.\n");
  printf("Usage: %s <OpenCL program file>\n", programName);
}

// Allocates zero-filled memory end terminates in case of failure
void* allocate(size_t size)
{
  void* ret = calloc(size, 1);
  if (!ret)
  {
    fprintf(stderr, "Failed to allocate %zu bytes\n", size);
    exit(EXIT_FAILURE);
  }
  return ret;
}

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    printUsage(argv[0]);
    exit(EXIT_FAILURE);
  }
  // Load OpenCL program source code to string.
  FILE* sourceFile = fopen(argv[1], "r");
  if (!sourceFile)
  {
    perror(argv[1]);
    printUsage(argv[0]);
    exit(EXIT_FAILURE);
  }
  fseek(sourceFile, 0, SEEK_END);
  size_t size = ftell(sourceFile);
  char *source = allocate((size + 1) * sizeof(char));
  rewind(sourceFile);
  fread(source, sizeof(char), size, sourceFile);
  fclose(sourceFile);

  printf("OpenCL source code:\n\"%s\"\n", source);
  cl_uint numPlatforms = 0;
  cl_int clRet = clGetPlatformIDs(0, NULL, &numPlatforms);
  if (CL_SUCCESS != clRet || 0 == numPlatforms)
  {
    printf("No compatible OpenCL platforms found\n");
    exit(EXIT_FAILURE);
  }
  cl_platform_id* platforms = allocate(numPlatforms * sizeof(cl_platform_id));
  clGetPlatformIDs(numPlatforms, platforms, NULL);
  for (cl_uint i = 0; i < numPlatforms; i++)
  {
    char* platformName = NULL;
    size_t platformNameSize = 0;
    clRet = clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, 0, NULL, &platformNameSize);
    platformName = allocate(platformNameSize + 1);
    clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, platformNameSize, platformName, NULL);
    printf("Platform \"%s\"\n", platformName);
    free(platformName);
    //TODO: devices loop
    //TODO: build program
    //TODO: run all kernels in program, one by one
  }
  free(platforms);
  free(source);
}
