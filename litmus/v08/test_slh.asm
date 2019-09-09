
test_slh:     file format elf64-x86-64


Disassembly of section .init:

00000000004003e8 <_init>:
  4003e8:	48 83 ec 08          	sub    $0x8,%rsp
  4003ec:	48 8b 05 05 0c 20 00 	mov    0x200c05(%rip),%rax        # 600ff8 <_DYNAMIC+0x1d0>
  4003f3:	48 85 c0             	test   %rax,%rax
  4003f6:	74 05                	je     4003fd <_init+0x15>
  4003f8:	e8 53 00 00 00       	callq  400450 <fopen@plt+0x10>
  4003fd:	48 83 c4 08          	add    $0x8,%rsp
  400401:	c3                   	retq   

Disassembly of section .plt:

0000000000400410 <fgetc_unlocked@plt-0x10>:
  400410:	ff 35 f2 0b 20 00    	pushq  0x200bf2(%rip)        # 601008 <_GLOBAL_OFFSET_TABLE_+0x8>
  400416:	ff 25 f4 0b 20 00    	jmpq   *0x200bf4(%rip)        # 601010 <_GLOBAL_OFFSET_TABLE_+0x10>
  40041c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400420 <fgetc_unlocked@plt>:
  400420:	ff 25 f2 0b 20 00    	jmpq   *0x200bf2(%rip)        # 601018 <_GLOBAL_OFFSET_TABLE_+0x18>
  400426:	68 00 00 00 00       	pushq  $0x0
  40042b:	e9 e0 ff ff ff       	jmpq   400410 <_init+0x28>

0000000000400430 <__libc_start_main@plt>:
  400430:	ff 25 ea 0b 20 00    	jmpq   *0x200bea(%rip)        # 601020 <_GLOBAL_OFFSET_TABLE_+0x20>
  400436:	68 01 00 00 00       	pushq  $0x1
  40043b:	e9 d0 ff ff ff       	jmpq   400410 <_init+0x28>

0000000000400440 <fopen@plt>:
  400440:	ff 25 e2 0b 20 00    	jmpq   *0x200be2(%rip)        # 601028 <_GLOBAL_OFFSET_TABLE_+0x28>
  400446:	68 02 00 00 00       	pushq  $0x2
  40044b:	e9 c0 ff ff ff       	jmpq   400410 <_init+0x28>

Disassembly of section .plt.got:

0000000000400450 <.plt.got>:
  400450:	ff 25 a2 0b 20 00    	jmpq   *0x200ba2(%rip)        # 600ff8 <_DYNAMIC+0x1d0>
  400456:	66 90                	xchg   %ax,%ax

Disassembly of section .text:

0000000000400460 <_start>:
  400460:	31 ed                	xor    %ebp,%ebp
  400462:	49 89 d1             	mov    %rdx,%r9
  400465:	5e                   	pop    %rsi
  400466:	48 89 e2             	mov    %rsp,%rdx
  400469:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  40046d:	50                   	push   %rax
  40046e:	54                   	push   %rsp
  40046f:	49 c7 c0 d0 06 40 00 	mov    $0x4006d0,%r8
  400476:	48 c7 c1 60 06 40 00 	mov    $0x400660,%rcx
  40047d:	48 c7 c7 90 05 40 00 	mov    $0x400590,%rdi
  400484:	e8 a7 ff ff ff       	callq  400430 <__libc_start_main@plt>
  400489:	f4                   	hlt    
  40048a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000400490 <deregister_tm_clones>:
  400490:	b8 48 10 60 00       	mov    $0x601048,%eax
  400495:	48 3d 48 10 60 00    	cmp    $0x601048,%rax
  40049b:	74 13                	je     4004b0 <deregister_tm_clones+0x20>
  40049d:	b8 00 00 00 00       	mov    $0x0,%eax
  4004a2:	48 85 c0             	test   %rax,%rax
  4004a5:	74 09                	je     4004b0 <deregister_tm_clones+0x20>
  4004a7:	bf 48 10 60 00       	mov    $0x601048,%edi
  4004ac:	ff e0                	jmpq   *%rax
  4004ae:	66 90                	xchg   %ax,%ax
  4004b0:	c3                   	retq   
  4004b1:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  4004b6:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  4004bd:	00 00 00 

00000000004004c0 <register_tm_clones>:
  4004c0:	be 48 10 60 00       	mov    $0x601048,%esi
  4004c5:	48 81 ee 48 10 60 00 	sub    $0x601048,%rsi
  4004cc:	48 c1 fe 03          	sar    $0x3,%rsi
  4004d0:	48 89 f0             	mov    %rsi,%rax
  4004d3:	48 c1 e8 3f          	shr    $0x3f,%rax
  4004d7:	48 01 c6             	add    %rax,%rsi
  4004da:	48 d1 fe             	sar    %rsi
  4004dd:	74 11                	je     4004f0 <register_tm_clones+0x30>
  4004df:	b8 00 00 00 00       	mov    $0x0,%eax
  4004e4:	48 85 c0             	test   %rax,%rax
  4004e7:	74 07                	je     4004f0 <register_tm_clones+0x30>
  4004e9:	bf 48 10 60 00       	mov    $0x601048,%edi
  4004ee:	ff e0                	jmpq   *%rax
  4004f0:	c3                   	retq   
  4004f1:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  4004f6:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  4004fd:	00 00 00 

0000000000400500 <__do_global_dtors_aux>:
  400500:	80 3d 49 0b 20 00 00 	cmpb   $0x0,0x200b49(%rip)        # 601050 <completed.7931>
  400507:	75 17                	jne    400520 <__do_global_dtors_aux+0x20>
  400509:	55                   	push   %rbp
  40050a:	48 89 e5             	mov    %rsp,%rbp
  40050d:	e8 7e ff ff ff       	callq  400490 <deregister_tm_clones>
  400512:	c6 05 37 0b 20 00 01 	movb   $0x1,0x200b37(%rip)        # 601050 <completed.7931>
  400519:	5d                   	pop    %rbp
  40051a:	c3                   	retq   
  40051b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  400520:	c3                   	retq   
  400521:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  400526:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  40052d:	00 00 00 

0000000000400530 <frame_dummy>:
  400530:	eb 8e                	jmp    4004c0 <register_tm_clones>
  400532:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  400539:	00 00 00 
  40053c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400540 <victim_fun>:
uint8_t array1[16];
uint8_t array2[256 * 512];
uint8_t temp = 0;


void victim_fun(int idx) {
  400540:	48 89 e0             	mov    %rsp,%rax
  400543:	48 c1 f8 3f          	sar    $0x3f,%rax
  400547:	31 c9                	xor    %ecx,%ecx
    temp &= array2[array1[idx < array1_size ? (idx + 1) : 0] * 512];
  400549:	39 3d f1 0a 20 00    	cmp    %edi,0x200af1(%rip)        # 601040 <array1_size>
  40054f:	8d 57 01             	lea    0x1(%rdi),%edx
  400552:	0f 47 ca             	cmova  %edx,%ecx
  400555:	48 c7 c2 ff ff ff ff 	mov    $0xffffffffffffffff,%rdx
  40055c:	48 63 c9             	movslq %ecx,%rcx
  40055f:	0f b6 89 60 10 60 00 	movzbl 0x601060(%rcx),%ecx
  400566:	48 c1 e1 09          	shl    $0x9,%rcx
  40056a:	48 09 c1             	or     %rax,%rcx
  40056d:	8a 89 70 10 60 00    	mov    0x601070(%rcx),%cl
  400573:	08 c1                	or     %al,%cl
  400575:	20 0d d6 0a 20 00    	and    %cl,0x200ad6(%rip)        # 601051 <temp>
}
  40057b:	48 c1 e0 2f          	shl    $0x2f,%rax
  40057f:	48 09 c4             	or     %rax,%rsp
  400582:	c3                   	retq   
  400583:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  40058a:	00 00 00 
  40058d:	0f 1f 00             	nopl   (%rax)

0000000000400590 <main>:


int main(int argn, char* args[]) {
  400590:	53                   	push   %rbx
  400591:	48 89 e0             	mov    %rsp,%rax
  400594:	48 c7 c3 ff ff ff ff 	mov    $0xffffffffffffffff,%rbx
  40059b:	48 c1 f8 3f          	sar    $0x3f,%rax
    int source;

    FILE *file = fopen("temp.txt", "r");
  40059f:	bf e4 06 40 00       	mov    $0x4006e4,%edi
  4005a4:	be ed 06 40 00       	mov    $0x4006ed,%esi
  4005a9:	48 c1 e0 2f          	shl    $0x2f,%rax
  4005ad:	48 09 c4             	or     %rax,%rsp
  4005b0:	e8 8b fe ff ff       	callq  400440 <fopen@plt>
  4005b5:	48 89 e2             	mov    %rsp,%rdx
  4005b8:	48 8b 4c 24 f8       	mov    -0x8(%rsp),%rcx
  4005bd:	48 c1 fa 3f          	sar    $0x3f,%rdx
  4005c1:	48 81 f9 b5 05 40 00 	cmp    $0x4005b5,%rcx
  4005c8:	48 0f 45 d3          	cmovne %rbx,%rdx

    if (file == NULL)
  4005cc:	48 85 c0             	test   %rax,%rax
  4005cf:	74 5b                	je     40062c <main+0x9c>
  4005d1:	48 0f 44 d3          	cmove  %rbx,%rdx
        return 1;

    source = fgetc(file);
  4005d5:	48 c1 e2 2f          	shl    $0x2f,%rdx
  4005d9:	48 89 c7             	mov    %rax,%rdi
  4005dc:	48 09 d4             	or     %rdx,%rsp
  4005df:	e8 3c fe ff ff       	callq  400420 <fgetc_unlocked@plt>
  4005e4:	48 89 e2             	mov    %rsp,%rdx
  4005e7:	48 8b 4c 24 f8       	mov    -0x8(%rsp),%rcx
  4005ec:	48 c1 fa 3f          	sar    $0x3f,%rdx
  4005f0:	48 81 f9 e4 05 40 00 	cmp    $0x4005e4,%rcx
  4005f7:	48 0f 45 d3          	cmovne %rbx,%rdx
  4005fb:	89 c1                	mov    %eax,%ecx
uint8_t array2[256 * 512];
uint8_t temp = 0;


void victim_fun(int idx) {
    temp &= array2[array1[idx < array1_size ? (idx + 1) : 0] * 512];
  4005fd:	8d 71 01             	lea    0x1(%rcx),%esi
  400600:	31 c0                	xor    %eax,%eax
  400602:	39 0d 38 0a 20 00    	cmp    %ecx,0x200a38(%rip)        # 601040 <array1_size>
  400608:	0f 46 f0             	cmovbe %eax,%esi
  40060b:	48 63 ce             	movslq %esi,%rcx
  40060e:	0f b6 89 60 10 60 00 	movzbl 0x601060(%rcx),%ecx
  400615:	48 c1 e1 09          	shl    $0x9,%rcx
  400619:	48 09 d1             	or     %rdx,%rcx
  40061c:	8a 89 70 10 60 00    	mov    0x601070(%rcx),%cl
  400622:	08 d1                	or     %dl,%cl
  400624:	20 0d 27 0a 20 00    	and    %cl,0x200a27(%rip)        # 601051 <temp>
  40062a:	eb 09                	jmp    400635 <main+0xa5>
  40062c:	48 0f 45 d3          	cmovne %rbx,%rdx
  400630:	b8 01 00 00 00       	mov    $0x1,%eax
        return 1;

    source = fgetc(file);
    victim_fun(source);
    return 0;
}
  400635:	48 c1 e2 2f          	shl    $0x2f,%rdx
  400639:	48 09 d4             	or     %rdx,%rsp
  40063c:	5b                   	pop    %rbx
  40063d:	c3                   	retq   
  40063e:	66 90                	xchg   %ax,%ax

0000000000400640 <__llvm_retpoline_r11>:
  400640:	e8 0b 00 00 00       	callq  400650 <__llvm_retpoline_r11+0x10>
  400645:	f3 90                	pause  
  400647:	0f ae e8             	lfence 
  40064a:	eb f9                	jmp    400645 <__llvm_retpoline_r11+0x5>
  40064c:	0f 1f 40 00          	nopl   0x0(%rax)
  400650:	4c 89 1c 24          	mov    %r11,(%rsp)
  400654:	c3                   	retq   
  400655:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  40065c:	00 00 00 
  40065f:	90                   	nop

0000000000400660 <__libc_csu_init>:
  400660:	41 57                	push   %r15
  400662:	41 56                	push   %r14
  400664:	41 89 ff             	mov    %edi,%r15d
  400667:	41 55                	push   %r13
  400669:	41 54                	push   %r12
  40066b:	4c 8d 25 a6 07 20 00 	lea    0x2007a6(%rip),%r12        # 600e18 <__frame_dummy_init_array_entry>
  400672:	55                   	push   %rbp
  400673:	48 8d 2d a6 07 20 00 	lea    0x2007a6(%rip),%rbp        # 600e20 <__init_array_end>
  40067a:	53                   	push   %rbx
  40067b:	49 89 f6             	mov    %rsi,%r14
  40067e:	49 89 d5             	mov    %rdx,%r13
  400681:	4c 29 e5             	sub    %r12,%rbp
  400684:	48 83 ec 08          	sub    $0x8,%rsp
  400688:	48 c1 fd 03          	sar    $0x3,%rbp
  40068c:	e8 57 fd ff ff       	callq  4003e8 <_init>
  400691:	48 85 ed             	test   %rbp,%rbp
  400694:	74 20                	je     4006b6 <__libc_csu_init+0x56>
  400696:	31 db                	xor    %ebx,%ebx
  400698:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  40069f:	00 
  4006a0:	4c 89 ea             	mov    %r13,%rdx
  4006a3:	4c 89 f6             	mov    %r14,%rsi
  4006a6:	44 89 ff             	mov    %r15d,%edi
  4006a9:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  4006ad:	48 83 c3 01          	add    $0x1,%rbx
  4006b1:	48 39 eb             	cmp    %rbp,%rbx
  4006b4:	75 ea                	jne    4006a0 <__libc_csu_init+0x40>
  4006b6:	48 83 c4 08          	add    $0x8,%rsp
  4006ba:	5b                   	pop    %rbx
  4006bb:	5d                   	pop    %rbp
  4006bc:	41 5c                	pop    %r12
  4006be:	41 5d                	pop    %r13
  4006c0:	41 5e                	pop    %r14
  4006c2:	41 5f                	pop    %r15
  4006c4:	c3                   	retq   
  4006c5:	90                   	nop
  4006c6:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  4006cd:	00 00 00 

00000000004006d0 <__libc_csu_fini>:
  4006d0:	f3 c3                	repz retq 

Disassembly of section .fini:

00000000004006d4 <_fini>:
  4006d4:	48 83 ec 08          	sub    $0x8,%rsp
  4006d8:	48 83 c4 08          	add    $0x8,%rsp
  4006dc:	c3                   	retq   
