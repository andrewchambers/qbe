#ifndef X /* amd64 */
	#define X(NMemArgs, SetsZeroFlag, LeavesFlags)
#endif

#ifndef V /* riscv64 */
	#define V(Imm)
#endif

#ifndef F
#define F(a,b,c,d,E,f,g,h,i,j)
#endif

#define T(a,b,c,d,E,f,g,h,i,j) {                                   \
	{[Kw]=K##a, [Kl]=K##b, [Ks]=K##c, [Kd]=K##d, [Ke]=K##E}, \
	{[Kw]=K##f, [Kl]=K##g, [Ks]=K##h, [Kd]=K##i, [Ke]=K##j}  \
}

/*********************/
/* PUBLIC OPERATIONS */
/*********************/

/*                                can fold                        */
/*                                | has identity                  */
/*                                | | identity value for arg[1]   */
/*                                | | | commutative               */
/*                                | | | | associative             */
/*                                | | | | | idempotent            */
/*                                | | | | | | c{eq,ne}[wl]        */
/*                                | | | | | | | c[us][gl][et][wl] */
/*                                | | | | | | | | value if = args */
/*                                | | | | | | | | | pinned        */
/* Arithmetic and Bits            v v v v v v v v v v             */
O(add,     T(w, l, s, d, E, w, l, s, d, E), F(1,1,0,1,1,0,0,0,0,0)) X(2,1,0) V(1)
O(sub,     T(w, l, s, d, E, w, l, s, d, E), F(1,1,0,0,0,0,0,0,0,0)) X(2,1,0) V(0)
O(neg,     T(w, l, s, d, E, x, x, x, x, E), F(1,0,0,0,0,0,0,0,0,0)) X(1,1,0) V(0)
O(div,     T(w, l, s, d, E, w, l, s, d, E), F(1,1,1,0,0,0,0,0,0,0)) X(0,0,0) V(0)
O(rem,     T(w, l, E, E, E, w, l, E, E, E), F(1,0,0,0,0,0,0,0,0,0)) X(0,0,0) V(0)
O(udiv,    T(w, l, E, E, E, w, l, E, E, E), F(1,1,1,0,0,0,0,0,0,0)) X(0,0,0) V(0)
O(urem,    T(w, l, E, E, E, w, l, E, E, E), F(1,0,0,0,0,0,0,0,0,0)) X(0,0,0) V(0)
O(mul,     T(w, l, s, d, E, w, l, s, d, E), F(1,1,1,1,0,0,0,0,0,0)) X(2,0,0) V(0)
O(and,     T(w, l, E, E, E, w, l, E, E, E), F(1,0,0,1,1,1,0,0,0,0)) X(2,1,0) V(1)
O(or,      T(w, l, E, E, E, w, l, E, E, E), F(1,1,0,1,1,1,0,0,0,0)) X(2,1,0) V(1)
O(xor,     T(w, l, E, E, E, w, l, E, E, E), F(1,1,0,1,1,0,0,0,0,0)) X(2,1,0) V(1)
O(sar,     T(w, l, E, E, E, w, w, E, E, E), F(1,1,0,0,0,0,0,0,0,0)) X(1,1,0) V(1)
O(shr,     T(w, l, E, E, E, w, w, E, E, E), F(1,1,0,0,0,0,0,0,0,0)) X(1,1,0) V(1)
O(shl,     T(w, l, E, E, E, w, w, E, E, E), F(1,1,0,0,0,0,0,0,0,0)) X(1,1,0) V(1)

/* Comparisons */
O(ceqw,    T(w, w, E, E, E, w, w, E, E, E), F(1,1,1,1,0,0,1,0,1,0)) X(0,1,0) V(0)
O(cnew,    T(w, w, E, E, E, w, w, E, E, E), F(1,1,0,1,0,0,1,0,0,0)) X(0,1,0) V(0)
O(csgew,   T(w, w, E, E, E, w, w, E, E, E), F(1,0,0,0,0,0,0,1,1,0)) X(0,1,0) V(0)
O(csgtw,   T(w, w, E, E, E, w, w, E, E, E), F(1,0,0,0,0,0,0,1,0,0)) X(0,1,0) V(0)
O(cslew,   T(w, w, E, E, E, w, w, E, E, E), F(1,0,0,0,0,0,0,1,1,0)) X(0,1,0) V(0)
O(csltw,   T(w, w, E, E, E, w, w, E, E, E), F(1,0,0,0,0,0,0,1,0,0)) X(0,1,0) V(1)
O(cugew,   T(w, w, E, E, E, w, w, E, E, E), F(1,0,0,0,0,0,0,1,1,0)) X(0,1,0) V(0)
O(cugtw,   T(w, w, E, E, E, w, w, E, E, E), F(1,0,0,0,0,0,0,1,0,0)) X(0,1,0) V(0)
O(culew,   T(w, w, E, E, E, w, w, E, E, E), F(1,0,0,0,0,0,0,1,1,0)) X(0,1,0) V(0)
O(cultw,   T(w, w, E, E, E, w, w, E, E, E), F(1,0,0,0,0,0,0,1,0,0)) X(0,1,0) V(1)

O(ceql,    T(l, l, E, E, E, l, l, E, E, E), F(1,0,0,1,0,0,1,0,1,0)) X(0,1,0) V(0)
O(cnel,    T(l, l, E, E, E, l, l, E, E, E), F(1,0,0,1,0,0,1,0,0,0)) X(0,1,0) V(0)
O(csgel,   T(l, l, E, E, E, l, l, E, E, E), F(1,0,0,0,0,0,0,1,1,0)) X(0,1,0) V(0)
O(csgtl,   T(l, l, E, E, E, l, l, E, E, E), F(1,0,0,0,0,0,0,1,0,0)) X(0,1,0) V(0)
O(cslel,   T(l, l, E, E, E, l, l, E, E, E), F(1,0,0,0,0,0,0,1,1,0)) X(0,1,0) V(0)
O(csltl,   T(l, l, E, E, E, l, l, E, E, E), F(1,0,0,0,0,0,0,1,0,0)) X(0,1,0) V(1)
O(cugel,   T(l, l, E, E, E, l, l, E, E, E), F(1,0,0,0,0,0,0,1,1,0)) X(0,1,0) V(0)
O(cugtl,   T(l, l, E, E, E, l, l, E, E, E), F(1,0,0,0,0,0,0,1,0,0)) X(0,1,0) V(0)
O(culel,   T(l, l, E, E, E, l, l, E, E, E), F(1,0,0,0,0,0,0,1,1,0)) X(0,1,0) V(0)
O(cultl,   T(l, l, E, E, E, l, l, E, E, E), F(1,0,0,0,0,0,0,1,0,0)) X(0,1,0) V(1)

O(ceqs,    T(s, s, E, E, E, s, s, E, E, E), F(1,0,0,1,0,0,0,0,0,0)) X(0,1,0) V(0)
O(cges,    T(s, s, E, E, E, s, s, E, E, E), F(1,0,0,0,0,0,0,0,0,0)) X(0,1,0) V(0)
O(cgts,    T(s, s, E, E, E, s, s, E, E, E), F(1,0,0,0,0,0,0,0,0,0)) X(0,1,0) V(0)
O(cles,    T(s, s, E, E, E, s, s, E, E, E), F(1,0,0,0,0,0,0,0,0,0)) X(0,1,0) V(0)
O(clts,    T(s, s, E, E, E, s, s, E, E, E), F(1,0,0,0,0,0,0,0,0,0)) X(0,1,0) V(0)
O(cnes,    T(s, s, E, E, E, s, s, E, E, E), F(1,0,0,1,0,0,0,0,0,0)) X(0,1,0) V(0)
O(cos,     T(s, s, E, E, E, s, s, E, E, E), F(1,0,0,1,0,0,0,0,0,0)) X(0,1,0) V(0)
O(cuos,    T(s, s, E, E, E, s, s, E, E, E), F(1,0,0,1,0,0,0,0,0,0)) X(0,1,0) V(0)

O(ceqd,    T(d, d, E, E, E, d, d, E, E, E), F(1,0,0,1,0,0,0,0,0,0)) X(0,1,0) V(0)
O(cged,    T(d, d, E, E, E, d, d, E, E, E), F(1,0,0,0,0,0,0,0,0,0)) X(0,1,0) V(0)
O(cgtd,    T(d, d, E, E, E, d, d, E, E, E), F(1,0,0,0,0,0,0,0,0,0)) X(0,1,0) V(0)
O(cled,    T(d, d, E, E, E, d, d, E, E, E), F(1,0,0,0,0,0,0,0,0,0)) X(0,1,0) V(0)
O(cltd,    T(d, d, E, E, E, d, d, E, E, E), F(1,0,0,0,0,0,0,0,0,0)) X(0,1,0) V(0)
O(cned,    T(d, d, E, E, E, d, d, E, E, E), F(1,0,0,1,0,0,0,0,0,0)) X(0,1,0) V(0)
O(cod,     T(d, d, E, E, E, d, d, E, E, E), F(1,0,0,1,0,0,0,0,0,0)) X(0,1,0) V(0)
O(cuod,    T(d, d, E, E, E, d, d, E, E, E), F(1,0,0,1,0,0,0,0,0,0)) X(0,1,0) V(0)

/* Memory */
O(storeb,  T(w, E, E, E, E, m, E, E, E, E), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,1) V(0)
O(storeh,  T(w, E, E, E, E, m, E, E, E, E), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,1) V(0)
O(storew,  T(w, E, E, E, E, m, E, E, E, E), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,1) V(0)
O(storel,  T(l, E, E, E, E, m, E, E, E, E), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,1) V(0)
O(stores,  T(s, E, E, E, E, m, E, E, E, E), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,1) V(0)
O(stored,  T(d, E, E, E, E, m, E, E, E, E), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,1) V(0)
O(storee,  T(e, E, E, E, E, m, E, E, E, E), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,1) V(0)

O(loadsb,  T(m, m, E, E, E, x, x, E, E, E), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,1) V(0)
O(loadub,  T(m, m, E, E, E, x, x, E, E, E), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,1) V(0)
O(loadsh,  T(m, m, E, E, E, x, x, E, E, E), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,1) V(0)
O(loaduh,  T(m, m, E, E, E, x, x, E, E, E), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,1) V(0)
O(loadsw,  T(m, m, E, E, E, x, x, E, E, E), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,1) V(0)
O(loaduw,  T(m, m, E, E, E, x, x, E, E, E), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,1) V(0)
O(load,    T(m, m, m, m, m, x, x, x, x, x), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,1) V(0)

/* Extensions and Truncations */
O(extsb,   T(w, w, E, E, E, x, x, E, E, E), F(1,0,0,0,0,0,0,0,0,0)) X(0,0,1) V(0)
O(extub,   T(w, w, E, E, E, x, x, E, E, E), F(1,0,0,0,0,0,0,0,0,0)) X(0,0,1) V(0)
O(extsh,   T(w, w, E, E, E, x, x, E, E, E), F(1,0,0,0,0,0,0,0,0,0)) X(0,0,1) V(0)
O(extuh,   T(w, w, E, E, E, x, x, E, E, E), F(1,0,0,0,0,0,0,0,0,0)) X(0,0,1) V(0)
O(extsw,   T(E, w, E, E, E, E, x, E, E, E), F(1,0,0,0,0,0,0,0,0,0)) X(0,0,1) V(0)
O(extuw,   T(E, w, E, E, E, E, x, E, E, E), F(1,0,0,0,0,0,0,0,0,0)) X(0,0,1) V(0)

O(exts,    T(E, E, E, s, E, E, E, E, x, E), F(1,0,0,0,0,0,0,0,0,0)) X(0,0,1) V(0)
O(truncd,  T(E, E, d, E, E, E, E, x, E, E), F(1,0,0,0,0,0,0,0,0,0)) X(0,0,1) V(0)
O(stosi,   T(s, s, E, E, E, x, x, E, E, E), F(1,0,0,0,0,0,0,0,0,0)) X(0,0,1) V(0)
O(stoui,   T(s, s, E, E, E, x, x, E, E, E), F(1,0,0,0,0,0,0,0,0,0)) X(0,0,1) V(0)
O(dtosi,   T(d, d, E, E, E, x, x, E, E, E), F(1,0,0,0,0,0,0,0,0,0)) X(0,0,1) V(0)
O(dtoui,   T(d, d, E, E, E, x, x, E, E, E), F(1,0,0,0,0,0,0,0,0,0)) X(0,0,1) V(0)
O(swtof,   T(E, E, w, w, E, E, E, x, x, E), F(1,0,0,0,0,0,0,0,0,0)) X(0,0,1) V(0)
O(uwtof,   T(E, E, w, w, E, E, E, x, x, E), F(1,0,0,0,0,0,0,0,0,0)) X(0,0,1) V(0)
O(sltof,   T(E, E, l, l, E, E, E, x, x, E), F(1,0,0,0,0,0,0,0,0,0)) X(0,0,1) V(0)
O(ultof,   T(E, E, l, l, E, E, E, x, x, E), F(1,0,0,0,0,0,0,0,0,0)) X(0,0,1) V(0)
O(cast,    T(s, d, w, l, E, x, x, x, x, E), F(1,0,0,0,0,0,0,0,0,0)) X(0,0,1) V(0)

/* Stack Allocation */
O(alloc4,  T(E, l, E, E, E, E, x, E, E, E), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,0) V(0)
O(alloc8,  T(E, l, E, E, E, E, x, E, E, E), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,0) V(0)
O(alloc16, T(E, l, E, E, E, E, x, E, E, E), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,0) V(0)

/* Variadic Function Helpers */
O(vaarg,   T(m, m, m, m, m, x, x, x, x, x), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,0) V(0)
O(vastart, T(m, E, E, E, E, x, E, E, E, E), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,0) V(0)

O(copy,    T(w, l, s, d, e, x, x, x, x, x), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,1) V(0)

/* Debug */
O(dbgloc,  T(w, E, E, E, E, w, E, E, E, E), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,1) V(0)

/****************************************/
/* INTERNAL OPERATIONS (keep nop first) */
/****************************************/

/* Miscellaneous and Architecture-Specific Operations */
O(nop,     T(x, x, x, x, E, x, x, x, x, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,1) V(0)
O(addr,    T(m, m, E, E, E, x, x, E, E, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,1) V(0)
O(fld,     T(m, m, m, m, m, x, x, x, x, x), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,1) V(0)
O(fstp,    T(m, m, m, m, m, x, x, x, x, x), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,1) V(0)
O(blit0,   T(m, E, E, E, E, m, E, E, E, E), F(0,0,0,0,0,0,0,0,0,1)) X(0,1,0) V(0)
O(blit1,   T(w, E, E, E, E, x, E, E, E, E), F(0,0,0,0,0,0,0,0,0,1)) X(0,1,0) V(0)
O(sel0,    T(w, E, E, E, E, x, E, E, E, E), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,0) V(0)
O(sel1,    T(w, l, E, E, E, w, l, E, E, E), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,0) V(0)
O(swap,    T(w, l, s, d, E, w, l, s, d, E), F(0,0,0,0,0,0,0,0,0,0)) X(1,0,0) V(0)
O(sign,    T(w, l, E, E, E, x, x, E, E, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,0) V(0)
O(salloc,  T(E, l, E, E, E, E, x, E, E, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,0) V(0)
O(xidiv,   T(w, l, E, E, E, x, x, E, E, E), F(0,0,0,0,0,0,0,0,0,0)) X(1,0,0) V(0)
O(xdiv,    T(w, l, E, E, E, x, x, E, E, E), F(0,0,0,0,0,0,0,0,0,0)) X(1,0,0) V(0)
O(xcmp,    T(w, l, s, d, E, w, l, s, d, E), F(0,0,0,0,0,0,0,0,0,0)) X(1,1,0) V(0)
O(xtest,   T(w, l, E, E, E, w, l, E, E, E), F(0,0,0,0,0,0,0,0,0,0)) X(1,1,0) V(0)
O(acmp,    T(w, l, E, E, E, w, l, E, E, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,0) V(0)
O(acmn,    T(w, l, E, E, E, w, l, E, E, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,0) V(0)
O(afcmp,   T(E, E, s, d, E, E, E, s, d, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,0) V(0)
O(reqz,    T(w, l, E, E, E, x, x, E, E, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,0) V(0)
O(rnez,    T(w, l, E, E, E, x, x, E, E, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,0) V(0)

/* Arguments, Parameters, and Calls */
O(par,     T(x, x, x, x, x, x, x, x, x, x), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,0) V(0)
O(parsb,   T(x, x, x, x, E, x, x, x, x, E), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,0) V(0)
O(parub,   T(x, x, x, x, E, x, x, x, x, E), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,0) V(0)
O(parsh,   T(x, x, x, x, E, x, x, x, x, E), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,0) V(0)
O(paruh,   T(x, x, x, x, E, x, x, x, x, E), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,0) V(0)
O(parc,    T(E, x, E, E, E, E, x, E, E, E), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,0) V(0)
O(pare,    T(E, x, E, E, E, E, x, E, E, E), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,0) V(0)
O(arg,     T(w, l, s, d, e, x, x, x, x, x), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,0) V(0)
O(argsb,   T(w, E, E, E, E, x, x, x, x, E), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,0) V(0)
O(argub,   T(w, E, E, E, E, x, x, x, x, E), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,0) V(0)
O(argsh,   T(w, E, E, E, E, x, x, x, x, E), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,0) V(0)
O(arguh,   T(w, E, E, E, E, x, x, x, x, E), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,0) V(0)
O(argc,    T(E, x, E, E, E, E, l, E, E, E), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,0) V(0)
O(arge,    T(E, l, E, E, E, E, x, E, E, E), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,0) V(0)
O(argv,    T(x, x, x, x, E, x, x, x, x, E), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,0) V(0)
O(call,    T(m, m, m, m, m, x, x, x, x, x), F(0,0,0,0,0,0,0,0,0,1)) X(0,0,0) V(0)

/* Flags Setting */
O(flagieq,  T(x, x, E, E, E, x, x, E, E, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,1) V(0)
O(flagine,  T(x, x, E, E, E, x, x, E, E, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,1) V(0)
O(flagisge, T(x, x, E, E, E, x, x, E, E, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,1) V(0)
O(flagisgt, T(x, x, E, E, E, x, x, E, E, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,1) V(0)
O(flagisle, T(x, x, E, E, E, x, x, E, E, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,1) V(0)
O(flagislt, T(x, x, E, E, E, x, x, E, E, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,1) V(0)
O(flagiuge, T(x, x, E, E, E, x, x, E, E, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,1) V(0)
O(flagiugt, T(x, x, E, E, E, x, x, E, E, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,1) V(0)
O(flagiule, T(x, x, E, E, E, x, x, E, E, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,1) V(0)
O(flagiult, T(x, x, E, E, E, x, x, E, E, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,1) V(0)
O(flagfeq,  T(x, x, E, E, E, x, x, E, E, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,1) V(0)
O(flagfge,  T(x, x, E, E, E, x, x, E, E, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,1) V(0)
O(flagfgt,  T(x, x, E, E, E, x, x, E, E, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,1) V(0)
O(flagfle,  T(x, x, E, E, E, x, x, E, E, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,1) V(0)
O(flagflt,  T(x, x, E, E, E, x, x, E, E, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,1) V(0)
O(flagfne,  T(x, x, E, E, E, x, x, E, E, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,1) V(0)
O(flagfo,   T(x, x, E, E, E, x, x, E, E, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,1) V(0)
O(flagfuo,  T(x, x, E, E, E, x, x, E, E, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,1) V(0)

/* Backend Flag Select (Condition Move) */
O(xselieq,  T(w, l, E, E, E, w, l, E, E, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,0) V(0)
O(xseline,  T(w, l, E, E, E, w, l, E, E, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,0) V(0)
O(xselisge, T(w, l, E, E, E, w, l, E, E, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,0) V(0)
O(xselisgt, T(w, l, E, E, E, w, l, E, E, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,0) V(0)
O(xselisle, T(w, l, E, E, E, w, l, E, E, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,0) V(0)
O(xselislt, T(w, l, E, E, E, w, l, E, E, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,0) V(0)
O(xseliuge, T(w, l, E, E, E, w, l, E, E, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,0) V(0)
O(xseliugt, T(w, l, E, E, E, w, l, E, E, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,0) V(0)
O(xseliule, T(w, l, E, E, E, w, l, E, E, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,0) V(0)
O(xseliult, T(w, l, E, E, E, w, l, E, E, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,0) V(0)
O(xselfeq,  T(E, E, s, d, E, E, E, s, d, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,0) V(0)
O(xselfge,  T(E, E, s, d, E, E, E, s, d, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,0) V(0)
O(xselfgt,  T(E, E, s, d, E, E, E, s, d, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,0) V(0)
O(xselfle,  T(E, E, s, d, E, E, E, s, d, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,0) V(0)
O(xselflt,  T(E, E, s, d, E, E, E, s, d, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,0) V(0)
O(xselfne,  T(E, E, s, d, E, E, E, s, d, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,0) V(0)
O(xselfo,   T(E, E, s, d, E, E, E, s, d, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,0) V(0)
O(xselfuo,  T(E, E, s, d, E, E, E, s, d, E), F(0,0,0,0,0,0,0,0,0,0)) X(0,0,0) V(0)

#undef T
#undef X
#undef V
#undef O

/*
| column -t -o ' '
*/
