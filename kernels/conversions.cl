__kernel void conversions()
{
  printf("rte: %d %d %d %d %d %d %d %d\n",
    convert_int_rte(0.5f), convert_int_rte(-0.5f), convert_int_rte(1.1f), convert_int_rte(-1.1f), convert_int_rte(1.5f), convert_int_rte(-1.5f), convert_int_rte(1.7f), convert_int_rte(-1.7f));

  printf("rtz: %d %d %d %d %d %d %d %d\n",
    convert_int_rtz(0.5f), convert_int_rtz(-0.5f), convert_int_rtz(1.1f), convert_int_rtz(-1.1f), convert_int_rtz(1.5f), convert_int_rtz(-1.5f), convert_int_rtz(1.7f), convert_int_rtz(-1.7f));

  printf("rtp: %d %d %d %d %d %d %d %d\n",
    convert_int_rtp(0.5f), convert_int_rtp(-0.5f), convert_int_rtp(1.1f), convert_int_rtp(-1.1f), convert_int_rtp(1.5f), convert_int_rtp(-1.5f), convert_int_rtp(1.7f), convert_int_rtp(-1.7f));

  printf("rtn: %d %d %d %d %d %d %d %d\n",
    convert_int_rtn(0.5f), convert_int_rtn(-0.5f), convert_int_rtn(1.1f), convert_int_rtn(-1.1f), convert_int_rtn(1.5f), convert_int_rtn(-1.5f), convert_int_rtn(1.7f), convert_int_rtn(-1.7f));
}
