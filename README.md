## Conversion of lambda to SKIBC implemented in antlr4

### SKIBC combinator

```
Sxyz = xz(yz)
Kxy = x  
Ix = x 
Bxyz = x(yz)
Cxyz = xzy
```

### Conversion rules

```

(1) \x.x   -> I

(2) \x.M   -> (KM)                (if x is not free in M)

(3) \x.(MN) -> (C(\x.M)N)         (if x is not free in N)

(4) \x.(MN) -> (BM(\x.N))         (if x is not free in M)

(5) \x.(MN) -> (S(\x.M)(\x.N))

(6) \x.(Mx) -> M                  (if x is not free in M)

(7) \x.(MM) -> (B(SII)(\x.M))     (if x is free in M)
      because (\x.(MM))y      -> (MM)[x:=y]
                              -> (M[x:=y])(M[x:=y])
              (B(SII)(\x.M))y -> (SII)((\x.M)y)
                              -> (SII)(M[x:=y])
                              -> I(M[x:=y])(I(M[x:=y]))
                              -> (M[x:=y])(M[x:=y])
```

exmaple 

```
[Y] is Y fixed-point combinator

[Y] ::= \f.((\x.f(xx))(\x.f(xx)))
[Y] ::= B(SII)\f.(\x.f(xx))                  (by 7)
[Y] ::= B(SII)(\f.(Bf(\x.(xx))))             (by 4)
[Y] ::= B(SII)(\f.(Bf(S(\x.x)(\x.x))))       (by 5)
[Y] ::= B(SII)(C(\f.Bf)(S(\x.x)(\x.x)))      (by 3)
[Y] ::= B(SII)(CB(SII))                      (by 6,1)

```

### Running the tests 

unzip [lambda2SKIBC-win64.zip](https://github.com/AkiraHakuta/lambda2SKIBC/releases/tag/untagged-ed9758e667939eb5ca74)  

Open `Dos Command Prompt`  
from `C:/.../lambda2SKIBC`


```
/* test1.txt */ 

[Y] ::= \f.((\x.f(xx))(\x.f(xx)));
[fact] := \f.\x.(([iszero]x)[1]([mult]x(f([pred]x))));
```


```
> lambda2skibc.exe test1.txt -t 

   0: [Y]::=\f.((\x.f(xx))(\x.f(xx)));
   1: [Y] ::= (B(SII)(\f.((B(f)(\x.(xx))))));
   2: [Y] ::= (B(SII)((C(\f.Bf)(((S(\x.x)(\x.x)))))));
   3: [Y] ::= (B(SII)(CB((SII))));
   4: [Y] ::= (B(SII)(CB(SII)));

   0: [fact]:=\f.\x.(([iszero]x)[1]([mult]x(f([pred]x))));
   1: [fact] := (\f.(S(\x.([iszero]x)[1])(\x.([mult]x(f([pred]x))))));
   2: [fact] := ((B(S((C(\x.([iszero]x))([1]))))(\f.((S(\x.[mult]x)(\x.(f([pred]x))))))));
   3: [fact] := (B(S(C(([iszero]))[1]))((B(S(([mult])))(\f.((B(f)(\x.([pred]x))))))));
   4: [fact] := (B(S(C[iszero][1]))(B(S[mult])((C(\f.Bf)((([pred])))))));
   5: [fact] := (B(S(C[iszero][1]))(B(S[mult])(CB[pred])));
   6: [fact] := (B(S(C[iszero][1]))(B(S[mult])(CB[pred])));
```

```
/* test2.txt */  

putStr("//fixed-point combinators");
[Y] ::= \f.((\x.f(xx))(\x.f(xx)));
[Z] ::= \f.((\x.(f(\y.(xxy))))(\x.(f(\y.(xxy)))));
[T] ::= (\x.\y.(y(xxy)))(\x.\y.(y(xxy)));
putStr("//The simplest fixed-point combinator, found by John Tromp, is");
[Y''] ::= (\x.\y.(xyx))(\y.\x.(y(xyx)));
....
....
[fold_left] := \f.\g.\a.\l.(([isnil]l)a(fg(ga([head]l))([tail]l)));
[fold_left'] := \f.\g.\a.\l.(([isnil]l)a(ffg(ga([head]l))([tail]l)));
[max_x_y] := \x.\y.(([iszero]([sub]xy))yx);
```

``` 
> lambda2skibc.exe test2.txt 

//fixedpoint combinators
[Y] ::= (B(SII)(CB(SII)));
[Z] ::= (B(SII)(CB(SII)));
[T] ::= (B(SI)(SII))(B(SI)(SII));
//The simplest fixed-point combinator, found by John Tromp, is
[Y''] ::= (SCI)(SB(C(BS(CI))I));
....
....
[fold_left] := (B(B(S(BS(C(S(K[isnil])I)))))(C(BC(B(BS)(B(B(BS))(C(BS(B(BB)(BB)))(C(BS(BB))(K[head]))))))(C(BS(BK(K[tail])))I)));
[fold_left'] := (B(B(S(BS(C(S(K[isnil])I)))))(C(BC(B(BS)(B(B(BS))(C(BS(B(BB)(B(BB)(SII))))(C(BS(BB))(K[head]))))))(C(BS(BK(K[tail])))I)));
[max_x_y] := (S(BC(C(BS(B(B[iszero])[sub]))I))I);
``` 


### Building (Windows only)   
<ol>
<li>

Install [mingw-w64](https://www.mingw-w64.org/downloads/)  

</li>
<li>

Install [cmake](https://cmake.org/download/)   
 
</li>
<li>

Install antlr4 of the Cpp target  
see [antlr4_Cpp_examples](https://github.com/AkiraHakuta/antlr4_Cpp_examples)  

</li>

Compile   
open Dos Command Prompt  
from `C:/.../lambda2SKIBC`  

```
> mkdir build
> cd build
> cmake -G "MinGW Makefiles" ..
> mingw32-make.exe  
```
</li>  
</ol>


