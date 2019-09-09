
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
  40046f:	49 c7 c0 10 07 40 00 	mov    $0x400710,%r8
  400476:	48 c7 c1 a0 06 40 00 	mov    $0x4006a0,%rcx
  40047d:	48 c7 c7 b0 05 40 00 	mov    $0x4005b0,%rdi
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
  400543:	49 c7 c0 ff ff ff ff 	mov    $0xffffffffffffffff,%r8
  40054a:	48 c1 f8 3f          	sar    $0x3f,%rax
    static size_t last_x = 0;
    if (idx == last_x) {                  
  40054e:	48 63 d7             	movslq %edi,%rdx
  400551:	48 39 15 08 0b 20 00 	cmp    %rdx,0x200b08(%rip)        # 601060 <victim_fun.last_x>
  400558:	75 2e                	jne    400588 <victim_fun+0x48>
  40055a:	49 0f 45 c0          	cmovne %r8,%rax
        temp &= array2[array1[idx] * 512];
  40055e:	0f b6 b2 70 10 60 00 	movzbl 0x601070(%rdx),%esi
  400565:	48 c1 e6 09          	shl    $0x9,%rsi
  400569:	48 09 c6             	or     %rax,%rsi
  40056c:	8a 8e 80 10 60 00    	mov    0x601080(%rsi),%cl
  400572:	08 c1                	or     %al,%cl
  400574:	20 0d de 0a 20 00    	and    %cl,0x200ade(%rip)        # 601058 <temp>
    }

    if (idx < array1_size)
  40057a:	39 3d c0 0a 20 00    	cmp    %edi,0x200ac0(%rip)        # 601040 <array1_size>
  400580:	77 12                	ja     400594 <victim_fun+0x54>
  400582:	49 0f 47 c0          	cmova  %r8,%rax
  400586:	eb 17                	jmp    40059f <victim_fun+0x5f>
  400588:	49 0f 44 c0          	cmove  %r8,%rax
  40058c:	39 3d ae 0a 20 00    	cmp    %edi,0x200aae(%rip)        # 601040 <array1_size>
  400592:	76 ee                	jbe    400582 <victim_fun+0x42>
  400594:	49 0f 46 c0          	cmovbe %r8,%rax
        last_x = idx;
  400598:	48 89 15 c1 0a 20 00 	mov    %rdx,0x200ac1(%rip)        # 601060 <victim_fun.last_x>
}
  40059f:	48 c1 e0 2f          	shl    $0x2f,%rax
  4005a3:	48 09 c4             	or     %rax,%rsp
  4005a6:	c3                   	retq   
  4005a7:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  4005ae:	00 00 

00000000004005b0 <main>:

int main(int argn, char* args[]) {
  4005b0:	53                   	push   %rbx
  4005b1:	48 89 e0             	mov    %rsp,%rax
  4005b4:	48 c7 c3 ff ff ff ff 	mov    $0xffffffffffffffff,%rbx
  4005bb:	48 c1 f8 3f          	sar    $0x3f,%rax
    int source;

    FILE *file = fopen("temp.txt", "r");
  4005bf:	bf 24 07 40 00       	mov    $0x400724,%edi
  4005c4:	be 2d 07 40 00       	mov    $0x40072d,%esi
  4005c9:	48 c1 e0 2f          	shl    $0x2f,%rax
  4005cd:	48 09 c4             	or     %rax,%rsp
  4005d0:	e8 6b fe ff ff       	callq  400440 <fopen@plt>
  4005d5:	48 89 e2             	mov    %rsp,%rdx
  4005d8:	48 8b 4c 24 f8       	mov    -0x8(%rsp),%rcx
  4005dd:	48 c1 fa 3f          	sar    $0x3f,%rdx
  4005e1:	48 81 f9 d5 05 40 00 	cmp    $0x4005d5,%rcx
  4005e8:	48 0f 45 d3          	cmovne %rbx,%rdx

    if (file == NULL)
  4005ec:	48 85 c0             	test   %rax,%rax
  4005ef:	74 58                	je     400649 <main+0x99>
  4005f1:	48 0f 44 d3          	cmove  %rbx,%rdx
        return 1;

    source = fgetc(file);
  4005f5:	48 c1 e2 2f          	shl    $0x2f,%rdx
  4005f9:	48 89 c7             	mov    %rax,%rdi
  4005fc:	48 09 d4             	or     %rdx,%rsp
  4005ff:	e8 1c fe ff ff       	callq  400420 <fgetc_unlocked@plt>
  400604:	48 89 e2             	mov    %rsp,%rdx
  400607:	48 8b 4c 24 f8       	mov    -0x8(%rsp),%rcx
  40060c:	48 c1 fa 3f          	sar    $0x3f,%rdx
  400610:	48 81 f9 04 06 40 00 	cmp    $0x400604,%rcx
  400617:	48 0f 45 d3          	cmovne %rbx,%rdx
uint8_t temp = 0;


void victim_fun(int idx) {
    static size_t last_x = 0;
    if (idx == last_x) {                  
  40061b:	48 63 f0             	movslq %eax,%rsi
  40061e:	48 39 35 3b 0a 20 00 	cmp    %rsi,0x200a3b(%rip)        # 601060 <victim_fun.last_x>
  400625:	75 2d                	jne    400654 <main+0xa4>
  400627:	48 0f 45 d3          	cmovne %rbx,%rdx
        temp &= array2[array1[idx] * 512];
  40062b:	0f b6 8e 70 10 60 00 	movzbl 0x601070(%rsi),%ecx
  400632:	48 c1 e1 09          	shl    $0x9,%rcx
  400636:	48 09 d1             	or     %rdx,%rcx
  400639:	8a 89 80 10 60 00    	mov    0x601080(%rcx),%cl
  40063f:	08 d1                	or     %dl,%cl
  400641:	20 0d 11 0a 20 00    	and    %cl,0x200a11(%rip)        # 601058 <temp>
  400647:	eb 0f                	jmp    400658 <main+0xa8>
  400649:	48 0f 45 d3          	cmovne %rbx,%rdx
  40064d:	b9 01 00 00 00       	mov    $0x1,%ecx
  400652:	eb 1f                	jmp    400673 <main+0xc3>
  400654:	48 0f 44 d3          	cmove  %rbx,%rdx
  400658:	31 c9                	xor    %ecx,%ecx
    }

    if (idx < array1_size)
  40065a:	39 05 e0 09 20 00    	cmp    %eax,0x2009e0(%rip)        # 601040 <array1_size>
  400660:	76 0d                	jbe    40066f <main+0xbf>
  400662:	48 0f 46 d3          	cmovbe %rbx,%rdx
        last_x = idx;
  400666:	48 89 35 f3 09 20 00 	mov    %rsi,0x2009f3(%rip)        # 601060 <victim_fun.last_x>
  40066d:	eb 04                	jmp    400673 <main+0xc3>
  40066f:	48 0f 47 d3          	cmova  %rbx,%rdx
        return 1;

    source = fgetc(file);
    victim_fun(source);
    return 0;
}
  400673:	48 c1 e2 2f          	shl    $0x2f,%rdx
  400677:	89 c8                	mov    %ecx,%eax
  400679:	48 09 d4             	or     %rdx,%rsp
  40067c:	5b                   	pop    %rbx
  40067d:	c3                   	retq   
  40067e:	66 90                	xchg   %ax,%ax

0000000000400680 <__llvm_retpoline_r11>:
  400680:	e8 0b 00 00 00       	callq  400690 <__llvm_retpoline_r11+0x10>
  400685:	f3 90                	pause  
  400687:	0f ae e8             	lfence 
  40068a:	eb f9                	jmp    400685 <__llvm_retpoline_r11+0x5>
  40068c:	0f 1f 40 00          	nopl   0x0(%rax)
  400690:	4c 89 1c 24          	mov    %r11,(%rsp)
  400694:	c3                   	retq   
  400695:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  40069c:	00 00 00 
  40069f:	90                   	nop

00000000004006a0 <__libc_csu_init>:
  4006a0:	41 57                	push   %r15
  4006a2:	41 56                	push   %r14
  4006a4:	41 89 ff             	mov    %edi,%r15d
  4006a7:	41 55                	push   %r13
  4006a9:	41 54                	push   %r12
  4006ab:	4c 8d 25 66 07 20 00 	lea    0x200766(%rip),%r12        # 600e18 <__frame_dummy_init_array_entry>
  4006b2:	55                   	push   %rbp
  4006b3:	48 8d 2d 66 07 20 00 	lea    0x200766(%rip),%rbp        # 600e20 <__init_array_end>
  4006ba:	53                   	push   %rbx
  4006bb:	49 89 f6             	mov    %rsi,%r14
  4006be:	49 89 d5             	mov    %rdx,%r13
  4006c1:	4c 29 e5             	sub    %r12,%rbp
  4006c4:	48 83 ec 08          	sub    $0x8,%rsp
  4006c8:	48 c1 fd 03          	sar    $0x3,%rbp
  4006cc:	e8 17 fd ff ff       	callq  4003e8 <_init>
  4006d1:	48 85 ed             	test   %rbp,%rbp
  4006d4:	74 20                	je     4006f6 <__libc_csu_init+0x56>
  4006d6:	31 db                	xor    %ebx,%ebx
  4006d8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  4006df:	00 
  4006e0:	4c 89 ea             	mov    %r13,%rdx
  4006e3:	4c 89 f6             	mov    %r14,%rsi
  4006e6:	44 89 ff             	mov    %r15d,%edi
  4006e9:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  4006ed:	48 83 c3 01          	add    $0x1,%rbx
  4006f1:	48 39 eb             	cmp    %rbp,%rbx
  4006f4:	75 ea                	jne    4006e0 <__libc_csu_init+0x40>
  4006f6:	48 83 c4 08          	add    $0x8,%rsp
  4006fa:	5b                   	pop    %rbx
  4006fb:	5d                   	pop    %rbp
  4006fc:	41 5c                	pop    %r12
  4006fe:	41 5d                	pop    %r13
  400700:	41 5e                	pop    %r14
  400702:	41 5f                	pop    %r15
  400704:	c3                   	retq   
  400705:	90                   	nop
  400706:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  40070d:	00 00 00 

0000000000400710 <__libc_csu_fini>:
  400710:	f3 c3                	repz retq 

Disassembly of section .fini:

0000000000400714 <_fini>:
  400714:	48 83 ec 08          	sub    $0x8,%rsp
  400718:	48 83 c4 08          	add    $0x8,%rsp
  40071c:	c3                   	retq   
