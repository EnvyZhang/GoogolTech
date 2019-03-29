//------------------------------------------------
// 累加求和
// begin 累加起点
// end   累加终点
//------------------------------------------------
int sum;

int add(int begin,int end)
{
	int i;
	int cc;
	
	i=begin;
lbl_loop:
	cc = i > end;
	if(cc) goto lbl_end;
	sum = sum + i;
	i = i + 1;
	goto lbl_loop;
lbl_end:
	return sum;
}