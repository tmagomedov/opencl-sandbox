__kernel void check_vector_literals()
{
  float4 val1 = (3, 2, 1, 0);
  printf("val1 %v4f\n", val1);

  float4 val2 = (float4)(0, 1, 2, 3);
  printf("val2 %v4f\n", val2);

  float4 val3 = 0;
  printf("val3 %v4f\n", val3);

  //float4 val4 = (float4)(0,1); //compilation error
  float4 val4 = (float4)(1);
  printf("val4 %v4f\n", val4);
}
