__kernel void bool_to_int_vec()
{
  int val = true;
  int2 val2 = true;
  printf("int val = true; // val=%d\n", val);
  printf("int2 val2 = true; // val2=%v2d\n", val2);
  if(val2.x == -1 && val2.y == -1)
  {
    printf("Compiler follows specification for bool->intn conversion, OK\n");
  }
  else
  {
    printf("Compiler does not follow specification for bool->intn conversion, FAILED\n");
  }
}
