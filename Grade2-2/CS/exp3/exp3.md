```assembly
Dump of assembler code for function phase_2:
0x08048b74 <+0>:	push   %esi
0x08048b75 <+1>:	push   %ebx
0x08048b76 <+2>:	sub    $0x34,%esp	/*	栈指针减0x34 开辟栈帧*/
0x08048b79 <+5>:	lea    0x18(%esp),%eax
0x08048b7d <+9>:	mov    %eax,0x4(%esp)	
/*	将0x18(%esp)中的值存入 %esp偏移4字节的位置	作为read_six_number函数的第一个参数*/
0x08048b81 <+13>:	mov    0x40(%esp),%eax
0x08048b85 <+17>:	mov    %eax,(%esp)	/*	第二参数	*/
0x08048b88 <+20>:	call   0x80492cb <read_six_numbers>	/*	读取6个数字	*/
0x08048b8d <+25>:	cmpl   $0x0,0x18(%esp)	/* 0x18(%esp)与0比较	*/
0x08048b92 <+30>:	jne    0x8048b9b <phase_2+39>	/*if != 0，跳转到0x8048b9b，炸弹爆炸 */
0x08048b94 <+32>:	cmpl   $0x1,0x1c(%esp)	/* 0x1c(%esp)与1比较	*/
0x08048b99 <+37>:	je     0x8048ba0 <phase_2+44>	/*if == 1，跳转到0x8048b0，否则炸弹爆炸 */
0x08048b9b <+39>:	call   0x8049196 <explode_bomb>
0x08048ba0 <+44>:	lea    0x20(%esp),%ebx	/* 从第3个数开始循环判断 */
0x08048ba4 <+48>:	lea    0x30(%esp),%esi	/* 第6个数 */
0x08048ba8 <+52>:	mov    -0x8(%ebx),%eax	/* 前第2个数*/
0x08048bab <+55>:	add    -0x4(%ebx),%eax	/* 前第2个数 + 前第1个数 */
0x08048bae <+58>:	cmp    %eax,(%ebx)			/* 比较当前数与前第2个数 + 前第1个数的和 */
0x08048bb0 <+60>:	je     0x8048bb7 <phase_2+67>	/* if ==，跳转，否则炸弹爆炸 */
0x08048bb2 <+62>:	call   0x8049196 <explode_bomb>
0x08048bb7 <+67>:	add    $0x4,%ebx			/* 继续判断下一个是否满足跳转条件 */
0x08048bba <+70>:	cmp    %esi,%ebx
0x08048bbc <+72>:	jne    0x8048ba8 <phase_2+52>		/* if (%esi != %ebx)循环 */
0x08048bbe <+74>:	add    $0x34,%esp
0x08048bc1 <+77>:	pop    %ebx
0x08048bc2 <+78>:	pop    %esi
0x08048bc3 <+79>:	ret
```

```c
for (int x = 0x20(%esp), if x != -0x30(%esp), x += 4)
{
  int val0 = *(x - 8);
  int val1 = *(x - 4);
  int val3 = *x;
  if (val3 != val0 + val1)
    explode_bomb();
}
```

```assembly
Dump of assembler code for function phase_3:
0x08048bc4 <+0>:	sub    $0x3c,%esp
0x08048bc7 <+3>:	lea    0x28(%esp),%eax
0x08048bcb <+7>:	mov    %eax,0x10(%esp)	/* 将输入的第三个数据（整型数字）地址存入 0x10(%esp)作为第三个参数 */
0x08048bcf <+11>:	lea    0x2f(%esp),%eax
0x08048bd3 <+15>:	mov    %eax,0xc(%esp)	/* 将输入的第二个数据（字符）地址存入 0xc(%esp)作为第二个参数 */
0x08048bd7 <+19>:	lea    0x24(%esp),%eax
0x08048bdb <+23>:	mov    %eax,0x8(%esp)	/* 将输入的第一个数据（整型数字）地址存入 0x8(%esp)作为第一个参数 */
0x08048bdf <+27>:	movl   $0x804a2be,0x4(%esp)	/*	输入数据： "%d %c %d"*/
0x08048be7 <+35>:	mov    0x40(%esp),%eax
0x08048beb <+39>:	mov    %eax,(%esp)
0x08048bee <+42>:	call   0x8048870 <__isoc99_sscanf@plt>
0x08048bf3 <+47>:	cmp    $0x2,%eax
0x08048bf6 <+50>:	jg     0x8048bfd <phase_3+57>
0x08048bf8 <+52>:	call   0x8049196 <explode_bomb>
0x08048bfd <+57>:	cmpl   $0x7,0x24(%esp)		/* 0x24(esp)（第一个数字）中的值 与 7 比较 */
0x08048c02 <+62>:	ja     0x8048d01 <phase_3+317>	/* if > 7，跳转，炸弹爆炸 */
0x08048c08 <+68>:	mov    0x24(%esp),%eax	/* 根据输入的第一个数字在跳转表中查找跳转地址 */
0x08048c0c <+72>:	jmp    *0x804a2e0(,%eax,4)	/* 根据跳转表跳转 */
0x08048c13 <+79>:	mov    $0x72,%eax	/* 答案字符的ASCII码 */
0x08048c18 <+84>:	cmpl   $0x28b,0x28(%esp)	/* 第二数字与0x28b比较 */
0x08048c20 <+92>:	je     0x8048d0b <phase_3+327>	/*if == 答案正确，跳转，否则炸弹爆炸*/
0x08048c26 <+98>:	call   0x8049196 <explode_bomb>
0x08048c2b <+103>:	mov    $0x72,%eax
0x08048c30 <+108>:	jmp    0x8048d0b <phase_3+327>
0x08048c35 <+113>:	mov    $0x76,%eax
0x08048c3a <+118>:	cmpl   $0x2e1,0x28(%esp)
0x08048c42 <+126>:	je     0x8048d0b <phase_3+327>
0x08048c48 <+132>:	call   0x8049196 <explode_bomb>
0x08048c4d <+137>:	mov    $0x76,%eax
0x08048c52 <+142>:	jmp    0x8048d0b <phase_3+327>
0x08048c57 <+147>:	mov    $0x71,%eax
0x08048c5c <+152>:	cmpl   $0x44,0x28(%esp)
0x08048c61 <+157>:	je     0x8048d0b <phase_3+327>
0x08048c67 <+163>:	call   0x8049196 <explode_bomb>
0x08048c6c <+168>:	mov    $0x71,%eax
0x08048c71 <+173>:	jmp    0x8048d0b <phase_3+327>
0x08048c76 <+178>:	mov    $0x64,%eax
0x08048c7b <+183>:	cmpl   $0x397,0x28(%esp)
0x08048c83 <+191>:	je     0x8048d0b <phase_3+327>
0x08048c89 <+197>:	call   0x8049196 <explode_bomb>
0x08048c8e <+202>:	mov    $0x64,%eax
0x08048c93 <+207>:	jmp    0x8048d0b <phase_3+327>
0x08048c95 <+209>:	mov    $0x68,%eax
0x08048c9a <+214>:	cmpl   $0x3d1,0x28(%esp)
0x08048ca2 <+222>:	je     0x8048d0b <phase_3+327>
0x08048ca4 <+224>:	call   0x8049196 <explode_bomb>
0x08048ca9 <+229>:	mov    $0x68,%eax
0x08048cae <+234>:	jmp    0x8048d0b <phase_3+327>
0x08048cb0 <+236>:	mov    $0x65,%eax
0x08048cb5 <+241>:	cmpl   $0x3ce,0x28(%esp)
0x08048cbd <+249>:	je     0x8048d0b <phase_3+327>
0x08048cbf <+251>:	call   0x8049196 <explode_bomb>
0x08048cc4 <+256>:	mov    $0x65,%eax
0x08048cc9 <+261>:	jmp    0x8048d0b <phase_3+327>
0x08048ccb <+263>:	mov    $0x70,%eax
0x08048cd0 <+268>:	cmpl   $0x134,0x28(%esp)
0x08048cd8 <+276>:	je     0x8048d0b <phase_3+327>
0x08048cda <+278>:	call   0x8049196 <explode_bomb>
0x08048cdf <+283>:	mov    $0x70,%eax
0x08048ce4 <+288>:	jmp    0x8048d0b <phase_3+327>
0x08048ce6 <+290>:	mov    $0x6d,%eax
0x08048ceb <+295>:	cmpl   $0xa5,0x28(%esp)
0x08048cf3 <+303>:	je     0x8048d0b <phase_3+327>
0x08048cf5 <+305>:	call   0x8049196 <explode_bomb>
0x08048cfa <+310>:	mov    $0x6d,%eax
0x08048cff <+315>:	jmp    0x8048d0b <phase_3+327>
0x08048d01 <+317>:	call   0x8049196 <explode_bomb>
0x08048d06 <+322>:	mov    $0x7a,%eax
0x08048d0b <+327>:	cmp    0x2f(%esp),%al	/* 比较字符的ASCII码 */
0x08048d0f <+331>:	je     0x8048d16 <phase_3+338>	/* if ==，跳转，否则炸弹爆炸 */
0x08048d11 <+333>:	call   0x8049196 <explode_bomb>
0x08048d16 <+338>:	add    $0x3c,%esp
0x08048d19 <+341>:	ret    

```

```c
int num1, ch, num2;
switch (num1)
{
  case 0:
    if (ch == 'r'&& num2 == 0x28b)
      	 jmp 0x8048d0b;
    else
      	explode_bomb;
    break;
  case 1:
    if (ch == 'v' && num2 == 0x2e1)
      	 jmp 0x8048d0b;
    else
      	explode_bomb;
  case 2:
    if (ch == 'q' && num2 == 0x44)
      		jmp	0x8048d0b;
    else
      	explode_bomb;
  case 3:
    if (ch == 'd' && num3 == 0x397)
      	jmp	0x8048d0b;
    else
      	explode_bomb;
  case 4:
    if (ch == 'h' && num3 == 0x3d1)
      	jmp	0x8048d0b;
    else
      	explode_bomb;
  case 5:
    if (ch == 'e' && num3 == 0x3ce)
      	jmp	0x8048d0b;
    else
      	explode_bomb;
  case 6:
    if (ch == 'p' && num3 == 0x134)
      	jmp	0x8048d0b;
    else
      	explode_bomb;
  case 7:
    if (ch == 'm' && num3 == 0xa5)
      	jmp	0x8048d0b;
    else
      	explode_bomb;
    break;
  default:
    explode_bomb;
    break;
}
```

```assembly
Dump of assembler code for function phase_4:
0x08048d77 <+0>:	sub    $0x2c,%esp
0x08048d7a <+3>:	lea    0x18(%esp),%eax
0x08048d7e <+7>:	mov    %eax,0xc(%esp)
0x08048d82 <+11>:	lea    0x1c(%esp),%eax
0x08048d86 <+15>:	mov    %eax,0x8(%esp)
0x08048d8a <+19>:	movl   $0x804a4a3,0x4(%esp)	/* 输入格式为%d %d */
0x08048d92 <+27>:	mov    0x30(%esp),%eax
0x08048d96 <+31>:	mov    %eax,(%esp)
0x08048d99 <+34>:	call   0x8048870 <__isoc99_sscanf@plt>
0x08048d9e <+39>:	cmp    $0x2,%eax			/* %eax与2的值比较 */
0x08048da1 <+42>:	jne    0x8048db1 <phase_4+58>	/* if != 炸弹爆炸 */
0x08048da3 <+44>:	mov    0x18(%esp),%eax
0x08048da7 <+48>:	cmp    $0x1,%eax	/* 0x18(%esp)地址中的值与1比较 */
0x08048daa <+51>:	jle    0x8048db1 <phase_4+58>	/* if <= 炸弹爆炸 */
0x08048dac <+53>:	cmp    $0x4,%eax	/* 继续与4比较 */
0x08048daf <+56>:	jle    0x8048db6 <phase_4+63>	/* if <= 跳转，否则炸弹爆炸 */
0x08048db1 <+58>:	call   0x8049196 <explode_bomb>
0x08048db6 <+63>:	mov    0x18(%esp),%eax
0x08048dba <+67>:	mov    %eax,0x4(%esp)		/*	输入的第二整数作为func4的第二参数 */
0x08048dbe <+71>:	movl   $0x8,(%esp)			/* 8作为func4的第一个参数 */
0x08048dc5 <+78>:	call   0x8048d1a <func4>
0x08048dca <+83>:	cmp    0x1c(%esp),%eax	/*fun4返回结果 与 0x1c(%esp)地址中的值(输入的第一个整数)比较 */
0x08048dce <+87>:	je     0x8048dd5 <phase_4+94> /* if == 跳转，否则炸弹爆炸 */
0x08048dd0 <+89>:	call   0x8049196 <explode_bomb>
0x08048dd5 <+94>:	add    $0x2c,%esp
0x08048dd8 <+97>:	ret 

Dump of assembler code for function func4:
0x08048d1a <+0>:	sub    $0x1c,%esp
/* 保存上一个递归函数的数据 */
0x08048d1d <+3>:	mov    %ebx,0x10(%esp)
0x08048d21 <+7>:	mov    %esi,0x14(%esp)
0x08048d25 <+11>:	mov    %edi,0x18(%esp)
/* 获得上一个递归函数传入的参数 */
0x08048d29 <+15>:	mov    0x20(%esp),%esi		/* %esi保存剩余递归次数 */		
0x08048d2d <+19>:	mov    0x24(%esp),%ebx		/* %ebx保存递归结果 */
0x08048d31 <+23>:	test   %esi,%esi
0x08048d33 <+25>:	jle    0x8048d60 <func4+70>
0x08048d35 <+27>:	cmp    $0x1,%esi
0x08048d38 <+30>:	je     0x8048d65 <func4+75>
0x08048d3a <+32>:	mov    %ebx,0x4(%esp)
0x08048d3e <+36>:	lea    -0x1(%esi),%eax
0x08048d41 <+39>:	mov    %eax,(%esp)
0x08048d44 <+42>:	call   0x8048d1a <func4>		/* n-1递归 */
0x08048d49 <+47>:	lea    (%eax,%ebx,1),%edi
0x08048d4c <+50>:	mov    %ebx,0x4(%esp)
0x08048d50 <+54>:	sub    $0x2,%esi
0x08048d53 <+57>:	mov    %esi,(%esp)
0x08048d56 <+60>:	call   0x8048d1a <func4>	/* n-2递归 */
0x08048d5b <+65>:	lea    (%edi,%eax,1),%ebx
0x08048d5e <+68>:	jmp    0x8048d65 <func4+75>
0x08048d60 <+70>:	mov    $0x0,%ebx 
0x08048d65 <+75>:	mov    %ebx,%eax
0x08048d67 <+77>:	mov    0x10(%esp),%ebx
0x08048d6b <+81>:	mov    0x14(%esp),%esi
0x08048d6f <+85>:	mov    0x18(%esp),%edi
0x08048d73 <+89>:	add    $0x1c,%esp
0x08048d76 <+92>:	ret 
```

```c
int func4 (int n, int sum)
{
   if (n == 0)
     return 0;
  else if (n == 1)
    return sum;
  else
    return func4(n - 1, sum) + func4(n - 2, sum) + sum;
} 
```



```assembly
Dump of assembler code for function phase_5:
0x08048dd9 <+0>:	sub    $0x2c,%esp
0x08048ddc <+3>:	lea    0x1c(%esp),%eax
0x08048de0 <+7>:	mov    %eax,0xc(%esp)
0x08048de4 <+11>:	lea    0x18(%esp),%eax
0x08048de8 <+15>:	mov    %eax,0x8(%esp)
0x08048dec <+19>:	movl   $0x804a4a3,0x4(%esp)	/* 输入格式为%d %d */
0x08048df4 <+27>:	mov    0x30(%esp),%eax
0x08048df8 <+31>:	mov    %eax,(%esp)
0x08048dfb <+34>:	call   0x8048870 <__isoc99_sscanf@plt>
0x08048e00 <+39>:	cmp    $0x1,%eax	/* sccanf函数成功执行(输入格式正确)，返回值>=1 */
0x08048e03 <+42>:	jg     0x8048e0a <phase_5+49>
0x08048e05 <+44>:	call   0x8049196 <explode_bomb>
0x08048e0a <+49>:	mov    0x18(%esp),%eax	/* 	输入的第一个整数 -> %eax */
0x08048e0e <+53>:	and    $0xf,%eax				/* 与0xf 相与 结果保存到 %eax中 */
0x08048e11 <+56>:	mov    %eax,0x18(%esp)	/*  结果写回栈中 */
0x08048e15 <+60>:	cmp    $0xf,%eax				/* 结果与0xf比较 */
0x08048e18 <+63>:	je     0x8048e44 <phase_5+107>	/* if == 炸弹爆炸 */
0x08048e1a <+65>:	mov    $0x0,%ecx				/* 初始化 %ecx */
0x08048e1f <+70>:	mov    $0x0,%edx				/* 初始化 %edx */
0x08048e24 <+75>:	add    $0x1,%edx				/* 每次循环 %edx += 1 */
0x08048e27 <+78>:	mov    0x804a300(,%eax,4),%eax
0x08048e2e <+85>:	add    %eax,%ecx				/* 每次循环将 %eax 的值累加到 %ecx 中 */
0x08048e30 <+87>:	cmp    $0xf,%eax				/* %eax的值与 0xf 比较 */
0x08048e33 <+90>:	jne    0x8048e24 <phase_5+75>	/* if == 退出循环 */
0x08048e35 <+92>:	mov    %eax,0x18(%esp)
0x08048e39 <+96>:	cmp    $0xf,%edx				/* %edx 与 0xf 比较 */
0x08048e3c <+99>:	jne    0x8048e44 <phase_5+107>	/* if != 炸弹爆炸 */
0x08048e3e <+101>:	cmp    0x1c(%esp),%ecx	/* 累加结果 %exc 与输入的第二整数比较 */
0x08048e42 <+105>:	je     0x8048e49 <phase_5+112>	/* if == 拆除 否则炸弹爆炸 */
0x08048e44 <+107>:	call   0x8049196 <explode_bomb>
0x08048e49 <+112>:	add    $0x2c,%esp
0x08048e4c <+115>:	ret   
```

```assembly
(gdb) x/4bx 0x804a300
0x804a300 <array.2955>:	0x0a	0x00	0x00	0x00		/* 10 */
0x804a304 <array.2955+4>:	0x02	0x00	0x00	0x00	/* 2 */
0x804a308 <array.2955+8>:	0x0e	0x00	0x00	0x00	/* 14 */
0x804a30c <array.2955+12>:	0x07	0x00	0x00	0x00	/* 7 */
0x804a310 <array.2955+16>:	0x08	0x00	0x00	0x00	/* 8 */
0x804a314 <array.2955+20>:	0x0c	0x00	0x00	0x00	/* 12 */
0x804a318 <array.2955+24>:	0x0f	0x00	0x00	0x00	/* 15 */
0x804a31c <array.2955+28>:	0x0b	0x00	0x00	0x00	/* 11 */
0x804a320 <array.2955+32>:	0x00	0x00	0x00	0x00	/* 0 */
0x804a324 <array.2955+36>:	0x04	0x00	0x00	0x00	/* 4 */
0x804a328 <array.2955+40>:	0x01	0x00	0x00	0x00	/* 1 */
0x804a32c <array.2955+44>:	0x0d	0x00	0x00	0x00	/* 13 */
0x804a330 <array.2955+48>:	0x03	0x00	0x00	0x00	/* 3 */
0x804a334 <array.2955+52>:	0x09	0x00	0x00	0x00	/* 9 */
0x804a338 <array.2955+56>:	0x06	0x00	0x00	0x00	/* 6 */
0x804a33c <array.2955+60>:	0x05	0x00	0x00	0x00	/* 5 */
```

```assembly
Dump of assembler code for function phase_6:
0x08048e4d <+0>:	push   %esi
0x08048e4e <+1>:	push   %ebx
0x08048e4f <+2>:	sub    $0x44,%esp
0x08048e52 <+5>:	lea    0x10(%esp),%eax
0x08048e56 <+9>:	mov    %eax,0x4(%esp)
0x08048e5a <+13>:	mov    0x50(%esp),%eax
0x08048e5e <+17>:	mov    %eax,(%esp)
0x08048e61 <+20>:	call   0x80492cb <read_six_numbers>	/* 同phase_2一样可知输入的是6个数字 */
/* 调用read_six_numbers后，从地址0x10(%exp)开始保存的是我们输入的6个数字 */
0x08048e66 <+25>:	mov    $0x0,%esi	/* 初始化%esi */
0x08048e6b <+30>:	mov    0x10(%esp,%esi,4),%eax		
0x08048e6f <+34>:	sub    $0x1,%eax
0x08048e72 <+37>:	cmp    $0x5,%eax
0x08048e75 <+40>:	jbe    0x8048e7c <phase_6+47>
0x08048e77 <+42>:	call   0x8049196 <explode_bomb>
/* 判断输入的数字是否 <= 6 否则炸弹爆炸 */
0x08048e7c <+47>:	add    $0x1,%esi	/* 外层循环次数 %esi 从1开始 */
0x08048e7f <+50>:	cmp    $0x6,%esi
0x08048e82 <+53>:	je     0x8048eb7 <phase_6+106>	/* 循环6次 */
0x08048e84 <+55>:	mov    %esi,%ebx
0x08048e86 <+57>:	mov    0x10(%esp,%ebx,4),%eax
0x08048e8a <+61>:	cmp    %eax,0xc(%esp,%esi,4)		/* 判断我们输入的值是否相等 */
0x08048e8e <+65>:	jne    0x8048e95 <phase_6+72>		/* if ！= 继续循环判断当前值和其他值，否则炸弹爆炸 */
0x08048e90 <+67>:	call   0x8049196 <explode_bomb>
0x08048e95 <+72>:	add    $0x1,%ebx			/* %ebx += 1 判断我们输入的下一个数*/
0x08048e98 <+75>:	cmp    $0x5,%ebx
0x08048e9b <+78>:	jle    0x8048e86 <phase_6+57>	/* 内层循环判断当前的值是否与其他值相等 */
0x08048e9d <+80>:	jmp    0x8048e6b <phase_6+30>	/* 外层循环下一个数 */
0x08048e9f <+82>:	mov    0x8(%edx),%edx	/* 下一个节点作为当前节点 */
0x08048ea2 <+85>:	add    $0x1,%eax	/* %eax += 1 */
0x08048ea5 <+88>:	cmp    %ecx,%eax	
0x08048ea7 <+90>:	jne    0x8048e9f <phase_6+82>	/* 内层循环找到目标节点 */
0x08048ea9 <+92>:	mov    %edx,0x28(%esp,%esi,4)	/* 将目标节点作为当前节点的下一个节点 */
0x08048ead <+96>:	add    $0x1,%ebx	/* 外层循环次数 %ebx +1 */
0x08048eb0 <+99>:	cmp    $0x6,%ebx	/* 外层循环6次*/
0x08048eb3 <+102>:	jne    0x8048ebc <phase_6+111>
0x08048eb5 <+104>:	jmp    0x8048ed3 <phase_6+134>
0x08048eb7 <+106>:	mov    $0x0,%ebx	/* 将 %ebx 清零 */
0x08048ebc <+111>:	mov    %ebx,%esi	/* 每次循环前 保存当前要更改的节点地址 */
0x08048ebe <+113>:	mov    0x10(%esp,%ebx,4),%ecx	/* 从栈中取出我们输入的数存入 %ecx */
0x08048ec2 <+117>:	mov    $0x1,%eax	/* 每次循环前将 %eax 置1 从1开始找目标节点*/
0x08048ec7 <+122>:	mov    $0x804c13c,%edx	/* 第1个节点的地址存入 %edx 每次循环从第1个节点开始查找*/
0x08048ecc <+127>:	cmp    $0x1,%ecx
0x08048ecf <+130>:	jg     0x8048e9f <phase_6+82>	/* 外层循环 */
0x08048ed1 <+132>:	jmp    0x8048ea9 <phase_6+92>
/* 循环结束后链表节点按我们输入的顺序保存在了栈中 */
0x08048ed3 <+134>:	mov    0x28(%esp),%ebx	
0x08048ed7 <+138>:	mov    0x2c(%esp),%eax
0x08048edb <+142>:	mov    %eax,0x8(%ebx)
0x08048ede <+145>:	mov    0x30(%esp),%edx
0x08048ee2 <+149>:	mov    %edx,0x8(%eax)
0x08048ee5 <+152>:	mov    0x34(%esp),%eax %   
0x08048ee9 <+156>:	mov    %eax,0x8(%edx)
0x08048eec <+159>:	mov    0x38(%esp),%edx
0x08048ef0 <+163>:	mov    %edx,0x8(%eax)
0x08048ef3 <+166>:	mov    0x3c(%esp),%eax
0x08048ef7 <+170>:	mov    %eax,0x8(%edx)
0x08048efa <+173>:	movl   $0x0,0x8(%eax)
0x08048f01 <+180>:	mov    $0x5,%esi		/* 循环变量 */
0x08048f06 <+185>:	mov    0x8(%ebx),%eax	/* 当前节点的下一个节点地址 */
0x08048f09 <+188>:	mov    (%eax),%edx		/* 当前节点的下一个节点的值value */
0x08048f0b <+190>:	cmp    %edx,(%ebx) /* 判断当前节点值value是否小于该节点下一个节点值 */
0x08048f0d <+192>:	jle    0x8048f14 <phase_6+199>	/*否 则炸弹爆炸*/
0x08048f0f <+194>:	call   0x8049196 <explode_bomb>
0x08048f14 <+199>:	mov    0x8(%ebx),%ebx	/* 遍历链表，判断链表顺序是否按节点值从小到大排序 */
0x08048f17 <+202>:	sub    $0x1,%esi			/*循环变量 - 1，共循环6次遍历6个节点*/
0x08048f1a <+205>:	jne    0x8048f06 <phase_6+185>
0x08048f1c <+207>:	add    $0x44,%esp
0x08048f1f <+210>:	pop    %ebx
0x08048f20 <+211>:	pop    %esi
0x08048f21 <+212>:	ret    

```

|    addr    |    value    |
| :--------: | :---------: |
| 0x24(%exp) | 06 00 00 00 |
| 0x20(%esp) | 05 00 00 00 |
| 0x1c(%esp) | 04 00 00 00 |
| 0x18(%esp) | 03 00 00 00 |
| 0x14(%esp) | 02 00 00 00 |
| 0x10(%esp) | 01 00 00 00 |

```c
for (int %esi = 1; %esi <= 6; %esi++)
{
  int x = 0x10(%esp,esi,4);		//当前判断的值
  if (x > 6)									//大于6炸弹爆炸
    explode_bomb;
  for (int %ebx = %esi; %ebx <= 6; %ebx++)
  {
    int tmp = 0x10(%esp,%ebx,4);
    if (x == tmp)						//xiang deng
      explode_bomb;
  }
}
jmp 0x8048eb7;

typedef struct
{
  int value;	//节点的变量
  int num;		//节点序号
  struct node* next;	//节点指针
} node;

for (int %ebx = 1; %ebx < 6; %ebx++)
{
  //cur from node1 to node6
  int x  = 0x10(%esp,%ebx,4);
    	tar = find_node(x);		//tar->num = x 查找目标节点
	cur->next = tar;					//将目标节点作为当前节点的下一个节点
}
```

|    addr    |         value          |
| :--------: | :--------------------: |
| 0x3c(%exp) | 48 c1 04 08 *(node2)*  |
| 0x38(%esp) | 60 c1 04 08 *(node4)*  |
| 0x34(%esp) | 54 c1 04 08 *(node3)*  |
| 0x30(%esp) | 3c c1 04 08 *(node1)*  |
| 0x2c(%esp) | 6c c1 04 08 *(node5)*  |
| 0x28(%esp) | 78 c1 04 08  *(node6)* |

```c
cur = head;	//从头节点开始
while (cur != NULL)
{
  struct node* cur_next = cur->next;
  if (cur->value > cur_next->value)
    explode_bomb;
  cur = cur_next;
}
```

```assembly
Dump of assembler code for function phase_defused:
0x0804931b <+0>:	sub    $0x8c,%esp
0x08049321 <+6>:	mov    %gs:0x14,%eax
0x08049327 <+12>:	mov    %eax,0x7c(%esp)
0x0804932b <+16>:	xor    %eax,%eax
0x0804932d <+18>:	cmpl   $0x6,0x804c3cc			/* 拆除6个引信后才有可能触发隐藏关 */
0x08049334 <+25>:	jne    0x80493a8 <phase_defused+141>
0x08049336 <+27>:	lea    0x2c(%esp),%eax
0x0804933a <+31>:	mov    %eax,0x10(%esp)
0x0804933e <+35>:	lea    0x28(%esp),%eax
0x08049342 <+39>:	mov    %eax,0xc(%esp)
0x08049346 <+43>:	lea    0x24(%esp),%eax
0x0804934a <+47>:	mov    %eax,0x8(%esp)
0x0804934e <+51>:	movl   $0x804a4a9,0x4(%esp)	/* sscanf函数从字符串读取的格式 */
0x08049356 <+59>:	movl   $0x804c4d0,(%esp)		/* 在phase_4的输入 */
0x0804935d <+66>:	call   0x8048870 <__isoc99_sscanf@plt>
0x08049362 <+71>:	cmp    $0x3,%eax						/*sscanf函数返回的是成功转换并赋值的字段数，要求满足3个即%d %d %s */
0x08049365 <+74>:	jne    0x804939c <phase_defused+129>	/* 不为3则进入不了secret_phase */
0x08049367 <+76>:	movl   $0x804a4b2,0x4(%esp)	/* 地址中存放的是我们要的字符串 */
0x0804936f <+84>:	lea    0x2c(%esp),%eax
0x08049373 <+88>:	mov    %eax,(%esp)
0x08049376 <+91>:	call   0x8049084 <strings_not_equal>	/* 判断我们输入的字符串与0x804a4b2中保存的字符串是否相同 */
0x0804937b <+96>:	test   %eax,%eax						/* 相同则返回0，并成功进入secret_phase的函数调用 */
0x0804937d <+98>:	jne    0x804939c <phase_defused+129>
0x0804937f <+100>:	movl   $0x804a378,(%esp)
0x08049386 <+107>:	call   0x8048800 <puts@plt>
0x0804938b <+112>:	movl   $0x804a3a0,(%esp)
0x08049392 <+119>:	call   0x8048800 <puts@plt>
0x08049397 <+124>:	call   0x8048f73 <secret_phase>			/* 调用secret_phase */
0x0804939c <+129>:	movl   $0x804a3d8,(%esp)
0x080493a3 <+136>:	call   0x8048800 <puts@plt>
0x080493a8 <+141>:	mov    0x7c(%esp),%eax
0x080493ac <+145>:	xor    %gs:0x14,%eax
0x080493b3 <+152>:	je     0x80493ba <phase_defused+159>
0x080493b5 <+154>:	call   0x80487d0 <__stack_chk_fail@plt>
0x080493ba <+159>:	add    $0x8c,%esp
0x080493c0 <+165>:	ret 
```

```assembly
Dump of assembler code for function secret_phase:
0x08048f73 <+0>:	push   %ebx
0x08048f74 <+1>:	sub    $0x18,%esp
0x08048f77 <+4>:	call   0x80491bd <read_line>		/* 读取输入的答案（字符串） */
0x08048f7c <+9>:	movl   $0xa,0x8(%esp)
0x08048f84 <+17>:	movl   $0x0,0x4(%esp)
0x08048f8c <+25>:	mov    %eax,(%esp)
0x08048f8f <+28>:	call   0x80488e0 <strtol@plt>		/* 将刚刚读取的字符串转换为长整型 */
0x08048f94 <+33>:	mov    %eax,%ebx								/* 拷贝一份返回值到%ebx中 */
0x08048f96 <+35>:	lea    -0x1(%eax),%eax
0x08048f99 <+38>:	cmp    $0x3e8,%eax							/* 结合上一条指令，比较的是%eax和1001的大小 */
0x08048f9e <+43>:	jbe    0x8048fa5 <secret_phase+50>	/* %eax 大于1001，则炸弹爆炸 */
0x08048fa0 <+45>:	call   0x8049196 <explode_bomb>
0x08048fa5 <+50>:	mov    %ebx,0x4(%esp)						/* 将%ebx作为一个参数传入fun7 */
0x08048fa9 <+54>:	movl   $0x804c088,(%esp)
0x08048fb0 <+61>:	call   0x8048f22 <fun7>
0x08048fb5 <+66>:	cmp    $0x3,%eax								/* fun7的返回值应该是3 */
0x08048fb8 <+69>:	je     0x8048fbf <secret_phase+76>	/* 满足则通关，否则炸弹爆炸 */
0x08048fba <+71>:	call   0x8049196 <explode_bomb>
0x08048fbf <+76>:	movl   $0x804a298,(%esp)
0x08048fc6 <+83>:	call   0x8048800 <puts@plt>
0x08048fcb <+88>:	call   0x804931b <phase_defused>
0x08048fd0 <+93>:	add    $0x18,%esp
0x08048fd3 <+96>:	pop    %ebx
0x08048fd4 <+97>:	ret 
```

```assembly
Dump of assembler code for function fun7:
0x08048f22 <+0>:	push   %ebx
0x08048f23 <+1>:	sub    $0x18,%esp
0x08048f26 <+4>:	mov    0x20(%esp),%edx
0x08048f2a <+8>:	mov    0x24(%esp),%ecx
0x08048f2e <+12>:	test   %edx,%edx						/* 空节点直接返回 */
0x08048f30 <+14>:	je     0x8048f69 <fun7+71>
0x08048f32 <+16>:	mov    (%edx),%ebx					/* 获取当前节点的值 */
0x08048f34 <+18>:	cmp    %ecx,%ebx						/* 比较我们输入的值 和 当前节点的值 */
0x08048f36 <+20>:	jle    0x8048f4b <fun7+41>	/* 如过当前节点值小于等于我们输入的值则跳转先去查找右节点 */
0x08048f38 <+22>:	mov    %ecx,0x4(%esp)	
0x08048f3c <+26>:	mov    0x4(%edx),%eax				/*否则先查找左节点*/
0x08048f3f <+29>:	mov    %eax,(%esp)
0x08048f42 <+32>:	call   0x8048f22 <fun7>
0x08048f47 <+37>:	add    %eax,%eax						/*如果是左节点则 %eax = 2 * %eax */
0x08048f49 <+39>:	jmp    0x8048f6e <fun7+76>
0x08048f4b <+41>:	mov    $0x0,%eax						/* 初始化%eax 保存的是查找的节点个数（不包括n1） */
0x08048f50 <+46>:	cmp    %ecx,%ebx						/* 比较我们输入的值 和 当前节点的值 */
0x08048f52 <+48>:	je     0x8048f6e <fun7+76>	/* 相等则函数返回 */
0x08048f54 <+50>:	mov    %ecx,0x4(%esp)				/* 否则将我们输入的值传入下一层递归 */
0x08048f58 <+54>:	mov    0x8(%edx),%eax				/* 查找当前节点的右节点 */
0x08048f5b <+57>:	mov    %eax,(%esp)
0x08048f5e <+60>:	call   0x8048f22 <fun7>
0x08048f63 <+65>:	lea    0x1(%eax,%eax,1),%eax/* 如果是右节点则 %eax = 2 * %eax + 1 */
0x08048f67 <+69>:	jmp    0x8048f6e <fun7+76>
0x08048f69 <+71>:	mov    $0xffffffff,%eax
0x08048f6e <+76>:	add    $0x18,%esp
0x08048f71 <+79>:	pop    %ebx
0x08048f72 <+80>:	ret
```

```assembly
0x804c088 <n1>:	0x24	0x00	0x00	0x00 
0x804c08c <n1+4>:	0x94	0xc0	0x04	0x08
0x804c090 <n1+8>:	0xa0	0xc0	0x04	0x08
0x804c094 <n21>:	0x08	0x00	0x00	0x00
0x804c098 <n21+4>:	0xc4	0xc0	0x04	0x08
0x804c09c <n21+8>:	0xac	0xc0	0x04	0x08
0x804c0a0 <n22>:	0x32	0x00	0x00	0x00
0x804c0a4 <n22+4>:	0xb8	0xc0	0x04	0x08
0x804c0a8 <n22+8>:	0xd0	0xc0	0x04	0x08
0x804c0ac <n32>:	0x16	0x00	0x00	0x00
0x804c0b0 <n32+4>:	0x18	0xc1	0x04	0x08
0x804c0b4 <n32+8>:	0x00	0xc1	0x04	0x08
0x804c0b8 <n33>:	0x2d	0x00	0x00	0x00
0x804c0bc <n33+4>:	0xdc	0xc0	0x04	0x08
0x804c0c0 <n33+8>:	0x24	0xc1	0x04	0x08
0x804c0c4 <n31>:	0x06	0x00	0x00	0x00
0x804c0c8 <n31+4>:	0xe8	0xc0	0x04	0x08
0x804c0cc <n31+8>:	0x0c	0xc1	0x04	0x08
0x804c0d0 <n34>:	0x6b	0x00	0x00	0x00
0x804c0d4 <n34+4>:	0xf4	0xc0	0x04	0x08
0x804c0d8 <n34+8>:	0x30	0xc1	0x04	0x08
0x804c0dc <n45>:	0x28	0x00	0x00	0x00
0x804c0e0 <n45+4>:	0x00	0x00	0x00	0x00
0x804c0e4 <n45+8>:	0x00	0x00	0x00	0x00
0x804c0e8 <n41>:	0x01	0x00	0x00	0x00
0x804c0ec <n41+4>:	0x00	0x00	0x00	0x00
0x804c0f0 <n41+8>:	0x00	0x00	0x00	0x00
0x804c0f4 <n47>:	0x63	0x00	0x00	0x00
0x804c0f8 <n47+4>:	0x00	0x00	0x00	0x00
0x804c0fc <n47+8>:	0x00	0x00	0x00	0x00
0x804c100 <n44>:	0x23	0x00	0x00	0x00
0x804c104 <n44+4>:	0x00	0x00	0x00	0x00
0x804c108 <n44+8>:	0x00	0x00	0x00	0x00
0x804c10c <n42>:	0x07	0x00	0x00	0x00
0x804c110 <n42+4>:	0x00	0x00	0x00	0x00
0x804c114 <n42+8>:	0x00	0x00	0x00	0x00
0x804c118 <n43>:	0x14	0x00	0x00	0x00
0x804c11c <n43+4>:	0x00	0x00	0x00	0x00
0x804c120 <n43+8>:	0x00	0x00	0x00	0x00
0x804c124 <n46>:	0x2f	0x00	0x00	0x00
0x804c128 <n46+4>:	0x00	0x00	0x00	0x00
0x804c12c <n46+8>:	0x00	0x00	0x00	0x00
0x804c130 <n48>:	0xe9	0x03	0x00	0x00
0x804c134 <n48+4>:	0x00	0x00	0x00	0x00
0x804c138 <n48+8>:	0x00	0x00	0x00	0x00
```

```c
typedef struct 
{
  int value;			//节点值
  struct n* left;	//左节点
  struct n* right;//右节点
} n;
```

![image-20240426下午53909096](/Users/fanglunlin/Library/Application Support/typora-user-images/image-20240426下午53909096.png)
