#include "../include/frame.h"

const int F_K = 6;         
const int F_WORD_SIZE = 4; 
#define F_MAX_REGS 32 

struct F_frame_ {
    Temp_label name;       
    F_accessList formals;  
    unsigned int locals;   
};

struct F_access_ {
    enum {
        inFrame, inReg
    } kind;
    union {
        int offset;    
        Temp_temp reg; 
    } u;
};

static Temp_temp regs[F_MAX_REGS]; 

static F_access     InFrame(int offset);
static F_access     InReg(Temp_temp reg);
static F_accessList F_AccessList(F_access head, F_accessList tail);

static void F_regs_init();
static Temp_tempList F_spec_regs(int r[], int n);


F_frame F_newFrame(Temp_label name, U_boolList formals) {
    F_frame f = checked_malloc(sizeof(*f));
    int offset = -F_WORD_SIZE; 

    f->name = name;
    f->formals = F_AccessList(InFrame(offset), NULL); 
    f->locals = 1;

    
    U_boolList b = NULL;
    F_accessList new_node = NULL, node = f->formals;
    for(b = formals->tail; b; b = b->tail) {
        offset -= F_WORD_SIZE;
        new_node = F_AccessList(InFrame(offset), NULL);
        node->tail = new_node;
        node = node->tail;
        f->locals++;
    }
    return f;
}

Temp_label F_name(F_frame f) {
    return f->name;
}

F_accessList F_formals(F_frame f) {
    return f->formals;
}

F_access F_allocLocal(F_frame f, bool escape) {
    f->locals++;
    return escape ? InFrame(-(f->locals * F_WORD_SIZE)) : InReg(Temp_newtemp());
}

T_exp F_Exp(F_access acc, T_exp framePtr) {
    if(acc->kind == inFrame) {
        return T_Mem(T_Binop(T_plus, framePtr, T_Const(acc->u.offset)));
    } else {
        return T_Temp(acc->u.reg);
    }
}

T_exp F_externalCall(string s, T_expList args) {
    return T_Call(T_Name(Temp_namedlabel(s)), args);
}


F_frag F_StringFrag(Temp_label label, string str) {
    F_frag f = checked_malloc(sizeof(*f));
    f->kind = F_stringFrag;
    f->u.stringg.label = label;
    f->u.stringg.str = str;
    return f;
}

F_frag F_ProcFrag(T_stm body, F_frame frame) {
    F_frag f = checked_malloc(sizeof(*f));
    f->kind = F_procFrag;
    f->u.proc.body = body;
    f->u.proc.frame = frame;
    return f;
}

F_fragList F_FragList(F_frag head, F_fragList tail) {
    F_fragList fl = checked_malloc(sizeof(*fl));
    fl->head = head;
    fl->tail = tail;
    return fl;
}

static F_accessList F_AccessList(F_access head, F_accessList tail) {
    F_accessList al = checked_malloc(sizeof(*al));
    al->head = head;
    al->tail = tail;
    return al;
}


static F_access InFrame(int offset) {
    F_access a = checked_malloc(sizeof(*a));
    a->kind = inFrame;
    a->u.offset = offset;
    return a;
}


static F_access InReg(Temp_temp reg) {
    F_access a = checked_malloc(sizeof(*a));
    a->kind = inReg;
    a->u.reg = reg;
    return a;
}

static void F_regs_init() {
    if(regs[0] == NULL) {
        for(int i = 0; i < 32; i++) {
            regs[i] = Temp_newtemp();
        }
    }
}

static Temp_tempList F_spec_regs(int r[], int n) {
    assert(n < F_MAX_REGS);
    Temp_tempList list = NULL, last = NULL;
    for(int i = 0; i < n; i++) {
        if(i == 0) {
            list = Temp_TempList(regs[r[i]], NULL);
            last = list;
        } else {
            last->tail = Temp_TempList(regs[r[i]], NULL);
            last = last->tail;
        }
    }
    return list;
}

Temp_map F_tempMap() {
    static Temp_map F_tempMap = NULL; 

    if(regs[0] == NULL) {
        F_regs_init();
    }

    if(F_tempMap == NULL) {
        F_tempMap = Temp_empty();
        Temp_enter(F_tempMap, regs[0], "$zero");
        Temp_enter(F_tempMap, regs[1], "$at");
        Temp_enter(F_tempMap, regs[2], "$v0");
        Temp_enter(F_tempMap, regs[3], "$v1");
        Temp_enter(F_tempMap, regs[4], "$a0");
        Temp_enter(F_tempMap, regs[5], "$a1");
        Temp_enter(F_tempMap, regs[6], "$a2");
        Temp_enter(F_tempMap, regs[7], "$a3");
        Temp_enter(F_tempMap, regs[8], "$t0");
        Temp_enter(F_tempMap, regs[9], "$t1");
        Temp_enter(F_tempMap, regs[10], "$t2");
        Temp_enter(F_tempMap, regs[11], "$t3");
        Temp_enter(F_tempMap, regs[12], "$t4");
        Temp_enter(F_tempMap, regs[13], "$t5");
        Temp_enter(F_tempMap, regs[14], "$t6");
        Temp_enter(F_tempMap, regs[15], "$t7");
        Temp_enter(F_tempMap, regs[16], "$s0");
        Temp_enter(F_tempMap, regs[17], "$s1");
        Temp_enter(F_tempMap, regs[18], "$s2");
        Temp_enter(F_tempMap, regs[19], "$s3");
        Temp_enter(F_tempMap, regs[20], "$s4");
        Temp_enter(F_tempMap, regs[21], "$s5");
        Temp_enter(F_tempMap, regs[22], "$s6");
        Temp_enter(F_tempMap, regs[23], "$s7");
        Temp_enter(F_tempMap, regs[24], "$t8");
        Temp_enter(F_tempMap, regs[25], "$t9");
        Temp_enter(F_tempMap, regs[26], "$k0");
        Temp_enter(F_tempMap, regs[27], "$k1");
        Temp_enter(F_tempMap, regs[28], "$gp");
        Temp_enter(F_tempMap, regs[29], "$sp");
        Temp_enter(F_tempMap, regs[30], "$fp");
        Temp_enter(F_tempMap, regs[31], "$ra");
        F_tempMap = Temp_layerMap(F_tempMap, Temp_name());
    }
    return F_tempMap;
}


Temp_temp F_ZERO() {
    if(regs[0] == NULL) {
        F_regs_init();
    }
    return regs[0];
}

Temp_temp F_RV() {
    if(regs[2] == NULL) {
        F_regs_init();
    }
    return regs[2];
}

Temp_temp F_SP() {
    if(regs[29] == NULL) {
        F_regs_init();
    }
    return regs[29];
}

Temp_temp F_FP() {
    if(regs[30] == NULL) {
        F_regs_init();
    }
    return regs[30];
}

Temp_temp F_RA() {
    if(regs[31] == NULL) {
        F_regs_init();
    }
    return regs[31];
}


Temp_tempList F_CalleeSaves() {
    static Temp_tempList list = NULL;
    if(list == NULL) {
        int index[] = {16, 17, 18, 19, 20, 21, 22, 23};
        list = F_spec_regs(index, sizeof(index) / sizeof(index[0]));
    }
    return list;
}


Temp_tempList F_CallerSaves() {
    static Temp_tempList list = NULL;
    if(list == NULL) {
        int index[] = {8, 9, 10, 11, 12, 13, 14, 15, 24, 25};
        list = F_spec_regs(index, sizeof(index) / sizeof(index[0]));
    }
    return list;
}


Temp_tempList F_ArgsRegs() {
    static Temp_tempList list = NULL;
    if(list == NULL) {
        int index[] = {4, 5, 6, 7};
        list = F_spec_regs(index, sizeof(index) / sizeof(index[0]));
    }
    return list;
}


Temp_tempList F_CallSaves() {
    static Temp_tempList list = NULL;
    if(list == NULL) {
        int index[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 24, 25, 31};
        list = F_spec_regs(index, sizeof(index) / sizeof(index[0]));
    }
    return list;
}

T_stm F_procEntryExit1(F_frame frame, T_stm stm) {
    return stm;
}

AS_instrList F_procEntryExit2(AS_instrList body) {
    static Temp_tempList returnSink = NULL;
    if(!returnSink) returnSink = Temp_TempList(F_ZERO(), 
                                    Temp_TempList(F_RA(), 
                                    Temp_TempList(F_SP(), 
                                    F_CalleeSaves())));
    return AS_splice(body, AS_InstrList(AS_Oper("", NULL, returnSink, NULL), NULL));
}

AS_proc F_procEntryExit3(F_frame frame, AS_instrList body) {
    char buf[100];
    sprintf(buf, "PROCEDURE %s\n", S_name(frame->name));
    return AS_Proc(String(buf), body, "END\n");
}


