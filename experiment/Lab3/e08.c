void print4(int a, int b, int c, int d) {
  println_int(a);
  println_int(b);
  println_int(c);
  println_int(d);
}

int main() {
  int v1=114,v2=514;
  int eq1=v1==v2, eq2=v1==v1,
      ne1=v1!=v2, ne2=v1!=v1,
      lt1=v1<v2, lt2=v1<v1,
      le1=v1<=v2, le2=v1<=v1,
      gt1=v1>v2, gt2=v1>v1,
      ge1=v1>=v2, ge2=v1>=v1;
  print4(eq1, eq2, ne1, ne2);
  print4(lt1, lt2, le1, le2);
  print4(gt1, gt2, ge1, ge2);

  int land1=114&&514, land2=114&&0, land3=0&&1, land4=0&&0;
  int lor1=1||514, lor2=1||0, lor3=0||1, lor4=114||0;
  int lnot1=!114514, lnot2=!0, lnot3=!lnot2;
  int lnot4=-(!123+2*3-1)*(-1*43);
  
  int super_hard = -(!((~3 || 2) && 1)) || (4 && -5);

  print4(land1, land2, land3, land4);
  print4(lor1, lor2, lor3, lor4);
  print4(lnot1, lnot2, lnot3, lnot4);
  
  println_int(super_hard);

  println_int(-(!((~3 || 2) && 1)) || (4 && -5)+222);


  return 0;
}
