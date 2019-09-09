
test_slh:     file format elf64-x86-64


Disassembly of section .init:

0000000000400420 <_init>:
  400420:	48 83 ec 08          	sub    $0x8,%rsp
  400424:	48 8b 05 cd 0b 20 00 	mov    0x200bcd(%rip),%rax        # 600ff8 <_DYNAMIC+0x1d0>
  40042b:	48 85 c0             	test   %rax,%rax
  40042e:	74 05                	je     400435 <_init+0x15>
  400430:	e8 5b 00 00 00       	callq  400490 <fopen@plt+0x10>
  400435:	48 83 c4 08          	add    $0x8,%rsp
  400439:	c3                   	retq   

Disassembly of section .plt:

0000000000400440 <fgetc_unlocked@plt-0x10>:
  400440:	ff 35 c2 0b 20 00    	pushq  0x200bc2(%rip)        # 601008 <_GLOBAL_OFFSET_TABLE_+0x8>
  400446:	ff 25 c4 0b 20 00    	jmpq   *0x200bc4(%rip)        # 601010 <_GLOBAL_OFFSET_TABLE_+0x10>
  40044c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400450 <fgetc_unlocked@plt>:
  400450:	ff 25 c2 0b 20 00    	jmpq   *0x200bc2(%rip)        # 601018 <_GLOBAL_OFFSET_TABLE_+0x18>
  400456:	68 00 00 00 00       	pushq  $0x0
  40045b:	e9 e0 ff ff ff       	jmpq   400440 <_init+0x20>

0000000000400460 <printf@plt>:
  400460:	ff 25 ba 0b 20 00    	jmpq   *0x200bba(%rip)        # 601020 <_GLOBAL_OFFSET_TABLE_+0x20>
  400466:	68 01 00 00 00       	pushq  $0x1
  40046b:	e9 d0 ff ff ff       	jmpq   400440 <_init+0x20>

0000000000400470 <__libc_start_main@plt>:
  400470:	ff 25 b2 0b 20 00    	jmpq   *0x200bb2(%rip)        # 601028 <_GLOBAL_OFFSET_TABLE_+0x28>
  400476:	68 02 00 00 00       	pushq  $0x2
  40047b:	e9 c0 ff ff ff       	jmpq   400440 <_init+0x20>

0000000000400480 <fopen@plt>:
  400480:	ff 25 aa 0b 20 00    	jmpq   *0x200baa(%rip)        # 601030 <_GLOBAL_OFFSET_TABLE_+0x30>
  400486:	68 03 00 00 00       	pushq  $0x3
  40048b:	e9 b0 ff ff ff       	jmpq   400440 <_init+0x20>

Disassembly of section .plt.got:

0000000000400490 <.plt.got>:
  400490:	ff 25 62 0b 20 00    	jmpq   *0x200b62(%rip)        # 600ff8 <_DYNAMIC+0x1d0>
  400496:	66 90                	xchg   %ax,%ax

Disassembly of section .text:

00000000004004a0 <_start>:
  4004a0:	31 ed                	xor    %ebp,%ebp
  4004a2:	49 89 d1             	mov    %rdx,%r9
  4004a5:	5e                   	pop    %rsi
  4004a6:	48 89 e2             	mov    %rsp,%rdx
  4004a9:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  4004ad:	50                   	push   %rax
  4004ae:	54                   	push   %rsp
  4004af:	49 c7 c0 70 07 40 00 	mov    $0x400770,%r8
  4004b6:	48 c7 c1 00 07 40 00 	mov    $0x400700,%rcx
  4004bd:	48 c7 c7 f0 05 40 00 	mov    $0x4005f0,%rdi
  4004c4:	e8 a7 ff ff ff       	callq  400470 <__libc_start_main@plt>
  4004c9:	f4                   	hlt    
  4004ca:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

00000000004004d0 <deregister_tm_clones>:
  4004d0:	b8 50 10 60 00       	mov    $0x601050,%eax
  4004d5:	48 3d 50 10 60 00    	cmp    $0x601050,%rax
  4004db:	74 13                	je     4004f0 <deregister_tm_clones+0x20>
  4004dd:	b8 00 00 00 00       	mov    $0x0,%eax
  4004e2:	48 85 c0             	test   %rax,%rax
  4004e5:	74 09                	je     4004f0 <deregister_tm_clones+0x20>
  4004e7:	bf 50 10 60 00       	mov    $0x601050,%edi
  4004ec:	ff e0                	jmpq   *%rax
  4004ee:	66 90                	xchg   %ax,%ax
  4004f0:	c3                   	retq   
  4004f1:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  4004f6:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  4004fd:	00 00 00 

0000000000400500 <register_tm_clones>:
  400500:	be 50 10 60 00       	mov    $0x601050,%esi
  400505:	48 81 ee 50 10 60 00 	sub    $0x601050,%rsi
  40050c:	48 c1 fe 03          	sar    $0x3,%rsi
  400510:	48 89 f0             	mov    %rsi,%rax
  400513:	48 c1 e8 3f          	shr    $0x3f,%rax
  400517:	48 01 c6             	add    %rax,%rsi
  40051a:	48 d1 fe             	sar    %rsi
  40051d:	74 11                	je     400530 <register_tm_clones+0x30>
  40051f:	b8 00 00 00 00       	mov    $0x0,%eax
  400524:	48 85 c0             	test   %rax,%rax
  400527:	74 07                	je     400530 <register_tm_clones+0x30>
  400529:	bf 50 10 60 00       	mov    $0x601050,%edi
  40052e:	ff e0                	jmpq   *%rax
  400530:	c3                   	retq   
  400531:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  400536:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  40053d:	00 00 00 

0000000000400540 <__do_global_dtors_aux>:
  400540:	80 3d 09 0b 20 00 00 	cmpb   $0x0,0x200b09(%rip)        # 601050 <__TMC_END__>
  400547:	75 17                	jne    400560 <__do_global_dtors_aux+0x20>
  400549:	55                   	push   %rbp
  40054a:	48 89 e5             	mov    %rsp,%rbp
  40054d:	e8 7e ff ff ff       	callq  4004d0 <deregister_tm_clones>
  400552:	c6 05 f7 0a 20 00 01 	movb   $0x1,0x200af7(%rip)        # 601050 <__TMC_END__>
  400559:	5d                   	pop    %rbp
  40055a:	c3                   	retq   
  40055b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  400560:	c3                   	retq   
  400561:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  400566:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  40056d:	00 00 00 

0000000000400570 <frame_dummy>:
  400570:	eb 8e                	jmp    400500 <register_tm_clones>
  400572:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  400579:	00 00 00 
  40057c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400580 <victim_fun>:

static __attribute__ ((noinline)) void leakByteNoinlineFunction(uint8_t k) { 
    temp &= array2[k* 512]; 
}

void victim_fun(size_t x) {
  400580:	48 89 e0             	mov    %rsp,%rax
  400583:	48 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%rcx
  40058a:	48 c1 f8 3f          	sar    $0x3f,%rax
         if (x < array1_size)
  40058e:	8b 15 b4 0a 20 00    	mov    0x200ab4(%rip),%edx        # 601048 <array1_size>
  400594:	48 39 fa             	cmp    %rdi,%rdx
  400597:	76 16                	jbe    4005af <victim_fun+0x2f>
  400599:	48 0f 46 c1          	cmovbe %rcx,%rax
                leakByteNoinlineFunction(array1[x]);
  40059d:	0f b6 bf 60 10 60 00 	movzbl 0x601060(%rdi),%edi
  4005a4:	09 c7                	or     %eax,%edi
  4005a6:	48 c1 e0 2f          	shl    $0x2f,%rax
  4005aa:	48 09 c4             	or     %rax,%rsp
  4005ad:	eb 11                	jmp    4005c0 <leakByteNoinlineFunction>
  4005af:	48 0f 47 c1          	cmova  %rcx,%rax
}
  4005b3:	48 c1 e0 2f          	shl    $0x2f,%rax
  4005b7:	48 09 c4             	or     %rax,%rsp
  4005ba:	c3                   	retq   
  4005bb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000004005c0 <leakByteNoinlineFunction>:
struct timespec time_start, time_end;
size_t time_diff;



static __attribute__ ((noinline)) void leakByteNoinlineFunction(uint8_t k) { 
  4005c0:	48 89 e0             	mov    %rsp,%rax
  4005c3:	48 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%rcx
  4005ca:	48 c1 f8 3f          	sar    $0x3f,%rax
    temp &= array2[k* 512]; 
  4005ce:	89 f9                	mov    %edi,%ecx
  4005d0:	48 c1 e1 09          	shl    $0x9,%rcx
  4005d4:	8a 89 90 10 60 00    	mov    0x601090(%rcx),%cl
  4005da:	08 c1                	or     %al,%cl
  4005dc:	20 0d 6f 0a 20 00    	and    %cl,0x200a6f(%rip)        # 601051 <temp>
}
  4005e2:	48 c1 e0 2f          	shl    $0x2f,%rax
  4005e6:	48 09 c4             	or     %rax,%rsp
  4005e9:	c3                   	retq   
  4005ea:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

00000000004005f0 <main>:
void victim_fun(size_t x) {
         if (x < array1_size)
                leakByteNoinlineFunction(array1[x]);
}

int main(int argn, char* args[]) {
  4005f0:	53                   	push   %rbx
  4005f1:	48 89 e0             	mov    %rsp,%rax
  4005f4:	48 c7 c3 ff ff ff ff 	mov    $0xffffffffffffffff,%rbx
  4005fb:	48 c1 f8 3f          	sar    $0x3f,%rax
    int source;

    FILE *file = fopen("temp.txt", "r");
  4005ff:	bf 84 07 40 00       	mov    $0x400784,%edi
  400604:	be 8d 07 40 00       	mov    $0x40078d,%esi
  400609:	48 c1 e0 2f          	shl    $0x2f,%rax
  40060d:	48 09 c4             	or     %rax,%rsp
  400610:	e8 6b fe ff ff       	callq  400480 <fopen@plt>
  400615:	48 89 e1             	mov    %rsp,%rcx
  400618:	48 8b 54 24 f8       	mov    -0x8(%rsp),%rdx
  40061d:	48 c1 f9 3f          	sar    $0x3f,%rcx
  400621:	48 81 fa 15 06 40 00 	cmp    $0x400615,%rdx
  400628:	48 0f 45 cb          	cmovne %rbx,%rcx

    if (file == NULL) {
  40062c:	48 85 c0             	test   %rax,%rax
  40062f:	74 64                	je     400695 <main+0xa5>
  400631:	48 0f 44 cb          	cmove  %rbx,%rcx
        printf("No file!");
        return 0;
    }
    source = fgetc(file);
  400635:	48 c1 e1 2f          	shl    $0x2f,%rcx
  400639:	48 89 c7             	mov    %rax,%rdi
  40063c:	48 09 cc             	or     %rcx,%rsp
  40063f:	e8 0c fe ff ff       	callq  400450 <fgetc_unlocked@plt>
  400644:	48 89 e1             	mov    %rsp,%rcx
  400647:	48 8b 54 24 f8       	mov    -0x8(%rsp),%rdx
  40064c:	48 c1 f9 3f          	sar    $0x3f,%rcx
  400650:	48 81 fa 44 06 40 00 	cmp    $0x400644,%rdx
  400657:	48 0f 45 cb          	cmovne %rbx,%rcx
    victim_fun(source);
  40065b:	48 98                	cltq   
static __attribute__ ((noinline)) void leakByteNoinlineFunction(uint8_t k) { 
    temp &= array2[k* 512]; 
}

void victim_fun(size_t x) {
         if (x < array1_size)
  40065d:	8b 15 e5 09 20 00    	mov    0x2009e5(%rip),%edx        # 601048 <array1_size>
  400663:	48 39 c2             	cmp    %rax,%rdx
  400666:	76 5c                	jbe    4006c4 <main+0xd4>
  400668:	48 0f 46 cb          	cmovbe %rbx,%rcx
                leakByteNoinlineFunction(array1[x]);
  40066c:	0f b6 b8 60 10 60 00 	movzbl 0x601060(%rax),%edi
  400673:	09 cf                	or     %ecx,%edi
  400675:	48 c1 e1 2f          	shl    $0x2f,%rcx
  400679:	48 09 cc             	or     %rcx,%rsp
  40067c:	e8 3f ff ff ff       	callq  4005c0 <leakByteNoinlineFunction>
  400681:	48 89 e1             	mov    %rsp,%rcx
  400684:	48 8b 44 24 f8       	mov    -0x8(%rsp),%rax
  400689:	48 c1 f9 3f          	sar    $0x3f,%rcx
  40068d:	48 3d 81 06 40 00    	cmp    $0x400681,%rax
  400693:	eb 29                	jmp    4006be <main+0xce>
  400695:	48 0f 45 cb          	cmovne %rbx,%rcx
    int source;

    FILE *file = fopen("temp.txt", "r");

    if (file == NULL) {
        printf("No file!");
  400699:	bf 8f 07 40 00       	mov    $0x40078f,%edi
  40069e:	48 c1 e1 2f          	shl    $0x2f,%rcx
  4006a2:	31 c0                	xor    %eax,%eax
  4006a4:	48 09 cc             	or     %rcx,%rsp
  4006a7:	e8 b4 fd ff ff       	callq  400460 <printf@plt>
  4006ac:	48 89 e1             	mov    %rsp,%rcx
  4006af:	48 8b 44 24 f8       	mov    -0x8(%rsp),%rax
  4006b4:	48 c1 f9 3f          	sar    $0x3f,%rcx
  4006b8:	48 3d ac 06 40 00    	cmp    $0x4006ac,%rax
  4006be:	48 0f 45 cb          	cmovne %rbx,%rcx
  4006c2:	eb 04                	jmp    4006c8 <main+0xd8>
  4006c4:	48 0f 47 cb          	cmova  %rbx,%rcx
        return 0;
    }
    source = fgetc(file);
    victim_fun(source);
    return 0;
}
  4006c8:	48 c1 e1 2f          	shl    $0x2f,%rcx
  4006cc:	31 c0                	xor    %eax,%eax
  4006ce:	48 09 cc             	or     %rcx,%rsp
  4006d1:	5b                   	pop    %rbx
  4006d2:	c3                   	retq   
  4006d3:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  4006da:	00 00 00 
  4006dd:	0f 1f 00             	nopl   (%rax)

00000000004006e0 <__llvm_retpoline_r11>:
  4006e0:	e8 0b 00 00 00       	callq  4006f0 <__llvm_retpoline_r11+0x10>
  4006e5:	f3 90                	pause  
  4006e7:	0f ae e8             	lfence 
  4006ea:	eb f9                	jmp    4006e5 <__llvm_retpoline_r11+0x5>
  4006ec:	0f 1f 40 00          	nopl   0x0(%rax)
  4006f0:	4c 89 1c 24          	mov    %r11,(%rsp)
  4006f4:	c3                   	retq   
  4006f5:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  4006fc:	00 00 00 
  4006ff:	90                   	nop

0000000000400700 <__libc_csu_init>:
  400700:	41 57                	push   %r15
  400702:	41 56                	push   %r14
  400704:	41 89 ff             	mov    %edi,%r15d
  400707:	41 55                	push   %r13
  400709:	41 54                	push   %r12
  40070b:	4c 8d 25 06 07 20 00 	lea    0x200706(%rip),%r12        # 600e18 <__frame_dummy_init_array_entry>
  400712:	55                   	push   %rbp
  400713:	48 8d 2d 06 07 20 00 	lea    0x200706(%rip),%rbp        # 600e20 <__init_array_end>
  40071a:	53                   	push   %rbx
  40071b:	49 89 f6             	mov    %rsi,%r14
  40071e:	49 89 d5             	mov    %rdx,%r13
  400721:	4c 29 e5             	sub    %r12,%rbp
  400724:	48 83 ec 08          	sub    $0x8,%rsp
  400728:	48 c1 fd 03          	sar    $0x3,%rbp
  40072c:	e8 ef fc ff ff       	callq  400420 <_init>
  400731:	48 85 ed             	test   %rbp,%rbp
  400734:	74 20                	je     400756 <__libc_csu_init+0x56>
  400736:	31 db                	xor    %ebx,%ebx
  400738:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  40073f:	00 
  400740:	4c 89 ea             	mov    %r13,%rdx
  400743:	4c 89 f6             	mov    %r14,%rsi
  400746:	44 89 ff             	mov    %r15d,%edi
  400749:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  40074d:	48 83 c3 01          	add    $0x1,%rbx
  400751:	48 39 eb             	cmp    %rbp,%rbx
  400754:	75 ea                	jne    400740 <__libc_csu_init+0x40>
  400756:	48 83 c4 08          	add    $0x8,%rsp
  40075a:	5b                   	pop    %rbx
  40075b:	5d                   	pop    %rbp
  40075c:	41 5c                	pop    %r12
  40075e:	41 5d                	pop    %r13
  400760:	41 5e                	pop    %r14
  400762:	41 5f                	pop    %r15
  400764:	c3                   	retq   
  400765:	90                   	nop
  400766:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  40076d:	00 00 00 

0000000000400770 <__libc_csu_fini>:
  400770:	f3 c3                	repz retq 

Disassembly of section .fini:

0000000000400774 <_fini>:
  400774:	48 83 ec 08          	sub    $0x8,%rsp
  400778:	48 83 c4 08          	add    $0x8,%rsp
  40077c:	c3                   	retq   
