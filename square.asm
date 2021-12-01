default rel

global squareSphere
global squareTetrahedron
global squareParallelepiped
global square

section .data
sqthree: dq 3FFBB645A1CAC083H

SECTION .text

squareSphere:
        push    rbp              
        mov     rbp, rsp                           
        movsd   [rbp-8H], xmm0                    
        movsd   xmm1, [rbp-8H]                
        movsd   xmm0, [rel ?_005]               
        mulsd   xmm0, xmm1                    
        mulsd   xmm0, [rbp-8H]                   
        pop     rbp                                   
        ret                                           

squareTetrahedron:
        push    rbp 
        mov     rbp, rsp 
        movsd   [rbp-8H], xmm0  
        movsd   xmm1, [rbp-8H]
        movsd   xmm0, [sqthree]
        mulsd   xmm0, xmm1 
        mulsd   xmm0, [rbp-8H]
        pop     rbp
        ret                                        

squareParallelepiped:
        push    rbp                                    
        mov     rbp, rsp                               
        movsd   [rbp-8H], xmm0                 
        movsd   [rbp-10H], xmm1                 
        movsd   [rbp-18H], xmm2                 
        movsd   xmm0, [rbp-8H]                   
        movapd  xmm1, xmm0                           
        mulsd   xmm1, [rbp-10H]                
        movsd   xmm0, [rbp-8H]                  
        mulsd   xmm0, [rbp-18H]                  
        addsd   xmm1, xmm0                  
        movsd   xmm0, [rbp-10H]         
        mulsd   xmm0, [rbp-18H]                 
        addsd   xmm0, xmm1                       
        addsd   xmm0, xmm0                      
        pop     rbp                                
        ret                                     

square: 
        push    rbp                                  
        mov     rbp, rsp                               
        sub     rsp, 40                              
        mov     eax, edi                              
        movsd   [rbp-10H], xmm0                  
        movsd   [rbp-18H], xmm1                  
        movsd   [rbp-20H], xmm2                 
        mov     byte [rbp-4H], al                   
        cmp     byte [rbp-4H], 1                  
        jnz     ?_001                            
        mov     rax, [rbp-10H]                 
        mov     [rbp-28H], rax                
        movsd   xmm0, [rbp-28H]                  
        call    squareSphere                       
        movq    rax, xmm0                          
        jmp     ?_004                                 

?_001:  cmp     byte [rbp-4H], 2                   
        jnz     ?_002                                  
        movsd   xmm1, [rbp-20H]                 
        movsd   xmm0, [rbp-18H]                 
        mov     rax, [rbp-10H]                 
        movapd  xmm2, xmm1                             
        movapd  xmm1, xmm0                           
        mov     [rbp-28H], rax                  
        movsd   xmm0, [rbp-28H]                 
        call    squareParallelepiped                   
        movq    rax, xmm0                             
        jmp     ?_004                               

?_002:  cmp     byte [rbp-4H], 3                     
        jnz     ?_003                               
        mov     rax, [rbp-10H]                
        mov     [rbp-28H], rax                  
        movsd   xmm0, [rbp-28H]                  
        call    squareTetrahedron                      
        movq    rax, xmm0                            
        jmp     ?_004                                

?_003:  mov     rax, [rel ?_007]                 
?_004:  mov     [rbp-28H], rax                 
        movsd   xmm0, [rbp-28H]                   
        leave                                         
        ret        
?_005:                                               
        dq 402921CAC0000000H                                    

?_006:  dq 3FFBB67AE8584CAAH                           

?_007:  dq 0000000000000000H                         



