
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
  40046f:	49 c7 c0 e0 06 40 00 	mov    $0x4006e0,%r8
  400476:	48 c7 c1 70 06 40 00 	mov    $0x400670,%rcx
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
    if (x < array1_size) 
        return 1;
    return 0;
}

void victim_fun(int idx) {
  400540:	48 89 e0             	mov    %rsp,%rax
  400543:	48 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%rcx
  40054a:	48 c1 f8 3f          	sar    $0x3f,%rax
    if (is_x_safe(idx)) {                  
  40054e:	48 63 d7             	movslq %edi,%rdx
uint8_t array1[16];
uint8_t array2[256 * 512];
uint8_t temp = 0;

inline static int is_x_safe(size_t x) {
    if (x < array1_size) 
  400551:	8b 35 e9 0a 20 00    	mov    0x200ae9(%rip),%esi        # 601040 <array1_size>
  400557:	48 39 d6             	cmp    %rdx,%rsi
        return 1;
    return 0;
}

void victim_fun(int idx) {
    if (is_x_safe(idx)) {                  
  40055a:	76 22                	jbe    40057e <victim_fun+0x3e>
  40055c:	48 0f 46 c1          	cmovbe %rcx,%rax
        temp &= array2[array1[idx] * 512];
  400560:	0f b6 8a 60 10 60 00 	movzbl 0x601060(%rdx),%ecx
  400567:	48 c1 e1 09          	shl    $0x9,%rcx
  40056b:	48 09 c1             	or     %rax,%rcx
  40056e:	8a 89 70 10 60 00    	mov    0x601070(%rcx),%cl
  400574:	08 c1                	or     %al,%cl
  400576:	20 0d d5 0a 20 00    	and    %cl,0x200ad5(%rip)        # 601051 <temp>
  40057c:	eb 04                	jmp    400582 <victim_fun+0x42>
  40057e:	48 0f 47 c1          	cmova  %rcx,%rax
    }
}
  400582:	48 c1 e0 2f          	shl    $0x2f,%rax
  400586:	48 09 c4             	or     %rax,%rsp
  400589:	c3                   	retq   
  40058a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000400590 <main>:

int main(int argn, char* args[]) {
  400590:	53                   	push   %rbx
  400591:	48 89 e0             	mov    %rsp,%rax
  400594:	48 c7 c3 ff ff ff ff 	mov    $0xffffffffffffffff,%rbx
  40059b:	48 c1 f8 3f          	sar    $0x3f,%rax
    int source;

    FILE *file = fopen("temp.txt", "r");
  40059f:	bf f4 06 40 00       	mov    $0x4006f4,%edi
  4005a4:	be fd 06 40 00       	mov    $0x4006fd,%esi
  4005a9:	48 c1 e0 2f          	shl    $0x2f,%rax
  4005ad:	48 09 c4             	or     %rax,%rsp
  4005b0:	e8 8b fe ff ff       	callq  400440 <fopen@plt>
  4005b5:	48 89 e1             	mov    %rsp,%rcx
  4005b8:	48 8b 54 24 f8       	mov    -0x8(%rsp),%rdx
  4005bd:	48 c1 f9 3f          	sar    $0x3f,%rcx
  4005c1:	48 81 fa b5 05 40 00 	cmp    $0x4005b5,%rdx
  4005c8:	48 0f 45 cb          	cmovne %rbx,%rcx

    if (file == NULL)
  4005cc:	48 85 c0             	test   %rax,%rax
  4005cf:	74 5c                	je     40062d <main+0x9d>
  4005d1:	48 0f 44 cb          	cmove  %rbx,%rcx
        return 1;

    source = fgetc(file);
  4005d5:	48 c1 e1 2f          	shl    $0x2f,%rcx
  4005d9:	48 89 c7             	mov    %rax,%rdi
  4005dc:	48 09 cc             	or     %rcx,%rsp
  4005df:	e8 3c fe ff ff       	callq  400420 <fgetc_unlocked@plt>
  4005e4:	48 89 e1             	mov    %rsp,%rcx
  4005e7:	48 8b 54 24 f8       	mov    -0x8(%rsp),%rdx
  4005ec:	48 c1 f9 3f          	sar    $0x3f,%rcx
  4005f0:	48 81 fa e4 05 40 00 	cmp    $0x4005e4,%rdx
  4005f7:	48 0f 45 cb          	cmovne %rbx,%rcx
        return 1;
    return 0;
}

void victim_fun(int idx) {
    if (is_x_safe(idx)) {                  
  4005fb:	48 63 d0             	movslq %eax,%rdx
uint8_t array1[16];
uint8_t array2[256 * 512];
uint8_t temp = 0;

inline static int is_x_safe(size_t x) {
    if (x < array1_size) 
  4005fe:	8b 35 3c 0a 20 00    	mov    0x200a3c(%rip),%esi        # 601040 <array1_size>
  400604:	31 c0                	xor    %eax,%eax
  400606:	48 39 d6             	cmp    %rdx,%rsi
        return 1;
    return 0;
}

void victim_fun(int idx) {
    if (is_x_safe(idx)) {                  
  400609:	76 2d                	jbe    400638 <main+0xa8>
  40060b:	48 0f 46 cb          	cmovbe %rbx,%rcx
        temp &= array2[array1[idx] * 512];
  40060f:	0f b6 92 60 10 60 00 	movzbl 0x601060(%rdx),%edx
  400616:	48 c1 e2 09          	shl    $0x9,%rdx
  40061a:	48 09 ca             	or     %rcx,%rdx
  40061d:	8a 92 70 10 60 00    	mov    0x601070(%rdx),%dl
  400623:	08 ca                	or     %cl,%dl
  400625:	20 15 26 0a 20 00    	and    %dl,0x200a26(%rip)        # 601051 <temp>
  40062b:	eb 0f                	jmp    40063c <main+0xac>
  40062d:	48 0f 45 cb          	cmovne %rbx,%rcx
  400631:	b8 01 00 00 00       	mov    $0x1,%eax
  400636:	eb 04                	jmp    40063c <main+0xac>
  400638:	48 0f 47 cb          	cmova  %rbx,%rcx
        return 1;

    source = fgetc(file);
    victim_fun(source);
    return 0;
}
  40063c:	48 c1 e1 2f          	shl    $0x2f,%rcx
  400640:	48 09 cc             	or     %rcx,%rsp
  400643:	5b                   	pop    %rbx
  400644:	c3                   	retq   
  400645:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  40064c:	00 00 00 
  40064f:	90                   	nop

0000000000400650 <__llvm_retpoline_r11>:
  400650:	e8 0b 00 00 00       	callq  400660 <__llvm_retpoline_r11+0x10>
  400655:	f3 90                	pause  
  400657:	0f ae e8             	lfence 
  40065a:	eb f9                	jmp    400655 <__llvm_retpoline_r11+0x5>
  40065c:	0f 1f 40 00          	nopl   0x0(%rax)
  400660:	4c 89 1c 24          	mov    %r11,(%rsp)
  400664:	c3                   	retq   
  400665:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  40066c:	00 00 00 
  40066f:	90                   	nop

0000000000400670 <__libc_csu_init>:
  400670:	41 57                	push   %r15
  400672:	41 56                	push   %r14
  400674:	41 89 ff             	mov    %edi,%r15d
  400677:	41 55                	push   %r13
  400679:	41 54                	push   %r12
  40067b:	4c 8d 25 96 07 20 00 	lea    0x200796(%rip),%r12        # 600e18 <__frame_dummy_init_array_entry>
  400682:	55                   	push   %rbp
  400683:	48 8d 2d 96 07 20 00 	lea    0x200796(%rip),%rbp        # 600e20 <__init_array_end>
  40068a:	53                   	push   %rbx
  40068b:	49 89 f6             	mov    %rsi,%r14
  40068e:	49 89 d5             	mov    %rdx,%r13
  400691:	4c 29 e5             	sub    %r12,%rbp
  400694:	48 83 ec 08          	sub    $0x8,%rsp
  400698:	48 c1 fd 03          	sar    $0x3,%rbp
  40069c:	e8 47 fd ff ff       	callq  4003e8 <_init>
  4006a1:	48 85 ed             	test   %rbp,%rbp
  4006a4:	74 20                	je     4006c6 <__libc_csu_init+0x56>
  4006a6:	31 db                	xor    %ebx,%ebx
  4006a8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  4006af:	00 
  4006b0:	4c 89 ea             	mov    %r13,%rdx
  4006b3:	4c 89 f6             	mov    %r14,%rsi
  4006b6:	44 89 ff             	mov    %r15d,%edi
  4006b9:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  4006bd:	48 83 c3 01          	add    $0x1,%rbx
  4006c1:	48 39 eb             	cmp    %rbp,%rbx
  4006c4:	75 ea                	jne    4006b0 <__libc_csu_init+0x40>
  4006c6:	48 83 c4 08          	add    $0x8,%rsp
  4006ca:	5b                   	pop    %rbx
  4006cb:	5d                   	pop    %rbp
  4006cc:	41 5c                	pop    %r12
  4006ce:	41 5d                	pop    %r13
  4006d0:	41 5e                	pop    %r14
  4006d2:	41 5f                	pop    %r15
  4006d4:	c3                   	retq   
  4006d5:	90                   	nop
  4006d6:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  4006dd:	00 00 00 

00000000004006e0 <__libc_csu_fini>:
  4006e0:	f3 c3                	repz retq 

Disassembly of section .fini:

00000000004006e4 <_fini>:
  4006e4:	48 83 ec 08          	sub    $0x8,%rsp
  4006e8:	48 83 c4 08          	add    $0x8,%rsp
  4006ec:	c3                   	retq   
