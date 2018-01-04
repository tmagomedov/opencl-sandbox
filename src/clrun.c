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

void printBuildLog(cl_program program, cl_device_id dev)
{
  size_t size = 0;
  clGetProgramBuildInfo(program, dev, CL_PROGRAM_BUILD_LOG, 0, NULL, &size);
  if (size > 2)
  {
    char* buildLog = allocate(size + 1);
    clGetProgramBuildInfo(program, dev, CL_PROGRAM_BUILD_LOG, size, buildLog, NULL);
    printf("Build log:\n");
    puts("============");
    puts(buildLog);
    puts("============");
  }
  else
  {
    printf("Build log is empty\n");
  }
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
  cl_uint nPlatforms = 0;
  cl_int clRet = clGetPlatformIDs(0, NULL, &nPlatforms);
  if (CL_SUCCESS != clRet || 0 == nPlatforms)
  {
    printf("No compatible OpenCL platforms found\n");
    exit(EXIT_FAILURE);
  }
  cl_platform_id* platforms = allocate(nPlatforms * sizeof(cl_platform_id));
  clGetPlatformIDs(nPlatforms, platforms, NULL);
  for (cl_uint i = 0; i < nPlatforms; i++)
  {
    char* platformName = NULL;
    size_t platformNameSize = 0;
    clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, 0, NULL, &platformNameSize);
    platformName = allocate(platformNameSize + 1);
    clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, platformNameSize, platformName, NULL);
    printf("Platform \"%s\"\n", platformName);
    free(platformName);

    cl_uint nDevices = 0;
    clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &nDevices);
    cl_device_id* devices = allocate(nDevices * sizeof(cl_device_id));
    clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, nDevices, devices, 0);
    for (cl_uint j = 0; j < nDevices; j++)
    {
      cl_device_id dev = devices[j];
      char* deviceName = NULL;
      size_t deviceNameSize = 0;
      clGetDeviceInfo(dev, CL_DEVICE_NAME, 0, NULL, &deviceNameSize);
      deviceName = allocate(deviceNameSize + 1);
      clGetDeviceInfo(dev, CL_DEVICE_NAME, deviceNameSize, deviceName, NULL);
      printf("Device \"%s\"\n", deviceName);
      cl_context context = clCreateContext(NULL, 1, &dev, NULL, NULL, &clRet);
      if (CL_SUCCESS == clRet)
      {
	cl_program program = clCreateProgramWithSource(context, 1, (const char**)&source, NULL, &clRet);
	if (CL_SUCCESS == clRet)
	{
          clRet = clBuildProgram(program, 1, &dev, "", NULL, NULL);
	  if (CL_SUCCESS == clRet)
	  {
	    printBuildLog(program, dev);

            //TODO: run all kernels in program, one by one
	  }
	  else
	  {
	    printf("Build failed\n");
	    printBuildLog(program, dev);
	  }
	  clReleaseProgram(program);
	}
	else
	{
	  printf("Failed to create program\n");
	}
        clReleaseContext(context);
      }
      else
      {
        printf("Failed to create context\n");
      }
    }
    free(devices);
  }
  free(platforms);
  free(source);
}
