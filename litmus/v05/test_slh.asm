
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
  40046f:	49 c7 c0 a0 06 40 00 	mov    $0x4006a0,%r8
  400476:	48 c7 c1 30 06 40 00 	mov    $0x400630,%rcx
  40047d:	48 c7 c7 70 05 40 00 	mov    $0x400570,%rdi
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
  400543:	48 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%rcx
  40054a:	48 c1 f8 3f          	sar    $0x3f,%rax
    size_t i;
    if (idx < array1_size) {                  
  40054e:	39 3d ec 0a 20 00    	cmp    %edi,0x200aec(%rip)        # 601040 <array1_size>
  400554:	76 0c                	jbe    400562 <victim_fun+0x22>
  400556:	48 0f 46 c1          	cmovbe %rcx,%rax
  40055a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
        for (i = idx - 1; i >= 0; i--) 
  400560:	eb fe                	jmp    400560 <victim_fun+0x20>
  400562:	48 0f 47 c1          	cmova  %rcx,%rax
            temp &= array2[array1[idx] * 512];
    }
}
  400566:	48 c1 e0 2f          	shl    $0x2f,%rax
  40056a:	48 09 c4             	or     %rax,%rsp
  40056d:	c3                   	retq   
  40056e:	66 90                	xchg   %ax,%ax

0000000000400570 <main>:

int main(int argn, char* args[]) {
  400570:	53                   	push   %rbx
  400571:	48 89 e0             	mov    %rsp,%rax
  400574:	48 c7 c3 ff ff ff ff 	mov    $0xffffffffffffffff,%rbx
  40057b:	48 c1 f8 3f          	sar    $0x3f,%rax
    int source;

    FILE *file = fopen("temp.txt", "r");
  40057f:	bf b4 06 40 00       	mov    $0x4006b4,%edi
  400584:	be bd 06 40 00       	mov    $0x4006bd,%esi
  400589:	48 c1 e0 2f          	shl    $0x2f,%rax
  40058d:	48 09 c4             	or     %rax,%rsp
  400590:	e8 ab fe ff ff       	callq  400440 <fopen@plt>
  400595:	48 89 e2             	mov    %rsp,%rdx
  400598:	48 8b 4c 24 f8       	mov    -0x8(%rsp),%rcx
  40059d:	48 c1 fa 3f          	sar    $0x3f,%rdx
  4005a1:	48 81 f9 95 05 40 00 	cmp    $0x400595,%rcx
  4005a8:	48 0f 45 d3          	cmovne %rbx,%rdx

    if (file == NULL)
  4005ac:	48 85 c0             	test   %rax,%rax
  4005af:	74 41                	je     4005f2 <main+0x82>
  4005b1:	48 0f 44 d3          	cmove  %rbx,%rdx
        return 1;

    source = fgetc(file);
  4005b5:	48 c1 e2 2f          	shl    $0x2f,%rdx
  4005b9:	48 89 c7             	mov    %rax,%rdi
  4005bc:	48 09 d4             	or     %rdx,%rsp
  4005bf:	e8 5c fe ff ff       	callq  400420 <fgetc_unlocked@plt>
  4005c4:	48 89 e2             	mov    %rsp,%rdx
  4005c7:	48 8b 4c 24 f8       	mov    -0x8(%rsp),%rcx
  4005cc:	48 c1 fa 3f          	sar    $0x3f,%rdx
  4005d0:	48 81 f9 c4 05 40 00 	cmp    $0x4005c4,%rcx
  4005d7:	48 0f 45 d3          	cmovne %rbx,%rdx
  4005db:	89 c1                	mov    %eax,%ecx
  4005dd:	31 c0                	xor    %eax,%eax
uint8_t temp = 0;


void victim_fun(int idx) {
    size_t i;
    if (idx < array1_size) {                  
  4005df:	39 0d 5b 0a 20 00    	cmp    %ecx,0x200a5b(%rip)        # 601040 <array1_size>
  4005e5:	76 16                	jbe    4005fd <main+0x8d>
  4005e7:	48 0f 46 d3          	cmovbe %rbx,%rdx
  4005eb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
        for (i = idx - 1; i >= 0; i--) 
  4005f0:	eb fe                	jmp    4005f0 <main+0x80>
  4005f2:	48 0f 45 d3          	cmovne %rbx,%rdx
  4005f6:	b8 01 00 00 00       	mov    $0x1,%eax
  4005fb:	eb 04                	jmp    400601 <main+0x91>
  4005fd:	48 0f 47 d3          	cmova  %rbx,%rdx
        return 1;

    source = fgetc(file);
    victim_fun(source);
    return 0;
}
  400601:	48 c1 e2 2f          	shl    $0x2f,%rdx
  400605:	48 09 d4             	or     %rdx,%rsp
  400608:	5b                   	pop    %rbx
  400609:	c3                   	retq   
  40060a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000400610 <__llvm_retpoline_r11>:
  400610:	e8 0b 00 00 00       	callq  400620 <__llvm_retpoline_r11+0x10>
  400615:	f3 90                	pause  
  400617:	0f ae e8             	lfence 
  40061a:	eb f9                	jmp    400615 <__llvm_retpoline_r11+0x5>
  40061c:	0f 1f 40 00          	nopl   0x0(%rax)
  400620:	4c 89 1c 24          	mov    %r11,(%rsp)
  400624:	c3                   	retq   
  400625:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  40062c:	00 00 00 
  40062f:	90                   	nop

0000000000400630 <__libc_csu_init>:
  400630:	41 57                	push   %r15
  400632:	41 56                	push   %r14
  400634:	41 89 ff             	mov    %edi,%r15d
  400637:	41 55                	push   %r13
  400639:	41 54                	push   %r12
  40063b:	4c 8d 25 d6 07 20 00 	lea    0x2007d6(%rip),%r12        # 600e18 <__frame_dummy_init_array_entry>
  400642:	55                   	push   %rbp
  400643:	48 8d 2d d6 07 20 00 	lea    0x2007d6(%rip),%rbp        # 600e20 <__init_array_end>
  40064a:	53                   	push   %rbx
  40064b:	49 89 f6             	mov    %rsi,%r14
  40064e:	49 89 d5             	mov    %rdx,%r13
  400651:	4c 29 e5             	sub    %r12,%rbp
  400654:	48 83 ec 08          	sub    $0x8,%rsp
  400658:	48 c1 fd 03          	sar    $0x3,%rbp
  40065c:	e8 87 fd ff ff       	callq  4003e8 <_init>
  400661:	48 85 ed             	test   %rbp,%rbp
  400664:	74 20                	je     400686 <__libc_csu_init+0x56>
  400666:	31 db                	xor    %ebx,%ebx
  400668:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  40066f:	00 
  400670:	4c 89 ea             	mov    %r13,%rdx
  400673:	4c 89 f6             	mov    %r14,%rsi
  400676:	44 89 ff             	mov    %r15d,%edi
  400679:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  40067d:	48 83 c3 01          	add    $0x1,%rbx
  400681:	48 39 eb             	cmp    %rbp,%rbx
  400684:	75 ea                	jne    400670 <__libc_csu_init+0x40>
  400686:	48 83 c4 08          	add    $0x8,%rsp
  40068a:	5b                   	pop    %rbx
  40068b:	5d                   	pop    %rbp
  40068c:	41 5c                	pop    %r12
  40068e:	41 5d                	pop    %r13
  400690:	41 5e                	pop    %r14
  400692:	41 5f                	pop    %r15
  400694:	c3                   	retq   
  400695:	90                   	nop
  400696:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  40069d:	00 00 00 

00000000004006a0 <__libc_csu_fini>:
  4006a0:	f3 c3                	repz retq 

Disassembly of section .fini:

00000000004006a4 <_fini>:
  4006a4:	48 83 ec 08          	sub    $0x8,%rsp
  4006a8:	48 83 c4 08          	add    $0x8,%rsp
  4006ac:	c3                   	retq   
