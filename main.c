#include "absyn.h"
#include "assem.h"
#include "canon.h"
#include "codegen.h"
#include "errormsg.h"
#include "escape.h"
#include "frame.h"
#include "frontend/parse.h"
#include "frontend/semantic.h"
#include "prabsyn.h"
#include "printtree.h"
#include "symbol.h"
#include "temp.h"
#include "tree.h"
#include "util/util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int print_absyn_tree = 0, print_ir_tree = 0, print_before_reg_alloc = 0,
    print_after_reg_alloc = 0, print_canon = 0;
static void do_proc(FILE *out, F_frame frame, T_stm body) {
  AS_instrList instr_l = NULL;
  T_stmList stm_l = NULL;

  /* dumping map */
  //  printf("Mapping\n");
  // Temp_dumpMap(out, F_tempMap());
  // printf("\n---------\n");

  stm_l = C_linearize(body);
  stm_l = C_traceSchedule(C_basicBlocks(stm_l));
  if (print_canon) {
    /* canon tree */
    printf("Canon tree\n");
    printStmList(out, stm_l);
    printf("\n---------\n");
    print_canon = 0;
  }

  /* assembly */
  instr_l = F_codegen(frame, stm_l);
  if (print_before_reg_alloc) {
    fprintf(out, "========== ASM  ==========\n");
    AS_printInstrList(out, instr_l, F_tempMap());
    fprintf(out, "\n========== End ==========\n\n");
    print_before_reg_alloc = 0;
  }
}

void help_menu(const char *prog_name) {
  printf("Usage: %s [flags]\n", prog_name);
  printf("    -h               prints this usage guide\n");
  printf("    -p               sets the input file path\n");
  printf("    -a               prints the abstract syntax tree\n");
  printf("    -i               prints the intermediate representation\n");
  printf(
      "    -c               prints the canonical intermediate representation "
      "tree\n");
  printf("    -s               prints the generated assembly code before regs "
         "allocation\n");
  printf("    -S               prints the generated assembly code after regs "
         "allocation\n");
  printf(
      "    -o               sets the name of the output binary               "
      "       \n");
}

int main(int argc, char *argv[]) {
  int ch;
  char *input_file, *output_file;
  while ((ch = getopt(argc, argv, "aho:p:isSc")) != -1) {
    switch (ch) {
    case 'p':
      input_file = (char *)malloc(strlen(optarg));
      strcpy(input_file, optarg);
      break;

    case 'a':
      print_absyn_tree = 1;
      break;

    case 'o':
      output_file = (char *)malloc(strlen(optarg));
      strcpy(output_file, optarg);
      break;

    case 'i':
      print_ir_tree = 1;
      break;

    case 'c':
      print_canon = 1;
      break;

    case 's':
      print_before_reg_alloc = 1;
      break;

    case 'S':
      print_after_reg_alloc = 1;
      break;

    case 'h':
      input_file ? help_menu(input_file) : help_menu("./tigerc");
      exit(EXIT_SUCCESS);
      break;

    default:
      help_menu(input_file);
      exit(EXIT_FAILURE);
      break;
    }
  }

  A_exp absyn_root = parse(input_file);
  if (absyn_root == NULL) {
    fprintf(stderr, "something wrong with parser\n");
    return 1;
  }

  FILE *out = stdout;
  if (print_absyn_tree) {
    /* Absyn tree */
    fprintf(out, "========== Absyn Tree ==========\n");
    pr_exp(out, absyn_root, 0);
    fprintf(out, "\n========== End ==========\n\n");
  }

  /* Set escape varibles */
  Esc_findEscape(absyn_root);

  /* Semantic and Translate */
  F_fragList frags = SEM_transProg(absyn_root);

  /* proc */
  for (F_fragList f = frags; f; f = f->tail) {
    if (f->head->kind == F_procFrag) {
      do_proc(out, f->head->u.proc.frame, f->head->u.proc.body);
    }
  }

  return 0;
}
