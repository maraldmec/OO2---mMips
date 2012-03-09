
#include <systemc.h>
#include "mips_trace.h"

// prefix for all names that are traced
char trace_mips_name_buffer[2048];
int trace_mips_prefix_len = 0;


vector< int > name_segments;
// add new component of the prefix
void push_prefix( const char *prefix ){
  if( name_segments.empty() ){
    trace_mips_name_buffer[0] = 0;
    trace_mips_prefix_len = 0;
  }
  
  strcat(trace_mips_name_buffer, prefix);
  trace_mips_prefix_len = strlen(trace_mips_name_buffer);
  name_segments.push_back( strlen(prefix) );
}
// remove last component of the prefix
void pop_prefix(){
  if( name_segments.empty() ) return;
  int len = *name_segments.rbegin();

  trace_mips_prefix_len -= len;
  trace_mips_name_buffer[trace_mips_prefix_len] = 0;
  name_segments.pop_back();
}

// macro to trace the given signal with name = prefix+name
#define _do_trace(tf, sig, name) \
  strcat(trace_mips_name_buffer,name); \
  sc_trace(tf, sig, trace_mips_name_buffer); \
  trace_mips_name_buffer[trace_mips_prefix_len] = '\0'; 


////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void trace_mips( sc_trace_file *tf, mMIPS *mips, const char *prefix )
{
  push_prefix(prefix);

  _do_trace(tf, mips->rom_dout, "rom_dout");
  _do_trace(tf, mips->rom_wait, "rom_wait");
  _do_trace(tf, mips->rom_addr, "rom_addr");
  _do_trace(tf, mips->rom_r, "rom_r");

  _do_trace(tf, mips->ram_dout, "ram_dout");
  _do_trace(tf, mips->ram_wait, "ram_wait");
  _do_trace(tf, mips->ram_din, "ram_din");
  _do_trace(tf, mips->ram_addr, "ram_addr");
  _do_trace(tf, mips->ram_r, "ram_r");
  _do_trace(tf, mips->ram_w, "ram_w");


  _do_trace(tf, mips->clk, "clk");
  _do_trace(tf, mips->bus_add1, "bus_add1");
  _do_trace(tf, mips->bus_add2, "bus_add2");
  _do_trace(tf, mips->bus_aluctrl, "bus_aluctrl");
  _do_trace(tf, mips->bus_alu_result, "bus_alu_result");
  _do_trace(tf, mips->bus_alu_result_2, "bus_alu_result_2");
  _do_trace(tf, mips->bus_alu_zero, "bus_alu_zero");
  _do_trace(tf, mips->bus_branch_ctrl, "bus_branch_ctrl");
  _do_trace(tf, mips->bus_ctrl2hazard_aluop, "bus_ctrl2hazard_aluop");
  _do_trace(tf, mips->bus_ctrl2hazard_alusrc, "bus_ctrl2hazard_alusrc");
  _do_trace(tf, mips->bus_ctrl2hazard_branch, "bus_ctrl2hazard_branch");
  _do_trace(tf, mips->bus_ctrl2hazard_memread, "bus_ctrl2hazard_memread");
  _do_trace(tf, mips->bus_ctrl2hazard_memtoreg, "bus_ctrl2hazard_memtoreg");
  _do_trace(tf, mips->bus_ctrl2hazard_memwrite, "bus_ctrl2hazard_memwrite");
  _do_trace(tf, mips->bus_ctrl2hazard_regdst, "bus_ctrl2hazard_regdst");
  _do_trace(tf, mips->bus_ctrl2hazard_regvalue, "bus_ctrl2hazard_regvalue");
  _do_trace(tf, mips->bus_ctrl2hazard_regwrite, "bus_ctrl2hazard_regwrite");
  _do_trace(tf, mips->bus_ctrl2hazard_target, "bus_ctrl2hazard_target");
  _do_trace(tf, mips->bus_ctrl2hazard_hilo_write, "bus_ctrl2hazard_hilo_write");
  _do_trace(tf, mips->bus_ctrl2hazard_hiloalu_sel, "bus_ctrl2hazard_hiloalu_sel");
  _do_trace(tf, mips->bus_ctrl_aluop, "bus_ctrl_aluop");
  _do_trace(tf, mips->bus_ctrl_alusrc, "bus_ctrl_alusrc");
  _do_trace(tf, mips->bus_ctrl_branch, "bus_ctrl_branch");
  _do_trace(tf, mips->bus_ctrl_c1, "bus_ctrl_c1");
  _do_trace(tf, mips->bus_ctrl_c31, "bus_ctrl_c31");
  _do_trace(tf, mips->bus_ctrl_c4, "bus_ctrl_c4");
  _do_trace(tf, mips->bus_ctrl_memread, "bus_ctrl_memread");
  _do_trace(tf, mips->bus_ctrl_memtoreg, "bus_ctrl_memtoreg");
  _do_trace(tf, mips->bus_ctrl_memwrite, "bus_ctrl_memwrite");
  _do_trace(tf, mips->bus_ctrl_regdst, "bus_ctrl_regdst");
  _do_trace(tf, mips->bus_ctrl_regvalue, "bus_ctrl_regvalue");
  _do_trace(tf, mips->bus_ctrl_regwrite, "bus_ctrl_regwrite");
  _do_trace(tf, mips->bus_ctrl_target, "bus_ctrl_target");
  _do_trace(tf, mips->bus_ctrl_enable, "bus_ctrl_enable");
  _do_trace(tf, mips->bus_ctrl_signextend, "bus_ctrl_signextend");
  _do_trace(tf, mips->bus_ctrl_hilo_write, "bus_ctrl_hilo_write");
  _do_trace(tf, mips->bus_ctrl_hiloalu_sel, "bus_ctrl_hiloalu_seld");
  _do_trace(tf, mips->bus_decoder_instr_10_6, "bus_decoder_instr_10_6");
  _do_trace(tf, mips->bus_decoder_instr_15_0, "bus_decoder_instr_15_0");
  _do_trace(tf, mips->bus_decoder_instr_15_11, "bus_decoder_instr_15_11");
  _do_trace(tf, mips->bus_decoder_instr_20_16, "bus_decoder_instr_20_16");
  _do_trace(tf, mips->bus_decoder_instr_25_0, "bus_decoder_instr_25_0");
  _do_trace(tf, mips->bus_decoder_instr_31_26, "bus_decoder_instr_31_26");
  _do_trace(tf, mips->bus_decoder_instr_5_0, "bus_decoder_instr_5_0");
  _do_trace(tf, mips->bus_dmem_1, "bus_dmem_1");
  _do_trace(tf, mips->bus_ex_ctrl_wb_memtoreg, "bus_ex_ctrl_wb_memtoreg");
  _do_trace(tf, mips->bus_ex_ctrl_wb_regwrite, "bus_ex_ctrl_wb_regwrite");
  _do_trace(tf, mips->bus_ex_regdst_addr, "bus_ex_regdst_addr");
  _do_trace(tf, mips->bus_ex_alu_result, "bus_ex_alu_result");
  _do_trace(tf, mips->bus_hazard_hazard, "bus_hazard_hazard");
  _do_trace(tf, mips->bus_hazard_ifidwrite, "bus_hazard_ifidwrite");
  _do_trace(tf, mips->bus_hazard_pcwrite, "bus_hazard_pcwrite");
  _do_trace(tf, mips->bus_id_ctrl_ex_aluop, "bus_id_ctrl_ex_aluop");
  _do_trace(tf, mips->bus_id_ctrl_ex_alusrc, "bus_id_ctrl_ex_alusrc");
  _do_trace(tf, mips->bus_id_ctrl_ex_hilo_write, "bus_id_ctrl_ex_hilo_write");
  _do_trace(tf, mips->bus_id_ctrl_ex_hiloalu_sel, "bus_id_ctrl_ex_hiloalu_sel");
  _do_trace(tf, mips->bus_id_ctrl_ex_regdst, "bus_id_ctrl_ex_regdst");
  _do_trace(tf, mips->bus_id_ctrl_ex_regvalue, "bus_id_ctrl_ex_regvalue");
  _do_trace(tf, mips->bus_id_ctrl_ex_target, "bus_id_ctrl_ex_target");
  _do_trace(tf, mips->bus_id_ctrl_mem_branch, "bus_id_ctrl_mem_branch");
  _do_trace(tf, mips->bus_id_ctrl_mem_memread, "bus_id_ctrl_mem_memread");
  _do_trace(tf, mips->bus_id_ctrl_mem_memwrite, "bus_id_ctrl_mem_memwrite");
  _do_trace(tf, mips->bus_id_ctrl_wb_memtoreg, "bus_id_ctrl_wb_memtoreg");
  _do_trace(tf, mips->bus_id_ctrl_wb_regwrite, "bus_id_ctrl_wb_regwrite");
  _do_trace(tf, mips->bus_id_data_reg1, "bus_id_data_reg1");
  _do_trace(tf, mips->bus_id_data_reg2, "bus_id_data_reg2");
  _do_trace(tf, mips->bus_id_instr_15_11, "bus_id_instr_15_11");
  _do_trace(tf, mips->bus_id_instr_20_16, "bus_id_instr_20_16");
  _do_trace(tf, mips->bus_id_instr_25_0, "bus_id_instr_25_0");
  _do_trace(tf, mips->bus_id_instr_5_0, "bus_id_instr_5_0");
  _do_trace(tf, mips->bus_id_pc, "bus_id_pc");
  _do_trace(tf, mips->bus_id_immediate, "bus_id_immediate");
  _do_trace(tf, mips->bus_if_instr, "bus_if_instr");
  _do_trace(tf, mips->bus_if_pc, "bus_if_pc");
  _do_trace(tf, mips->bus_mem_alu_result, "bus_mem_alu_result");
  _do_trace(tf, mips->bus_mem_ctrl_wb_memtoreg, "bus_mem_ctrl_wb_memtoreg");
  _do_trace(tf, mips->bus_mem_ctrl_wb_regwrite, "bus_mem_ctrl_wb_regwrite");
  _do_trace(tf, mips->bus_mem_dmem_data, "bus_mem_dmem_data");
  _do_trace(tf, mips->bus_mem_regdst_addr, "bus_mem_regdst_addr");
  _do_trace(tf, mips->bus_mux2, "bus_mux2");
  _do_trace(tf, mips->bus_mux3, "bus_mux3");
  _do_trace(tf, mips->bus_mux4, "bus_mux4");
  _do_trace(tf, mips->bus_mux5, "bus_mux5");
  _do_trace(tf, mips->bus_mux6, "bus_mux6");
  _do_trace(tf, mips->bus_mux6, "bus_mux8");
  _do_trace(tf, mips->bus_pc, "bus_pc");
  _do_trace(tf, mips->bus_registers_1, "bus_registers_1");
  _do_trace(tf, mips->bus_registers_2, "bus_registers_2");
  _do_trace(tf, mips->bus_register_hi, "bus_register_hi");
  _do_trace(tf, mips->bus_register_lo, "bus_register_lo");
  _do_trace(tf, mips->bus_shiftleft, "bus_shiftleft");
  _do_trace(tf, mips->bus_shiftleft_jmp, "bus_shiftleft_jmp");
  _do_trace(tf, mips->bus_imm2word, "bus_imm2word");
  _do_trace(tf, mips->bus_signextendbyte, "bus_signextendbyte");
  _do_trace(tf, mips->bus_decoder_nb_instr_20_16, "bus_decoder_nb_instr_20_16");
  _do_trace(tf, mips->bus_decoder_nb_instr_25_21, "bus_decoder_nb_instr_25_21");
  _do_trace(tf, mips->bus_dmem_wait, "bus_dmem_wait");
  _do_trace(tf, mips->bus_pipe_en, "bus_pipe_en");
  _do_trace(tf, mips->memdev->dev_buffer, "memdev.dev_buffer");
  _do_trace(tf, mips->memdev->bufw, "memdev.bufw");
  _do_trace(tf, mips->memdev->sending, "memdev.sending");

  char stbuf[32];
  for (int i = 0; i < REGSIZE; i++){
    sprintf(stbuf, "registers.reg(%d_1)", i);
    _do_trace(tf, mips->registers->regs1->bram->memory[i], stbuf);
    sprintf(stbuf, "registers.reg(%d_2)", i);
    _do_trace(tf, mips->registers->regs2->bram->memory[i], stbuf);
  }
  
  pop_prefix();

}
